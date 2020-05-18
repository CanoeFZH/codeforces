#include <iostream>
#include <cstdlib>
#include <string>
#include <cstring>
#include <iostream>

using namespace std;

const int N = int(3e5) + 100;
const long long INF = (long long)(1e18) + 100;

int a[N], b[N];
long long dp[3][N];
int n, q;

long long solve(int add, int index) {
    long long & res = dp[add][index];

    if (res != -1) {
        return res;
    }

    if (index == n) {
        return res = 0;
    }

    res = INF;
    for (int i = 0; i <= 2; i++) {
        if (index == 0 || a[index] + i != a[index - 1] + add) {
            res = min(res, solve(i, index + 1) + b[index] *  (long long)(i));
        }
    }

    return res;
}

int main() {
    scanf("%d", &q);
    while(q--) {
        scanf("%d", &n);
        for (int i = 0; i < n; i++) {
            scanf("%d", a + i);
            scanf("%d", b + i);
        }
        
        for (int i = 0; i <= n; i++) {
            dp[0][i] = dp[1][i] = dp[2][i] = -1;
        }
        cout << solve(0, 0) << endl;
    }
    return 0;
}
