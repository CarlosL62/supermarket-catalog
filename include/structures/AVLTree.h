#ifndef SUPERMARKET_CATALOG_AVLTREE_H
#define SUPERMARKET_CATALOG_AVLTREE_H
#include "../models/Product.h"
#include <fstream>

class AVLTree {
private:
    struct AVLNode {
        Product data;
        AVLNode *left, *right;
        int height;

        AVLNode(const Product& product) : data(product), left(nullptr), right(nullptr), height(1) {}
    };

    AVLNode* root;

    AVLNode* insert(AVLNode* node, const Product& product);
    AVLNode* rotateLeft(AVLNode* node);
    AVLNode* rotateRight(AVLNode* node);

    int getHeight(AVLNode* node);
    int getBalanceFactor(AVLNode* node);

    AVLNode* search(AVLNode* node, const std::string& name);
    AVLNode* remove(AVLNode* node, const std::string& name);
    AVLNode* minValueNode(AVLNode* node);
    void inorderTraversal(AVLNode* node) const;
    void destroyTree(AVLNode* node);

    void generateDotNodes(std::ofstream& file, AVLNode* node) const;
    void generateDotEdges(std::ofstream& file, AVLNode* node) const;
public:
    AVLTree();
    ~AVLTree();

    void insert(const Product& product);
    Product* search(const std::string& name);
    void remove(const std::string& name);
    void inorderTraversal() const;

    void generateDotFile(const std::string& filePath) const;
};


#endif //SUPERMARKET_CATALOG_AVLTREE_H