#include "../../include/structures/HashTable.h"

HashTable::HashTable(int size) : capacity(size) {
    table.resize(capacity);
}

int HashTable::hashFunction(const std::string &barcode) {
    unsigned long hash = 0;

    for (char character : barcode) {
        // Polynomial rolling hash
        hash = hash * 31 + character;
    }

    return static_cast<int>(hash % capacity);
}

bool HashTable::insert(const Product &product) {
    int index = hashFunction(product.barcode);

    if (table[index].searchByBarcode(product.barcode) != nullptr) {
        return false;
    }

    table[index].insert(product);
    return true;
}

Product* HashTable::search(const std::string &barcode) {
    int index = hashFunction(barcode);
    return table[index].searchByBarcode(barcode);
}

bool HashTable::remove(const std::string &barcode) {
    int index = hashFunction(barcode);
    return table[index].removeByBarcode(barcode);
}
