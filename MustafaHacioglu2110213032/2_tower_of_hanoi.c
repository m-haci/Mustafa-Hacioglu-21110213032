#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Global counter for moves
int moveCount = 0;

// Structure to represent a disk
typedef struct {
    int size;
} Disk;

// Structure to represent a tower/peg
typedef struct {
    Disk disks[100];
    int top;
    char name;
} Tower;

// Initialize tower
void initTower(Tower* tower, char name) {
    tower->top = -1;
    tower->name = name;
}

// Push disk onto tower
void push(Tower* tower, int size) {
    if (tower->top < 99) {
        tower->top++;
        tower->disks[tower->top].size = size;
    }
}

// Pop disk from tower
int pop(Tower* tower) {
    if (tower->top >= 0) {
        int size = tower->disks[tower->top].size;
        tower->top--;
        return size;
    }
    return -1;
}

// Display all three towers
void displayTowers(Tower* source, Tower* auxiliary, Tower* destination, int n) {
    printf("\n");
    printf("════════════════════════════════════════════════════════\n");
    
    // Print from top to bottom
    for (int level = n - 1; level >= 0; level--) {
        // Tower A
        printf("  ");
        if (level <= source->top) {
            int size = source->disks[level].size;
            for (int i = 0; i < n - size; i++) printf(" ");
            for (int i = 0; i < size * 2 - 1; i++) printf("█");
            for (int i = 0; i < n - size; i++) printf(" ");
        } else {
            for (int i = 0; i < n - 1; i++) printf(" ");
            printf("│");
            for (int i = 0; i < n - 1; i++) printf(" ");
        }
        
        printf("   ");
        
        // Tower B
        if (level <= auxiliary->top) {
            int size = auxiliary->disks[level].size;
            for (int i = 0; i < n - size; i++) printf(" ");
            for (int i = 0; i < size * 2 - 1; i++) printf("█");
            for (int i = 0; i < n - size; i++) printf(" ");
        } else {
            for (int i = 0; i < n - 1; i++) printf(" ");
            printf("│");
            for (int i = 0; i < n - 1; i++) printf(" ");
        }
        
        printf("   ");
        
        // Tower C
        if (level <= destination->top) {
            int size = destination->disks[level].size;
            for (int i = 0; i < n - size; i++) printf(" ");
            for (int i = 0; i < size * 2 - 1; i++) printf("█");
            for (int i = 0; i < n - size; i++) printf(" ");
        } else {
            for (int i = 0; i < n - 1; i++) printf(" ");
            printf("│");
            for (int i = 0; i < n - 1; i++) printf(" ");
        }
        
        printf("\n");
    }
    
    // Base
    printf("  ");
    for (int i = 0; i < n * 2 - 1; i++) printf("═");
    printf("   ");
    for (int i = 0; i < n * 2 - 1; i++) printf("═");
    printf("   ");
    for (int i = 0; i < n * 2 - 1; i++) printf("═");
    printf("\n");
    
    // Tower labels
    printf("  ");
    for (int i = 0; i < n - 1; i++) printf(" ");
    printf("%c", source->name);
    for (int i = 0; i < n - 1; i++) printf(" ");
    printf("   ");
    
    for (int i = 0; i < n - 1; i++) printf(" ");
    printf("%c", auxiliary->name);
    for (int i = 0; i < n - 1; i++) printf(" ");
    printf("   ");
    
    for (int i = 0; i < n - 1; i++) printf(" ");
    printf("%c", destination->name);
    for (int i = 0; i < n - 1; i++) printf(" ");
    printf("\n");
    
    printf("════════════════════════════════════════════════════════\n");
}

// Basic recursive Tower of Hanoi - just shows moves
void towerOfHanoiBasic(int n, char source, char destination, char auxiliary) {
    if (n == 1) {
        moveCount++;
        printf("Move %d: Move disk 1 from %c to %c\n", moveCount, source, destination);
        return;
    }
    
    // Move n-1 disks from source to auxiliary using destination
    towerOfHanoiBasic(n - 1, source, auxiliary, destination);
    
    // Move the largest disk from source to destination
    moveCount++;
    printf("Move %d: Move disk %d from %c to %c\n", moveCount, n, source, destination);
    
    // Move n-1 disks from auxiliary to destination using source
    towerOfHanoiBasic(n - 1, auxiliary, destination, source);
}

// Advanced Tower of Hanoi with visualization
void towerOfHanoiVisual(int n, Tower* source, Tower* auxiliary, Tower* destination, 
                        int totalDisks, int delay) {
    if (n == 1) {
        moveCount++;
        int disk = pop(source);
        printf("\n>>> Move %d: Move disk %d from %c to %c\n", 
               moveCount, disk, source->name, destination->name);
        push(destination, disk);
        
        if (delay > 0) {
            displayTowers(source, auxiliary, destination, totalDisks);
            // Simple delay
            for (long i = 0; i < delay * 100000000L; i++);
        }
        return;
    }
    
    // Move n-1 disks from source to auxiliary using destination
    towerOfHanoiVisual(n - 1, source, destination, auxiliary, totalDisks, delay);
    
    // Move the largest disk
    moveCount++;
    int disk = pop(source);
    printf("\n>>> Move %d: Move disk %d from %c to %c\n", 
           moveCount, disk, source->name, destination->name);
    push(destination, disk);
    
    if (delay > 0) {
        displayTowers(source, auxiliary, destination, totalDisks);
        // Simple delay
        for (long i = 0; i < delay * 100000000L; i++);
    }
    
    // Move n-1 disks from auxiliary to destination using source
    towerOfHanoiVisual(n - 1, auxiliary, source, destination, totalDisks, delay);
}

// Calculate total moves (2^n - 1)
long long calculateMoves(int n) {
    long long moves = 1;
    for (int i = 0; i < n; i++) {
        moves *= 2;
    }
    return moves - 1;
}

// Display theory and complexity
void displayTheory(int n) {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║          TOWER OF HANOI - THEORY & COMPLEXITY            ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    printf("📚 RULES:\n");
    printf("  1. Only one disk can be moved at a time\n");
    printf("  2. Only the top disk of any tower can be moved\n");
    printf("  3. A larger disk cannot be placed on a smaller disk\n\n");
    
    printf("🎯 OBJECTIVE:\n");
    printf("  Move all %d disks from Tower A to Tower C\n", n);
    printf("  using Tower B as auxiliary\n\n");
    
    printf("🔢 RECURSIVE ALGORITHM:\n");
    printf("  To move n disks from Source to Destination:\n");
    printf("    1. Move (n-1) disks from Source to Auxiliary\n");
    printf("    2. Move largest disk from Source to Destination\n");
    printf("    3. Move (n-1) disks from Auxiliary to Destination\n\n");
    
    printf("⏱️  COMPLEXITY ANALYSIS:\n");
    printf("  Time Complexity:  O(2^n)\n");
    printf("  Space Complexity: O(n) - recursion stack depth\n");
    printf("  Total Moves:      2^%d - 1 = %lld moves\n\n", n, calculateMoves(n));
    
    // Show growth
    printf("📊 EXPONENTIAL GROWTH:\n");
    printf("  ┌────────┬──────────────┬─────────────────────┐\n");
    printf("  │ Disks  │ Total Moves  │   Time (1 sec/move) │\n");
    printf("  ├────────┼──────────────┼─────────────────────┤\n");
    for (int i = 1; i <= 10; i++) {
        long long moves = calculateMoves(i);
        if (moves < 60) {
            printf("  │   %2d   │   %10lld │      %lld seconds       │\n", i, moves, moves);
        } else if (moves < 3600) {
            printf("  │   %2d   │   %10lld │      %lld minutes       │\n", i, moves, moves / 60);
        } else if (moves < 86400) {
            printf("  │   %2d   │   %10lld │      %.1f hours         │\n", i, moves, moves / 3600.0);
        } else {
            printf("  │   %2d   │   %10lld │      %.1f days          │\n", i, moves, moves / 86400.0);
        }
    }
    printf("  └────────┴──────────────┴─────────────────────┘\n\n");
    
    printf("💡 FUN FACT: Legend says monks are solving a 64-disk puzzle.\n");
    printf("   When complete, the world will end. Time needed:\n");
    printf("   2^64 - 1 = 18,446,744,073,709,551,615 moves\n");
    printf("   ≈ 585 billion years (if 1 move/second)!\n\n");
}

int main() {
    int choice, n;
    
    printf("╔══════════════════════════════════════════════════════════╗\n");
    printf("║              TOWER OF HANOI SOLVER                       ║\n");
    printf("║          (Recursive Algorithm Implementation)            ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    printf("Select mode:\n");
    printf("1. Theory & Complexity Analysis\n");
    printf("2. Basic Solution (Text Only)\n");
    printf("3. Visual Solution (Animated)\n");
    printf("4. All Three\n");
    printf("\nEnter choice (1-4): ");
    scanf("%d", &choice);
    
    printf("\nEnter number of disks (1-10 recommended): ");
    scanf("%d", &n);
    
    if (n < 1 || n > 20) {
        printf("Invalid number! Using n=3\n");
        n = 3;
    }
    
    if (choice == 1 || choice == 4) {
        displayTheory(n);
        if (choice == 1) return 0;
    }
    
    if (choice == 2 || choice == 4) {
        printf("\n═══════════════════════════════════════════════════════════\n");
        printf("             BASIC SOLUTION (TEXT ONLY)\n");
        printf("═══════════════════════════════════════════════════════════\n\n");
        
        moveCount = 0;
        clock_t start = clock();
        towerOfHanoiBasic(n, 'A', 'C', 'B');
        clock_t end = clock();
        
        double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        printf("\n✅ Solution completed!\n");
        printf("Total moves: %d\n", moveCount);
        printf("Execution time: %.6f seconds\n", timeTaken);
        printf("Moves per second: %.0f\n\n", moveCount / timeTaken);
        
        if (choice == 2) return 0;
    }
    
    if (choice == 3 || choice == 4) {
        printf("\n═══════════════════════════════════════════════════════════\n");
        printf("             VISUAL SOLUTION (ANIMATED)\n");
        printf("═══════════════════════════════════════════════════════════\n");
        
        int delay = 0;
        if (n <= 5) {
            printf("\nEnable animation? (0=No, 1=Slow, 2=Fast): ");
            scanf("%d", &delay);
        }
        
        // Initialize towers
        Tower towerA, towerB, towerC;
        initTower(&towerA, 'A');
        initTower(&towerB, 'B');
        initTower(&towerC, 'C');
        
        // Put all disks on tower A (largest to smallest)
        for (int i = n; i >= 1; i--) {
            push(&towerA, i);
        }
        
        printf("\nInitial State:");
        displayTowers(&towerA, &towerB, &towerC, n);
        
        printf("\nPress Enter to start solving...");
        getchar();
        getchar();
        
        moveCount = 0;
        clock_t start = clock();
        
        towerOfHanoiVisual(n, &towerA, &towerB, &towerC, n, delay);
        
        clock_t end = clock();
        double timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        
        printf("\n\n🎉 PUZZLE SOLVED! 🎉\n");
        printf("\nFinal State:");
        displayTowers(&towerA, &towerB, &towerC, n);
        
        printf("\n╔══════════════════════════════════════════════════════════╗\n");
        printf("║                    STATISTICS                            ║\n");
        printf("╠══════════════════════════════════════════════════════════╣\n");
        printf("║  Total Moves:         %-10d                        ║\n", moveCount);
        printf("║  Expected Moves:      %-10lld                        ║\n", calculateMoves(n));
        printf("║  Execution Time:      %-10.6f seconds              ║\n", timeTaken);
        printf("║  Moves/Second:        %-10.0f                        ║\n", moveCount / timeTaken);
        printf("╚══════════════════════════════════════════════════════════╝\n");
    }
    
    return 0;
}
