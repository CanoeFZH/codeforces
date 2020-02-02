#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cstdlib>
#include <iostream>

using namespace std;

const int N = 110;
const int MOD = 998244353;
typedef long long ll;

ll l[N], r[N], s[N], dp[N][N];

ll quick_mod(ll x, int y) {
    ll acc = 1;
    for( ; y; y >>= 1) {
        if (y & 1) {
            acc = acc * x % MOD;
        }
        x = x * x % MOD;
    }
    return acc;
}

ll cnm(ll n, int m) {
    ll acc = 1;
    for(int i = 1; i <= m; i++) {
        acc = acc * (n + m - i) % MOD * quick_mod(i, MOD - 2) % MOD;
    }
    return acc;
}

int main() {
    int n;
    ll total_size = 1;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
        s[i * 2 - 1] = l[i];
        s[i * 2] = ++r[i];
        total_size = (r[i] - l[i]) * total_size % MOD;
    }

    sort(s + 1, s + 2 * n + 1);
    int points = unique(s + 1, s + 2 * n + 1) - (s + 1);
    for (int i = 1; i <= n; i++) {
        l[i] = lower_bound(s + 1, s + points + 1, l[i]) - s;
        r[i] = lower_bound(s + 1, s + points + 1, r[i]) - s;
    }

    for (int i = 1; i <= points + 1; i++) {
        dp[0][i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for(int j = l[i]; j < r[i]; j++) {
            for (int k = i - 1; k >= 0; k--) {
                //cout << "i:" << i << " j:" << j << " k:" << k << " size:" << s[j + 1] - s[j] << endl;
                dp[i][j] = (dp[i][j] + dp[k][j + 1] * cnm(s[j + 1] - s[j], i - k)) % MOD;
                if (l[k] > j || r[k] <= j) {
                    break;
                }
            }
        }
        for (int j = points; j >= 1; j--) {
            dp[i][j] = (dp[i][j] + dp[i][j + 1]) % MOD;
        }
    }

    cout << dp[n][1] * quick_mod(total_size, MOD - 2) % MOD << endl;
    return 0;
}