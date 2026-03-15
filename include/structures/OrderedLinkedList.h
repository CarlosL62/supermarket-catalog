#ifndef SUPERMARKET_CATALOG_ORDEREDLINKEDLIST_H
#define SUPERMARKET_CATALOG_ORDEREDLINKEDLIST_H

#include "BaseLinkedList.h"

class OrderedLinkedList : public BaseLinkedList {
public:
    void insert(const Product& product) override;
};

#endif //SUPERMARKET_CATALOG_ORDEREDLINKEDLIST_H