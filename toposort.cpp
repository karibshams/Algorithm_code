#include <bits/stdc++.h>
using namespace std;

const int MAX = 100;
struct Queue {
    int items[MAX];
    int start = 0;
    int end = 0;

    bool isEmpty() {
        return start == end;
    }

    void enqueue(int value) {
        items[end++] = value;
    }

    int dequeue() {
        return items[start++];
    }
};
void topologicalSort(int nodes, int edges, int graph[][MAX], int indegree[]) {
    Queue q;
    for (int i = 1; i <= nodes; i++) {
        if (indegree[i] == 0) {
            q.enqueue(i);
        }
    }
    while (!q.isEmpty()) {
        int current = q.dequeue();
        cout << current << " ";
        for (int neighbor = 1; neighbor <= nodes; neighbor++) {
            if (graph[current][neighbor]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.enqueue(neighbor);
                }
            }
        }
    }
}
int main() {
    int nodes, edges;
    cout << "Enter number of nodes and edges:\n";
    cin >> nodes >> edges;
int graph[MAX][MAX] = {0};
int indegree[MAX] = {0};

 cout << "Enter the edges (from node u to node v):\n";
    for (int i = 0; i < edges; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = 1;
        indegree[v]++;
    }
cout << "Topological Sort Order: ";
    topologicalSort(nodes, edges, graph, indegree);
return 0;
}
