#ifndef SUPERMARKET_CATALOG_LINKEDLIST_H
#define SUPERMARKET_CATALOG_LINKEDLIST_H

#include "BaseLinkedList.h"

class UnorderedLinkedList : public BaseLinkedList {
public:
    void insert(const Product& product) override;
};

#endif //SUPERMARKET_CATALOG_LINKEDLIST_H