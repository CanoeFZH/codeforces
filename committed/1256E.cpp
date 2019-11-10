#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int N = 200043;
const int INF = int(1e9) + 43;

int n;
int dp[N], t[N], p[N];
pair<int, int> a[N];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        a[i].second = i;
        scanf("%d", &a[i].first);
    }

    sort(a, a + n);
    for (int i = 1; i <= n; i++) {
        dp[i] = INF;
        p[i] = -1;
    }
    
    for (int i = 0; i < n; i++) {
        for (int j = 3; j <= 5 && i + j <= n; j++) {
            int diff = a[i + j - 1].first - a[i].first;
            if (dp[i + j] > dp[i] + diff) {
                dp[i + j] = dp[i] + diff;
                p[i + j] = i;
            }
        }
    }

    int cur = n, cnt = 0;
    while (cur) {
        for (int i = cur - 1; i >= p[cur]; i--) {
            t[a[i].second] = cnt + 1;
        }
        cnt ++;
        cur = p[cur];
    }

    printf("%d %d\n", dp[n], cnt);

    for (int i = 0; i < n; i++) {
        if (i) {
            printf(" ");
        }
        printf("%d", t[i]);
    }
    puts(" ");

    return 0;
}
