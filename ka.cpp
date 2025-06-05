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
int findCluster(int cluster[], int v) {
    if (cluster[v] != v) {
        cluster[v] = findCluster(cluster, cluster[v]);
    }
    return cluster[v];
}
void mergeCluster(int cluster[], int uRoot, int vRoot) {
    cluster[vRoot] = uRoot;
}
int main() {
int n, e;
Edge edges[MAX], T[MAX];
int cluster[MAX];
cout << "Enter number of vertices and edges: ";
    cin >> n >> e;

    cout << "Enter edges (u v weight):" << endl;
    for (int i = 0; i < e; i++) {
        cin >> edges[i].u >> edges[i].v >> edges[i].weight;
    }
    for (int i = 0; i < n; i++) {
        cluster[i] = i;
    }
    sortEdges(edges, e);
int edgeCount = 0;
int totalCost = 0;
    for (int i = 0; i < e && edgeCount < n - 1; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].weight;
        int cu = findCluster(cluster, u);
        int cv = findCluster(cluster, v);
        if (cu != cv) {
            T[edgeCount++] = edges[i];
            totalCost += w;
            mergeCluster(cluster, cu, cv);
        }
    }
cout << "\nMinimum Spanning Tree edges:\n";
    for (int i = 0; i < edgeCount; i++) {
        cout << T[i].u << " - " << T[i].v << " : " << T[i].weight << endl;
    }
cout << "Total cost: " << totalCost << endl;
return 0;
}
