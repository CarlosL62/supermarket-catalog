#ifndef SUPERMARKET_CATALOG_BASELINKEDLIST_H
#define SUPERMARKET_CATALOG_BASELINKEDLIST_H

#include "ListNode.h"

class BaseLinkedList {
protected:
    ListNode* head;

public:
    BaseLinkedList();
    virtual ~BaseLinkedList();

    bool isEmpty() const;
    Product* searchByName(const std::string& name);
    Product* searchByBarcode(const std::string& barcode);
    bool removeByBarcode(const std::string& barcode);
    void display() const;

    virtual void insert(const Product& product) = 0;
};

#endif //SUPERMARKET_CATALOG_BASELINKEDLIST_H