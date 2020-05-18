#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

const int MOD = 1e9 + 7;

int norm(int a) {
    while(a >= MOD) a -= MOD;
    while(a < 0) a += MOD;
    return a;
}

int mul(int a, int b) {
    return int(a * 1LL * b % MOD);
}

int binPow(int a, int k) {
    int ans = 1;
    for (; k > 0; k >>= 1) {
        if (k & 1) {
            ans = mul(ans, a);
        }

        a = mul(a, a);
    }

    return ans;
}

int inv(int a) {
    return binPow(a, MOD - 2);
}

int n;
vector<int> l, r, p;

int calcEq(int i0) {
    int i1 = i0 + 1;
    int pSame = 0;
    if (i0 > 0) {
        int cnt = max(0, min({r[i0 - 1], r[i0], r[i1]}) - max({l[i0 - 1], l[i0], l[i1]}));
        pSame = mul(cnt, inv(mul(mul(r[i0 - 1] - l[i0 - 1], r[i0] - l[i0]),  r[i1] - l[i1])));
    }

    return norm(1 - norm(2 - p[i0] - p[i1]) + pSame);
}

int main() {
    cin >> n;
    l.resize(n);
    r.resize(n);

    for(int i = 0; i < n; i++) {
        cin >> l[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> r[i];
        r[i] ++;
    }
    
    p.assign(n, 0);
    p[0] = 1;
    for (int i = 1; i < n; i++) {
        int cnt = max(0, min(r[i - 1], r[i]) - max(l[i - 1], l[i]));
        p[i] = norm(1 - mul(cnt, inv(mul(r[i - 1] - l[i - 1], r[i] - l[i]))));
    }

    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum = norm(sum + p[i]);
    }

    int ans = 0;    
    for (int i = 0; i < n; i++) {
        int currentSum = sum;
        for (int j = max(0, i - 1); j < min(n, i + 2); j++) {
            currentSum = norm(currentSum - p[j]);
        }

        ans = norm(ans + mul(p[i], currentSum));
        
        if (i > 0) {
            ans = norm(ans + calcEq(i - 1));
        }

        ans = norm(ans + p[i]);
        
        if (i + 1 < n) {
            ans = norm(ans + calcEq(i));
        }
    }
    
    cout << ans << endl;
    return 0;
}
