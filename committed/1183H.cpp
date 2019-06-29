#include <cstdio>
#include <cstring>
#include <algorithm>
#include <string>
#include <cstdlib>
#include <iostream>
#include <vector>

using namespace std;

const long long INF64 = 1e12;


int main() {

    int n;
    long long k;
    cin >> n >> k;
    --k;

    string s;
    cin >> s;

    vector<vector <int> > lst(n, vector<int> (26, -1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 26; j++) {
            if (i > 0) {
                lst[i][j] = lst[i - 1][j];
            }
        }
        lst[i][s[i] - 'a'] = i;
    }

    vector<vector <long long> > dp(n + 1, vector<long long>(n + 1));
    for (int i = 0; i < n; i++) {
        dp[i][1] = 1;
    }

    for (int len = 2; len < n; len++) {
        for (int i = 1; i < n; i++) {
            for (int j = 0; j < 26; j++) {
                if (lst[i - 1][j] != -1) {
                    dp[i][len] = min(INF64, dp[i][len] + dp[lst[i - 1][j]][len - 1]);
                }
            }
        }
    }

    long long ans = 0;
    for (int len = n - 1; len >= 1; len--) {
        long long cnt = 0;
        for (int j = 0; j < 26; j++) {
            if (lst[n - 1][j] != -1) {
                cnt += dp[lst[n - 1][j]][len];
            }
        }
        
        if (cnt >= k) {
            ans += k * (n - len);
            k = 0;
            break;
        } else {
            ans += cnt * (n - len);
            k -= cnt;
        }
    }

    if (k == 1) {
        ans += n;
        --k;
    }

    if (k > 0) {
        cout << -1 << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}
