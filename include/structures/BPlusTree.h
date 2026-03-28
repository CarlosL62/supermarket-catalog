#ifndef SUPERMARKET_CATALOG_BPLUSTREE_H
#define SUPERMARKET_CATALOG_BPLUSTREE_H

#include <string>
#include <vector>
#include <fstream>
#include "../models/Product.h"

class BPlusTree {
private:
    struct BPlusTreeNode {
        std::vector<std::string> keys;
        std::vector<std::vector<Product>> values;
        std::vector<BPlusTreeNode*> children;
        bool isLeaf;
        BPlusTreeNode* next;

        BPlusTreeNode(bool leaf);
    };

    BPlusTreeNode* root;
    int minDegree;

    BPlusTreeNode* findLeaf(const std::string& category) const;
    void splitChild(BPlusTreeNode* parent, int childIndex);
    void insertNonFull(BPlusTreeNode* node, const Product& product);
    void remove(BPlusTreeNode* node, const Product& product);
    void destroyTree(BPlusTreeNode* node);
    void generateDotNodes(std::ofstream& file, BPlusTreeNode* node) const;
    void generateDotEdges(std::ofstream& file, BPlusTreeNode* node) const;

public:
    BPlusTree(int degree = 2);
    ~BPlusTree();

    void insert(const Product& product);
    std::vector<Product> search(const std::string& category) const;
    void remove(const Product& product);
    void generateDotFile(const std::string& filePath) const;
};

#endif // SUPERMARKET_CATALOG_BPLUSTREE_H
