cmake_minimum_required(VERSION 4.1)
project(supermarket_catalog)

set(CMAKE_CXX_STANDARD 20)

add_executable(supermarket_catalog src/main.cpp
        include/models/Product.h
        include/Services/CatalogService.h
        src/services/CatalogService.cpp
)
