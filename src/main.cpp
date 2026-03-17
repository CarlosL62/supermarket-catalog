#include <iostream>
#include "../include/models/Product.h"
#include "../include/services/CatalogService.h"

int main() {
    int option;
    CatalogService catalogService;

    //TEST
    Product p1 = {"Milk", "123", "Dairy", "2026-01-01", "BrandA", 10.5, 20};
    Product p2 = {"Bread", "456", "Bakery", "2026-01-02", "BrandB", 5.0, 30};
    Product p3 = {"Apple", "789", "Fruits", "2026-01-03", "BrandC", 3.0, 50};

    catalogService.addProduct(p1);
    catalogService.addProduct(p2);
    catalogService.addProduct(p3);

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

        switch (option) {
            case 1: {
                Product product;

                std::cout << "Nombre: ";
                std::cin >> product.name;
                std::cout << "Código de barras: ";
                std::cin >> product.barcode;
                std::cout << "Categoría: ";
                std::cin >> product.category;
                std::cout << "Fecha de expiración (YYYY-MM-DD): ";
                std::cin >> product.expiryDate;
                std::cout << "Marca: ";
                std::cin >> product.brand;
                std::cout << "Precio: ";
                std::cin >> product.price;
                std::cout << "Stock: ";
                std::cin >> product.stock;

                catalogService.addProduct(product);
                break;
            }
            case 2: {
                std::string barcode;
                std::cout << "Ingrese el código de barras del producto a eliminar: ";
                std::cin >> barcode;

                catalogService.deleteProductByBarcode(barcode);
                break;
            }
            case 3: {
                std::string name;
                std::cout << "Ingrese el nombre del producto a buscar: ";
                std::cin >> name;

                Product* foundProduct = catalogService.searchByName(name);
                if (foundProduct != nullptr) {
                    catalogService.displayProduct(*foundProduct);
                }
                break;
            }
            case 4: {
                std::string barcode;
                std::cout << "Ingrese el código de barras del producto a buscar: ";
                std::cin >> barcode;

                Product* foundProduct = catalogService.searchByBarcode(barcode);
                if (foundProduct != nullptr) {
                    catalogService.displayProduct(*foundProduct);
                }
                break;
            }
            case 5:
                std::cout << "Opcion aun no implementada." << std::endl;
                break;
            case 6:
                std::cout << "Opcion aun no implementada." << std::endl;
                break;
            case 7:
                catalogService.listProductsByName();
                break;
            case 8:
                std::cout << "Opcion aun no implementada." << std::endl;
                break;
            case 9:
                std::cout << "Opcion aun no implementada." << std::endl;
                break;
            case 10:
                std::cout << "Opcion aun no implementada." << std::endl;
                break;
            case 0:
                std::cout << "Saliendo del sistema..." << std::endl;
                break;
            default:
                std::cout << "Opcion invalida. Intente de nuevo." << std::endl;
                break;
        }
    } while (option != 0);

    return 0;
}