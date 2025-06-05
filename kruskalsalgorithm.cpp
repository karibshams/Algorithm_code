#include <iostream>
using namespace std;

const int MAX = 100;

struct Edge {
    int u, v, weight;
};

void sortEdges(Edge edges[], int e) {
    for (int i = 0; i < e - 1; i++) {
        for (int j = i + 1; j < e; j++) {
            if (edges[i].weight > edges[j].weight) {
                Edge temp = edges[i];
                edges[i] = edges[j];
                edges[j] = temp;
            }
        }
    }
}

// Find root of a node
int find(int parent[], int u) {
    while (u != parent[u]) {
        u = parent[u];
    }
    return u;
}

// Union two clusters
void unite(int parent[], int uRoot, int vRoot) {
    parent[vRoot] = uRoot;
}

int main() {
    int n, e;
    Edge edges[MAX], mst[MAX];
    int parent[MAX];

    cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    cout << "Enter edges (u v weight):" << endl;
    for (int i = 0; i < e; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }

    // Initialize clusters (each node is its own cluster)
    for (int i = 0; i < n; i++) {
        parent[i] = i;
    }

    // Sort edges by weight
    sortEdges(edges, e);

    int count = 0;  // edges added to MST
    int totalCost = 0;

    for (int i = 0; i < e && count < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;

        int rootU = find(parent, u);
        int rootV = find(parent, v);

        if (rootU != rootV) {
            mst[count++] = edges[i];
            totalCost += w;
            unite(parent, rootU, rootV);
        }
    }

    cout << "\nMinimum Spanning Tree:" << endl;
    for (int i = 0; i < count; i++) {
        cout << mst[i].u << " - " << mst[i].v << " : " << mst[i].weight << endl;
    }

    cout << "Total cost of MST: " << totalCost << endl;

    return 0;
}
