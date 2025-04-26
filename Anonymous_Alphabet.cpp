//Medvedev Aleksandr DSAI-03
//I use materials from Lab 10 and Tutorial slides
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <list>

using namespace std;

template<typename V, typename E>
class Graph {
public:
    struct Vertex {
        V label;
        list<typename list<Vertex>::iterator> edges;
        Vertex(V l) : label(l) {}
    };

    list<Vertex> vertices;
    unordered_map<V, typename list<Vertex>::iterator> vertex_map;

    void addVertex(V label) {
        if (vertex_map.find(label) == vertex_map.end()) {
            vertices.emplace_back(label);
            auto it = --vertices.end();
            vertex_map[label] = it;
        }
    }

    void addEdge(V from, V to) {
        auto from_it = vertex_map.find(from);
        auto to_it = vertex_map.find(to);
        if (from_it == vertex_map.end() || to_it == vertex_map.end()) return;

        for (auto& e : from_it->second->edges) {
            if (e == to_it->second) return;
        }
        from_it->second->edges.push_back(to_it->second);
    }

    list<V> AleksandrMedvedev_topsort() {
        unordered_map<V, bool> visited;
        unordered_map<V, bool> onStack;
        list<V> result;

        for (auto& v : vertices) {
            if (!visited[v.label]) {
                if (!AleksandrMedvedev_dfs(v.label, visited, onStack, result)) {
                    return {};
                }
            }
        }

        result.reverse();
        return result;
    }

private:
    bool AleksandrMedvedev_dfs(V label, unordered_map<V, bool>& visited, unordered_map<V, bool>& onStack, list<V>& result) {
        if (onStack[label]) return false;
        if (visited[label]) return true;

        visited[label] = true;
        onStack[label] = true;

        auto v_it = vertex_map[label];
        for (auto& target : v_it->edges) {
            if (!AleksandrMedvedev_dfs(target->label, visited, onStack, result)) {
                return false;
            }
        }

        onStack[label] = false;
        result.push_back(label);
        return true;
    }
};

bool validateWords(const vector<string>& words) {
    for (size_t i = 0; i < words.size() - 1; ++i) {
        const string& a = words[i];
        const string& b = words[i + 1];
        size_t min_len = min(a.size(), b.size());
        size_t pos = 0;
        while (pos < min_len && a[pos] == b[pos]) ++pos;
        if (pos == min_len && a.size() > b.size()) return false;
    }
    return true;
}

vector<char> getUniqueChars(const vector<string>& words) {
    vector<char> chars;
    unordered_map<char, bool> exists;
    for (const auto& word : words) {
        for (char c : word) {
            if (!exists[c]) {
                exists[c] = true;
                chars.push_back(c);
            }
        }
    }
    return chars;
}

void buildDependencies(Graph<char, bool>& graph, const vector<string>& words) {
    for (size_t i = 0; i < words.size() - 1; ++i) {
        const string& a = words[i];
        const string& b = words[i + 1];
        size_t min_len = min(a.size(), b.size());
        size_t pos = 0;
        while (pos < min_len && a[pos] == b[pos]) ++pos;
        if (pos < min_len) {
            graph.addEdge(a[pos], b[pos]);
        }
    }
}

int main() {
    int N;
    cin >> N;
    vector<string> words(N);
    for (int i = 0; i < N; ++i) {
        cin >> words[i];
    }

    if (!validateWords(words)) {
        cout << "Doh" << endl;
        return 0;
    }

    vector<char> chars = getUniqueChars(words);
    Graph<char, bool> graph;
    for (char c : chars) graph.addVertex(c);

    buildDependencies(graph, words);

    list<char> order = graph.AleksandrMedvedev_topsort();

    if (order.size() != chars.size()) {
        cout << "Doh" << endl;
    } else {
        for (char c : order) cout << c;
        cout << endl;
    }

    return 0;
}