#include <iostream>
#include "../../include/structures/BaseLinkedList.h"

BaseLinkedList::BaseLinkedList() : head(nullptr) {}

BaseLinkedList::~BaseLinkedList() {
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

bool BaseLinkedList::isEmpty() const {
    return head == nullptr;
}

Product *BaseLinkedList::searchByName(const std::string &name) {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->data.name == name) {
            return &current->data;
        }
        current = current->next;
    }

    return nullptr;
}

Product *BaseLinkedList::searchByBarcode(const std::string &barcode) {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->data.barcode == barcode) {
            return &current->data;
        }
        current = current->next;
    }

    return nullptr;
}

bool BaseLinkedList::removeByBarcode(const std::string &barcode) {
    if (isEmpty()) {
        return false;
    }

    if (head->data.barcode == barcode) {
        ListNode* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
        return true;
    }

    ListNode* current = head;
    while (current->next != nullptr && current->next->data.barcode != barcode) {
        current = current->next;
    }

    if (current->next == nullptr) {
        return false;
    }

    ListNode* nodeToDelete = current->next;
    current->next = nodeToDelete->next;
    delete nodeToDelete;
    return true;
}

void BaseLinkedList::display() const {
    if (isEmpty()) {
        std::cout << "La lista está vacía." << std::endl;
        return;
    }

    ListNode* current = head;
    while (current != nullptr) {
        std::cout << "Nombre: " << current->data.name << std::endl;
        std::cout << "Código: " << current->data.barcode << std::endl;
        std::cout << "Categoría: " << current->data.category << std::endl;
        std::cout << "Fecha de expiración: " << current->data.expiryDate << std::endl;
        std::cout << "Marca: " << current->data.brand << std::endl;
        std::cout << "Precio: " << current->data.price << std::endl;
        std::cout << "Stock: " << current->data.stock << std::endl;
        std::cout << "-----------------------------" << std::endl;

        current = current->next;
    }
}
