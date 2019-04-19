#include <cstdio>
#include <iostream>

using namespace std;

typedef long long ll;

const int N = 1e7 + 5;
const ll MAX_LCM = 1e16;

int cnt[N], last[N];

int main() {
    int n, x;
    cin >> n;
    ll LCM = MAX_LCM;
    int first_index = 0, second_index = 0;
    for(int i = 0; i < n; i++) {
        cin >> x;
        // mark x for checking k * gcd; if a number exists twice, it will be a good condidate.
        if (cnt[x] && x < LCM) {
            LCM = x;
            first_index = last[x];
            second_index = i + 1;
        }
        cnt[x] = 1;
        last[x] = i + 1;
    }

    for (int gcd = 1; gcd < N; gcd++) {
        int gcd_first_index = 0, gcd_second_index = 0;
        ll k_gcd_first = 0, k_gcd_second = 0;
        ll gcd_LCM = MAX_LCM;

        for (int k = 1; k * gcd < N; k++) {
            int k_gcd = k * gcd;
            if (cnt[k_gcd] && gcd_first_index == 0) {
                k_gcd_first = k_gcd;
                gcd_first_index = last[k_gcd];
            } else if (cnt[k_gcd] && gcd_second_index == 0) {
                k_gcd_second = k_gcd;
                gcd_second_index = last[k_gcd];
                break; // have found the smalled k_i * k_j * gcd * gcd 
            }
        }

        if (gcd_first_index && gcd_second_index) {
            // LCM(a, b) = (a * b) / GCD(a, b).
            gcd_LCM = k_gcd_first / gcd * k_gcd_second;
        }

        if (gcd_LCM < LCM) {
            LCM = gcd_LCM;
            first_index = min(gcd_first_index, gcd_second_index);
            second_index = max(gcd_first_index, gcd_second_index);
        }

    }

    cout << first_index << " " << second_index << endl;
    return 0;
}
