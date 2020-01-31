#include <cstdio>
#include <iostream>
#include <algorithm>

using namespace std;

using ll = long long;

const int maxn = 2e5 + 5;
int n;
int p[maxn];
ll a[maxn], t[maxn * 4], mn[maxn * 4];

void push_down(int x) {
	t[x << 1] += t[x];
	t[x << 1 | 1] += t[x];
	mn[x << 1] += t[x];
	mn[x << 1 | 1] += t[x];
	t[x] = 0;
}

void update(int l, int r, int x, int a, int b, int d) {
	if(l > b || r < a) {
		return;
	}
	if(l >= a && r <= b) {
		t[x] += d;
		mn[x] += d;
		return;
	}
	push_down(x);
	int mid = (l + r) >> 1;
	update(l, mid, x << 1, a, b, d);
	update(mid + 1, r, x << 1 | 1, a, b, d);
	mn[x] = min(mn[x << 1], mn[x << 1 | 1]);
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &p[i]);
	}
	ll ans = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
		ans += a[i];
	}
	for(int i = 1; i <= n; ++i) {
		update(0, n, 1, p[i], n, a[i]);
    }

	for(int i = 1; i < n; ++i) {
		update(0, n, 1, p[i], n, -a[i]);
		update(0, n, 1, 0, p[i] - 1, a[i]);
		ans = min(ans, mn[1]);
	}
	printf("%lld\n", ans);
	return 0;
}