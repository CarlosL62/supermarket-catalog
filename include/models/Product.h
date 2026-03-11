#ifndef SUPERMARKET_CATALOG_PRODUCT_H
#define SUPERMARKET_CATALOG_PRODUCT_H
#include <string>

struct Product {
    std::string name;
    std::string barcode;
    std::string category;
    std::string expiryDate;
    std::string brand;
    double price;
    int stock;
};

#endif //SUPERMARKET_CATALOG_PRODUCT_H