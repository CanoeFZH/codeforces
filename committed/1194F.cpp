#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 200005;
const int MOD = 1000000007;
const int INV = (MOD + 1) / 2;

typedef long long ll;

ll f[N], rev[N], fac[N];

ll quickPow(ll a, int b) {
    ll res = 1;
    for (; b; b >>= 1) {
        if (b & 1) {
            res = res * a % MOD;
        }

        a = a * a % MOD;
    }

    return res;
}

ll C(int a, int b) {
    if (a < b) {
        return 0;
    }

    return fac[a] * rev[b] % MOD * rev[a - b] % MOD;
}

int main() {
    int n;
    ll T;
    cin >> n >> T;

    fac[0] = 1;
    for (int i = 1; i <= n; i++) {
        fac[i] = fac[i - 1] * i % MOD;
    }
    
    rev[n] = quickPow(fac[n], MOD - 2);
    for (int i = n; i >= 1; i--) {
        rev[i - 1] = rev[i] * i % MOD;
    }

    f[0] = 1;
    for (int i = 1; i <= n; i++) {
        int t;
        cin >> t;
        ll a = T;
        ll b = T - t;
        T = b;
        if (b < 0) {
            break;
        }

        f[i] = 2 * f[i - 1] % MOD;
        if (b >= i) {
            continue;
        }
        // b < i, not enough time for extra time.
        ll res = 0;
        for (int j = b; j < i && j <= a; j++) {
            res += C(i - 1, j) * (1 + (j > b)) % MOD;
        }

        f[i] = (f[i] - res % MOD + MOD) % MOD;
    }

    ll ans = 0, mul = 1;
    for (int i = 1; i <= n; i++) {
        mul = mul * INV % MOD;
        ans = (ans + f[i] * mul % MOD) % MOD;
    }

    cout << ans << endl;
    return 0;
}
