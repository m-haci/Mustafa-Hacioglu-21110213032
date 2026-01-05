#include <stdio.h>
#include <stdlib.h>

// Node structure for circular linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    
    if (*head == NULL) {
        newNode->next = newNode; // Points to itself
        *head = newNode;
        printf("Inserted %d (first node - circular)\n", data);
        return;
    }
    
    // Find last node
    Node* temp = *head;
    while (temp->next != *head) {
        temp = temp->next;
    }
    
    newNode->next = *head;
    temp->next = newNode;
    *head = newNode;
    
    printf("Inserted %d at beginning\n", data);
}

// Insert at end
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    
    if (*head == NULL) {
        newNode->next = newNode;
        *head = newNode;
        printf("Inserted %d (first node - circular)\n", data);
        return;
    }
    
    Node* temp = *head;
    while (temp->next != *head) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->next = *head;
    
    printf("Inserted %d at end\n", data);
}

// Insert at specific position
void insertAtPosition(Node** head, int data, int position) {
    if (position < 1) {
        printf("Invalid position!\n");
        return;
    }
    
    if (position == 1) {
        insertAtBeginning(head, data);
        return;
    }
    
    Node* newNode = createNode(data);
    Node* temp = *head;
    
    for (int i = 1; i < position - 1; i++) {
        temp = temp->next;
        if (temp == *head) {
            printf("Position out of range!\n");
            free(newNode);
            return;
        }
    }
    
    newNode->next = temp->next;
    temp->next = newNode;
    
    printf("Inserted %d at position %d\n", data, position);
}

// Insert after specific value
void insertAfterValue(Node** head, int data, int afterValue) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* temp = *head;
    do {
        if (temp->data == afterValue) {
            Node* newNode = createNode(data);
            newNode->next = temp->next;
            temp->next = newNode;
            printf("Inserted %d after %d\n", data, afterValue);
            return;
        }
        temp = temp->next;
    } while (temp != *head);
    
    printf("Value %d not found!\n", afterValue);
}

// Insert before specific value
void insertBeforeValue(Node** head, int data, int beforeValue) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    // Special case: insert before head
    if ((*head)->data == beforeValue) {
        insertAtBeginning(head, data);
        return;
    }
    
    Node* temp = *head;
    do {
        if (temp->next->data == beforeValue) {
            Node* newNode = createNode(data);
            newNode->next = temp->next;
            temp->next = newNode;
            printf("Inserted %d before %d\n", data, beforeValue);
            return;
        }
        temp = temp->next;
    } while (temp != *head);
    
    printf("Value %d not found!\n", beforeValue);
}

// Delete from beginning
void deleteFromBeginning(Node** head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* temp = *head;
    int data = temp->data;
    
    // Only one node
    if (temp->next == *head) {
        free(temp);
        *head = NULL;
        printf("Deleted %d (list is now empty)\n", data);
        return;
    }
    
    // Find last node
    Node* last = *head;
    while (last->next != *head) {
        last = last->next;
    }
    
    *head = temp->next;
    last->next = *head;
    free(temp);
    
    printf("Deleted %d from beginning\n", data);
}

// Delete from end
void deleteFromEnd(Node** head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* temp = *head;
    
    // Only one node
    if (temp->next == *head) {
        int data = temp->data;
        free(temp);
        *head = NULL;
        printf("Deleted %d (list is now empty)\n", data);
        return;
    }
    
    // Find second last node
    Node* prev = NULL;
    while (temp->next != *head) {
        prev = temp;
        temp = temp->next;
    }
    
    int data = temp->data;
    prev->next = *head;
    free(temp);
    
    printf("Deleted %d from end\n", data);
}

// Delete from specific position
void deleteFromPosition(Node** head, int position) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    if (position < 1) {
        printf("Invalid position!\n");
        return;
    }
    
    if (position == 1) {
        deleteFromBeginning(head);
        return;
    }
    
    Node* temp = *head;
    Node* prev = NULL;
    
    for (int i = 1; i < position; i++) {
        prev = temp;
        temp = temp->next;
        if (temp == *head) {
            printf("Position out of range!\n");
            return;
        }
    }
    
    int data = temp->data;
    prev->next = temp->next;
    free(temp);
    
    printf("Deleted %d from position %d\n", data, position);
}

// Delete specific value
void deleteValue(Node** head, int value) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* temp = *head;
    Node* prev = NULL;
    
    // Check if head node contains the value
    if (temp->data == value) {
        deleteFromBeginning(head);
        return;
    }
    
    // Search for the value
    do {
        prev = temp;
        temp = temp->next;
        if (temp->data == value) {
            prev->next = temp->next;
            free(temp);
            printf("Deleted value %d\n", value);
            return;
        }
    } while (temp != *head);
    
    printf("Value %d not found!\n", value);
}

// Traversal (display)
void traverse(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    printf("\nCircular traversal: ");
    Node* temp = head;
    do {
        printf("%d", temp->data);
        if (temp->next != head) {
            printf(" -> ");
        }
        temp = temp->next;
    } while (temp != head);
    printf(" -> (back to %d)\n", head->data);
}

// Display detailed view showing circular nature
void displayDetailed(Node* head) {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    
    printf("\nDetailed view:\n");
    printf("%-15s %-10s %-15s\n", "Address", "Data", "Next");
    printf("------------------------------------------------\n");
    
    Node* temp = head;
    do {
        printf("%-15p %-10d %-15p", (void*)temp, temp->data, (void*)temp->next);
        if (temp->next == head) {
            printf(" <- HEAD");
        }
        printf("\n");
        temp = temp->next;
    } while (temp != head);
}

// Display as circular diagram
void displayCircular(Node* head) {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    
    printf("\nCircular visualization:\n");
    printf("     ┌─────────────────────┐\n");
    printf("     │                     ↓\n");
    
    Node* temp = head;
    int count = 0;
    do {
        if (count == 0) {
            printf("HEAD → ");
        }
        printf("[%d]", temp->data);
        temp = temp->next;
        if (temp != head) {
            printf(" → ");
        }
        count++;
    } while (temp != head);
    
    printf("\n     ↑                     │\n");
    printf("     └─────────────────────┘\n");
}

// Count nodes
int countNodes(Node* head) {
    if (head == NULL) {
        return 0;
    }
    
    int count = 0;
    Node* temp = head;
    do {
        count++;
        temp = temp->next;
    } while (temp != head);
    
    return count;
}

// Search for value
int search(Node* head, int value) {
    if (head == NULL) {
        return -1;
    }
    
    int position = 1;
    Node* temp = head;
    
    do {
        if (temp->data == value) {
            return position;
        }
        position++;
        temp = temp->next;
    } while (temp != head);
    
    return -1;
}

// Check if list is circular (verification)
int isCircular(Node* head) {
    if (head == NULL) {
        return 1; // Empty list is considered circular
    }
    
    Node* temp = head->next;
    while (temp != NULL && temp != head) {
        temp = temp->next;
    }
    
    return (temp == head);
}

// Split circular list into two halves
void splitList(Node* head, Node** head1, Node** head2) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* slow = head;
    Node* fast = head;
    
    // Find middle using slow and fast pointers
    while (fast->next != head && fast->next->next != head) {
        slow = slow->next;
        fast = fast->next->next;
    }
    
    // If even number of nodes
    if (fast->next->next == head) {
        fast = fast->next;
    }
    
    // Set head of first half
    *head1 = head;
    
    // Set head of second half
    if (head->next != head) {
        *head2 = slow->next;
    }
    
    // Make first half circular
    fast->next = slow->next;
    
    // Make second half circular
    slow->next = head;
    
    printf("List split into two circular lists!\n");
}

// Clear entire list
void clearList(Node** head) {
    if (*head == NULL) {
        printf("List is already empty!\n");
        return;
    }
    
    Node* current = *head;
    Node* next;
    Node* firstNode = *head;
    
    do {
        next = current->next;
        free(current);
        current = next;
    } while (current != firstNode);
    
    *head = NULL;
    printf("List cleared!\n");
}

// Demo function
void demo() {
    Node* head = NULL;
    
    printf("\n=== CIRCULAR LINKED LIST DEMO ===\n");
    
    printf("\n--- Insertion Operations ---\n");
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    traverse(head);
    displayCircular(head);
    
    insertAtBeginning(&head, 5);
    traverse(head);
    
    insertAtPosition(&head, 15, 3);
    traverse(head);
    
    insertAfterValue(&head, 25, 20);
    traverse(head);
    
    insertBeforeValue(&head, 12, 15);
    traverse(head);
    displayCircular(head);
    
    printf("\n--- Detailed Display ---\n");
    displayDetailed(head);
    
    printf("\n--- Verification ---\n");
    printf("Is list circular? %s\n", isCircular(head) ? "YES" : "NO");
    printf("Total nodes: %d\n", countNodes(head));
    
    printf("\n--- Search Operation ---\n");
    int searchValue = 20;
    int pos = search(head, searchValue);
    if (pos != -1) {
        printf("Value %d found at position %d\n", searchValue, pos);
    } else {
        printf("Value %d not found\n", searchValue);
    }
    
    printf("\n--- Deletion Operations ---\n");
    deleteFromBeginning(&head);
    traverse(head);
    
    deleteFromEnd(&head);
    traverse(head);
    
    deleteFromPosition(&head, 2);
    traverse(head);
    
    deleteValue(&head, 20);
    traverse(head);
    displayCircular(head);
    
    printf("\n--- Split List Demo ---\n");
    // Create a fresh list for splitting
    clearList(&head);
    for (int i = 1; i <= 6; i++) {
        insertAtEnd(&head, i * 10);
    }
    printf("Original list:\n");
    traverse(head);
    
    Node* head1 = NULL;
    Node* head2 = NULL;
    splitList(head, &head1, &head2);
    
    printf("\nFirst half:\n");
    traverse(head1);
    printf("Second half:\n");
    traverse(head2);
    
    clearList(&head1);
    clearList(&head2);
}

// Interactive menu
void interactiveMode() {
    Node* head = NULL;
    int choice, data, position, value;
    
    while (1) {
        printf("\n=== CIRCULAR LINKED LIST OPERATIONS ===\n");
        printf("1.  Insert at Beginning\n");
        printf("2.  Insert at End\n");
        printf("3.  Insert at Position\n");
        printf("4.  Insert After Value\n");
        printf("5.  Insert Before Value\n");
        printf("6.  Delete from Beginning\n");
        printf("7.  Delete from End\n");
        printf("8.  Delete from Position\n");
        printf("9.  Delete by Value\n");
        printf("10. Traverse\n");
        printf("11. Display Detailed\n");
        printf("12. Display Circular Diagram\n");
        printf("13. Count Nodes\n");
        printf("14. Search Value\n");
        printf("15. Verify Circular\n");
        printf("16. Clear List\n");
        printf("0.  Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtBeginning(&head, data);
                break;
            case 2:
                printf("Enter data: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;
            case 3:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Enter position: ");
                scanf("%d", &position);
                insertAtPosition(&head, data, position);
                break;
            case 4:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Insert after value: ");
                scanf("%d", &value);
                insertAfterValue(&head, data, value);
                break;
            case 5:
                printf("Enter data: ");
                scanf("%d", &data);
                printf("Insert before value: ");
                scanf("%d", &value);
                insertBeforeValue(&head, data, value);
                break;
            case 6:
                deleteFromBeginning(&head);
                break;
            case 7:
                deleteFromEnd(&head);
                break;
            case 8:
                printf("Enter position: ");
                scanf("%d", &position);
                deleteFromPosition(&head, position);
                break;
            case 9:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteValue(&head, value);
                break;
            case 10:
                traverse(head);
                break;
            case 11:
                displayDetailed(head);
                break;
            case 12:
                displayCircular(head);
                break;
            case 13:
                printf("Total nodes: %d\n", countNodes(head));
                break;
            case 14:
                printf("Enter value to search: ");
                scanf("%d", &value);
                position = search(head, value);
                if (position != -1) {
                    printf("Found at position %d\n", position);
                } else {
                    printf("Not found\n");
                }
                break;
            case 15:
                printf("Is circular? %s\n", isCircular(head) ? "YES" : "NO");
                break;
            case 16:
                clearList(&head);
                break;
            case 0:
                clearList(&head);
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {
    int choice;
    
    printf("==================================================\n");
    printf("     CIRCULAR LINKED LIST IMPLEMENTATION\n");
    printf("==================================================\n\n");
    
    printf("1. Interactive Mode\n");
    printf("2. Demo Mode\n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    if (choice == 1) {
        interactiveMode();
    } else if (choice == 2) {
        demo();
    } else {
        printf("Invalid choice!\n");
    }
    
    return 0;
}
