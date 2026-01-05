#include <stdio.h>
#include <stdlib.h>

#define MAX_TERMS 100

// Sparse matrix element structure
typedef struct {
    int row;
    int col;
    int value;
} SparseElement;

// Function to convert regular matrix to sparse matrix
int convertToSparse(int matrix[][10], int rows, int cols, SparseElement sparse[]) {
    int k = 0; // Index for sparse array
    
    // Store matrix dimensions in first element
    sparse[0].row = rows;
    sparse[0].col = cols;
    sparse[0].value = 0; // Will store count of non-zero elements
    
    k = 1;
    
    // Traverse the matrix and store non-zero elements
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (matrix[i][j] != 0) {
                sparse[k].row = i;
                sparse[k].col = j;
                sparse[k].value = matrix[i][j];
                k++;
            }
        }
    }
    
    // Store the count of non-zero elements
    sparse[0].value = k - 1;
    
    return k; // Return total elements (including header)
}

// Function to display regular matrix
void displayMatrix(int matrix[][10], int rows, int cols) {
    printf("\nOriginal Matrix (%dx%d):\n", rows, cols);
    printf("------------------------\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to display sparse matrix
void displaySparse(SparseElement sparse[], int size) {
    printf("\nSparse Matrix Representation:\n");
    printf("-----------------------------\n");
    printf(" Row | Column | Value\n");
    printf("-----|--------|------\n");
    
    // First row contains dimensions and count
    printf("%4d | %6d | %5d  <- (rows, cols, count)\n", 
           sparse[0].row, sparse[0].col, sparse[0].value);
    printf("-----|--------|------\n");
    
    // Print non-zero elements
    for (int i = 1; i < size; i++) {
        printf("%4d | %6d | %5d\n", 
               sparse[i].row, sparse[i].col, sparse[i].value);
    }
}

// Function to calculate space savings
void calculateSavings(int rows, int cols, int nonZeroCount) {
    int originalSize = rows * cols * sizeof(int);
    int sparseSize = (nonZeroCount + 1) * sizeof(SparseElement);
    float savingsPercent = ((float)(originalSize - sparseSize) / originalSize) * 100;
    
    printf("\n=== Memory Analysis ===\n");
    printf("Original matrix size: %d elements × %lu bytes = %d bytes\n", 
           rows * cols, sizeof(int), originalSize);
    printf("Sparse matrix size: %d elements × %lu bytes = %d bytes\n", 
           nonZeroCount + 1, sizeof(SparseElement), sparseSize);
    printf("Space savings: %.2f%%\n", savingsPercent);
    printf("Compression ratio: %.2fx\n", (float)originalSize / sparseSize);
}

// Function to reconstruct original matrix from sparse representation
void reconstructMatrix(SparseElement sparse[], int size, int result[][10]) {
    int rows = sparse[0].row;
    int cols = sparse[0].col;
    
    // Initialize result matrix with zeros
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = 0;
        }
    }
    
    // Fill in non-zero values
    for (int i = 1; i < size; i++) {
        result[sparse[i].row][sparse[i].col] = sparse[i].value;
    }
}

int main() {
    // Example 1: 4x5 sparse matrix
    int matrix1[10][10] = {
        {0, 0, 3, 0, 4},
        {0, 0, 5, 7, 0},
        {0, 0, 0, 0, 0},
        {0, 2, 6, 0, 0}
    };
    int rows1 = 4, cols1 = 5;
    
    printf("═══════════════════════════════════════════════\n");
    printf("   SPARSE MATRIX CONVERSION - EXAMPLE 1\n");
    printf("═══════════════════════════════════════════════\n");
    
    SparseElement sparse1[MAX_TERMS];
    int sparseSize1 = convertToSparse(matrix1, rows1, cols1, sparse1);
    
    displayMatrix(matrix1, rows1, cols1);
    displaySparse(sparse1, sparseSize1);
    calculateSavings(rows1, cols1, sparse1[0].value);
    
    // Verify by reconstructing
    printf("\n--- Verification: Reconstructed Matrix ---\n");
    int reconstructed[10][10];
    reconstructMatrix(sparse1, sparseSize1, reconstructed);
    displayMatrix(reconstructed, rows1, cols1);
    
    // Example 2: More sparse matrix (6x6)
    printf("\n\n═══════════════════════════════════════════════\n");
    printf("   SPARSE MATRIX CONVERSION - EXAMPLE 2\n");
    printf("═══════════════════════════════════════════════\n");
    
    int matrix2[10][10] = {
        {0, 0, 0, 0, 0, 12},
        {0, 15, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {8, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0},
        {0, 0, 0, 20, 0, 0}
    };
    int rows2 = 6, cols2 = 6;
    
    SparseElement sparse2[MAX_TERMS];
    int sparseSize2 = convertToSparse(matrix2, rows2, cols2, sparse2);
    
    displayMatrix(matrix2, rows2, cols2);
    displaySparse(sparse2, sparseSize2);
    calculateSavings(rows2, cols2, sparse2[0].value);
    
    // Example 3: User input
    printf("\n\n═══════════════════════════════════════════════\n");
    printf("   CUSTOM SPARSE MATRIX INPUT\n");
    printf("═══════════════════════════════════════════════\n");
    
    int customRows, customCols;
    int customMatrix[10][10];
    
    printf("\nEnter number of rows (max 10): ");
    scanf("%d", &customRows);
    printf("Enter number of columns (max 10): ");
    scanf("%d", &customCols);
    
    if (customRows > 10 || customCols > 10 || customRows < 1 || customCols < 1) {
        printf("Invalid dimensions!\n");
        return 1;
    }
    
    printf("\nEnter matrix elements (row by row):\n");
    for (int i = 0; i < customRows; i++) {
        for (int j = 0; j < customCols; j++) {
            printf("Element [%d][%d]: ", i, j);
            scanf("%d", &customMatrix[i][j]);
        }
    }
    
    SparseElement customSparse[MAX_TERMS];
    int customSparseSize = convertToSparse(customMatrix, customRows, customCols, customSparse);
    
    displayMatrix(customMatrix, customRows, customCols);
    displaySparse(customSparse, customSparseSize);
    calculateSavings(customRows, customCols, customSparse[0].value);
    
    // Sparsity analysis
    int totalElements = customRows * customCols;
    int nonZeroElements = customSparse[0].value;
    float sparsityRatio = ((float)(totalElements - nonZeroElements) / totalElements) * 100;
    
    printf("\n=== Sparsity Analysis ===\n");
    printf("Total elements: %d\n", totalElements);
    printf("Non-zero elements: %d\n", nonZeroElements);
    printf("Zero elements: %d\n", totalElements - nonZeroElements);
    printf("Sparsity ratio: %.2f%% (percentage of zeros)\n", sparsityRatio);
    
    if (sparsityRatio > 70) {
        printf("✓ This is a highly sparse matrix - sparse representation is very beneficial!\n");
    } else if (sparsityRatio > 40) {
        printf("✓ This is a moderately sparse matrix - sparse representation is beneficial.\n");
    } else {
        printf("⚠ This matrix is not very sparse - sparse representation may not save much space.\n");
    }
    
    return 0;
}
