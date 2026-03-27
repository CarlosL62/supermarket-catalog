cmake_minimum_required(VERSION 4.1)
project(supermarket_catalog)

set(CMAKE_CXX_STANDARD 20)

add_executable(supermarket_catalog src/main.cpp
        include/models/Product.h
        include/Services/CatalogService.h
        src/services/CatalogService.cpp
        include/structures/UnorderedLinkedList.h
        src/structures/UnorderedLinkedList.cpp
        include/structures/BaseLinkedList.h
        include/structures/OrderedLinkedList.h
        src/structures/BaseLinkedList.cpp
        src/structures/OrderedLinkedList.cpp
        include/structures/HashTable.h
        src/structures/HashTable.cpp
        include/structures/AVLTree.h
        src/structures/AVLTree.cpp
        include/utils/CSVLoader.h
        src/utils/CSVLoader.cpp
        include/structures/BTree.h
        src/structures/BTree.cpp
)
