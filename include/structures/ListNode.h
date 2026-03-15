#ifndef SUPERMARKET_CATALOG_LISTNODE_H
#define SUPERMARKET_CATALOG_LISTNODE_H

#include "../models/Product.h"

struct ListNode {
    Product data;
    ListNode* next;

    ListNode(const Product& product) : data(product), next(nullptr) {}
};

#endif // SUPERMARKET_CATALOG_LISTNODE_H