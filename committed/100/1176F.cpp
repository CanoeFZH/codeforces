#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

using namespace std;

const int N = 3e5 + 10;
const long long INF = 1e18;

long long dp[N][10], b[4][4], c[4][4];
pair<long long, int> p[N];

int main() {
    int n, m;
    cin >> n;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= 9; j++) {
            dp[i][j] = -INF;
        }
    }
    dp[0][0] = 0;

    for(int i = 1; i <= n; i++) {
        cin >> m;
        for(int j = 1; j <= m; j++) {
            cin >> p[j].second >> p[j].first;
        }

        sort(p + 1, p + m + 1);
        for (int j = 0; j <= 3; j++) {
            for (int k = 1; k <= 3; k++) {
                b[j][k] = c[j][k] = -INF;
            }
        }

        for (int j = 1; j <= m; j++) {
            for (int k = 3; k >= p[j].second; k--) {
                for (int l = 1; l <= 3; l++) {
                    b[k][l] = max(b[k][l], b[k - p[j].second][l - 1] + p[j].first);
                    c[k][l] = max(c[k][l], b[k - p[j].second][l - 1] + 2 * p[j].first);
                }
            }
        }

        for (int j = 0; j <= 9; j++) {
            for (int k = 0; k <= 3; k++) {
                if (j < k) {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - k + 10] + c[3][k]);
                } else {
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - k] + b[3][k]);
                }
            }
        }
    }

    long long ans = 0;
    for (int i = 0; i < 10; i++) {
        ans = max(ans, dp[n][i]);
    }
    cout << ans << endl;
    return 0;
}
