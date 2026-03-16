#ifndef SUPERMARKET_CATALOG_HASHTABLE_H
#define SUPERMARKET_CATALOG_HASHTABLE_H

#include <vector>
#include "UnorderedLinkedList.h"

class HashTable {
private:
    std::vector<UnorderedLinkedList> table;
    int capacity;

    int hashFunction(const std::string& barcode);
public:
    HashTable(int size = 101);

    bool insert(const Product& product);
    Product* search(const std::string& barcode);
    bool remove(const std::string& barcode);
};

#endif //SUPERMARKET_CATALOG_HASHTABLE_H