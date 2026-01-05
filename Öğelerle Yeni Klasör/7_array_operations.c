#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Array structure
typedef struct {
    int arr[MAX_SIZE];
    int size;
    int capacity;
} Array;

// Initialize array
void initArray(Array* a) {
    a->size = 0;
    a->capacity = MAX_SIZE;
}

// Display array
void display(Array* a) {
    if (a->size == 0) {
        printf("Array is empty!\n");
        return;
    }
    
    printf("\nArray: [");
    for (int i = 0; i < a->size; i++) {
        printf("%d", a->arr[i]);
        if (i < a->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
    printf("Size: %d, Capacity: %d\n", a->size, a->capacity);
}

// Display with indices
void displayWithIndices(Array* a) {
    if (a->size == 0) {
        printf("Array is empty!\n");
        return;
    }
    
    printf("\nIndex: ");
    for (int i = 0; i < a->size; i++) {
        printf("%4d ", i);
    }
    printf("\nValue: ");
    for (int i = 0; i < a->size; i++) {
        printf("%4d ", a->arr[i]);
    }
    printf("\n");
}

// Insert at end
void insertAtEnd(Array* a, int value) {
    if (a->size >= a->capacity) {
        printf("Array is full! Cannot insert.\n");
        return;
    }
    
    a->arr[a->size] = value;
    a->size++;
    
    printf("Inserted %d at end (index %d)\n", value, a->size - 1);
}

// Insert at beginning
void insertAtBeginning(Array* a, int value) {
    if (a->size >= a->capacity) {
        printf("Array is full! Cannot insert.\n");
        return;
    }
    
    // Shift all elements to the right
    for (int i = a->size; i > 0; i--) {
        a->arr[i] = a->arr[i - 1];
    }
    
    a->arr[0] = value;
    a->size++;
    
    printf("Inserted %d at beginning (shifted %d elements)\n", value, a->size - 1);
}

// Insert at specific position
void insertAtPosition(Array* a, int value, int position) {
    if (a->size >= a->capacity) {
        printf("Array is full! Cannot insert.\n");
        return;
    }
    
    if (position < 0 || position > a->size) {
        printf("Invalid position! Valid range: 0 to %d\n", a->size);
        return;
    }
    
    // Shift elements from position to end
    for (int i = a->size; i > position; i--) {
        a->arr[i] = a->arr[i - 1];
    }
    
    a->arr[position] = value;
    a->size++;
    
    printf("Inserted %d at position %d (shifted %d elements)\n", 
           value, position, a->size - position - 1);
}

// Insert in sorted array (maintains sorted order)
void insertSorted(Array* a, int value) {
    if (a->size >= a->capacity) {
        printf("Array is full! Cannot insert.\n");
        return;
    }
    
    int position = 0;
    // Find the correct position
    while (position < a->size && a->arr[position] < value) {
        position++;
    }
    
    // Shift elements
    for (int i = a->size; i > position; i--) {
        a->arr[i] = a->arr[i - 1];
    }
    
    a->arr[position] = value;
    a->size++;
    
    printf("Inserted %d at position %d (maintaining sorted order)\n", value, position);
}

// Delete from end
void deleteFromEnd(Array* a) {
    if (a->size == 0) {
        printf("Array is empty! Cannot delete.\n");
        return;
    }
    
    int deletedValue = a->arr[a->size - 1];
    a->size--;
    
    printf("Deleted %d from end\n", deletedValue);
}

// Delete from beginning
void deleteFromBeginning(Array* a) {
    if (a->size == 0) {
        printf("Array is empty! Cannot delete.\n");
        return;
    }
    
    int deletedValue = a->arr[0];
    
    // Shift all elements to the left
    for (int i = 0; i < a->size - 1; i++) {
        a->arr[i] = a->arr[i + 1];
    }
    
    a->size--;
    
    printf("Deleted %d from beginning (shifted %d elements left)\n", 
           deletedValue, a->size);
}

// Delete from specific position
void deleteFromPosition(Array* a, int position) {
    if (a->size == 0) {
        printf("Array is empty! Cannot delete.\n");
        return;
    }
    
    if (position < 0 || position >= a->size) {
        printf("Invalid position! Valid range: 0 to %d\n", a->size - 1);
        return;
    }
    
    int deletedValue = a->arr[position];
    
    // Shift elements from position+1 to end
    for (int i = position; i < a->size - 1; i++) {
        a->arr[i] = a->arr[i + 1];
    }
    
    a->size--;
    
    printf("Deleted %d from position %d (shifted %d elements left)\n", 
           deletedValue, position, a->size - position);
}

// Delete by value (first occurrence)
void deleteByValue(Array* a, int value) {
    if (a->size == 0) {
        printf("Array is empty! Cannot delete.\n");
        return;
    }
    
    int position = -1;
    for (int i = 0; i < a->size; i++) {
        if (a->arr[i] == value) {
            position = i;
            break;
        }
    }
    
    if (position == -1) {
        printf("Value %d not found in array!\n", value);
        return;
    }
    
    deleteFromPosition(a, position);
}

// Delete all occurrences of a value
void deleteAllOccurrences(Array* a, int value) {
    if (a->size == 0) {
        printf("Array is empty! Cannot delete.\n");
        return;
    }
    
    int count = 0;
    int writeIndex = 0;
    
    for (int readIndex = 0; readIndex < a->size; readIndex++) {
        if (a->arr[readIndex] != value) {
            a->arr[writeIndex] = a->arr[readIndex];
            writeIndex++;
        } else {
            count++;
        }
    }
    
    a->size = writeIndex;
    
    if (count > 0) {
        printf("Deleted %d occurrence(s) of value %d\n", count, value);
    } else {
        printf("Value %d not found in array!\n", value);
    }
}

// Search for value (linear search)
int search(Array* a, int value) {
    for (int i = 0; i < a->size; i++) {
        if (a->arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Binary search (for sorted arrays)
int binarySearch(Array* a, int value) {
    int left = 0;
    int right = a->size - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (a->arr[mid] == value) {
            return mid;
        }
        
        if (a->arr[mid] < value) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1;
}

// Reverse array
void reverse(Array* a) {
    if (a->size == 0) {
        printf("Array is empty!\n");
        return;
    }
    
    for (int i = 0; i < a->size / 2; i++) {
        int temp = a->arr[i];
        a->arr[i] = a->arr[a->size - 1 - i];
        a->arr[a->size - 1 - i] = temp;
    }
    
    printf("Array reversed!\n");
}

// Find minimum
int findMin(Array* a) {
    if (a->size == 0) {
        printf("Array is empty!\n");
        return -1;
    }
    
    int min = a->arr[0];
    for (int i = 1; i < a->size; i++) {
        if (a->arr[i] < min) {
            min = a->arr[i];
        }
    }
    return min;
}

// Find maximum
int findMax(Array* a) {
    if (a->size == 0) {
        printf("Array is empty!\n");
        return -1;
    }
    
    int max = a->arr[0];
    for (int i = 1; i < a->size; i++) {
        if (a->arr[i] > max) {
            max = a->arr[i];
        }
    }
    return max;
}

// Demo function
void demo() {
    Array arr;
    initArray(&arr);
    
    printf("\n=== ARRAY OPERATIONS DEMO ===\n");
    
    printf("\n--- Insertion at End ---\n");
    insertAtEnd(&arr, 10);
    insertAtEnd(&arr, 20);
    insertAtEnd(&arr, 30);
    display(&arr);
    displayWithIndices(&arr);
    
    printf("\n--- Insertion at Beginning ---\n");
    insertAtBeginning(&arr, 5);
    display(&arr);
    displayWithIndices(&arr);
    
    printf("\n--- Insertion at Position ---\n");
    insertAtPosition(&arr, 15, 2);
    display(&arr);
    displayWithIndices(&arr);
    
    printf("\n--- Insertion at Position (End) ---\n");
    insertAtPosition(&arr, 40, arr.size);
    display(&arr);
    
    printf("\n--- Delete from End ---\n");
    deleteFromEnd(&arr);
    display(&arr);
    
    printf("\n--- Delete from Beginning ---\n");
    deleteFromBeginning(&arr);
    display(&arr);
    
    printf("\n--- Delete from Position ---\n");
    deleteFromPosition(&arr, 1);
    display(&arr);
    displayWithIndices(&arr);
    
    printf("\n--- Delete by Value ---\n");
    deleteByValue(&arr, 20);
    display(&arr);
    
    printf("\n--- Search Operations ---\n");
    int searchValue = 15;
    int pos = search(&arr, searchValue);
    if (pos != -1) {
        printf("Value %d found at index %d\n", searchValue, pos);
    } else {
        printf("Value %d not found\n", searchValue);
    }
    
    printf("\n--- Additional Elements ---\n");
    insertAtEnd(&arr, 25);
    insertAtEnd(&arr, 35);
    insertAtEnd(&arr, 25);
    insertAtEnd(&arr, 45);
    display(&arr);
    
    printf("\n--- Delete All Occurrences ---\n");
    deleteAllOccurrences(&arr, 25);
    display(&arr);
    
    printf("\n--- Reverse Array ---\n");
    reverse(&arr);
    display(&arr);
    
    printf("\n--- Min/Max ---\n");
    printf("Minimum: %d\n", findMin(&arr));
    printf("Maximum: %d\n", findMax(&arr));
    
    printf("\n--- Sorted Insertion Demo ---\n");
    Array sortedArr;
    initArray(&sortedArr);
    insertSorted(&sortedArr, 30);
    insertSorted(&sortedArr, 10);
    insertSorted(&sortedArr, 50);
    insertSorted(&sortedArr, 20);
    insertSorted(&sortedArr, 40);
    display(&sortedArr);
    
    printf("\n--- Binary Search on Sorted Array ---\n");
    int searchVal = 30;
    int idx = binarySearch(&sortedArr, searchVal);
    if (idx != -1) {
        printf("Value %d found at index %d (binary search)\n", searchVal, idx);
    } else {
        printf("Value %d not found\n", searchVal);
    }
}

// Interactive menu
void interactiveMode() {
    Array arr;
    initArray(&arr);
    int choice, value, position;
    
    while (1) {
        printf("\n=== ARRAY OPERATIONS ===\n");
        printf("1.  Insert at End\n");
        printf("2.  Insert at Beginning\n");
        printf("3.  Insert at Position\n");
        printf("4.  Delete from End\n");
        printf("5.  Delete from Beginning\n");
        printf("6.  Delete from Position\n");
        printf("7.  Delete by Value\n");
        printf("8.  Delete All Occurrences\n");
        printf("9.  Display Array\n");
        printf("10. Display with Indices\n");
        printf("11. Search Value\n");
        printf("12. Reverse Array\n");
        printf("13. Find Min/Max\n");
        printf("0.  Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtEnd(&arr, value);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtBeginning(&arr, value);
                break;
            case 3:
                printf("Enter value: ");
                scanf("%d", &value);
                printf("Enter position (0-%d): ", arr.size);
                scanf("%d", &position);
                insertAtPosition(&arr, value, position);
                break;
            case 4:
                deleteFromEnd(&arr);
                break;
            case 5:
                deleteFromBeginning(&arr);
                break;
            case 6:
                printf("Enter position (0-%d): ", arr.size - 1);
                scanf("%d", &position);
                deleteFromPosition(&arr, position);
                break;
            case 7:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                deleteByValue(&arr, value);
                break;
            case 8:
                printf("Enter value to delete all: ");
                scanf("%d", &value);
                deleteAllOccurrences(&arr, value);
                break;
            case 9:
                display(&arr);
                break;
            case 10:
                displayWithIndices(&arr);
                break;
            case 11:
                printf("Enter value to search: ");
                scanf("%d", &value);
                position = search(&arr, value);
                if (position != -1) {
                    printf("Found at index %d\n", position);
                } else {
                    printf("Not found\n");
                }
                break;
            case 12:
                reverse(&arr);
                break;
            case 13:
                printf("Min: %d, Max: %d\n", findMin(&arr), findMax(&arr));
                break;
            case 0:
                return;
            default:
                printf("Invalid choice!\n");
        }
    }
}

int main() {
    int choice;
    
    printf("==================================================\n");
    printf("      ARRAY INSERTION & DELETION OPERATIONS\n");
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
