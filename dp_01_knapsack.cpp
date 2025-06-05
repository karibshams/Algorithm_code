#include <bits/stdc++.h>
using namespace std;
int M[100][100];
bool C[100][100];

void knapsack(int B, int n, int cost[], int volume[]) {
    int b, i;
    for (b = 0; b <= B; b++) {
        if (volume[1] <= b) {
            M[1][b] = cost[1];
            C[1][b] = true;
        } else {
            M[1][b] = 0;
            C[1][b] = false;
        }
    }
    for (i = 2; i <= n; i++) {
        for (b = 0; b <= B; b++) {
            if (volume[i] <= b && M[i - 1][b - volume[i]] + cost[i] > M[i - 1][b]) {
                M[i][b] = M[i - 1][b - volume[i]] + cost[i];
                C[i][b] = true;
            } else {
                M[i][b] = M[i - 1][b];
                C[i][b] = false;
            }
        }
    }
cout << "\nThe solution is\n";
cout << "Optimum: " << M[n][B] << endl;

 b = B;
for (int i = n; i >= 1; i--) {
    if (C[i][b]) {
            cout << "Item " << i << " Cost " << cost[i] << " Volume " << volume[i] << endl;
           b -= volume[i];
        }
    }
}
int main() {
    int cost[100], volume[100];
    int n, B;

cout << "Enter the number of items: ";
cin >> n;
cout << "Enter the knapsack capacity: ";
cin >> B;

cout << "Enter the weight and value of the items:\n";
  for (int i = 1; i <= n; i++) {
        cout << "Item " << i << " - Volume and Cost: ";
        cin >> volume[i] >> cost[i];
    }
  knapsack(B, n, cost, volume);
return 0;
}
