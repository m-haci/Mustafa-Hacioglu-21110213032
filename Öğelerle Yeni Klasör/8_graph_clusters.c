#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VERTICES 20

// Graph structure using adjacency matrix
typedef struct {
    int adjMatrix[MAX_VERTICES][MAX_VERTICES];
    int numVertices;
} Graph;

// Initialize graph
void initGraph(Graph* g, int vertices) {
    g->numVertices = vertices;
    for (int i = 0; i < vertices; i++) {
        for (int j = 0; j < vertices; j++) {
            g->adjMatrix[i][j] = 0;
        }
    }
}

// Add edge (undirected graph)
void addEdge(Graph* g, int src, int dest) {
    if (src >= g->numVertices || dest >= g->numVertices || src < 0 || dest < 0) {
        printf("Invalid vertex!\n");
        return;
    }
    g->adjMatrix[src][dest] = 1;
    g->adjMatrix[dest][src] = 1; // Undirected
}

// Display adjacency matrix
void displayMatrix(Graph* g) {
    printf("\nAdjacency Matrix:\n");
    printf("   ");
    for (int i = 0; i < g->numVertices; i++) {
        printf("%3d", i);
    }
    printf("\n");
    
    for (int i = 0; i < g->numVertices; i++) {
        printf("%3d", i);
        for (int j = 0; j < g->numVertices; j++) {
            printf("%3d", g->adjMatrix[i][j]);
        }
        printf("\n");
    }
}

// DFS helper for finding clusters
void DFS(Graph* g, int vertex, int visited[], int cluster[], int* clusterSize) {
    visited[vertex] = 1;
    cluster[(*clusterSize)++] = vertex;
    
    for (int i = 0; i < g->numVertices; i++) {
        if (g->adjMatrix[vertex][i] == 1 && !visited[i]) {
            DFS(g, i, visited, cluster, clusterSize);
        }
    }
}

// Find all clusters (connected components)
int findClusters(Graph* g, int clusters[][MAX_VERTICES], int clusterSizes[]) {
    int visited[MAX_VERTICES] = {0};
    int numClusters = 0;
    
    for (int i = 0; i < g->numVertices; i++) {
        if (!visited[i]) {
            clusterSizes[numClusters] = 0;
            DFS(g, i, visited, clusters[numClusters], &clusterSizes[numClusters]);
            numClusters++;
        }
    }
    
    return numClusters;
}

// Display clusters
void displayClusters(int clusters[][MAX_VERTICES], int clusterSizes[], int numClusters) {
    printf("\n=== CLUSTER ANALYSIS ===\n");
    printf("Total clusters found: %d\n\n", numClusters);
    
    for (int i = 0; i < numClusters; i++) {
        printf("Cluster %d (size %d): { ", i + 1, clusterSizes[i]);
        for (int j = 0; j < clusterSizes[i]; j++) {
            printf("%d", clusters[i][j]);
            if (j < clusterSizes[i] - 1) {
                printf(", ");
            }
        }
        printf(" }\n");
    }
}

// Visualize graph
void visualizeGraph(Graph* g) {
    printf("\n=== GRAPH VISUALIZATION ===\n");
    for (int i = 0; i < g->numVertices; i++) {
        printf("Vertex %d: ", i);
        int hasEdge = 0;
        for (int j = 0; j < g->numVertices; j++) {
            if (g->adjMatrix[i][j] == 1) {
                if (hasEdge) printf(", ");
                printf("%d", j);
                hasEdge = 1;
            }
        }
        if (!hasEdge) {
            printf("(isolated)");
        }
        printf("\n");
    }
}

// Calculate cluster statistics
void clusterStatistics(int clusters[][MAX_VERTICES], int clusterSizes[], int numClusters) {
    printf("\n=== CLUSTER STATISTICS ===\n");
    
    // Find largest and smallest clusters
    int maxSize = 0, minSize = MAX_VERTICES;
    int maxIdx = 0, minIdx = 0;
    
    for (int i = 0; i < numClusters; i++) {
        if (clusterSizes[i] > maxSize) {
            maxSize = clusterSizes[i];
            maxIdx = i;
        }
        if (clusterSizes[i] < minSize) {
            minSize = clusterSizes[i];
            minIdx = i;
        }
    }
    
    printf("Largest cluster: Cluster %d with %d vertices\n", maxIdx + 1, maxSize);
    printf("Smallest cluster: Cluster %d with %d vertices\n", minIdx + 1, minSize);
    
    // Calculate average cluster size
    float avgSize = 0;
    for (int i = 0; i < numClusters; i++) {
        avgSize += clusterSizes[i];
    }
    avgSize /= numClusters;
    printf("Average cluster size: %.2f\n", avgSize);
    
    // Count isolated vertices
    int isolatedCount = 0;
    for (int i = 0; i < numClusters; i++) {
        if (clusterSizes[i] == 1) {
            isolatedCount++;
        }
    }
    printf("Isolated vertices: %d\n", isolatedCount);
}

// Check if graph is connected
int isConnected(Graph* g) {
    int clusters[MAX_VERTICES][MAX_VERTICES];
    int clusterSizes[MAX_VERTICES];
    int numClusters = findClusters(g, clusters, clusterSizes);
    return (numClusters == 1);
}

// Count edges in graph
int countEdges(Graph* g) {
    int count = 0;
    for (int i = 0; i < g->numVertices; i++) {
        for (int j = i + 1; j < g->numVertices; j++) {
            if (g->adjMatrix[i][j] == 1) {
                count++;
            }
        }
    }
    return count;
}

// Demo 1: Simple disconnected graph
void demo1() {
    printf("\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║              DEMO 1: Simple Disconnected Graph           ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    Graph g;
    initGraph(&g, 7);
    
    // Cluster 1: 0-1-2
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    
    // Cluster 2: 3-4
    addEdge(&g, 3, 4);
    
    // Cluster 3: 5 (isolated)
    
    // Cluster 4: 6 (isolated)
    
    printf("\nCreated graph with 7 vertices and %d edges\n", countEdges(&g));
    displayMatrix(&g);
    visualizeGraph(&g);
    
    int clusters[MAX_VERTICES][MAX_VERTICES];
    int clusterSizes[MAX_VERTICES];
    int numClusters = findClusters(&g, clusters, clusterSizes);
    
    displayClusters(clusters, clusterSizes, numClusters);
    clusterStatistics(clusters, clusterSizes, numClusters);
    
    printf("\nIs graph connected? %s\n", isConnected(&g) ? "YES" : "NO");
}

// Demo 2: Social network example
void demo2() {
    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║       DEMO 2: Social Network (Friend Groups)            ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    Graph g;
    initGraph(&g, 10);
    
    // Friend Group 1: 0-1-2-3
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 0); // Creates a cycle
    
    // Friend Group 2: 4-5-6
    addEdge(&g, 4, 5);
    addEdge(&g, 5, 6);
    addEdge(&g, 6, 4);
    
    // Friend Group 3: 7-8
    addEdge(&g, 7, 8);
    
    // Isolated person: 9
    
    printf("\nSocial network with 10 people and %d friendships\n", countEdges(&g));
    visualizeGraph(&g);
    
    int clusters[MAX_VERTICES][MAX_VERTICES];
    int clusterSizes[MAX_VERTICES];
    int numClusters = findClusters(&g, clusters, clusterSizes);
    
    displayClusters(clusters, clusterSizes, numClusters);
    clusterStatistics(clusters, clusterSizes, numClusters);
}

// Demo 3: Network topology
void demo3() {
    printf("\n\n╔══════════════════════════════════════════════════════════╗\n");
    printf("║         DEMO 3: Computer Network Topology               ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n");
    
    Graph g;
    initGraph(&g, 12);
    
    // Network Segment 1 (Offices): 0-1-2-3-4
    addEdge(&g, 0, 1);
    addEdge(&g, 1, 2);
    addEdge(&g, 2, 3);
    addEdge(&g, 3, 4);
    addEdge(&g, 4, 0);
    
    // Network Segment 2 (Lab): 5-6-7
    addEdge(&g, 5, 6);
    addEdge(&g, 6, 7);
    
    // Network Segment 3 (Server Room): 8-9
    addEdge(&g, 8, 9);
    
    // Offline computers: 10, 11
    
    printf("\nNetwork with 12 computers and %d connections\n", countEdges(&g));
    visualizeGraph(&g);
    
    int clusters[MAX_VERTICES][MAX_VERTICES];
    int clusterSizes[MAX_VERTICES];
    int numClusters = findClusters(&g, clusters, clusterSizes);
    
    displayClusters(clusters, clusterSizes, numClusters);
    clusterStatistics(clusters, clusterSizes, numClusters);
    
    printf("\n⚠️  Warning: Network has %d disconnected segments!\n", numClusters);
    printf("Recommendation: Connect all segments for full network connectivity.\n");
}

// Interactive mode
void interactiveMode() {
    Graph g;
    int vertices, choice, src, dest;
    
    printf("\nEnter number of vertices (1-%d): ", MAX_VERTICES);
    scanf("%d", &vertices);
    
    if (vertices < 1 || vertices > MAX_VERTICES) {
        printf("Invalid number of vertices!\n");
        return;
    }
    
    initGraph(&g, vertices);
    
    while (1) {
        printf("\n=== GRAPH CLUSTER ANALYSIS ===\n");
        printf("1. Add Edge\n");
        printf("2. Display Adjacency Matrix\n");
        printf("3. Visualize Graph\n");
        printf("4. Find Clusters\n");
        printf("5. Check if Connected\n");
        printf("6. Count Edges\n");
        printf("0. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                printf("Enter edge (src dest): ");
                scanf("%d %d", &src, &dest);
                addEdge(&g, src, dest);
                printf("Edge added: %d -- %d\n", src, dest);
                break;
                
            case 2:
                displayMatrix(&g);
                break;
                
            case 3:
                visualizeGraph(&g);
                break;
                
            case 4: {
                int clusters[MAX_VERTICES][MAX_VERTICES];
                int clusterSizes[MAX_VERTICES];
                int numClusters = findClusters(&g, clusters, clusterSizes);
                displayClusters(clusters, clusterSizes, numClusters);
                clusterStatistics(clusters, clusterSizes, numClusters);
                break;
            }
                
            case 5:
                printf("Is graph connected? %s\n", isConnected(&g) ? "YES" : "NO");
                break;
                
            case 6:
                printf("Total edges: %d\n", countEdges(&g));
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
    printf("║        GRAPH CLUSTER DETECTION (ARRAY-BASED)            ║\n");
    printf("║         Finding Connected Components in Graphs          ║\n");
    printf("╚══════════════════════════════════════════════════════════╝\n\n");
    
    printf("Select mode:\n");
    printf("1. Demo 1 - Simple Disconnected Graph\n");
    printf("2. Demo 2 - Social Network Example\n");
    printf("3. Demo 3 - Computer Network Topology\n");
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
    
    printf("\n\n=== ALGORITHM EXPLANATION ===\n");
    printf("Cluster detection uses Depth-First Search (DFS) to find\n");
    printf("connected components in an undirected graph.\n\n");
    printf("Time Complexity:  O(V + E)\n");
    printf("Space Complexity: O(V)\n");
    printf("where V = vertices, E = edges\n");
    
    return 0;
}
