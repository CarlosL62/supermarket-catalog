#include "../../include/structures/BPlusTree.h"

#include <iostream>
#include <fstream>
#include <filesystem>

BPlusTree::BPlusTreeNode::BPlusTreeNode(bool leaf) : isLeaf(leaf), next(nullptr) {}

BPlusTree::BPlusTree(int degree) : root(nullptr), minDegree(degree) {}

BPlusTree::~BPlusTree() {
    destroyTree(root);
}

void BPlusTree::destroyTree(BPlusTreeNode* node) {
    if (node == nullptr) {
        return;
    }

    for (BPlusTreeNode* child : node->children) {
        destroyTree(child);
    }

    delete node;
}

// Follow internal nodes until reaching the correct leaf
BPlusTree::BPlusTreeNode* BPlusTree::findLeaf(const std::string& category) const {
    if (root == nullptr) {
        return nullptr;
    }

    BPlusTreeNode* current = root;

    while (!current->isLeaf) {
        int i = 0;

        while (i < static_cast<int>(current->keys.size()) && category >= current->keys[i]) {
            i++;
        }

        current = current->children[i];
    }

    return current;
}

// Public search by category (returns all products in that category)
std::vector<Product> BPlusTree::search(const std::string& category) const {
    BPlusTreeNode* leaf = findLeaf(category);

    if (leaf == nullptr) {
        return {};
    }

    for (int i = 0; i < static_cast<int>(leaf->keys.size()); i++) {
        if (leaf->keys[i] == category) {
            return leaf->values[i];
        }
    }

    return {};
}

// Split a full child and promote the separator key
void BPlusTree::splitChild(BPlusTreeNode* parent, int childIndex) {
    BPlusTreeNode* fullChild = parent->children[childIndex];
    BPlusTreeNode* newChild = new BPlusTreeNode(fullChild->isLeaf);

    int middleIndex = minDegree - 1;

    if (fullChild->isLeaf) {
        // In leaves, keep duplicate separator logic and move half the data right
        for (int i = middleIndex; i < static_cast<int>(fullChild->keys.size()); i++) {
            newChild->keys.push_back(fullChild->keys[i]);
            newChild->values.push_back(fullChild->values[i]);
        }

        fullChild->keys.resize(middleIndex);
        fullChild->values.resize(middleIndex);

        newChild->next = fullChild->next;
        fullChild->next = newChild;

        parent->keys.insert(parent->keys.begin() + childIndex, newChild->keys[0]);
        parent->children.insert(parent->children.begin() + childIndex + 1, newChild);
    } else {
        // In internal nodes, middle key goes up and is not duplicated below
        std::string promotedKey = fullChild->keys[middleIndex];

        for (int i = middleIndex + 1; i < static_cast<int>(fullChild->keys.size()); i++) {
            newChild->keys.push_back(fullChild->keys[i]);
        }

        for (int i = middleIndex + 1; i < static_cast<int>(fullChild->children.size()); i++) {
            newChild->children.push_back(fullChild->children[i]);
        }

        fullChild->keys.resize(middleIndex);
        fullChild->children.resize(middleIndex + 1);

        parent->keys.insert(parent->keys.begin() + childIndex, promotedKey);
        parent->children.insert(parent->children.begin() + childIndex + 1, newChild);
    }
}

// Insert into a node that is guaranteed not to be full
void BPlusTree::insertNonFull(BPlusTreeNode* node, const Product& product) {
    int i = static_cast<int>(node->keys.size()) - 1;

    if (node->isLeaf) {
        while (i >= 0 && product.category < node->keys[i]) {
            i--;
        }

        // If category already exists in this leaf, just append the product
        if (i >= 0 && node->keys[i] == product.category) {
            node->values[i].push_back(product);
            return;
        }

        node->keys.insert(node->keys.begin() + i + 1, product.category);
        node->values.insert(node->values.begin() + i + 1, std::vector<Product>{product});
        return;
    }

    while (i >= 0 && product.category < node->keys[i]) {
        i--;
    }

    i++;

    if (static_cast<int>(node->children[i]->keys.size()) == 2 * minDegree - 1) {
        splitChild(node, i);

        if (product.category >= node->keys[i]) {
            i++;
        }
    }

    insertNonFull(node->children[i], product);
}

// Public insert entry point
void BPlusTree::insert(const Product& product) {
    if (root == nullptr) {
        root = new BPlusTreeNode(true);
        root->keys.push_back(product.category);
        root->values.push_back(std::vector<Product>{product});
        return;
    }

    if (static_cast<int>(root->keys.size()) == 2 * minDegree - 1) {
        BPlusTreeNode* newRoot = new BPlusTreeNode(false);
        newRoot->children.push_back(root);

        splitChild(newRoot, 0);

        int i = 0;
        if (product.category >= newRoot->keys[0]) {
            i++;
        }

        insertNonFull(newRoot->children[i], product);
        root = newRoot;
    } else {
        insertNonFull(root, product);
    }
}
// Basic remove: works at leaf level without rebalancing
void BPlusTree::remove(BPlusTreeNode* node, const Product& product) {
    if (node == nullptr) {
        return;
    }

    if (!node->isLeaf) {
        int i = 0;

        while (i < static_cast<int>(node->keys.size()) && product.category >= node->keys[i]) {
            i++;
        }

        remove(node->children[i], product);
        return;
    }

    for (int i = 0; i < static_cast<int>(node->keys.size()); i++) {
        if (node->keys[i] == product.category) {
            std::vector<Product>& categoryProducts = node->values[i];

            for (int j = 0; j < static_cast<int>(categoryProducts.size()); j++) {
                if (categoryProducts[j].barcode == product.barcode) {
                    categoryProducts.erase(categoryProducts.begin() + j);
                    break;
                }
            }

            // If no products remain in this category, remove the category key too
            if (categoryProducts.empty()) {
                node->keys.erase(node->keys.begin() + i);
                node->values.erase(node->values.begin() + i);
            }

            return;
        }
    }
}

// Public remove entry point
void BPlusTree::remove(const Product& product) {
    remove(root, product);
}

// Generate DOT nodes for the current B+ Tree
void BPlusTree::generateDotNodes(std::ofstream& file, BPlusTreeNode* node) const {
    if (node == nullptr) {
        return;
    }

    std::string nodeId = "node" + std::to_string(reinterpret_cast<std::uintptr_t>(node));

    file << "    " << nodeId << " [shape=box, label=\"";

    for (size_t i = 0; i < node->keys.size(); i++) {
        file << node->keys[i];
        if (i + 1 < node->keys.size()) {
            file << " | ";
        }
    }

    if (node->keys.empty()) {
        file << "empty";
    }

    file << "\"];" << std::endl;

    for (BPlusTreeNode* child : node->children) {
        generateDotNodes(file, child);
    }
}

// Generate parent-child edges for the current B+ Tree
void BPlusTree::generateDotEdges(std::ofstream& file, BPlusTreeNode* node) const {
    if (node == nullptr) {
        return;
    }

    std::string parentId = "node" + std::to_string(reinterpret_cast<std::uintptr_t>(node));

    for (BPlusTreeNode* child : node->children) {
        if (child != nullptr) {
            std::string childId = "node" + std::to_string(reinterpret_cast<std::uintptr_t>(child));
            file << "    " << parentId << " -> " << childId << ";" << std::endl;
        }
    }

    // Draw leaf links too, so the B+ part is visible
    if (node->isLeaf && node->next != nullptr) {
        std::string nextId = "node" + std::to_string(reinterpret_cast<std::uintptr_t>(node->next));
        file << "    " << parentId << " -> " << nextId << " [style=dashed, color=blue, constraint=false];" << std::endl;
    }

    for (BPlusTreeNode* child : node->children) {
        generateDotEdges(file, child);
    }
}

// Export the current B+ Tree to DOT and PNG
void BPlusTree::generateDotFile(const std::string& filePath) const {
    std::filesystem::path path(filePath);
    if (!path.parent_path().empty()) {
        std::filesystem::create_directories(path.parent_path());
    }

    std::ofstream file(filePath);

    if (!file.is_open()) {
        std::cout << "Could not create DOT file for B+ Tree." << std::endl;
        return;
    }

    file << "digraph BPlusTree {" << std::endl;
    file << "    rankdir=TB;" << std::endl;
    file << "    node [fontname=\"Arial\"];" << std::endl;

    if (root != nullptr) {
        generateDotNodes(file, root);
        generateDotEdges(file, root);
    }

    file << "}" << std::endl;
    file.close();

    std::string pngPath = filePath.substr(0, filePath.find_last_of('.')) + ".png";
    std::string command = "dot -Tpng \"" + filePath + "\" -o \"" + pngPath + "\"";
    int result = system(command.c_str());

    if (result != 0) {
        std::cout << "Generación fallida del PNG B+ Tree. Asegurese de tener instalado Graphviz" << std::endl;
    } else {
        std::cout << "Generación exitosa del PNG B+ Tree en: " << pngPath << std::endl;
    }
}