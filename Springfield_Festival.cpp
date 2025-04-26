#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

static const double INF = numeric_limits<double>::infinity();

struct Edge {
    int to;
    double cost;
};

struct PairComparator {
    bool operator()(const pair<double,int> &a, const pair<double,int> &b) const {
        return a.first > b.first;
    }
};

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    unordered_map<string,int> stallID;
    stallID.reserve(N);
    stallID.max_load_factor(0.7f);

    vector<string> stallNames;
    vector<long long> stallTax;
    vector<vector<Edge>> adj;
    int currentID = 0;

    auto addStall = [&](const string &name, long long tax){
        stallID[name] = currentID;
        stallNames.push_back(name);
        stallTax.push_back(tax);
        adj.push_back({});
        ++currentID;
    };

    for(int i = 0; i < N; i++){
        string cmd;
        cin >> cmd;
        if(cmd == "ADD"){
            string name;
            long long tax;
            cin >> name >> tax;
            addStall(name, tax);
        } else if(cmd == "CONNECT"){
            string s1, s2;
            long long dist;
            cin >> s1 >> s2 >> dist;
            int id1 = stallID[s1], id2 = stallID[s2];
            double cost = double(dist) / (stallTax[id1] + stallTax[id2]);
            adj[id1].push_back({id2, cost});
            adj[id2].push_back({id1, cost});
        } else if(cmd == "PRINT_MIN"){
            int n = currentID;
            vector<bool> used(n, false);
            vector<double> minEdge(n, INF);
            vector<int> parent(n, -1);
            vector< pair<int,int> > mstEdges;
            mstEdges.reserve(n - 1);

            for(int start = 0; start < n; start++){
                if(!used[start]){
                    minEdge[start] = 0.0;
                    priority_queue< pair<double,int>,
                                    vector< pair<double,int> >,
                                    PairComparator > pq;
                    pq.push(make_pair(0.0, start));

                    while(!pq.empty()){
                        auto top = pq.top();
                        pq.pop();
                        double c = top.first;
                        int u = top.second;

                        if(used[u]) continue;
                        used[u] = true;
                        if(parent[u] != -1) mstEdges.push_back(make_pair(parent[u], u));

                        for(auto &e : adj[u]){
                            int v = e.to;
                            double w = e.cost;
                            if(!used[v] && w < minEdge[v]){
                                minEdge[v] = w;
                                parent[v] = u;
                                pq.push(make_pair(w, v));
                            }
                        }
                    }
                }
            }

            for(int i = 0; i < (int)mstEdges.size(); i++){
                int u = mstEdges[i].first;
                int v = mstEdges[i].second;
                cout << stallNames[u] << ":" << stallNames[v];
                if(i + 1 < (int)mstEdges.size()) cout << " ";
            }
            cout << "\n";
        }
    }
    return 0;
}
