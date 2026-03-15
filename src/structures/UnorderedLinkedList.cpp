#include "../../include/structures/UnorderedLinkedList.h"

void UnorderedLinkedList::insert(const Product& product) {
    ListNode* newNode = new ListNode(product);

    if (isEmpty()) {
        head = newNode;
        return;
    }

    ListNode* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }

    current->next = newNode;
}