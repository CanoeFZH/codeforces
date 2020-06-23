#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;

const int INF = 1e9;
const int N = 1010;

vector<int> adj[N], depth(N), max_depth(N);

int n, root, dist;

void dfs(int u, int p) {
  max_depth[u] = depth[u];
  for (auto v : adj[u]) {
    if (v == p) {
      continue;
    }
    depth[v] = 1 + depth[u];
    dfs(v, u);
    max_depth[u] = max(max_depth[v], max_depth[u]);
  }
}

void find_nodes(int u, int p, int req_depth, vector<int> &nodes) {
  if (depth[u] == req_depth) {
    nodes.push_back(u);
    return;
  }

  for (auto v : adj[u]) {
    if (v != p && max_depth[v] <= n / 2) {
      find_nodes(v, u, req_depth, nodes);
    }
  }
}

pair<int, int> query(vector<int> &nodes) {
  cout << "? " << nodes.size() << " ";
  for (int node : nodes) {
    cout << node << " ";
  }
  cout << endl;

  fflush(stdout);

  int x, d;
  cin >> x >> d;
  return {x, d};
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("input", "r", stdin);
#endif
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  int t;
  cin >> t;
  while (t--) {
    cin >> n;
    for (int i = 1; i <= n; i++) {
      adj[i].clear();
      depth[i] = 0;
      max_depth[i] = 0;
    }

    for (int i = 1; i < n; i++) {
      int u, v;
      cin >> u >> v;
      adj[u].push_back(v);
      adj[v].push_back(u);
    }

    vector<int> nodes;
    for (int i = 1; i <= n; i++) {
      nodes.push_back(i);
    }

    pair<int, int> r = query(nodes);
    root = r.first, dist = r.second;
    dfs(root, 0);

    int s = 0, e = n / 2, first_node = root;
    while (s <= e) {
      int m = (s + e) / 2;
      vector<int> node_set;
      find_nodes(root, 0, m, node_set);

      if (node_set.empty()) {
        e = m - 1;
      } else {
        pair<int, int> r = query(node_set);
        if (r.second == dist) {
          first_node = r.first;
          s = m + 1;
        } else {
          e = m - 1;
        }
      }
    }

    vector<int> candidate_second;
    queue<pair<int, int> > q;
    vector<int> vis(N + 1);
    q.push({first_node, 0});

    while (!q.empty()) {
      pair<int, int> u = q.front();
      q.pop();

      vis[u.first] = 1;
      if (u.second == dist) {
        candidate_second.push_back(u.first);
      }

      for (auto v : adj[u.first]) {
        if (!vis[v]) {
          vis[v] = 1;
          q.push({v, u.second + 1});
        }
      }
    }

    r = query(candidate_second);
    cout << "! " << first_node << " " << r.first << endl;
    string correct;
    cin >> correct;
  }
  return 0;
}
