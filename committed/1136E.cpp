#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define ls (x<<1)
#define rs (ls|1)
#define lson ls,L,mid
#define rson rs,mid+1,R

using namespace std;

const int N = 100010;
const long long INF = 1e17;

int n, Q, x;
long long a[N], t[N], k[N], b[N], y;
long long tag[N << 2], sum[N << 2];
char op;

void push(int x, int L, int R) {
	int mid = (L + R) >> 1;
	if (tag[x] != INF) {
		sum[ls] = tag[x] * (mid - L + 1);
		sum[rs] = tag[x] * (R - mid);
		tag[ls] = tag[rs] = tag[x];
		tag[x] = INF;
	}
}

void build(int x, int L, int R) {
	int mid = (L + R) >> 1;
	tag[x] = INF;
	if (L == R) {
		sum[x] = b[L];
		return;
	}
	build(lson);
	build(rson);
	sum[x] = sum[ls] + sum[rs];
}

void modify(int x, int L, int R, int l, int r, long long k) {
	if (L == l && R == r) {
		tag[x] = k;
		sum[x] = k * (r - l + 1);
		return;
	}
	int mid = (L + R) >> 1;
	push(x, L, R);
	if (r <= mid) { 
		modify(lson, l, r, k);
	} else if (l > mid) {
		modify(rson, l, r, k);
	} else {
		modify(lson, l, mid, k);
		modify(rson, mid + 1, r, k);
	}
	sum[x] = sum[ls] + sum[rs];
}

long long query(int x, int L, int R, int l, int r) {
	if (L == l && R == r) {
		return sum[x];
	}
	int mid = (L + R) >> 1;
	push(x, L, R);
	if (r <= mid) {
		return query(lson, l, r);
	} else if (l > mid) {
		return query(rson, l, r);
	} else {
		return query(lson, l, mid) + query(rson, mid + 1, r);
	}
}

int main() {

	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a[i];
	}
	for (int i = 1; i < n; i++) {
		cin >> k[i];
		k[i] += k[i - 1];
		t[i] = t[i - 1] + k[i];
		b[i] = a[i] - k[i - 1];
	}
	b[n] = a[n] - k[n - 1];
	build(1, 1, n);
	cin >> Q;
	while (Q--) {
		cin >> op >> x >> y;
		if (op == 's') {
			cout << query(1, 1, n, x, y) + t[y - 1] - (x >= 2 ? t[x - 2] : 0) << endl;
		} else {
			int l = x, r = n, res = l;
			long long cmp = query(1, 1, n, x, x) + y;
			while (l <= r) {
				int mid = (l + r) >> 1;
				if (query(1, 1, n, mid, mid) >= cmp) {
					r = mid - 1;
				} else {
					res = mid;
					l = mid + 1;
				}
			}
			modify(1, 1, n, x, res, cmp);
		}
	}
	return 0;
}