#include <stdio.h>
#include <stdlib.h>

// Node structure for doubly linked list
typedef struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
} Node;

// Create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Insert at beginning
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        printf("Inserted %d (list was empty)\n", data);
        return;
    }
    
    newNode->next = *head;
    (*head)->prev = newNode;
    *head = newNode;
    
    printf("Inserted %d at beginning\n", data);
}

// Insert at end
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    
    if (*head == NULL) {
        *head = newNode;
        printf("Inserted %d (list was empty)\n", data);
        return;
    }
    
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    temp->next = newNode;
    newNode->prev = temp;
    
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
    
    for (int i = 1; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Position out of range!\n");
        free(newNode);
        return;
    }
    
    newNode->next = temp->next;
    newNode->prev = temp;
    
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    
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
    while (temp != NULL && temp->data != afterValue) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Value %d not found in list!\n", afterValue);
        return;
    }
    
    Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    
    temp->next = newNode;
    
    printf("Inserted %d after %d\n", data, afterValue);
}

// Insert before specific value
void insertBeforeValue(Node** head, int data, int beforeValue) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* temp = *head;
    while (temp != NULL && temp->data != beforeValue) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Value %d not found in list!\n", beforeValue);
        return;
    }
    
    Node* newNode = createNode(data);
    newNode->next = temp;
    newNode->prev = temp->prev;
    
    if (temp->prev != NULL) {
        temp->prev->next = newNode;
    } else {
        *head = newNode;
    }
    
    temp->prev = newNode;
    
    printf("Inserted %d before %d\n", data, beforeValue);
}

// Delete from beginning
void deleteFromBeginning(Node** head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* temp = *head;
    int data = temp->data;
    
    *head = temp->next;
    
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    
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
    
    if (temp->next == NULL) {
        int data = temp->data;
        free(temp);
        *head = NULL;
        printf("Deleted %d from end (list is now empty)\n", data);
        return;
    }
    
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    int data = temp->data;
    temp->prev->next = NULL;
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
    
    for (int i = 1; i < position && temp != NULL; i++) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Position out of range!\n");
        return;
    }
    
    int data = temp->data;
    
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    }
    
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    
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
    
    while (temp != NULL && temp->data != value) {
        temp = temp->next;
    }
    
    if (temp == NULL) {
        printf("Value %d not found!\n", value);
        return;
    }
    
    if (temp->prev != NULL) {
        temp->prev->next = temp->next;
    } else {
        *head = temp->next;
    }
    
    if (temp->next != NULL) {
        temp->next->prev = temp->prev;
    }
    
    free(temp);
    printf("Deleted value %d\n", value);
}

// Forward traversal
void traverseForward(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    printf("\nForward traversal: ");
    Node* temp = head;
    printf("NULL <-> ");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->next != NULL) {
            printf(" <-> ");
        }
        temp = temp->next;
    }
    printf(" <-> NULL\n");
}

// Backward traversal
void traverseBackward(Node* head) {
    if (head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    // Go to last node
    Node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    
    printf("Backward traversal: ");
    printf("NULL <-> ");
    while (temp != NULL) {
        printf("%d", temp->data);
        if (temp->prev != NULL) {
            printf(" <-> ");
        }
        temp = temp->prev;
    }
    printf(" <-> NULL\n");
}

// Display with details
void displayDetailed(Node* head) {
    if (head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    
    printf("\nDetailed view:\n");
    printf("%-10s %-10s %-10s %-10s\n", "Address", "Prev", "Data", "Next");
    printf("--------------------------------------------------\n");
    
    Node* temp = head;
    while (temp != NULL) {
        printf("%-10p %-10p %-10d %-10p\n", 
               (void*)temp, 
               (void*)temp->prev, 
               temp->data, 
               (void*)temp->next);
        temp = temp->next;
    }
}

// Count nodes
int countNodes(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Search for value
int search(Node* head, int value) {
    int position = 1;
    Node* temp = head;
    
    while (temp != NULL) {
        if (temp->data == value) {
            return position;
        }
        position++;
        temp = temp->next;
    }
    
    return -1;
}

// Reverse the list
void reverse(Node** head) {
    if (*head == NULL) {
        printf("List is empty!\n");
        return;
    }
    
    Node* temp = NULL;
    Node* current = *head;
    
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }
    
    if (temp != NULL) {
        *head = temp->prev;
    }
    
    printf("List reversed!\n");
}

// Clear entire list
void clearList(Node** head) {
    Node* current = *head;
    Node* next;
    
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    
    *head = NULL;
    printf("List cleared!\n");
}

// Demo function
void demo() {
    Node* head = NULL;
    
    printf("\n=== DOUBLE LINKED LIST DEMO ===\n");
    
    printf("\n--- Insertion Operations ---\n");
    insertAtEnd(&head, 10);
    insertAtEnd(&head, 20);
    insertAtEnd(&head, 30);
    traverseForward(head);
    
    insertAtBeginning(&head, 5);
    traverseForward(head);
    
    insertAtPosition(&head, 15, 3);
    traverseForward(head);
    
    insertAfterValue(&head, 25, 20);
    traverseForward(head);
    
    insertBeforeValue(&head, 12, 15);
    traverseForward(head);
    
    printf("\n--- Traversal Operations ---\n");
    traverseForward(head);
    traverseBackward(head);
    displayDetailed(head);
    
    printf("\n--- Deletion Operations ---\n");
    deleteFromBeginning(&head);
    traverseForward(head);
    
    deleteFromEnd(&head);
    traverseForward(head);
    
    deleteFromPosition(&head, 2);
    traverseForward(head);
    
    deleteValue(&head, 20);
    traverseForward(head);
    
    printf("\n--- Other Operations ---\n");
    printf("Total nodes: %d\n", countNodes(head));
    
    int searchValue = 15;
    int pos = search(head, searchValue);
    if (pos != -1) {
        printf("Value %d found at position %d\n", searchValue, pos);
    } else {
        printf("Value %d not found\n", searchValue);
    }
    
    reverse(&head);
    traverseForward(head);
    
    clearList(&head);
}

// Interactive menu
void interactiveMode() {
    Node* head = NULL;
    int choice, data, position, value;
    
    while (1) {
        printf("\n=== DOUBLE LINKED LIST OPERATIONS ===\n");
        printf("1.  Insert at Beginning\n");
        printf("2.  Insert at End\n");
        printf("3.  Insert at Position\n");
        printf("4.  Insert After Value\n");
        printf("5.  Insert Before Value\n");
        printf("6.  Delete from Beginning\n");
        printf("7.  Delete from End\n");
        printf("8.  Delete from Position\n");
        printf("9.  Delete by Value\n");
        printf("10. Forward Traversal\n");
        printf("11. Backward Traversal\n");
        printf("12. Display Detailed\n");
        printf("13. Count Nodes\n");
        printf("14. Search Value\n");
        printf("15. Reverse List\n");
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
                traverseForward(head);
                break;
            case 11:
                traverseBackward(head);
                break;
            case 12:
                displayDetailed(head);
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
                reverse(&head);
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
    printf("      DOUBLE LINKED LIST IMPLEMENTATION\n");
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
