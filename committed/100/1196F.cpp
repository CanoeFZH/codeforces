#include <bits/stdc++.h>

using namespace std;

const int N = 2e5;

vector<pair<long long, int>> node[N];
set<pair<int, int>> closed_set;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    while(m--) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;

        node[a].push_back({c, b});
        node[b].push_back({c, a});
    }

    priority_queue<tuple<long long, int, int>> pq;

    for(int u = 0; u < n; u++) {
        sort(node[u].begin(), node[u].end());
        node[u].resize(min((int)node[u].size(), k));
        for(auto p: node[u]) {
            if(p.second > u) {
                pq.push({-p.first, u, p.second});
            }
        }
    }
    
    while(pq.size()) {
        long long w;
        int u, v;
        tie(w, u, v) = pq.top();
        pq.pop();
        if (u == v || closed_set.count({u, v})) {
            continue;
        }

        closed_set.insert({u, v});
        w = -w;

        if (--k == 0) {
            cout << w << endl;
            break;
        }

        for(auto p: node[u]) {
            pq.push({-(w + p.first), min(p.second, v), max(p.second, v)});
        }

        for(auto p: node[v]) {
            pq.push({-(w + p.first), min(p.second, u), max(p.second, u)});
        }
    }
    return 0;
}
