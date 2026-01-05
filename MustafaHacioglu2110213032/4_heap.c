#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Heap structure
typedef struct {
    int arr[MAX_SIZE];
    int size;
    int capacity;
    int isMaxHeap; // 1 for max heap, 0 for min heap
} Heap;

// Initialize heap
void initHeap(Heap* h, int isMaxHeap) {
    h->size = 0;
    h->capacity = MAX_SIZE;
    h->isMaxHeap = isMaxHeap;
}

// Get parent index
int parent(int i) {
    return (i - 1) / 2;
}

// Get left child index
int leftChild(int i) {
    return 2 * i + 1;
}

// Get right child index
int rightChild(int i) {
    return 2 * i + 2;
}

// Swap two elements
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify up (for insertion)
void heapifyUp(Heap* h, int index) {
    if (index == 0) return;
    
    int parentIdx = parent(index);
    
    if (h->isMaxHeap) {
        // Max Heap: parent should be greater
        if (h->arr[parentIdx] < h->arr[index]) {
            swap(&h->arr[parentIdx], &h->arr[index]);
            heapifyUp(h, parentIdx);
        }
    } else {
        // Min Heap: parent should be smaller
        if (h->arr[parentIdx] > h->arr[index]) {
            swap(&h->arr[parentIdx], &h->arr[index]);
            heapifyUp(h, parentIdx);
        }
    }
}

// Heapify down (for deletion)
void heapifyDown(Heap* h, int index) {
    int left = leftChild(index);
    int right = rightChild(index);
    int target = index;
    
    if (h->isMaxHeap) {
        // Max Heap: find largest among root, left, right
        if (left < h->size && h->arr[left] > h->arr[target]) {
            target = left;
        }
        if (right < h->size && h->arr[right] > h->arr[target]) {
            target = right;
        }
    } else {
        // Min Heap: find smallest among root, left, right
        if (left < h->size && h->arr[left] < h->arr[target]) {
            target = left;
        }
        if (right < h->size && h->arr[right] < h->arr[target]) {
            target = right;
        }
    }
    
    if (target != index) {
        swap(&h->arr[index], &h->arr[target]);
        heapifyDown(h, target);
    }
}

// Insert element into heap
void insert(Heap* h, int value) {
    if (h->size >= h->capacity) {
        printf("Heap is full!\n");
        return;
    }
    
    h->arr[h->size] = value;
    h->size++;
    heapifyUp(h, h->size - 1);
    
    printf("Inserted %d\n", value);
}

// Extract root (max/min)
int extractRoot(Heap* h) {
    if (h->size == 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    
    int root = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    h->size--;
    heapifyDown(h, 0);
    
    return root;
}

// Peek root without removing
int peek(Heap* h) {
    if (h->size == 0) {
        printf("Heap is empty!\n");
        return -1;
    }
    return h->arr[0];
}

// Display heap as array
void displayArray(Heap* h) {
    printf("\nHeap array: [");
    for (int i = 0; i < h->size; i++) {
        printf("%d", h->arr[i]);
        if (i < h->size - 1) printf(", ");
    }
    printf("]\n");
}

// Display heap as tree (visual)
void displayTree(Heap* h, int index, int level) {
    if (index >= h->size) return;
    
    // Display right subtree
    displayTree(h, rightChild(index), level + 1);
    
    // Display current node
    for (int i = 0; i < level; i++) {
        printf("      ");
    }
    printf("%d\n", h->arr[index]);
    
    // Display left subtree
    displayTree(h, leftChild(index), level + 1);
}

// Build heap from array
void buildHeap(Heap* h, int arr[], int n) {
    h->size = n;
    for (int i = 0; i < n; i++) {
        h->arr[i] = arr[i];
    }
    
    // Start from last non-leaf node and heapify down
    for (int i = (n / 2) - 1; i >= 0; i--) {
        heapifyDown(h, i);
    }
}

// Heap sort
void heapSort(int arr[], int n, int ascending) {
    Heap h;
    // For ascending sort, use max heap
    // For descending sort, use min heap
    initHeap(&h, ascending ? 1 : 0);
    buildHeap(&h, arr, n);
    
    for (int i = n - 1; i >= 0; i--) {
        arr[i] = extractRoot(&h);
    }
}

// Get height of heap
int getHeight(Heap* h) {
    if (h->size == 0) return 0;
    int height = 0;
    int nodes = 1;
    int counted = 0;
    
    while (counted < h->size) {
        height++;
        counted += nodes;
        nodes *= 2;
    }
    return height;
}

// Check if heap property is satisfied
int isValidHeap(Heap* h) {
    for (int i = 0; i < h->size; i++) {
        int left = leftChild(i);
        int right = rightChild(i);
        
        if (h->isMaxHeap) {
            if (left < h->size && h->arr[i] < h->arr[left]) return 0;
            if (right < h->size && h->arr[i] < h->arr[right]) return 0;
        } else {
            if (left < h->size && h->arr[i] > h->arr[left]) return 0;
            if (right < h->size && h->arr[i] > h->arr[right]) return 0;
        }
    }
    return 1;
}

// Interactive menu for heap operations
void interactiveMode() {
    Heap heap;
    int choice, value, heapType;
    
    printf("\nSelect heap type:\n");
    printf("1. Max Heap\n");
    printf("2. Min Heap\n");
    printf("Choice: ");
    scanf("%d", &heapType);
    
    initHeap(&heap, heapType == 1);
    printf("\n%s created!\n", heapType == 1 ? "Max Heap" : "Min Heap");
    
    while (1) {
        printf("\n=== %s OPERATIONS ===\n", heapType == 1 ? "MAX HEAP" : "MIN HEAP");
        printf("1. Insert\n");
        printf("2. Extract %s\n", heapType == 1 ? "Max" : "Min");
        printf("3. Peek %s\n", heapType == 1 ? "Max" : "Min");
        printf("4. Display Array\n");
        printf("5. Display Tree\n");
        printf("6. Check Validity\n");
        printf("7. Get Size & Height\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insert(&heap, value);
                displayArray(&heap);
                break;
                
            case 2:
                value = extractRoot(&heap);
                if (value != -1) {
                    printf("Extracted: %d\n", value);
                    displayArray(&heap);
                }
                break;
                
            case 3:
                value = peek(&heap);
                if (value != -1) {
                    printf("Root value: %d\n", value);
                }
                break;
                
            case 4:
                displayArray(&heap);
                break;
                
            case 5:
                printf("\nTree visualization:\n");
                displayTree(&heap, 0, 0);
                break;
                
            case 6:
                if (isValidHeap(&heap)) {
                    printf("Valid %s property satisfied!\n", 
                           heapType == 1 ? "Max Heap" : "Min Heap");
                } else {
                    printf("Invalid heap!\n");
                }
                break;
                
            case 7:
                printf("Size: %d\n", heap.size);
                printf("Height: %d\n", getHeight(&heap));
                break;
                
            case 0:
                return;
                
            default:
                printf("Invalid choice!\n");
        }
    }
}

// Demo function
void demo() {
    printf("\n=== MAX HEAP DEMO ===\n");
    Heap maxHeap;
    initHeap(&maxHeap, 1);
    
    int values[] = {10, 20, 15, 40, 50, 100, 25, 45};
    int n = 8;
    
    printf("\nInserting values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        insert(&maxHeap, values[i]);
    }
    
    displayArray(&maxHeap);
    printf("\nTree structure:\n");
    displayTree(&maxHeap, 0, 0);
    
    printf("\nExtracting max elements:\n");
    for (int i = 0; i < 3; i++) {
        int max = extractRoot(&maxHeap);
        printf("Extracted: %d\n", max);
    }
    displayArray(&maxHeap);
    
    printf("\n\n=== MIN HEAP DEMO ===\n");
    Heap minHeap;
    initHeap(&minHeap, 0);
    
    printf("\nInserting same values: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", values[i]);
        insert(&minHeap, values[i]);
    }
    
    displayArray(&minHeap);
    printf("\nTree structure:\n");
    displayTree(&minHeap, 0, 0);
    
    printf("\nExtracting min elements:\n");
    for (int i = 0; i < 3; i++) {
        int min = extractRoot(&minHeap);
        printf("Extracted: %d\n", min);
    }
    displayArray(&minHeap);
    
    // Heap Sort demo
    printf("\n\n=== HEAP SORT DEMO ===\n");
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int size = 7;
    
    printf("Original array: ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    
    heapSort(arr, size, 1);
    printf("\nAscending sort:  ");
    for (int i = 0; i < size; i++) printf("%d ", arr[i]);
    
    int arr2[] = {64, 34, 25, 12, 22, 11, 90};
    heapSort(arr2, size, 0);
    printf("\nDescending sort: ");
    for (int i = 0; i < size; i++) printf("%d ", arr2[i]);
    printf("\n");
}

int main() {
    int choice;
    
    printf("==================================================\n");
    printf("         MAX HEAP & MIN HEAP IMPLEMENTATION\n");
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
