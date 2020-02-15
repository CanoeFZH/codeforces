#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cstring>

using namespace std;

const int N = 512;

int c[N][N][4], s[N][N][N >> 1], id[N >> 1];
char a[N][N];

bool check(int w, int x1, int y1, int x2, int y2) {
    if (!w) {
        return 1;
    }
    int d = (w << 1) - 2;
    return s[x2][y2][w] - s[x1 + d][y2][w] - s[x2][y1 + d][w] + s[x1 + d][y1 + d][w];
}

int main() {
 	id['G'] = 0; 
    id['Y'] = 1;
    id['R'] = 2;
    id['B'] = 3;
    int n, m, q;
    scanf("%d%d%d", &n, &m, &q);
    for (int i = 1; i <= n; i++) {
        scanf("%s", a[i] + 1);
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int t = id[a[i][j]];
            c[i][j][t] = min(min(c[i - 1][j][t], c[i][j - 1][t]), c[i - 1][j - 1][t]) + 1;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            for (int k = 1; k <= min(i >> 1, j >> 1); k++) {
                s[i][j][k] = s[i][j - 1][k] + s[i - 1][j][k] - s[i - 1][j - 1][k];
                if (c[i][j][id['B']] >= k && c[i - k][j][id['G']] >= k && c[i][j - k][id['Y']] >= k && c[i - k][j - k][id['R']] >= k) {
                    s[i][j][k]++;
                }
            }
        }
    }

    for(int x1, y1, x2, y2; q; q--) {
        scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
        int ans = 0, L = 0, R = min((x2 - x1 + 1) >> 1, (y2 - y1 + 1) >> 1);
        while(L <= R) {
            int M = (L + R) >> 1;
            if(check(M, x1, y1, x2, y2)) {
                ans = M;
                L = M + 1;
            } else {
                R = M - 1;
            }
        }
        printf("%d\n", ans * ans * 4);
    }
    return 0;
}