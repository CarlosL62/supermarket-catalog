#include "../../include/structures/AVLTree.h"

#include <iostream>

AVLTree::AVLTree() : root(nullptr) {}

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

void AVLTree::inorderTraversal(AVLNode *node) const {
    if (node == nullptr) {
        return;
    }

    inorderTraversal(node->left);

    std::cout << "Nombre: " << node->data.name << std::endl;
    std::cout << "Código de barras: " << node->data.barcode << std::endl;
    std::cout << "Categoría: " << node->data.category << std::endl;
    std::cout << "Marca: " << node->data.brand << std::endl;
    std::cout << "Precio: " << node->data.price << std::endl;
    std::cout << "Stock: " << node->data.stock << std::endl;
    std::cout << "-------------------------------------" << std::endl;

    inorderTraversal(node->right);
}

void AVLTree::inorderTraversal() const {
    inorderTraversal(root);
}
