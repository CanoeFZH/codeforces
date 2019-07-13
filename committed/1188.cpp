#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

const int N = 1024;
const int A = 100000;
const int MOD = 998244353;

long long dp[N][N];
int a[N];

int main() {
    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    sort(a + 1, a + n + 1);
    
    long long ans = 0;
    for (int i = 0; i <= A / (k - 1); i++) {
        int last = 0;
        for (int j = 1; j <= n; j++) {
            while(last < j && a[j] - a[last + 1] >= i) {
                last++;
            }

            for (int x = 1; x <= k; x++) {
                dp[j][x] = dp[j - 1][x] + dp[last][x - 1] + (x == 1);
                dp[j][x] %= MOD;
            }
        }

        ans += dp[n][k];
    }
    
    cout << ans % MOD << endl;
    return 0;
}
