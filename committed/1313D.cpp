#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <set>
#include <cstdio>

using namespace std;

const int K = (1 << 8) + 1;
const int N = 1e5 + 1;
const int INF = 1e9;

int dp[K], parity[K], id[N];

vector<pair<int, int> > events;
set<int> S;

int main() {
//#define _DEBUG
#ifdef _DEBUG
    freopen("input", "r", stdin);
#endif

    int n, m, k;
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        events.push_back({x, i});
        events.push_back({y + 1, -i});
    }

    sort(events.begin(), events.end());

    int last = 0;
    for (int i = 0; i < k; i++) {
        S.insert(i);
    }

    for (int i = 1; i < (1 << k); i++) {
        dp[i] = -INF;
        parity[i] = parity[i >> 1] ^ (i & 1);
    }

    for (auto event: events) {
        for (int i = 0; i < (1 << k); i++) {
            if (parity[i]) {
                dp[i] += event.first - last;
            }
        }
        last = event.first;

        if (event.second > 0) {
            id[event.second] = *S.begin();
            S.erase(S.begin());
            for (int i = 0; i < (1 << k); i++) {
                int subset = i ^ (1 << id[event.second]);
                dp[i] = max(dp[i], dp[subset]);
            }
        } else {
            event.second *= -1;
            S.insert(id[event.second]);
            for (int i = 0; i < (1 << k); i++) {
                int subset = i ^ (1 << id[event.second]);
                dp[subset] = max(dp[subset], dp[i]);
                dp[i] = -INF;
            }
        }
    }

    printf("%d\n", dp[0]);
    return 0;
}