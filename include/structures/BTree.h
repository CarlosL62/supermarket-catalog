#ifndef SUPERMARKET_CATALOG_BTREE_H
#define SUPERMARKET_CATALOG_BTREE_H

#include <vector>
#include <fstream>
#include "../models/Product.h"

class BTree {
private:
    struct BTreeNode {
        std::vector<Product> keys;
        std::vector<BTreeNode*> children;
        bool isLeaf;

        BTreeNode(bool isLeaf);
    };

    BTreeNode* root;
    int minDegree;

    Product* search(BTreeNode* node, const std::string& expiryDate);
    void searchByRange(BTreeNode* node, const std::string& startDate, const std::string& endDate, std::vector<Product>& results) const;
    void splitChild(BTreeNode* parent, int childIndex);
    void insertNonFull(BTreeNode* node, const Product& product);
    void remove(BTreeNode* node, const std::string& expiryDate);
    Product getSuccessor(BTreeNode* node, int index);
    void destroyTree(BTreeNode* node);
    void generateDotNodes(std::ofstream& file, BTreeNode* node) const;
    void generateDotEdges(std::ofstream& file, BTreeNode* node) const;
public:
    BTree(int degree = 2);
    ~BTree();

    Product* search(const std::string& expiryDate);
    std::vector<Product> searchByRange(const std::string& startDate, const std::string& endDate) const;
    void insert(const Product& product);
    void remove(const std::string& expiryDate);
    void generateDotFile(const std::string& filePath) const;
};

#endif //SUPERMARKET_CATALOG_BTREE_H
