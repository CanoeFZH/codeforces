#include <iostream>
#include <algorithm>
#include <cstdio>

using namespace std;

const int N = 4e5;
int a[N], b[N];

int main() {
#define _DEBUG
#ifndef _DEBUG
    freopen("input", "r", stdin);
#endif
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    int ans = 0;
    for (int mask = 1; mask < (1 << 29); mask <<= 1) {
        for (int i = 0; i < n; i++) {
            b[i] = (a[i] & (mask - 1));
        }

        sort(b, b + n);
        int r = n - 1, carry = 0;
        for (int l = 0; l < n; l++) {
            while (r >= 0 && b[l] + b[r] >= mask) {
                r--;
            }
            // b[l] + b[r + 1 ... n - 1] >= mask
            // if l == r, -1 for case a[l] == a[r], and same with r > l
            carry += (n - 1) - r - (r < l);
        }
        // n is even, add will be add odd times
        if ((n - 1) & 1) {
            for (int i = 0; i < n; i++) {
                ans ^= a[i] & mask;
            }
        }
        // l < r and l > r
        if ((carry / 2) & 1) {
            ans ^= mask;
        }
    }

    cout << ans << endl;
    return 0;
}
