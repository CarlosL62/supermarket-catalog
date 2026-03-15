#include "../../include/structures/OrderedLinkedList.h"

void OrderedLinkedList::insert(const Product& product) {
    ListNode* newNode = new ListNode(product);

    if (isEmpty() || product.name < head->data.name) {
        newNode->next = head;
        head = newNode;
        return;
    }

    ListNode* current = head;
    while (current->next != nullptr && current->next->data.name < product.name) {
        current = current->next;
    }
    newNode->next = current->next;
    current->next = newNode;
}