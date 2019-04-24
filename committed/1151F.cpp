#include <cstdio>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

typedef long long lint;

const int MOD = 1e9 + 7;
const int N = 100 + 5;

int n, k, A[N], start_zero_count = 0, C[2];

class matrix {
    public:
        int X[N][N] = {};

        matrix operator * (matrix & P) {
            matrix R;
            for (int i = 0; i <= n; i++) {
                for(int j = 0; j <= n; j++) {
                    for(int k = 0; k <= n; k++) {
                        R.X[i][k] = (R.X[i][k] + 1LL * X[i][j] * P.X[j][k]) % MOD;
                    }
                }
            }
            return R;
        }
        matrix operator ^ (int e) {
            if (e == 1) {
                return *this;
            }
            matrix T = *this ^ (e / 2);
            T = T * T;
            return e % 2 ? T * *this : T;
        }
} T;


lint quick_mod(lint a, int e) {
    if (e == 0) {
        return 1;
    }
    lint t = quick_mod(a, e / 2);
    t = t * t % MOD;
    return e % 2 ? t * a % MOD : t;
}

lint inv(lint x) {
    return quick_mod(x % MOD, MOD - 2);
}

int main() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> A[i];
        C[A[i]]++;
    }

    for (int i = 1; i <= C[0]; i++) {
        if (A[i] == 0) {
            start_zero_count += 1;
        }
    }

    lint s = n * (n - 1) / 2;
    lint u = inv(s);

    for (int i = 0; i <= C[0]; i++) {
        lint p = i * (C[1] - (C[0] - i));
        lint q = (C[0] - i) * (C[0] - i);
        lint r = s - p - q;

        if (i > 0) {
            T.X[i][i - 1] = p * u % MOD;
        }
        
        if (i < C[0]) {
            T.X[i][i + 1] = q * u % MOD;
        }
        T.X[i][i] = r * u % MOD;
    }

    matrix R = T ^ k;
    cout << R.X[start_zero_count][C[0]] << endl;

    return 0;
}
