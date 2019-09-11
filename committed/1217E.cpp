#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 200 * 1000 + 13;
const int INF = 2e9;
const int LOGN = 9;

struct node {
    int best;
    int mn[LOGN];

    node() {
        best = INF;
        for(int i = 0; i < LOGN; i++) {
            mn[i] = INF;
        }
    }

    int& operator[] (int x) {
        return mn[x];
    }
};

int a[N];
node tree[4 * N];

void update(node &t, int val) {
    int x = val;
    for(int i = 0; i < LOGN; i++) {
        if (x % 10 != 0) {
            t[i] = min(t[i], val);
        }

        x /= 10;
    }
}

node merge(node &a, node &b) {
    node c;
    c.best = min(a.best, b.best);
    for(int i = 0; i < LOGN; i++) {
        c[i] = min(a[i], b[i]);
        if (a[i] < INF && b[i] < INF) {
            c.best = min(c.best, a[i] + b[i]);
        }
    }

    return c;
}

void build(int v, int l, int r) {
    if (l == r - 1) {
        tree[v] = node();
        update(tree[v], a[l]);
        return;
    }

    int m = (l + r) / 2;
    build(v * 2, l, m);
    build(v * 2 + 1, m, r);
    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

void update(int v, int l, int r, int pos, int val) {
    if (l == r - 1) {
        tree[v] = node();
        update(tree[v], val);
        return;
    }

    int m = (l + r) / 2;
    if (pos < m) {
        update(v * 2, l, m, pos, val);
    } else {
        update(v * 2 + 1, m, r, pos, val);
    }

    tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
}

node get(int v, int l, int r, int query_l, int query_r) {
    if (l == query_l && r == query_r) {
        return tree[v];
    }

    int m = (l + r) / 2;
    if (query_r <= m) {
        return get(v * 2, l, m, query_l, query_r);
    }

    if (query_l >= m) {
        return get(v * 2 + 1, m, r, query_l, query_r);
    }

    node left = get(v * 2, l, m, query_l, m);
    node right = get(v * 2 + 1, m, r, m, query_r);
    return merge(left, right);
}

int main() {
    int n, m;
    scanf("%d%d", &n, &m);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }

    build(1, 0, n);

    for (int i = 0; i < m; i++) {
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        --x;

        if (t == 1) {
            update(1, 0, n, x, y);
        } else {
            node res = get(1, 0, n, x, y);
            printf("%d\n", res.best == INF ? -1 : res.best);
        }
    }

    return 0;
}
