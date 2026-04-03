#include <iostream>
#include <chrono>
#include <iomanip>
#include <vector>
#include "../../include/services/CatalogService.h"

CatalogService::CatalogService() = default;

bool CatalogService::addProduct(const Product& product, bool showMessage) {
    unorderedList.insert(product);
    orderedList.insert(product);
    hashTable.insert(product);
    avlTree.insert(product);
    bTree.insert(product);
    bPlusTree.insert(product);
    if (showMessage) {
        std::cout << "Producto agregado correctamente." << std::endl;
    }
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
    using Clock = std::chrono::high_resolution_clock;
    using Microseconds = std::chrono::duration<double, std::micro>;

    const std::vector<std::string> successfulNameQueries = {
        "Leche", "Pan", "Manzana", "Queso", "Arroz", "Frijol", "Jugo"
    };

    const std::vector<std::string> successfulBarcodeQueries = {
        "1234567890123", "9876543210000", "5555555555555",
        "1112223334445", "9998887776661", "2223334445556", "3334445556667"
    };

    const std::string failedNameQuery = "ProductoInexistenteXYZ";
    const std::string failedBarcodeQuery = "0000000000000";

    const std::string firstNameQuery = "Leche";
    const std::string lastNameQuery = "Jugo";
    const std::string firstBarcodeQuery = "1234567890123";
    const std::string lastBarcodeQuery = "3334445556667";

    const int N = 20;
    const int M = 5;

    auto averageSearchTime = [&](const std::vector<std::string>& queries, auto searchFunction) {
        double totalMicroseconds = 0.0;
        int totalRuns = 0;

        for (int repeat = 0; repeat < M; repeat++) {
            for (int i = 0; i < N; i++) {
                const std::string& query = queries[i % queries.size()];

                auto start = Clock::now();
                volatile const Product* result = searchFunction(query);
                (void)result;
                auto end = Clock::now();

                totalMicroseconds += Microseconds(end - start).count();
                totalRuns++;
            }
        }

        if (totalRuns == 0) {
            return 0.0;
        }

        return totalMicroseconds / totalRuns;
    };

    auto& unordered = const_cast<UnorderedLinkedList&>(unorderedList);
    auto& ordered = const_cast<OrderedLinkedList&>(orderedList);
    auto& avl = const_cast<AVLTree&>(avlTree);
    auto& hash = const_cast<HashTable&>(hashTable);

    std::cout << "\n===== COMPARACIÓN DE RENDIMIENTO DE BÚSQUEDA =====" << std::endl;
    std::cout << "Tiempo promedio en microsegundos (us)" << std::endl;
    std::cout << "N consultas: " << N << std::endl;
    std::cout << "M repeticiones: " << M << std::endl;
    std::cout << std::fixed << std::setprecision(2);

    std::cout << "\n--- Búsqueda por nombre: consultas exitosas ---" << std::endl;
    std::cout << std::setw(28) << std::left << "Lista no ordenada"
              << averageSearchTime(successfulNameQueries, [&](const std::string& query) {
                     return unordered.searchByName(query);
                 }) << " us" << std::endl;
    std::cout << std::setw(28) << std::left << "Lista ordenada"
              << averageSearchTime(successfulNameQueries, [&](const std::string& query) {
                     return ordered.searchByName(query);
                 }) << " us" << std::endl;
    std::cout << std::setw(28) << std::left << "Árbol AVL"
              << averageSearchTime(successfulNameQueries, [&](const std::string& query) {
                     return avl.search(query);
                 }) << " us" << std::endl;

    std::cout << "\n--- Búsqueda por nombre: consulta fallida ---" << std::endl;
    std::cout << std::setw(28) << std::left << "Lista no ordenada"
              << averageSearchTime({failedNameQuery}, [&](const std::string& query) {
                     return unordered.searchByName(query);
                 }) << " us" << std::endl;
    std::cout << std::setw(28) << std::left << "Lista ordenada"
              << averageSearchTime({failedNameQuery}, [&](const std::string& query) {
                     return ordered.searchByName(query);
                 }) << " us" << std::endl;
    std::cout << std::setw(28) << std::left << "Árbol AVL"
              << averageSearchTime({failedNameQuery}, [&](const std::string& query) {
                     return avl.search(query);
                 }) << " us" << std::endl;

    std::cout << "\n--- Búsqueda por nombre: extremos (primero/último) ---" << std::endl;
    std::cout << std::setw(28) << std::left << "Lista no ordenada"
              << averageSearchTime({firstNameQuery, lastNameQuery}, [&](const std::string& query) {
                     return unordered.searchByName(query);
                 }) << " us" << std::endl;
    std::cout << std::setw(28) << std::left << "Lista ordenada"
              << averageSearchTime({firstNameQuery, lastNameQuery}, [&](const std::string& query) {
                     return ordered.searchByName(query);
                 }) << " us" << std::endl;
    std::cout << std::setw(28) << std::left << "Árbol AVL"
              << averageSearchTime({firstNameQuery, lastNameQuery}, [&](const std::string& query) {
                     return avl.search(query);
                 }) << " us" << std::endl;

    std::cout << "\n--- Búsqueda por código: consultas exitosas ---" << std::endl;
    std::cout << std::setw(28) << std::left << "Hash table"
              << averageSearchTime(successfulBarcodeQueries, [&](const std::string& query) {
                     return hash.search(query);
                 }) << " us" << std::endl;

    std::cout << "\n--- Búsqueda por código: consulta fallida ---" << std::endl;
    std::cout << std::setw(28) << std::left << "Hash table"
              << averageSearchTime({failedBarcodeQuery}, [&](const std::string& query) {
                     return hash.search(query);
                 }) << " us" << std::endl;

    std::cout << "\n--- Búsqueda por código: extremos (primero/último) ---" << std::endl;
    std::cout << std::setw(28) << std::left << "Hash table"
              << averageSearchTime({firstBarcodeQuery, lastBarcodeQuery}, [&](const std::string& query) {
                     return hash.search(query);
                 }) << " us" << std::endl;

    std::cout << "\nResumen teórico:" << std::endl;
    std::cout << "- Lista no ordenada: O(n)" << std::endl;
    std::cout << "- Lista ordenada: O(n)" << std::endl;
    std::cout << "- Árbol AVL: O(log n)" << std::endl;
    std::cout << "- Hash table (promedio): O(1)" << std::endl;
}

void CatalogService::loadFromCSV(const std::string& filePath) {
    // Load products from CSV using CSVLoader
    std::vector<Product> products = CSVLoader::loadProducts(filePath);

    if (products.empty()) {
        std::cout << "No se cargaron productos desde el CSV." << std::endl;
        return;
    }

    // Insert each product into all structures without printing one by one
    for (const Product& product : products) {
        addProduct(product, false);
    }

    std::cout << "Productos cargados correctamente." << std::endl;
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
