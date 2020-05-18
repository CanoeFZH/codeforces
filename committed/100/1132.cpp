#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

ll cnt[10], w, ans = 0;

void dfs(int cur, ll total){
    if (cur == 9){
        ans = max(ans, w - total);
        return;
    }
    ll a = min(cnt[cur], total / cur);
    for(ll i = a; i >= max(a-8, 0ll); i--)
        dfs(cur + 1, total - i *cur);
}

int main(){
    cin >> w;
    for(int i = 1; i <= 8; i++) cin >> cnt[i];
    dfs(1, w);
    cout << ans << endl;
}