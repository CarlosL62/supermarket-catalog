#include <iostream>
#include "../../include/services/CatalogService.h"

CatalogService::CatalogService() = default;

bool CatalogService::addProduct(const Product& product) {
    unorderedList.insert(product);
    orderedList.insert(product);
    hashTable.insert(product);
    avlTree.insert(product);
    bTree.insert(product);
    bPlusTree.insert(product);
    std::cout << "Producto agregado correctamente." << std::endl;
    // displayProduct(product);
    return true;
}

bool CatalogService::deleteProductByBarcode(const std::string& barcode) {
    Product* productToDelete = hashTable.search(barcode);

    if (productToDelete == nullptr) {
        std::cout << "No se encontró un producto con ese código de barras." << std::endl;
        return false;
    }

    unorderedList.removeByBarcode(barcode);
    orderedList.removeByBarcode(barcode);
    avlTree.remove(productToDelete->name);
    bTree.remove(productToDelete->expiryDate);
    bPlusTree.remove(*productToDelete);
    hashTable.remove(barcode);

    std::cout << "Producto eliminado correctamente." << std::endl;
    return true;
}

Product* CatalogService::searchByName(const std::string& name) {
    Product* foundProduct = avlTree.search(name);

    if (foundProduct == nullptr) {
        std::cout << "No se encontró un producto con ese nombre." << std::endl;
        return nullptr;
    }

    return foundProduct;
}

Product* CatalogService::searchByBarcode(const std::string& barcode) {
    Product* foundProduct = hashTable.search(barcode);

    if (foundProduct == nullptr) {
        std::cout << "No se encontró un producto con ese código de barras." << std::endl;
        return nullptr;
    }

    return foundProduct;
}

std::vector<Product> CatalogService::searchByCategory(const std::string& category) const {
    return bPlusTree.search(category);
}

std::vector<Product> CatalogService::searchByExpiryDateRange(const std::string& startDate, const std::string& endDate) const {
    return bTree.searchByRange(startDate, endDate);
}

void CatalogService::listProductsByName() const {
    std::cout << "Listado actual desde el árbol AVL:" << std::endl;
    avlTree.inorderTraversal();
}

void CatalogService::compareSearchPerformance() const {
    std::cout << "Comparación de rendimiento aún no implementada." << std::endl;
}

void CatalogService::loadFromCSV(const std::string& filePath) {
    // Load products from CSV using CSVLoader
    std::vector<Product> products = CSVLoader::loadProducts(filePath);

    // Insert each product into all structures
    for (const Product& product : products) {
        addProduct(product);
    }

    std::cout << "Productos cargados desde CSV correctamente." << std::endl;
    std::cout << "Total de productos cargados: " << products.size() << std::endl;
}

void CatalogService::generateTreeVisualizations() const {
    avlTree.generateDotFile("../data/avl_tree.dot");
    bTree.generateDotFile("../data/b_tree.dot");
    bPlusTree.generateDotFile("../data/b_plus_tree.dot");
}

void CatalogService::displayProduct(const Product& product) const {
    std::cout << "Nombre: " << product.name << std::endl;
    std::cout << "Código de barras: " << product.barcode << std::endl;
    std::cout << "Categoría: " << product.category << std::endl;
    std::cout << "Fecha de vencimiento: " << product.expiryDate << std::endl;
    std::cout << "Marca: " << product.brand << std::endl;
    std::cout << "Precio: Q " << product.price << std::endl;
    std::cout << "Cantidad: " << product.stock << " unidades" << std::endl;
}
