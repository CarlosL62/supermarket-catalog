#ifndef SUPERMARKET_CATALOG_CSVLOADER_H
#define SUPERMARKET_CATALOG_CSVLOADER_H

#include <vector>
#include "../models/Product.h"

class CSVLoader {
public:
    static std::vector<Product> loadProducts(const std::string& filePath);
};

#endif //SUPERMARKET_CATALOG_CSVLOADER_H