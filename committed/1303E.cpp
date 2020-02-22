#include <iomanip>
#include <iostream>
#include <queue>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int INF = 1e9;

#define sz(a) int((a).size())

string s, t;
vector <vector<int> > next_char;

inline bool read() {
    if (!(cin >> s >> t)) {
        return false;
    }
    return true;
}

bool calc(const string &a, const string & b) {
    vector<vector<int> > dp(sz(a) + 1, vector <int> (sz(b) + 1, INF));
    dp[0][0] = 0;
    for (int i = 0; i <= sz(a); i++) {
        for (int j = 0; j <= sz(b); j++) {
            if (dp[i][j] > sz(s)) {
                continue;
            }

            int l = dp[i][j];
            //cout << next_char[l][a[i] - 'a'] << " i, j " << next_char[l][b[j] - 'a'] << endl;
            if (i < sz(a)) {
                dp[i + 1][j] = min(dp[i + 1][j], next_char[l][a[i] - 'a'] + 1);
            }

            if (j < sz(b)) {
                dp[i][j + 1] = min(dp[i][j + 1], next_char[l][b[j] - 'a'] + 1);
            }
        }
    }
    //cout << dp[sz(a)][sz(b)] << " last" << endl;
    return dp[sz(a)][sz(b)] < INF;
}

void solve() {
    next_char.assign(sz(s) + 1, vector<int>(26, INF));
    for (int i = sz(s) - 1; ~i; i--) {
        next_char[i] = next_char[i + 1];
        next_char[i][s[i] - 'a'] = i;
    }

    for (int i = 0; i < sz(t); i++) {
        string a = t.substr(0, i);
        string b = t.substr(i, sz(t));
        //cout << a << " " << b << endl;
        if (calc(a, b)) {
            cout << "YES" << endl;
            return;
        }
    }

    cout << "NO" << endl;
}

int main() {
//#define _DEBUG
#ifdef _DEBUG
    freopen("input", "r", stdin);
    int tt = clock();
#endif

    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    cout << fixed << setprecision(15);

    int tc;
    for (cin >> tc; tc; tc--) {
        read();
        solve();
    }

#ifdef _DEBUG
    //cerr << "TIME=" << clock() - tt << endl;
#endif
    return 0;
}

