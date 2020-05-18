#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int N = 2e5 + 10;
const int INF = 2e9;
const int M = N << 2;

pair <int, int> a[N], b[N];
pair< pair <int, int>, int> c[N];

int max_value[M], add[M];

void build(int k, int l, int r) {
    if (l == r) {
        max_value[k] = -b[l].second;
        return;
    }
    int m = (l + r) >> 1;
    build(k << 1, l, m);
    build(k << 1 | 1, m + 1, r);
    max_value[k] = max(max_value[k << 1], max_value[k << 1 | 1]);
}

inline void push_down(int k) {
    add[k << 1] += add[k];
    add[k << 1 | 1] += add[k];
    max_value[k << 1] += add[k];
    max_value[k << 1 | 1] += add[k];
    add[k] = 0;
}

void update(int k, int l, int r, int ul, int ur, int w) {
    if (l > ur || r < ul) {
        return;
    }

    if (ul <= l && ur >= r) {
        add[k] += w;
        max_value[k] += w;
        return;
    }

    push_down(k);
    int m = (l + r) >> 1;
    update(k << 1, l, m, ul, ur, w);
    update(k << 1 | 1, m + 1, r, ul, ur, w);
    max_value[k] = max(max_value[k << 1], max_value[k << 1 | 1]);
}

int main() {
//#define _DEBUG
#ifdef _DEBUG
    freopen("input", "r", stdin);
#endif

    int n, m, p;
    scanf("%d%d%d", &n, &m, &p);
    for (int i = 1; i <= n; i++) {
        scanf("%d%d", &a[i].first, &a[i].second);
    }

    for (int i = 1; i <= m; i++) {
        scanf("%d%d", &b[i].first, &b[i].second);
    }

    for (int i = 1; i <= p; i++) {
        scanf("%d%d%d", &c[i].first.first, &c[i].first.second, &c[i].second);
    }

    sort(a + 1, a + n + 1);
    sort(b + 1, b + m + 1);
    sort(c + 1, c + p + 1);

    build(1, 1, m);
    int ans = -INF;
    for(int i = 1, last = 1; i <= n; i++) {
        while(last <= p && a[i].first > c[last].first.first) {
            int x = lower_bound(b + 1, b + m + 1, make_pair(c[last].first.second + 1, 0)) - b;
            update(1, 1, m, x, m, c[last].second);
            last++;
        }

        ans = max(ans, max_value[1] - a[i].second);
    }

    printf("%d\n", ans);
    return 0;
}