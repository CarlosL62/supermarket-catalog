#include <iostream>
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

        switch (option) {
            case 1: {
                // Example of addition of a product, this will be replaced by user input
                Product product {
                    "Milk",
                    "1234567890123",
                    "Dairy",
                    "2024-12-31",
                    "Brand A",
                    1.99,
                    30
                };

                catalogService.addProduct(product);
                break;
            }
            case 2:
                std::cout << "Opcion aun no implementada." << std::endl;
                break;
            case 3:
                std::cout << "Opcion aun no implementada." << std::endl;
                break;
            case 4:
                std::cout << "Opcion aun no implementada." << std::endl;
                break;
            case 5:
                std::cout << "Opcion aun no implementada." << std::endl;
                break;
            case 6:
                std::cout << "Opcion aun no implementada." << std::endl;
                break;
            case 7:
                std::cout << "Opcion aun no implementada." << std::endl;
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