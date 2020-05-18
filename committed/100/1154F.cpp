#include <cstdio>
#include <cstring>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>

using namespace std;

const int INF = 1e9;

int main() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> a(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }

    sort(a.begin(), a.end());
    a.resize(k);
    reverse(a.begin(), a.end());

    vector<int> offers(k + 1);
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        if (x <= k) {
            offers[x] = max(offers[x], y);
        }
    }

    vector<int> sum_a(k + 1);
    for(int i = 0; i < k; i++) {
        sum_a[i + 1] = sum_a[i] + a[i];
    }

    vector<int> dp(k + 1, INF);
    dp[0] = 0;

    for(int i = 0; i < k; i++) {
        dp[i + 1] = min(dp[i + 1], dp[i] + a[i]);
        for(int j = 0; j <= k; j++) {
            if (offers[j] == 0) {
                continue;
            }
            if (i + j > k) {
                break;
            }
            dp[i + j] = min(dp[i + j], dp[i] + sum_a[i + j - offers[j]] - sum_a[i]);
        }
    }

    cout << dp[k] << endl;
    return 0;
}