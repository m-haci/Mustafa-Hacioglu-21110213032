#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 20

// Queue structure for BFS
typedef struct {
    int items[MAX_VERTICES];
    int front;
    int rear;
} Queue;

// Graph structure
typedef struct {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

// Queue operations
void initQueue(Queue* q) {
    q->front = -1;
    q->rear = -1;
}

int isQueueEmpty(Queue* q) {
    return q->front == -1;
}

void enqueue(Queue* q, int value) {
    if (q->front == -1) {
        q->front = 0;
    }
    q->rear++;
    q->items[q->rear] = value;
}

int dequeue(Queue* q) {
    int item = q->items[q->front];
    q->front++;
    if (q->front > q->rear) {
        q->front = q->rear = -1;
    }
    return item;
}

// Graph operations
void initGraph(Graph* g, int vertices) {
    g->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
}

void addEdge(Graph* g, int src, int dest) {
    if (src >= g->numVertices || dest >= g->numVertices || src < 0 || dest < 0) {
        return;
    }
    g->adjMatrix[src][dest] = 1;
    g->adjMatrix[dest][src] = 1;
}

// DFS - Recursive implementation
void DFS_Recursive(Graph* g, int vertex, int visited[]) {
    visited[vertex] = 1;
    printf("%d ", vertex);
    
    for (int i = 0; i < g->numVertices; i++) {
        if (g->adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFS_Recursive(g, i, visited);
        }
    }
}

// DFS - Iterative implementation (using stack)
void DFS_Iterative(Graph* g, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    int stack[MAX_VERTICES];
    int top = -1;
    
    // Push start vertex
    stack[++top] = startVertex;
    
    printf("DFS (Iterative) from vertex %d: ", startVertex);
    
    while (top >= 0) {
        int vertex = stack[top--];
        
        if (!visited[vertex]) {
            printf("%d ", vertex);
            visited[vertex] = 1;
            
            // Push all adjacent vertices
            for (int i = g->numVertices - 1; i >= 0; i--) {
                if (g->adjMatrix[vertex][i] == 1 && !visited[i]) {
                    stack[++top] = i;
                }
            }
        }
    }
    printf("\n");
}

// BFS implementation
void BFS(Graph* g, int startVertex) {
    int visited[MAX_VERTICES] = {0};
    Queue q;
    initQueue(&q);
    
    visited[startVertex] = 1;
    enqueue(&q, startVertex);
    
    printf("BFS from vertex %d: ", startVertex);
    
    while (!isQueueEmpty(&q)) {
        int vertex = dequeue(&q);
        printf("%d ", vertex);
        
        for (int i = 0; i < g->numVertices; i++) {
            if (g->adjMatrix[vertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                enqueue(&q, i);
            }
        }
    }
    printf("\n");
}

// DFS with path tracking
void DFS_WithPath(Graph* g, int start, int end, int visited[], int path[], int pathLen) {
    static int found = 0;
    
    visited[start] = 1;
    path[pathLen] = start;
    pathLen++;
    
    if (start == end) {
        printf("Path found: ");
        for (int i = 0; i < pathLen; i++) {
            printf("%d", path[i]);
            if (i < pathLen - 1) printf(" -> ");
        }
        printf("\n");
        found = 1;
        return;
    }
    
    for (int i = 0; i < g->numVertices; i++) {
        if (g->adjMatrix[start][i] == 1 && !visited[i] && !found) {
            DFS_WithPath(g, i, end, visited, path, pathLen);
        }
    }
    
    visited[start] = 0; // Backtrack
}

// BFS for shortest path
void BFS_ShortestPath(Graph* g, int start, int end) {
    int visited[MAX_VERTICES] = {0};
    int parent[MAX_VERTICES];
    Queue q;
    initQueue(&q);
    
    for (int i = 0; i < g->numVertices; i++) {
        parent[i] = -1;
    }
    
    visited[start] = 1;
    enqueue(&q, start);
    
    while (!isQueueEmpty(&q)) {
        int vertex = dequeue(&q);
        
        if (vertex == end) {
            // Reconstruct path
            int path[MAX_VERTICES];
            int pathLen = 0;
            int current = end;
            
            while (current != -1) {
                path[pathLen++] = current;
                current = parent[current];
            }
            
            printf("Shortest path from %d to %d: ", start, end);
            for (int i = pathLen - 1; i >= 0; i--) {
                printf("%d", path[i]);
                if (i > 0) printf(" -> ");
            }
            printf(" (length: %d)\n", pathLen - 1);
            return;
        }
        
        for (int i = 0; i < g->numVertices; i++) {
            if (g->adjMatrix[vertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                parent[i] = vertex;
                enqueue(&q, i);
            }
        }
    }
    
    printf("No path exists from %d to %d\n", start, end);
}

// Display graph
void displayGraph(Graph* g) {
    printf("\nGraph (Adjacency List representation):\n");
    for (int i = 0; i < g->numVertices; i++) {
        printf("Vertex %d: ", i);
        for (int j = 0; j < g->numVertices; j++) {
            if (g->adjMatrix[i][j] == 1) {
                printf("%d ", j);
            }
        }
        printf("\n");
    }
}

// Demo 1: Simple graph traversal
void demo1() {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║           DEMO 1: Basic DFS and BFS Traversal            ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    Graph g;
    initGraph(&g, 6);
    
    // Create graph
    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 3);
    addEdge(&g, 1, 4);
    addEdge(&g, 2, 4);
    addEdge(&g, 3, 4);
    addEdge(&g, 3, 5);
    
    displayGraph(&g);
    
    printf("\n--- Traversals from vertex 0 ---\n");
    
    int visited[MAX_VERTICES] = {0};
    printf("DFS (Recursive) from vertex 0: ");
    DFS_Recursive(&g, 0, visited);
    printf("\n");
    
    DFS_Iterative(&g, 0);
    BFS(&g, 0);
}

// Demo 2: Path finding
void demo2() {
    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║              DEMO 2: Path Finding                        ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    Graph g;
    initGraph(&g, 8);
    
    // Create a more complex graph
    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 3);
    addEdge(&g, 2, 3);
    addEdge(&g, 2, 4);
    addEdge(&g, 3, 5);
    addEdge(&g, 4, 5);
    addEdge(&g, 5, 6);
    addEdge(&g, 5, 7);
    
    displayGraph(&g);
    
    printf("\n--- Finding paths ---\n");
    
    int visited[MAX_VERTICES] = {0};
    int path[MAX_VERTICES];
    
    printf("DFS path from 0 to 7:\n");
    DFS_WithPath(&g, 0, 7, visited, path, 0);
    
    printf("\n");
    BFS_ShortestPath(&g, 0, 7);
    BFS_ShortestPath(&g, 0, 6);
    BFS_ShortestPath(&g, 1, 4);
}

// Demo 3: Level-wise BFS
void demo3() {
    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║         DEMO 3: Level-wise BFS (Tree Structure)         ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    Graph g;
    initGraph(&g, 7);
    
    // Create tree structure
    addEdge(&g, 0, 1);
    addEdge(&g, 0, 2);
    addEdge(&g, 1, 3);
    addEdge(&g, 1, 4);
    addEdge(&g, 2, 5);
    addEdge(&g, 2, 6);
    
    displayGraph(&g);
    
    printf("\nLevel-wise BFS from root (0):\n");
    
    int visited[MAX_VERTICES] = {0};
    int level[MAX_VERTICES] = {0};
    Queue q;
    initQueue(&q);
    
    visited[0] = 1;
    level[0] = 0;
    enqueue(&q, 0);
    
    int currentLevel = -1;
    
    while (!isQueueEmpty(&q)) {
        int vertex = dequeue(&q);
        
        if (level[vertex] != currentLevel) {
            currentLevel = level[vertex];
            printf("\nLevel %d: ", currentLevel);
        }
        
        printf("%d ", vertex);
        
        for (int i = 0; i < g.numVertices; i++) {
            if (g.adjMatrix[vertex][i] == 1 && !visited[i]) {
                visited[i] = 1;
                level[i] = level[vertex] + 1;
                enqueue(&q, i);
            }
        }
    }
    printf("\n");
}

// Interactive mode
void interactiveMode() {
    Graph g;
    int vertices, choice, src, dest, start, end;
    
    printf("\nEnter number of vertices: ");
    scanf("%d", &vertices);
    
    if (vertices < 1 || vertices > MAX_VERTICES) {
        printf("Invalid number!\n");
        return;
    }
    
    initGraph(&g, vertices);
    
    while (1) {
        printf("\n=== DFS & BFS OPERATIONS ===\n");
        printf("1. Add Edge\n");
        printf("2. Display Graph\n");
        printf("3. DFS (Recursive)\n");
        printf("4. DFS (Iterative)\n");
        printf("5. BFS\n");
        printf("6. Find Shortest Path (BFS)\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter edge (src dest): ");
                scanf("%d %d", &src, &dest);
                addEdge(&g, src, dest);
                printf("Edge added!\n");
                break;
                
            case 2:
                displayGraph(&g);
                break;
                
            case 3: {
                printf("Start vertex: ");
                scanf("%d", &start);
                int visited[MAX_VERTICES] = {0};
                printf("DFS: ");
                DFS_Recursive(&g, start, visited);
                printf("\n");
                break;
            }
                
            case 4:
                printf("Start vertex: ");
                scanf("%d", &start);
                DFS_Iterative(&g, start);
                break;
                
            case 5:
                printf("Start vertex: ");
                scanf("%d", &start);
                BFS(&g, start);
                break;
                
            case 6:
                printf("Start vertex: ");
                scanf("%d", &start);
                printf("End vertex: ");
                scanf("%d", &end);
                BFS_ShortestPath(&g, start, end);
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
    printf("║          DFS & BFS IMPLEMENTATION                        ║\n");
    printf("║     Depth-First Search & Breadth-First Search           ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    printf("Select mode:\n");
    printf("1. Demo 1 - Basic Traversals\n");
    printf("2. Demo 2 - Path Finding\n");
    printf("3. Demo 3 - Level-wise BFS\n");
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
    
    printf("\n\n=== ALGORITHM COMPARISON ===\n");
    printf("┌─────────────┬──────────────────┬──────────────────┐\n");
    printf("│  Algorithm  │   Time Complexity│ Space Complexity │\n");
    printf("├─────────────┼──────────────────┼──────────────────┤\n");
    printf("│  DFS        │      O(V + E)    │      O(V)        │\n");
    printf("│  BFS        │      O(V + E)    │      O(V)        │\n");
    printf("└─────────────┴──────────────────┴──────────────────┘\n\n");
    
    printf("DFS: Good for path existence, topological sort, cycle detection\n");
    printf("BFS: Good for shortest path, level-order traversal\n");
    
    return 0;
}
