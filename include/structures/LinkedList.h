#ifndef SUPERMARKET_CATALOG_LINKEDLIST_H
#define SUPERMARKET_CATALOG_LINKEDLIST_H

#include "../models/Product.h"
#include "ListNode.h"

class LinkedList {
private:
    ListNode* head;
public:
    LinkedList();
    ~LinkedList();

    bool isEmpty() const;

    void insert(const Product& product);
    Product* searchByName(const std::string& name);
    Product* searchByBarcode(const std::string& barcode);
    bool removeByBarcode(const std::string& barcode);

    void display() const;
};

#endif //SUPERMARKET_CATALOG_LINKEDLIST_H