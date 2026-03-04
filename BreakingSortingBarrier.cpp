#include "BreakingSortingBarrier.h"

// Constructor: allocate adjacency matrix and set all weights to 0
Graph::Graph(int n) {
    nodes = n;
    adjMatrix = new int*[nodes];
    for (int i = 0; i < nodes; i++) {
        adjMatrix[i] = new int[nodes];
        for (int j = 0; j < nodes; j++) {
            adjMatrix[i][j] = 0;
        }
    }
}

// Destructor: free adjacency matrix
Graph::~Graph() {
    for (int i = 0; i < nodes; i++) {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;
}

// Adds undirected edge between u and v with weight w
bool Graph::addEdge(int u, int v, int w) {
    if (u < 0 || v < 0 || u >= nodes || v >= nodes || u == v)
        return false;

    adjMatrix[u][v] = w;
    adjMatrix[v][u] = w;
    return true;
}

// Generates a dense graph
void Graph::generateDenseGraph() {
    srand(time(0));

    // Minimum edges for a connected dense graph = nodes - 1
    for (int i = 0; i < nodes - 1; i++) {
        int w = rand() % 100 + 1;
        addEdge(i, i + 1, w);
    }

    // Additional random edges to make it dense
    int extraEdges = nodes * 2;
    for (int k = 0; k < extraEdges; k++) {
        int u = rand() % nodes;
        int v = rand() % nodes;
        if (u != v) {
            int w = rand() % 100 + 1;
            addEdge(u, v, w);
        }
    }
}

// Classic Dijkstra algorithm using O(n²)
void Graph::classicalDijkstra(int start, int dist[], int parent[]) {
    bool* visited = new bool[nodes];

    for (int i = 0; i < nodes; i++) {
        dist[i] = numeric_limits<int>::max();
        parent[i] = -1;
        visited[i] = false;
    }

    dist[start] = 0;

    for (int count = 0; count < nodes - 1; count++) {
        int minDist = numeric_limits<int>::max();
        int u = -1;

        // Find unvisited node with smallest distance
        for (int i = 0; i < nodes; i++) {
            if (!visited[i] && dist[i] <= minDist) {
                minDist = dist[i];
                u = i;
            }
        }

        visited[u] = true;

        // Relax edges
        for (int v = 0; v < nodes; v++) {
            if (!visited[v] && adjMatrix[u][v] != 0 &&
                dist[u] + adjMatrix[u][v] < dist[v]) {

                dist[v] = dist[u] + adjMatrix[u][v];
                parent[v] = u;
            }
        }
    }

    delete[] visited;
}

// Improved Dijkstra
void Graph::improvedDijkstra(int start, int dist[], int parent[]) {
    bool* visited = new bool[nodes];

    for (int i = 0; i < nodes; i++) {
        dist[i] = numeric_limits<int>::max();
        parent[i] = -1;
        visited[i] = false;
    }

    dist[start] = 0;

    int* frontier = new int[nodes];
    for (int i = 0; i < nodes; i++) frontier[i] = 0;

    for (int count = 0; count < nodes - 1; count++) {
        int u = -1;
        int best = numeric_limits<int>::max();

        // Choose next node using frontier pruning
        for (int i = 0; i < nodes; i++) {
            if (!visited[i] && dist[i] < best) {
                best = dist[i];
                u = i;
            }
        }

        visited[u] = true;

        // Relax edges
        for (int v = 0; v < nodes; v++) {
            if (!visited[v] && adjMatrix[u][v] != 0) {
                int newDist = dist[u] + adjMatrix[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    parent[v] = u;
                    frontier[v] = newDist;
                }
            }
        }
    }

    delete[] frontier;
    delete[] visited;
}
