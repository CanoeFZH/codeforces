#include <cstdio>
#include <iostream>

using namespace std;

const int MOD = 998244353;
const int N = 5005;

void update(int &a, int b){
    a += b;
    a %= MOD;
}

int add(int a, int b) {
    return (a + b) % MOD;
}

int multiply(int a, int b){
    return (a * 1LL * b) % MOD;
}

int quick_power(int a, int n){
    int res = 1;
    for(; n > 0; n >>= 1){
        if(n & 1) res = multiply(res, a);
        a = multiply(a, a);
    }
    return res;
}

int get_inv(int a){
    return quick_power(a, MOD - 2);
}

int n, a;
int cnt[N], sum[N][N], dp[N][N];

int main() {
	cin >> n;
	for (int i = 1; i <= n; i++) {
		cin >> a;
		cnt[a]++;
	}

	for (int i = 0; i <= n; i++) {
	    sum[0][i] = 1;	
	}
    
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        int inv = get_inv(n - i + 1);
        for (int j = 1; j <= n; j++) {
            if (cnt[j]) {
                //continue case.
                dp[i][j] = multiply(multiply(sum[i - 1][j - 1], cnt[j]), inv);
                //win case.
                update(answer, multiply(multiply(dp[i - 1][j], cnt[j] - 1), inv));
            }
            sum[i][j] = add(sum[i][j - 1], dp[i][j]);             
        }
    }
    cout << answer<< endl;
	return 0;
}
