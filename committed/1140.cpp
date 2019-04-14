#include <vector>
#include <iostream>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MOD = 998244353;

int norm(int a) {
    a = (a % MOD + MOD) % MOD;
    return a;
}

int multiply(int a, int b) {
    return int(a * 1LL * b % MOD);
}

int n, k;
vector<int> a;

bool read() {
    if (!(cin >> n >> k)) {
        return false;
    }
    a.resize(n);
    for(int i = 0; i < n; i++) {
        cin >> a[i];
    }
    return true;
}

pair<int, int> calc(int len) {
    if (len == 0) {
        return {0, 1};
    }
    if (len & 1) {
        auto half_case = calc(len >> 1);
        int same_case = norm(multiply(half_case.first, half_case.first) +
                             multiply(k - 1, multiply(half_case.second, half_case.second)));
        int diff_case = norm(multiply(2, multiply(half_case.first, half_case.second)) +
                             multiply(k - 2, multiply(half_case.second, half_case.second)));
        return {same_case, diff_case};
    } 
    auto minus_case = calc(len - 1);
    int same_case = multiply(k - 1, minus_case.second);
    int diff_case = norm(minus_case.first + multiply(k - 2, minus_case.second));
    return {same_case, diff_case};
}

vector <int> current_array;

int calc_segment(int l, int r) {
    if (r >= current_array.size()) {
        int len = r - l - 1, current_case = 1;
        if (l < 0) {
            len --;
            current_case = k;
        }
        if (len == 0) return current_case;
        auto res = calc(len - 1);
        return multiply(current_case, norm(res.first + multiply(k - 1, res.second)));
    }
    if (l < 0) {
        if (r - l == 1) {
            return 1;
        }
        auto res = calc(r - l - 2);
        return norm(res.first + multiply(k - 1, res.second));
    }
    auto res = calc(r - l - 1);
    return current_array[l] == current_array[r] ? res.first : res.second;
}

void solve() {
    int ans = 1;
    for(int k = 0; k < 2; k++) {
        current_array.clear();
        for(int i = 0; 2 * i + k < n; i++) {
            current_array.push_back(a[2 * i + k]);
        }

        int last = -1;
        for(int i = 0; i < current_array.size(); i++) {
            if (current_array[i] == -1) {
                continue;
            }
            ans = multiply(ans, calc_segment(last, i));
            last = i;
        }
        ans = multiply(ans, calc_segment(last, current_array.size()));
    }
    cout << ans << endl;
}

int main() {
    if (read()) {
        solve();
    }
    return 0;
}