#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 1e5 + 10;
const int P = 8;
const int B = (1 << 8) + 10;

struct People {
    int a, s[P];
    bool operator <(const People &t) const {
        return a > t.a;
    }
} people[N];

int cnt[B];
long long dp[N][B];

int main() {
//#define _DEBUG
#ifdef _DEBUG
    freopen("input", "r", stdin);
#endif
    int n, p, k;
    scanf("%d%d%d", &n, &p, &k);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &people[i].a);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < p; j++) {
            scanf("%d", &people[i].s[j]);
        }
    }

    sort(people + 1, people + n + 1);

    for (int i = 0; i < (1 << p); i++) {
        cnt[i] = cnt[i >> 1] + (i & 1);
    }

    memset(dp, 0xFE, sizeof(dp));
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int mask = 0; mask < (1 << p); mask++) {
            dp[i][mask] = max(dp[i][mask], dp[i - 1][mask] + (i <= cnt[mask] + k ? people[i].a : 0));
            for (int j = 0; j < p; j++) {
                if (((1 << j) & mask)) {
                    dp[i][mask] = max(dp[i][mask], dp[i - 1][mask ^ (1 << j)] + people[i].s[j]);
                }
            }
        }
    }

    printf("%lld\n", dp[n][(1 << p) - 1]);
    return 0;
}