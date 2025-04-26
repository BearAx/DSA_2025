#include <iostream>
#include <vector>

using namespace std;

int find(vector<int>& parent, int a) {
    if (parent[a] != a)
        parent[a] = find(parent, parent[a]);
    return parent[a];
}

void unionSets(vector<int>& parent, vector<int>& rank, int a, int b) {
    a = find(parent, a);
    b = find(parent, b);
    if (a != b) {
        if (rank[a] < rank[b]) {
            int temp = a;
            a = b;
            b = temp;
        }
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, m;
    cin >> n >> m;
    
    vector<int> parent(n + 1), rank(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        parent[i] = i;
    }
    
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        unionSets(parent, rank, u, v);
    }
    
    int components = 0;
    for (int i = 1; i <= n; ++i) {
        if (find(parent, i) == i)
            components++;
    }
    
    cout << components << "\n";
    return 0;
}
