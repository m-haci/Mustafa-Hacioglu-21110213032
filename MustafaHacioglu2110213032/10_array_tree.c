#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_SIZE 100

// Binary Tree using array
typedef struct {
    int arr[MAX_SIZE];
    int size;
} ArrayTree;

// Initialize tree
void initTree(ArrayTree* t) {
    t->size = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        t->arr[i] = -1; // -1 indicates empty node
    }
}

// Parent index: (i-1)/2
int parent(int i) {
    return (i - 1) / 2;
}

// Left child index: 2*i + 1
int leftChild(int i) {
    return 2 * i + 1;
}

// Right child index: 2*i + 2
int rightChild(int i) {
    return 2 * i + 2;
}

// Insert at specific index
void insertAtIndex(ArrayTree* t, int index, int value) {
    if (index >= MAX_SIZE) {
        printf("Index out of bounds!\n");
        return;
    }
    
    if (t->arr[index] != -1) {
        printf("Position already occupied! Overwriting...\n");
    }
    
    t->arr[index] = value;
    if (index >= t->size) {
        t->size = index + 1;
    }
    
    printf("Inserted %d at index %d\n", value, index);
}

// Insert as complete binary tree (level-order)
void insertLevelOrder(ArrayTree* t, int value) {
    if (t->size >= MAX_SIZE) {
        printf("Tree is full!\n");
        return;
    }
    
    t->arr[t->size] = value;
    printf("Inserted %d at index %d\n", value, t->size);
    t->size++;
}

// Delete from index
void deleteAtIndex(ArrayTree* t, int index) {
    if (index >= t->size || t->arr[index] == -1) {
        printf("Invalid index!\n");
        return;
    }
    
    int value = t->arr[index];
    t->arr[index] = -1;
    printf("Deleted %d from index %d\n", value, index);
}

// Display array representation
void displayArray(ArrayTree* t) {
    printf("\nArray representation:\n");
    printf("Index: ");
    for (int i = 0; i < t->size; i++) {
        printf("%4d ", i);
    }
    printf("\nValue: ");
    for (int i = 0; i < t->size; i++) {
        if (t->arr[i] == -1) {
            printf("   - ");
        } else {
            printf("%4d ", t->arr[i]);
        }
    }
    printf("\n");
}

// Display tree structure (visual)
void displayTreeStructure(ArrayTree* t, int index, int level) {
    if (index >= t->size || t->arr[index] == -1) {
        return;
    }
    
    // Display right subtree
    displayTreeStructure(t, rightChild(index), level + 1);
    
    // Display current node
    for (int i = 0; i < level; i++) {
        printf("      ");
    }
    printf("%d\n", t->arr[index]);
    
    // Display left subtree
    displayTreeStructure(t, leftChild(index), level + 1);
}

// Display with parent-child relationships
void displayRelationships(ArrayTree* t) {
    printf("\nParent-Child Relationships:\n");
    printf("%-10s %-10s %-10s %-10s\n", "Index", "Value", "Left Child", "Right Child");
    printf("-------------------------------------------------------\n");
    
    for (int i = 0; i < t->size; i++) {
        if (t->arr[i] != -1) {
            printf("%-10d %-10d ", i, t->arr[i]);
            
            int left = leftChild(i);
            int right = rightChild(i);
            
            if (left < t->size && t->arr[left] != -1) {
                printf("%-10d ", t->arr[left]);
            } else {
                printf("%-10s ", "-");
            }
            
            if (right < t->size && t->arr[right] != -1) {
                printf("%-10d\n", t->arr[right]);
            } else {
                printf("%-10s\n", "-");
            }
        }
    }
}

// Preorder traversal (Root-Left-Right)
void preorder(ArrayTree* t, int index) {
    if (index >= t->size || t->arr[index] == -1) {
        return;
    }
    
    printf("%d ", t->arr[index]);
    preorder(t, leftChild(index));
    preorder(t, rightChild(index));
}

// Inorder traversal (Left-Root-Right)
void inorder(ArrayTree* t, int index) {
    if (index >= t->size || t->arr[index] == -1) {
        return;
    }
    
    inorder(t, leftChild(index));
    printf("%d ", t->arr[index]);
    inorder(t, rightChild(index));
}

// Postorder traversal (Left-Right-Root)
void postorder(ArrayTree* t, int index) {
    if (index >= t->size || t->arr[index] == -1) {
        return;
    }
    
    postorder(t, leftChild(index));
    postorder(t, rightChild(index));
    printf("%d ", t->arr[index]);
}

// Level-order traversal
void levelOrder(ArrayTree* t) {
    printf("Level-order: ");
    for (int i = 0; i < t->size; i++) {
        if (t->arr[i] != -1) {
            printf("%d ", t->arr[i]);
        }
    }
    printf("\n");
}

// Get height of tree
int getHeight(ArrayTree* t, int index) {
    if (index >= t->size || t->arr[index] == -1) {
        return -1;
    }
    
    int leftHeight = getHeight(t, leftChild(index));
    int rightHeight = getHeight(t, rightChild(index));
    
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Count nodes
int countNodes(ArrayTree* t) {
    int count = 0;
    for (int i = 0; i < t->size; i++) {
        if (t->arr[i] != -1) {
            count++;
        }
    }
    return count;
}

// Search for value
int search(ArrayTree* t, int value) {
    for (int i = 0; i < t->size; i++) {
        if (t->arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Check if tree is complete
int isComplete(ArrayTree* t) {
    int lastIndex = -1;
    
    // Find last non-empty index
    for (int i = 0; i < t->size; i++) {
        if (t->arr[i] != -1) {
            lastIndex = i;
        }
    }
    
    // Check if all indices before lastIndex are filled
    for (int i = 0; i < lastIndex; i++) {
        if (t->arr[i] == -1) {
            return 0;
        }
    }
    
    return 1;
}

// Demo 1: Complete binary tree
void demo1() {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║         DEMO 1: Complete Binary Tree Creation           ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    ArrayTree tree;
    initTree(&tree);
    
    printf("\nInserting nodes in level-order:\n");
    insertLevelOrder(&tree, 1);
    insertLevelOrder(&tree, 2);
    insertLevelOrder(&tree, 3);
    insertLevelOrder(&tree, 4);
    insertLevelOrder(&tree, 5);
    insertLevelOrder(&tree, 6);
    insertLevelOrder(&tree, 7);
    
    displayArray(&tree);
    
    printf("\nTree structure:\n");
    displayTreeStructure(&tree, 0, 0);
    
    displayRelationships(&tree);
    
    printf("\nTraversals:\n");
    printf("Preorder:  ");
    preorder(&tree, 0);
    printf("\nInorder:   ");
    inorder(&tree, 0);
    printf("\nPostorder: ");
    postorder(&tree, 0);
    printf("\n");
    levelOrder(&tree);
    
    printf("\nTree properties:\n");
    printf("Height: %d\n", getHeight(&tree, 0));
    printf("Total nodes: %d\n", countNodes(&tree));
    printf("Is complete? %s\n", isComplete(&tree) ? "YES" : "NO");
}

// Demo 2: Custom tree structure
void demo2() {
    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║         DEMO 2: Custom Tree Structure                   ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    ArrayTree tree;
    initTree(&tree);
    
    printf("\nCreating custom tree structure:\n");
    insertAtIndex(&tree, 0, 10);  // Root
    insertAtIndex(&tree, 1, 20);  // Left child of root
    insertAtIndex(&tree, 2, 30);  // Right child of root
    insertAtIndex(&tree, 3, 40);  // Left child of 20
    insertAtIndex(&tree, 6, 70);  // Right child of 30
    
    displayArray(&tree);
    
    printf("\nTree structure (with gaps):\n");
    displayTreeStructure(&tree, 0, 0);
    
    displayRelationships(&tree);
    
    printf("\nIs complete? %s (because of gaps)\n", 
           isComplete(&tree) ? "YES" : "NO");
}

// Demo 3: Binary Search Tree operations
void demo3() {
    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║    DEMO 3: Array-based BST (Manual Construction)        ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    ArrayTree tree;
    initTree(&tree);
    
    printf("\nBuilding BST structure:\n");
    insertAtIndex(&tree, 0, 50);   // Root
    insertAtIndex(&tree, 1, 30);   // Left
    insertAtIndex(&tree, 2, 70);   // Right
    insertAtIndex(&tree, 3, 20);   // Left-Left
    insertAtIndex(&tree, 4, 40);   // Left-Right
    insertAtIndex(&tree, 5, 60);   // Right-Left
    insertAtIndex(&tree, 6, 80);   // Right-Right
    
    displayArray(&tree);
    
    printf("\nTree structure:\n");
    displayTreeStructure(&tree, 0, 0);
    
    printf("\nInorder (should be sorted): ");
    inorder(&tree, 0);
    printf("\n");
    
    printf("\nSearch operations:\n");
    int searchValue = 40;
    int index = search(&tree, searchValue);
    if (index != -1) {
        printf("Value %d found at index %d\n", searchValue, index);
    } else {
        printf("Value %d not found\n", searchValue);
    }
}

// Interactive mode
void interactiveMode() {
    ArrayTree tree;
    initTree(&tree);
    int choice, index, value;
    
    while (1) {
        printf("\n=== ARRAY-BASED TREE OPERATIONS ===\n");
        printf("1.  Insert at Index\n");
        printf("2.  Insert Level-order\n");
        printf("3.  Delete at Index\n");
        printf("4.  Display Array\n");
        printf("5.  Display Tree Structure\n");
        printf("6.  Display Relationships\n");
        printf("7.  Preorder Traversal\n");
        printf("8.  Inorder Traversal\n");
        printf("9.  Postorder Traversal\n");
        printf("10. Level-order Traversal\n");
        printf("11. Get Height\n");
        printf("12. Count Nodes\n");
        printf("13. Search Value\n");
        printf("14. Check if Complete\n");
        printf("0.  Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter index: ");
                scanf("%d", &index);
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtIndex(&tree, index, value);
                break;
                
            case 2:
                printf("Enter value: ");
                scanf("%d", &value);
                insertLevelOrder(&tree, value);
                break;
                
            case 3:
                printf("Enter index: ");
                scanf("%d", &index);
                deleteAtIndex(&tree, index);
                break;
                
            case 4:
                displayArray(&tree);
                break;
                
            case 5:
                printf("\nTree structure:\n");
                displayTreeStructure(&tree, 0, 0);
                break;
                
            case 6:
                displayRelationships(&tree);
                break;
                
            case 7:
                printf("Preorder: ");
                preorder(&tree, 0);
                printf("\n");
                break;
                
            case 8:
                printf("Inorder: ");
                inorder(&tree, 0);
                printf("\n");
                break;
                
            case 9:
                printf("Postorder: ");
                postorder(&tree, 0);
                printf("\n");
                break;
                
            case 10:
                levelOrder(&tree);
                break;
                
            case 11:
                printf("Height: %d\n", getHeight(&tree, 0));
                break;
                
            case 12:
                printf("Total nodes: %d\n", countNodes(&tree));
                break;
                
            case 13:
                printf("Enter value to search: ");
                scanf("%d", &value);
                index = search(&tree, value);
                if (index != -1) {
                    printf("Found at index %d\n", index);
                } else {
                    printf("Not found\n");
                }
                break;
                
            case 14:
                printf("Is complete? %s\n", isComplete(&tree) ? "YES" : "NO");
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
    
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║         TREE CREATION USING ARRAY                        ║\n");
    printf("║      Binary Tree Array-Based Implementation             ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    printf("Array-based tree uses indices for relationships:\n");
    printf("  - Parent of i:      (i-1)/2\n");
    printf("  - Left child of i:  2*i + 1\n");
    printf("  - Right child of i: 2*i + 2\n\n");
    
    printf("Select mode:\n");
    printf("1. Demo 1 - Complete Binary Tree\n");
    printf("2. Demo 2 - Custom Tree Structure\n");
    printf("3. Demo 3 - Binary Search Tree\n");
    printf("4. Run All Demos\n");
    printf("5. Interactive Mode\n");
    printf("Choice: ");
    scanf("%d", &choice);
    
    switch (choice) {
        case 1:
            demo1();
            break;
        case 2:
            demo2();
            break;
        case 3:
            demo3();
            break;
        case 4:
            demo1();
            demo2();
            demo3();
            break;
        case 5:
            interactiveMode();
            break;
        default:
            printf("Invalid choice!\n");
    }
    
    printf("\n\n=== ADVANTAGES & DISADVANTAGES ===\n");
    printf("Advantages:\n");
    printf("  ✓ Simple implementation\n");
    printf("  ✓ Direct parent/child access: O(1)\n");
    printf("  ✓ No pointers needed\n");
    printf("  ✓ Cache-friendly (contiguous memory)\n\n");
    
    printf("Disadvantages:\n");
    printf("  ✗ Wastes space for incomplete trees\n");
    printf("  ✗ Fixed maximum size\n");
    printf("  ✗ Insertion/deletion may require shifting\n");
    
    return 0;
}
