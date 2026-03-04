#ifndef BREAKINGSORTINGBARRIER_H
#define BREAKINGSORTINGBARRIER_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

class Graph {
private:
    int nodes;              // Number of nodes
    int** adjMatrix;        // Adjacency matrix

public:
    Graph(int n);           // Constructor
    ~Graph();               // Destructor
    bool addEdge(int u, int v, int w); // Add undirected weighted edge
    void generateDenseGraph();         // Random dense graph generator
    void classicalDijkstra(int start, int dist[], int parent[]);
    void improvedDijkstra(int start, int dist[], int parent[]);
};

#endif
