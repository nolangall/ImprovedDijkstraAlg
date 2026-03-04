#include "BreakingSortingBarrier.h"
#include <chrono>
using namespace std;

bool compareResults(int* d1, int* d2, int N) {
    for (int i = 0; i < N; i++)
        if (d1[i] != d2[i])
            return false;
    return true;
}

int main() {
    int N;
    cout << "Enter number of nodes: ";
    cin >> N;

    Graph g(N);
    g.generateDenseGraph();

    int* distClassic = new int[N];
    int* parentClassic = new int[N];
    int* distImproved = new int[N];
    int* parentImproved = new int[N];

    int start = 0;

    double classicalTotal = 0.0;
    double improvedTotal = 0.0;

    for (int i = 0; i < 30; i++) {
        auto t1 = chrono::high_resolution_clock::now();
        g.classicalDijkstra(start, distClassic, parentClassic);
        auto t2 = chrono::high_resolution_clock::now();
        classicalTotal += chrono::duration<double>(t2 - t1).count();  // seconds

        auto i1 = chrono::high_resolution_clock::now();
        g.improvedDijkstra(start, distImproved, parentImproved);
        auto i2 = chrono::high_resolution_clock::now();
        improvedTotal += chrono::duration<double>(i2 - i1).count();  // seconds

        if (!compareResults(distClassic, distImproved, N)) {
            cout << "ERROR: Distances do not match!\n";
            return 0;
        }
    }

    cout << "\nCorrectness Match: YES\n";
    cout << "Average Classical Dijkstra: " << classicalTotal / 30.0 << " seconds\n";
    cout << "Average Improved Dijkstra:  " << improvedTotal / 30.0 << " seconds\n";

    delete[] distClassic;
    delete[] parentClassic;
    delete[] distImproved;
    delete[] parentImproved;

    return 0;
}
