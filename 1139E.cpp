#include <cstdio>
#include <iostream>
#include <vector>
#include <cstring>

using namespace std;

const int N = 5022;

vector<int> adj[N];
int c[N], p[N], k[N];
int match[N], ans[N];
bool used[N], deleted[N];
int max_matching;

int DFS(int u) {
    if (used[u]) {
        return 0;
    }
    used[u] = 1;
    for(int v: adj[u]) {
        if (match[v] == -1 || DFS(match[v])) {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}

void matching() {
    while(1) {
        memset(used, 0, sizeof(used));
        if(DFS(max_matching)) {
            max_matching++;
        } else {
            break;
        }
    }
}

int main() {
    int n, m, d;
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> p[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    cin >> d;
    for (int i = 1; i <= d; i++) {
        cin >> k[i];
        deleted[k[i]] = 1;
    }
    for (int i = 1; i <= n; i++) {
        if (!deleted[i]) {
            adj[p[i]].push_back(c[i]);
        }
    }
    max_matching = 0;
    memset(match, -1, sizeof(match));
    for (int i = d; i>= 1; i--) {
        matching();
        ans[i] = max_matching;
        adj[p[k[i]]].push_back(c[k[i]]);
    }

    for (int i = 1; i <= d; i++) {
        cout << ans[i] << endl;
    }
    return 0;
}