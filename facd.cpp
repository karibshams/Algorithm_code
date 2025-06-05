#include <iostream>
#include <vector>
using namespace std;

int n, m, k; // total objects, bins, classes
vector<vector<int>> Ar; // initial root distribution

// Function to print a distribution
void Output(const vector<vector<int>>& A) {
    for (const auto& bin : A) {
        cout << "(";
        for (int j = 0; j < k; ++j) {
            cout << bin[j];
            if (j < k - 1) cout << ",";
        }
        cout << ") ";
    }
    cout << endl;
}

// Check if A has a child (non-zero at some level)
bool HasChild(const vector<vector<int>>& A, int level) {
    for (int j = 0; j < k; ++j) {
        if (A[m - 1 - level][j] > 0)
            return true;
    }
    return false;
}

// Generate the first child of A
vector<vector<int>> GenerateFirstChild(const vector<vector<int>>& A, int level) {
    vector<vector<int>> child = A;
    for (int j = 0; j < k; ++j) {
        if (child[m - 1 - level][j] > 0) {
            child[m - 2 - level][j] = 1;
            child[m - 1 - level][j] -= 1;
            break; // only one step to generate first child
        }
    }
    return child;
}

// Check if A has right sibling (non-zero one level right)
bool HasRightSibling(const vector<vector<int>>& A, int level) {
    for (int j = 0; j < k; ++j) {
        if (A[m - level][j] > 0)
            return true;
    }
    return false;
}

// Generate right sibling by transferring one item from right bin
vector<vector<int>> GenerateRightSibling(const vector<vector<int>>& A, int level) {
    vector<vector<int>> sibling = A;
    for (int j = 0; j < k; ++j) {
        if (sibling[m - level][j] > 0) {
            sibling[m - level - 1][j] += 1;
            sibling[m - level][j] -= 1;
            break;
        }
    }
    return sibling;
}

// Generate ancestor Aa of A at level i − q (returns both Aa and q)
pair<vector<vector<int>>, int> GenerateAncestor(const vector<vector<int>>& A, int level) {
    vector<vector<int>> ancestor = A;
    int q = 0;
    for (int i = 1; i < m; ++i) {
        bool isZero = true;
        for (int j = 0; j < k; ++j) {
            if (A[i][j] != 0) {
                isZero = false;
                break;
            }
        }
        if (isZero) q++;
        else break;
    }

    if (q < m) {
        swap(ancestor[0], ancestor[q]);
    }
    return {ancestor, q};
}

// Generate right sibling of ancestor Aa
vector<vector<int>> GenerateRightSiblingOfAncestor(const vector<vector<int>>& Aa, int q) {
    vector<vector<int>> Aas = Aa;
    for (int j = 0; j < k; ++j) {
        if (Aas[q + 1][j] > 0) {
            Aas[q][j] += 1;
            Aas[q + 1][j] -= 1;
            break;
        }
    }
    return Aas;
}

// Recursive procedure
void FindAllChildDistributions2(vector<vector<int>> A, int level) {
    Output(A);

    if (HasChild(A, level)) {
        vector<vector<int>> Ac = GenerateFirstChild(A, level);
        FindAllChildDistributions2(Ac, level + 1);
    }
    else if (HasRightSibling(A, level)) {
        vector<vector<int>> As = GenerateRightSibling(A, level);
        FindAllChildDistributions2(As, level);
    }
    else {
        auto [Aa, q] = GenerateAncestor(A, level);
        if (level - q <= 0) return; // root reached
        vector<vector<int>> Aas = GenerateRightSiblingOfAncestor(Aa, q);
        FindAllChildDistributions2(Aas, level - q);
    }
}

// Entry point of algorithm
void FindAllDistributions2() {
    FindAllChildDistributions2(Ar, 0);
}

// Driver
int main() {
    // Example: n = 3, m = 3, k = 2
    n = 3;
    m = 3;
    k = 2;

    Ar = vector<vector<int>>(m, vector<int>(k, 0));
    Ar[m - 1][0] = 2; // n1 = 2 (e.g. 2 apples)
    Ar[m - 1][1] = 1; // n2 = 1 (e.g. 1 banana)

    FindAllDistributions2();

    return 0;
}
