#ifndef SUPERMARKET_CATALOG_CATALOGSERVICE_H
#define SUPERMARKET_CATALOG_CATALOGSERVICE_H
#include "../utils/CSVLoader.h"
#include "../structures/UnorderedLinkedList.h"
#include "../structures/OrderedLinkedList.h"
#include "../structures/HashTable.h"
#include "../structures/AVLTree.h"
#include "../structures/BTree.h"
#include "../structures/BPlusTree.h"

class CatalogService {
private:
    UnorderedLinkedList unorderedList;
    OrderedLinkedList orderedList;
    HashTable hashTable;
    AVLTree avlTree;
    BTree bTree;
    BPlusTree bPlusTree;
public:
    CatalogService();

    bool addProduct(const Product& product, bool showMessage);
    bool deleteProductByBarcode(const std::string& barcode);

    Product* searchByName(const std::string& name);
    Product* searchByBarcode(const std::string& barcode);
    std::vector<Product> searchByCategory(const std::string& category) const;
    std::vector<Product> searchByExpiryDateRange(const std::string& startDate, const std::string& endDate) const;

    void listProductsByName() const;
    void compareSearchPerformance() const;
    void loadFromCSV(const std::string& filePath);
    void generateTreeVisualizations() const;

    void displayProduct(const Product& product) const;
};

#endif //SUPERMARKET_CATALOG_CATALOGSERVICE_H