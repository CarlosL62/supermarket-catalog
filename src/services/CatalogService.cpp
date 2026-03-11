#include <iostream>
#include "../../include/services/CatalogService.h"

#include "../../include/models/Product.h"

CatalogService::CatalogService() = default;

bool CatalogService::addProduct(const Product& product) {
    std::cout << "Producto agregado correctamente." << std::endl;
    displayProduct(product);
    return true; // Temporal: all structures implemented here later
}

bool CatalogService::deleteProductByBarcode(const std::string& barcode) {
    std::cout << "Eliminar producto por código de barras aún no implementado." << std::endl;
    return false;
}

Product* CatalogService::searchByName(const std::string& name) {
    std::cout << "Búsqueda por nombre aún no implementada." << std::endl;
    return nullptr;
}

Product* CatalogService::searchByBarcode(const std::string& barcode) {
    std::cout << "Búsqueda por código de barras aún no implementada." << std::endl;
    return nullptr;
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
    std::cout << "Listado por nombre aún no implementado." << std::endl;
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
