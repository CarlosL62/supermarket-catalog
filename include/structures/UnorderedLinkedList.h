#ifndef SUPERMARKET_CATALOG_UNORDEREDLINKEDLIST_H
#define SUPERMARKET_CATALOG_UNORDEREDLINKEDLIST_H

#include "BaseLinkedList.h"

class UnorderedLinkedList : public BaseLinkedList {
public:
    void insert(const Product& product) override;
};

#endif //SUPERMARKET_CATALOG_UNORDEREDLINKEDLIST_H