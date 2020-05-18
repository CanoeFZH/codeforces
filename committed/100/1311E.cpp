#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 5e3 + 2;

int d[N], p[N], c[N];

void solve(int n, int x) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += i;
        d[i + 1] = i;
        p[i + 1] = i;
        c[i] = 1;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i - 2; j++) {
            int depth_change = (d[i] - (d[j] + 1)) * (n - i + 1);
            if (c[j] < 2 && d[j] + 1 < d[i] && sum - depth_change >= x) {
                c[j]++;
                c[p[i]]--;
                p[i] = j;
                sum -= depth_change;
                for (int k = i; k <= n; k++) {
                    d[k] = (d[j] + 1) + k - i;
                }
                break;
            }
        }
    }
    
    if (sum == x) {
        puts("YES");
        for (int i = 2; i <= n; i++) {
            printf("%d%c", p[i], " \n"[i == n]);
        }
    } else {
        puts("NO");
    }
}

int main() {
//#define _DEBUG
#ifdef _DEBUG
    freopen("input", "r", stdin);
#endif
    int t;
    scanf("%d", &t);
    while(t--) {
        int n, x;
        scanf("%d%d", &n, &x);
        solve(n, x);
    }
    return 0;
}