#include <iostream>
#include <stack>
#include <cstdlib>
#include <algorithm>
#include <cstring>

using namespace std;

const int N = 510;

int a[N], dp[N];
stack <int> s;

int main() {
    cin.tie(0), cout.tie(0), ios::sync_with_stdio(0);
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    memset(dp, 0x3f, sizeof(dp));

    dp[0] = 0;

    for (int i = 0; i < n; i++) {
        while(!s.empty()) {
            s.pop();
        }

        for (int j = i + 1; j <= n; j++) {
            int x = a[j];
            while(!s.empty() && s.top() == x) {
                s.pop();
                x++;
            }
            s.push(x);

            dp[j] = min(dp[j], dp[i] + (int) s.size());
        }
    }

    cout << dp[n] << "\n";
    return 0;
}