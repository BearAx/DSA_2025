#include <iostream>
#include <vector>
#include <list>
#include <unordered_map>
#include <unordered_set>
#include <queue>

using namespace std;

template<typename VLabel, typename ELabel>
class Graph {
private:
    struct Edge;

    struct Vertex {
        VLabel label;
        list<Edge> edges;
        Vertex(const VLabel &l) : label(l) {}
    };

    struct Edge {
        VLabel from;
        VLabel to;
        ELabel label;
        Edge(const VLabel &f, const VLabel &t, const ELabel &l) : from(f), to(t), label(l) {}
    };

    list<Vertex> vertices;
    list<Edge> edges;
    unordered_map<VLabel, typename list<Vertex>::iterator> vertex_map;

public:
    void add_vertex(const VLabel &label) {
        if (vertex_map.find(label) == vertex_map.end()) {
            vertices.emplace_back(label);
            vertex_map[label] = --vertices.end();
        }
    }

    void add_edge(const VLabel &from, const VLabel &to, const ELabel &label) {
        auto it = vertex_map.find(from);
        if (it != vertex_map.end()) {
            Edge e(from, to, label);
            it->second->edges.push_back(e);
            edges.push_back(e);
        }
    }

    unordered_set<VLabel> AleksandrMedvedev_bfs(const vector<VLabel> &start) {
        unordered_set<VLabel> visited;
        queue<VLabel> q;
        for (const auto &s : start) {
            if (vertex_map.find(s) != vertex_map.end() && visited.find(s) == visited.end()) {
                q.push(s);
                visited.insert(s);
            }
        }
        while (!q.empty()) {
            VLabel current = q.front();
            q.pop();
            auto vit = vertex_map.find(current);
            if (vit == vertex_map.end()) continue;
            for (const auto &e : vit->second->edges) {
                VLabel neighbor = e.to;
                if (visited.find(neighbor) == visited.end()) {
                    visited.insert(neighbor);
                    q.push(neighbor);
                }
            }
        }
        return visited;
    }

    vector<VLabel> AleksandrMedvedev_topsort() {
        unordered_map<VLabel, int> in_degree;
        unordered_map<VLabel, vector<VLabel>> adj;
        for (const auto &v : vertices) {
            in_degree[v.label] = 0;
            adj[v.label] = vector<VLabel>();
        }
        for (const auto &e : edges) {
            adj[e.from].push_back(e.to);
            in_degree[e.to]++;
        }
        queue<VLabel> q;
        for (const auto &v : vertices) {
            if (in_degree[v.label] == 0) q.push(v.label);
        }
        vector<VLabel> order;
        while (!q.empty()) {
            VLabel u = q.front();
            q.pop();
            order.push_back(u);
            for (const VLabel &v : adj[u]) {
                if (--in_degree[v] == 0) q.push(v);
            }
        }
        if (order.size() != vertices.size()) return vector<VLabel>();
        return order;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, r;
    cin >> n >> r;

    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<int> roots(r);
    for (int i = 0; i < r; ++i) cin >> roots[i];

    Graph<int, int> g;
    for (int i = 0; i < n; ++i) g.add_vertex(i);
    for (int i = 0; i < n; ++i) if (a[i] >= 0) g.add_edge(i, a[i], 0);

    unordered_set<int> visited = g.AleksandrMedvedev_bfs(roots);
    vector<bool> garbage(n, true);
    for (int v : visited) garbage[v] = false;

    vector<pair<int, int>> blocks;
    int start = -1, cnt = 0;
    for (int i = 0; i < n; ++i) {
        if (garbage[i]) {
            if (start == -1) start = i;
            cnt++;
        } else {
            if (start != -1) {
                blocks.emplace_back(start, cnt);
                start = -1;
                cnt = 0;
            }
        }
    }
    if (start != -1) blocks.emplace_back(start, cnt);

    cout << blocks.size() << "\n";
    for (const auto &p : blocks) cout << p.first << " " << p.second << "\n";
}