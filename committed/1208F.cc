#include <cstdio>
#include <iostream>

const int N = 1 << 21;

int c[N], a[N];

void insert(int x, int b) {
    if (c[x] >= 2) {
        return;
    }

    if (b == -1) {
        return void(++c[x]);
    }

    insert(x, b - 1);
    if (x >> b & 1) {
        insert(x ^ 1 << b, b - 1);
    }
}

int query(int x) {
    int ret = 0, p = 0;
    for (int i = 20; ~i; --i) {
        if (x >> i & 1) {
            ret |= 1 << i;
        } else if (c[p | 1 << i] >= 2) {
            ret |= 1 << i;
            p |= 1 << i;
        }
    }

    return ret;
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
	std::cin >> n;

    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }

    int answer = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (i < n - 2) {
            answer = std::max(query(a[i]), answer);
        }
        insert(a[i], 20);
    }

    std::cout << answer << std::endl;
    return 0;
}
