#include <bits/stdc++.h>

using namespace std;

const int N = 300000 + 13;

int a[N];
vector <int> g[N];
int red_total_count = 0, blue_total_count = 0;
int answer = 0;

pair <int, int> dfs(int u, int p = -1) {
    int r = (a[u] == 1), b = (a[u] == 2);
    for (auto v: g[u])  {
        if (v == p) {
            continue;
        }
        auto sub_tree = dfs(v, u);
        answer += (sub_tree.first == red_total_count && sub_tree.second == 0);
        answer += (sub_tree.first == 0 && sub_tree.second == blue_total_count);
        r += sub_tree.first;
        b += sub_tree.second;
    }
    return make_pair(r, b);
}

int main() {
    int n;
    cin >> n;
    for(int i = 0; i < n; i++) {
        cin >> a[i];
        red_total_count += (a[i] == 1);
        blue_total_count += (a[i] == 2);
    }
    int u, v;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(0);
    cout << answer << endl;
    return 0;
}