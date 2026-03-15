#include <iostream>
#include "../../include/services/CatalogService.h"
#include "../../include/models/Product.h"

CatalogService::CatalogService() = default;

bool CatalogService::addProduct(const Product& product) {
    productList.insert(product);
    std::cout << "Producto agregado correctamente." << std::endl;
    displayProduct(product);
    return true;
}

bool CatalogService::deleteProductByBarcode(const std::string& barcode) {
    bool removed = productList.removeByBarcode(barcode);
    if (removed) {
        std::cout << "Produto eliminado correctamente." << std::endl;
        return true;
    }

    std::cout << "No se encontró un producto con ese código de barras." << std::endl;
    return false;
}

Product* CatalogService::searchByName(const std::string& name) {
    Product* foundProduct = productList.searchByName(name);

    if (foundProduct == nullptr) {
        std::cout << "No se encontró un producto con ese nombre." << std::endl;
        return nullptr;
    }

    return foundProduct;
}

Product* CatalogService::searchByBarcode(const std::string& barcode) {
    Product* foundProduct = productList.searchByBarcode(barcode);

    if (foundProduct == nullptr) {
        std::cout << "No se encontró un producto con ese código de barras." << std::endl;
        return nullptr;
    }

    return foundProduct;
}

std::vector<Product> CatalogService::searchByCategory(const std::string& category) const {
    std::cout << "Búsqueda por categoría aún no implementada." << std::endl;
    return {};
}

std::vector<Product> CatalogService::searchByExpiryDateRange(const std::string& startDate, const std::string& endDate) const {
    std::cout << "Búsqueda por rango de fechas aún no implementada." << std::endl;
    return {};
}

void CatalogService::listProductsByName() const {
    std::cout << "Listado actual desde la lista enlazada no ordenada" << std::endl;
    productList.display();
}

void CatalogService::compareSearchPerformance() const {
    std::cout << "Comparación de rendimiento aún no implementada." << std::endl;
}

void CatalogService::loadFromCSV(const std::string& filePath) {
    std::cout << "Carga desde CSV aún no implementada." << std::endl;
}

void CatalogService::generateTreeVisualizations() const {
    std::cout << "Visualización de árboles aún no implementada." << std::endl;
}

void CatalogService::displayProduct(const Product& product) const {
    std::cout << "Nombre: " << product.name << std::endl;
    std::cout << "Código de barras: " << product.barcode << std::endl;
    std::cout << "Categoría: " << product.category << std::endl;
    std::cout << "Fecha de vencimiento: " << product.expiryDate << std::endl;
    std::cout << "Marca: " << product.brand << std::endl;
    std::cout << "Precio: $" << product.price << std::endl;
    std::cout << "Cantidad: " << product.stock << " unidades" << std::endl;
}
