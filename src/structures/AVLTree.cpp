#include "../../include/structures/AVLTree.h"

#include <iostream>
#include <filesystem>

AVLTree::AVLTree() : root(nullptr) {}

void AVLTree::destroyTree(AVLNode* node) {
    if (node == nullptr) {
        return;
    }

    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

AVLTree::~AVLTree() {
    destroyTree(root);
}

int AVLTree::getHeight(AVLNode* node) {
    if (node == nullptr) {
        return 0;
    }

    return node->height;
}

int AVLTree::getBalanceFactor(AVLNode *node) {
    if (node == nullptr) {
        return 0;
    }

    return getHeight(node->right)-getHeight(node->left);
}

AVLTree::AVLNode* AVLTree::rotateLeft(AVLNode* node) {
    AVLNode* newRoot = node->right;
    AVLNode* transferredSubtree = newRoot->left;

    newRoot->left = node;
    node->right = transferredSubtree;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

AVLTree::AVLNode* AVLTree::rotateRight(AVLNode* node) {
    AVLNode* newRoot = node->left;
    AVLNode* transferredSubtree = newRoot->right;

    newRoot->right = node;
    node->left = transferredSubtree;

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

    return newRoot;
}

AVLTree::AVLNode *AVLTree::insert(AVLNode *node, const Product &product) {
    if (node == nullptr) {
        return new AVLNode(product);
    }

    if (product.name < node->data.name) {
        node->left = insert(node->left, product);
    } else if (product.name > node->data.name) {
        node->right = insert(node->right, product);
    } else {
        return node;
    }

    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);

    // Right Right case
    if (balance > 1 && product.name > node->right->data.name) {
        return rotateLeft(node);
    }

    // Right Left case
    if (balance > 1 && product.name < node->right->data.name) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Left Left case
    if (balance < -1 && product.name < node->left->data.name) {
        return rotateRight(node);
    }

    // Left Right case
    if (balance < -1 && product.name > node->left->data.name) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    return node;
}

void AVLTree::insert(const Product &product) {
    root = insert(root, product);
}

AVLTree::AVLNode* AVLTree::search(AVLNode* node, const std::string& name) {
    if (node == nullptr) {
        return nullptr;
    }

    if (name == node->data.name) {
        return node;
    }

    if (name < node->data.name) {
        return search(node->left, name);
    }

    return search(node->right, name);
}

Product* AVLTree::search(const std::string& name) {
    AVLNode* foundNode = search(root, name);

    if (foundNode == nullptr) {
        return nullptr;
    }

    return &foundNode->data;
}

AVLTree::AVLNode* AVLTree::minValueNode(AVLNode* node) {
    AVLNode* current = node;

    while (current != nullptr && current->left != nullptr) {
        current = current->left;
    }

    return current;
}

AVLTree::AVLNode* AVLTree::remove(AVLNode* node, const std::string& name) {
    if (node == nullptr) {
        return nullptr;
    }

    if (name < node->data.name) {
        node->left = remove(node->left, name);
    } else if (name > node->data.name) {
        node->right = remove(node->right, name);
    } else {
        // The node to delete has been found

        // Check if the node does not have any children (leaf node)
        if (node->left == nullptr && node->right == nullptr) {
            delete node;
            return nullptr;
        }
        // Check if the node has only one right child
        if (node->left == nullptr) {
            AVLNode* temp = node->right;
            delete node;
            return temp;
        }
        // Check if the node has only one left child
        if (node->right == nullptr) {
            AVLNode* temp = node->left;
            delete node;
            return temp;
        }

        // The node has two children, find the in-order successor (smallest in the right subtree)
        AVLNode* successor = minValueNode(node->right);
        node->data = successor->data;
        node->right = remove(node->right, successor->data.name);
    }

    // Set the new height and balance
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    int balance = getBalanceFactor(node);

    // Right Right case
    if (balance > 1 && getBalanceFactor(node->right) >= 0) {
        return rotateLeft(node);
    }

    // Right Left case
    if (balance > 1 && getBalanceFactor(node->right) < 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    // Left Left case
    if (balance < -1 && getBalanceFactor(node->left) <= 0) {
        return rotateRight(node);
    }

    //Left Right case
    if (balance < -1 && getBalanceFactor(node->left) > 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    return node;
}

void AVLTree::remove(const std::string &name) {
    root = remove(root, name);
}

void AVLTree::inorderTraversal(AVLNode *node) const {
    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left);

    std::cout << "Nombre: " << node->data.name << std::endl;
    std::cout << "Código de barras: " << node->data.barcode << std::endl;
    std::cout << "Categoría: " << node->data.category << std::endl;
    std::cout << "Fecha de expiración: " << node->data.expiryDate << std::endl;
    std::cout << "Marca: " << node->data.brand << std::endl;
    std::cout << "Precio: " << node->data.price << std::endl;
    std::cout << "Stock: " << node->data.stock << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    inorderTraversal(node->right);
}

void AVLTree::inorderTraversal() const {
    inorderTraversal(root);
}

void AVLTree::generateDotNodes(std::ofstream &file, AVLNode *node) const {
    if (node == nullptr) {
        return;
    }

    file << "    \"" << node->data.name << "\" [label=\""
        << node->data.name << "\"];" << std::endl;

    generateDotNodes(file, node->left);
    generateDotNodes(file, node->right);
}


void AVLTree::generateDotEdges(std::ofstream &file, AVLNode *node) const {
    if (node == nullptr) {
        return;
    }

    if (node->left != nullptr) {
        file << "    \"" << node->data.name << "\"->\""
            << node->left->data.name << "\";" << std::endl;
    }

    if (node->right != nullptr) {
        file << "    \"" << node->data.name << "\"->\""
            << node->right->data.name << "\";" << std::endl;
    }

    generateDotEdges(file, node->left);
    generateDotEdges(file, node->right);
}

void AVLTree::generateDotFile(const std::string &filePath) const {
    // Ensure directory exists
    std::filesystem::path path(filePath);
    std::filesystem::create_directories(path.parent_path());

    std::ofstream file(filePath);

    if (!file.is_open()) {
        std::cout << "No se pudo crear el archivo DOT." << std::endl;
        return;
    }

    file << "digraph AVLTree {" << std::endl;
    file << "    node [shape=circle];" << std::endl;

    if (root != nullptr) {
        generateDotNodes(file, root);
        generateDotEdges(file, root);
    }

    file << "}" << std::endl;
    file.close();

    // Generate PNG using Graphviz
    std::string pngPath = filePath.substr(0, filePath.find_last_of('.')) + ".png";
    std::string command = "dot -Tpng " + filePath + " -o " + pngPath;
    system(command.c_str());

    int result = system(command.c_str());

    if (result != 0) {
        std::cout << "Generación fallida del PNG AVL_Tree. Asegurese de tener instalado Graphviz" << std::endl;
    } else {
        std::cout << "Generación exitosa del PNG AVL_Tree en: " << pngPath << std::endl;
    }
}