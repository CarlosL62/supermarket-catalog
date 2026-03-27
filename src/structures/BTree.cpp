#include "../../include/structures/BTree.h"

BTree::BTreeNode::BTreeNode(bool leaf) : isLeaf(leaf) {}

BTree::BTree(int degree) : root(nullptr), minDegree(degree) {}

BTree::~BTree() {
    destroyTree(root);
}

void BTree::destroyTree(BTreeNode* node) {
    if (node == nullptr) {
        return;
    }

    for (BTreeNode* child : node->children) {
        destroyTree(child);
    }

    delete node;
}

Product* BTree::search(BTreeNode* node, const std::string& expiryDate) {
    if (node == nullptr) {
        return nullptr;
    }

    // Find position where key should be
    int i = 0;

    // Move forward while current key is smaller than target
    while (i < static_cast<int>(node->keys.size()) && expiryDate > node->keys[i].expiryDate) {
        i++;
    }

    // If we found exact match, return it
    if (i < static_cast<int>(node->keys.size()) && expiryDate == node->keys[i].expiryDate) {
        return &node->keys[i];
    }

    // If it is a leaf and not found, stop there
    if (node->isLeaf) {
        return nullptr;
    }

    // Otherwise, go down to the correct child
    return search(node->children[i], expiryDate);
}

Product* BTree::search(const std::string& expiryDate) {
    return search(root, expiryDate);
}

// Get the smallest key from the right subtree
Product BTree::getSuccessor(BTreeNode* node, int index) {
    BTreeNode* current = node->children[index + 1];

    while (!current->isLeaf) {
        current = current->children[0];
    }

    return current->keys[0];
}

// Split a full child into two nodes and move the middle key up
void BTree::splitChild(BTreeNode* parent, int childIndex) {
    BTreeNode* fullChild = parent->children[childIndex];
    BTreeNode* newChild = new BTreeNode(fullChild->isLeaf);

    // Middle key goes up to the parent
    Product middleKey = fullChild->keys[minDegree - 1];

    // Keys after the middle go to the new rigth child
    for (int i = minDegree; i < static_cast<int>(fullChild->keys.size()); i++) {
        newChild->keys.push_back(fullChild->keys[i]);
    }

    // If it is not a leaf, move the corresponding children too
    if (!fullChild->isLeaf) {
        for (int i = minDegree; i < static_cast<int>(fullChild->children.size()); i++) {
            newChild->children.push_back(fullChild->children[i]);
        }
    }

    // Keep only the left part in the original child
    fullChild->keys.resize(minDegree - 1);
    if (!fullChild->isLeaf) {
        fullChild->children.resize(minDegree);
    }

    // Insert the new child and the promoted key into the parent
    parent->children.insert(parent->children.begin() + childIndex + 1 ,newChild);
    parent->keys.insert(parent->keys.begin() + childIndex, middleKey);
}

// Insert into a node that is guaranteed not to be full
void BTree::insertNonFull(BTreeNode* node, const Product& product) {
    int i = static_cast<int>(node->keys.size()) - 1;

    if (node->isLeaf) {
        // Make room for the new key in sorted order
        node->keys.push_back(product);

        while (i >= 0 && product.expiryDate < node->keys[i].expiryDate) {
            node->keys[i + 1] = node->keys[i];
            i--;
        }

        node->keys[i + 1] = product;
        return;
    }

    // Find the child where the key should go
    while (i >= 0 && product.expiryDate < node->keys[i].expiryDate) {
        i--;
    }

    i++;

    // If the child is full, split it first
    if (static_cast<int>(node->children[i]->keys.size()) == 2 * minDegree - 1) {
        splitChild(node, i);

        // After split, decide again if we go right
        if (product.expiryDate > node->keys[i].expiryDate) {
            i++;
        }
    }

    insertNonFull(node->children[i], product);
}

// Public insert entry point
void BTree::insert(const Product& product) {
    if (root == nullptr) {
        root = new BTreeNode(true);
        root->keys.push_back(product);
        return;
    }

    // If root is full, tree height grows here
    if (static_cast<int>(root->keys.size()) == 2 * minDegree - 1) {
        BTreeNode* newRoot = new BTreeNode(false);
        newRoot->children.push_back(root);

        splitChild(newRoot, 0);

        int i = 0;
        if (product.expiryDate > newRoot->keys[0].expiryDate) {
            i++;
        }

        insertNonFull(newRoot->children[i], product);
        root = newRoot;
    } else {
        insertNonFull(root, product);
    }
}

// Recursive range search by expiry date
void BTree::searchByRange(BTreeNode* node, const std::string& startDate, const std::string& endDate, std::vector<Product>& results) const {
    if (node == nullptr) {
        return;
    }

    int i = 0;

    while (i < static_cast<int>(node->keys.size())) {
        if (!node->isLeaf && i < static_cast<int>(node->children.size())) {
            searchByRange(node->children[i], startDate, endDate, results);
        }

        if (node->keys[i].expiryDate >= startDate && node->keys[i].expiryDate <= endDate) {
            results.push_back(node->keys[i]);
        }

        i++;
    }

    if (!node->isLeaf && i < static_cast<int>(node->children.size())) {
        searchByRange(node->children[i], startDate, endDate, results);
    }
}

// Public range search entry point
std::vector<Product> BTree::searchByRange(const std::string& startDate, const std::string& endDate) const {
    std::vector<Product> results;
    searchByRange(root, startDate, endDate, results);
    return results;
}

// Remove by expiry date (handles leaf and simple internal-node replacement)
void BTree::remove(BTreeNode* node, const std::string& expiryDate) {
    if (node == nullptr) {
        return;
    }

    int i = 0;

    while (i < static_cast<int>(node->keys.size()) && expiryDate > node->keys[i].expiryDate) {
        i++;
    }

    // If we found the key inside this node
    if (i < static_cast<int>(node->keys.size()) && node->keys[i].expiryDate == expiryDate) {
        // Easy case: remove directly from leaf
        if (node->isLeaf) {
            node->keys.erase(node->keys.begin() + i);
            return;
        }

        // For internal node, replace with successor from right subtree
        Product successor = getSuccessor(node, i);
        node->keys[i] = successor;
        remove(node->children[i + 1], successor.expiryDate);
        return;
    }

    // If not found here and this is a leaf, nothing else to do
    if (node->isLeaf) {
        return;
    }

    // Keep going down to the child where the key should be
    if (i < static_cast<int>(node->children.size())) {
        remove(node->children[i], expiryDate);
    }
}

// Public remove entry point
void BTree::remove(const std::string& expiryDate) {
    remove(root, expiryDate);
}