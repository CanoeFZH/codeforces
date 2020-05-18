#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 86;
const int INF = 1e9;

int c[N][N], dp[N][N], tag[N];

int main() {

//#define _DEBUG
#ifdef _DEBUG
    freopen("input", "r", stdin);
#endif

    srand(time(0));
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            scanf("%d", c[i] + j);
        }
    }

    int ans = INF;
    for (int t = 0; t < 3000; t++) {
        for (int i = 2; i <= n; i++) {
            tag[i] = rand() % 2;
        }

        memset(dp, 0x3f, sizeof dp);
        dp[1][0] = 0;
        for (int r = 1; r <= k; r++) {
            for (int u = 1; u <= n; u++) {
                for (int v = 1; v <= n; v++) {
                    if (tag[u] ^ tag[v]) {
                        dp[v][r] = min(dp[v][r], dp[u][r - 1] + c[u][v]);   
                    }
                }
            }
        }
        ans = min(ans, dp[1][k]);
    }
    printf("%d\n", ans);
    return 0;
}