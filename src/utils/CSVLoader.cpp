#include "../../include/utils/CSVLoader.h"

#include <fstream>
#include <iostream>
#include <sstream>

// This file reads the CSV and converts each row into a Product
std::vector<Product> CSVLoader::loadProducts(const std::string &filePath) {
    std::vector<Product> products;

    // Try to open the file
    std::ifstream file(filePath);
    if (!file.is_open()) {
        // If it fails, return empty file
        std::cout << "Error al abrir el archivo: " << filePath << std::endl;
        return products;
    }

    int validCount = 0;
    int skippedCount = 0;

    std::string line;

    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        if (line.empty()) continue; // Skip empty lines

        // Turn line into a stream to split fields
        std::istringstream ss(line);
        std::string token;
        std::vector<std::string> fields;

        // Split by commas
        while (std::getline(ss, token, ',')) {
            // Trim basic leading/trailing spaces
            if (!token.empty() && token.front() == ' ') token.erase(0, 1);
            if (!token.empty() && token.back() == ' ') token.pop_back();

            fields.push_back(token);
        }

        // Validate field count
        if (fields.size() < 7) {
            std::cout << "Fila inválida (campos insuficientes): " << line << std::endl;
            skippedCount++;
            continue;
        }

        // Build Product from parsed feilds
        Product product;
        product.name = fields[0];
        product.barcode = fields[1];
        product.category = fields[2];
        product.expiryDate = fields[3];
        product.brand = fields[4];

        // Convert numeric fields
        try {
            product.price = std::stod(fields[5]);
            product.stock = std::stoi(fields[6]);
        } catch (...) {
            // If it fails, skip this row
            std::cout << "Error al convertir datos numéricos: " << line << std::endl;
            skippedCount++;
            continue;
        }

        // Add valid product to result list
        products.push_back(product);
        validCount++;
    }

    std::cout << "Productos válidos cargados: " << validCount << std::endl;
    std::cout << "Filas omitidas: " << skippedCount << std::endl;

    file.close();
    return products;
}