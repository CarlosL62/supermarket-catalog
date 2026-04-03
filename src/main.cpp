#include <iostream>
#include <vector>
#include <limits>
#include "../include/models/Product.h"
#include "../include/services/CatalogService.h"

int main() {
    int option;
    CatalogService catalogService;

    do {
        std::cout << "\n===== SISTEMA DE CATALOGO DE SUPERMERCADO =====" << std::endl;
        std::cout << "1. Agregar producto" << std::endl;
        std::cout << "2. Eliminar producto" << std::endl;
        std::cout << "3. Buscar por nombre" << std::endl;
        std::cout << "4. Buscar por codigo de barras" << std::endl;
        std::cout << "5. Buscar por categoria" << std::endl;
        std::cout << "6. Buscar por rango de fecha de caducidad" << std::endl;
        std::cout << "7. Listar productos por nombre" << std::endl;
        std::cout << "8. Comparar rendimiento de busquedas" << std::endl;
        std::cout << "9. Cargar productos desde CSV" << std::endl;
        std::cout << "10. Visualizar arboles" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Seleccione una opcion: ";
        std::cin >> option;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (option) {
            case 1: {
                Product product;

                std::cout << "Nombre: ";
                std::getline(std::cin, product.name);
                if (product.name.empty()) {
                    std::cout << "El nombre no puede estar vacío." << std::endl;
                    break;
                }
                std::cout << "Código de barras: ";
                std::getline(std::cin, product.barcode);
                if (product.barcode.empty()) {
                    std::cout << "El código de barras no puede estar vacío." << std::endl;
                    break;
                }
                std::cout << "Categoría: ";
                std::getline(std::cin, product.category);
                if (product.category.empty()) {
                    std::cout << "La categoría no puede estar vacía." << std::endl;
                    break;
                }
                std::cout << "Fecha de expiración (YYYY-MM-DD): ";
                std::getline(std::cin, product.expiryDate);
                if (product.expiryDate.empty()) {
                    std::cout << "La fecha de expiración no puede estar vacía." << std::endl;
                    break;
                }
                std::cout << "Marca: ";
                std::getline(std::cin, product.brand);
                if (product.brand.empty()) {
                    std::cout << "La marca no puede estar vacía." << std::endl;
                    break;
                }
                std::cout << "Precio: ";
                std::cin >> product.price;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Stock: ";
                std::cin >> product.stock;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                catalogService.addProduct(product, true);
                break;
            }
            case 2: {
                std::string barcode;
                std::cout << "Ingrese el código de barras del producto a eliminar: ";
                std::getline(std::cin, barcode);
                if (barcode.empty()) {
                    std::cout << "El código de barras no puede estar vacío." << std::endl;
                    break;
                }

                catalogService.deleteProductByBarcode(barcode);
                break;
            }
            case 3: {
                std::string name;
                std::cout << "Ingrese el nombre del producto a buscar: ";
                std::getline(std::cin, name);
                if (name.empty()) {
                    std::cout << "El nombre no puede estar vacío." << std::endl;
                    break;
                }

                Product* foundProduct = catalogService.searchByName(name);
                if (foundProduct != nullptr) {
                    catalogService.displayProduct(*foundProduct);
                }
                break;
            }
            case 4: {
                std::string barcode;
                std::cout << "Ingrese el código de barras del producto a buscar: ";
                std::getline(std::cin, barcode);
                if (barcode.empty()) {
                    std::cout << "El código de barras no puede estar vacío." << std::endl;
                    break;
                }

                Product* foundProduct = catalogService.searchByBarcode(barcode);
                if (foundProduct != nullptr) {
                    catalogService.displayProduct(*foundProduct);
                }
                break;
            }
            case 5: {
                std::string category;
                std::cout << "Ingrese la categoria a buscar: ";
                std::getline(std::cin, category);
                if (category.empty()) {
                    std::cout << "La categoría no puede estar vacía." << std::endl;
                    break;
                }

                std::vector<Product> results = catalogService.searchByCategory(category);

                if (results.empty()) {
                    std::cout << "No se encontraron productos en esa categoria." << std::endl;
                } else {
                    std::cout << "\nProductos encontrados: " << results.size() << std::endl;
                    std::cout << "----------------------------------------" << std::endl;

                    for (const Product& product : results) {
                        catalogService.displayProduct(product);
                        std::cout << "----------------------------------------" << std::endl;
                    }
                }

                break;
            }
            case 6: {
                std::string startDate, endDate;
                std::cout << "Ingrese fecha de inicio (YYYY-MM-DD): ";
                std::getline(std::cin, startDate);
                std::cout << "Ingrese fecha de fin (YYYY-MM-DD): ";
                std::getline(std::cin, endDate);
                if (startDate.empty() || endDate.empty()) {
                    std::cout << "Las fechas no pueden estar vacías." << std::endl;
                    break;
                }

                std::vector<Product> results = catalogService.searchByExpiryDateRange(startDate, endDate);

                if (results.empty()) {
                    std::cout << "No se encontraron productos en ese rango." << std::endl;
                } else {
                    std::cout << "\nProductos encontrados en el rango: " << results.size() << std::endl;
                    std::cout << "----------------------------------------" << std::endl;

                    for (const Product& product : results) {
                        catalogService.displayProduct(product);
                        std::cout << "----------------------------------------" << std::endl;
                    }
                }
            }
                break;
            case 7:
                catalogService.listProductsByName();
                break;
            case 8:
                catalogService.compareSearchPerformance();
                break;
            case 9: {
                std::string filePath;
                std::cout << "Ingrese la ruta del archivo CSV: ";
                std::getline(std::cin, filePath);
                if (filePath.empty()) {
                    std::cout << "La ruta no puede estar vacía." << std::endl;
                    break;
                }

                catalogService.loadFromCSV(filePath);
                break;
            }
            case 10:
                catalogService.generateTreeVisualizations();
                break;
            case 0:
                std::cout << "Saliendo del sistema..." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
                break;
        }
        if (option != 0) {
            std::cout << "\nPresione Enter para continuar...";
            std::cin.get();
            system("clear");
        }
    } while (option != 0);

    return 0;
}