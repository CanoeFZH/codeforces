#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

const int K = 1005, N = 55, M = 55, INF = 1e9 + 7, C = 26;

int k, n, m;
int kmp_s[N], next_s[N][C], kmp_t[M], next_t[M][C];
int dp[K][N][M];
char code[K], s[N], t[M];

void init(char s[], int n, int kmp[], int next[][C]) {

    kmp[1] = 0;
    for (int i = 2; i <= n; i++) {
        int index = kmp[i - 1];
        while (index > 0 && s[index + 1] != s[i]) {
            index = kmp[index];
        }

        if (s[index + 1] == s[i]) {
            ++index;
        }

        kmp[i] = index;
    }

    for (int i = 0; i <= n; i++) {
        for(char c = 'a'; c <= 'z'; c++) {
            int index = i;
            while (index > 0 && s[index + 1] != c) {
                index = kmp[index];
            }

            if (s[index + 1] == c) {
                ++index;
            }

            next[i][c - 'a'] = index;
        }
    }
}


int main() {
    scanf("%s%s%s", code + 1, s + 1, t + 1);

    k = strlen(code + 1);
    n = strlen(s + 1);
    m = strlen(t + 1);

    init(s, n, kmp_s, next_s);
    init(t, m, kmp_t, next_t);

    for(int i = 0; i <= k; i++) {
        for(int ks = 0; ks <= n; ks++) {
            for(int kt = 0; kt <= m; kt++) {
                dp[i][ks][kt] = -INF;
            }
        }
    }

    dp[0][0][0] = 0;

    for(int i = 0; i < k; i++) {
        for (int ks = 0; ks <= n; ks++) {
            for (int kt = 0; kt <= m; kt++) {
                for(char ch = 'a'; ch <= 'z'; ch++) {
                    if (code[i + 1] == '*' || code[i + 1] == ch) {
                        int c = ch - 'a';
                        int ns = next_s[ks][c], nt = next_t[kt][c];

                        int extra = (ns == n) - (nt == m);
                        dp[i + 1][ns][nt] = max(dp[i + 1][ns][nt], extra + dp[i][ks][kt]);
                    }
                }
            }
        }
    }

    int answer = -INF;
    for (int ks = 0; ks <= n; ks++) {
        for (int kt = 0; kt <= m; kt++) {
            answer = max(answer, dp[k][ks][kt]);
        }
    }

    printf("%d\n", answer);
}