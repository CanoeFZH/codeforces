#include <cstdio>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define ls (v<<1)
#define rs (ls|1)
#define lson ls,vl,mid
#define rson rs,mid+1,vr

using namespace std;

const int N = 4 * 100005;
const int mod = 1000000007;

typedef long long ll;

int a[N];
int product[4 * N], lazy_product[4 * N];
ll mask[4 * N], lazy_mask[4 * N];

vector <int> primes, inverse_primes;

int multiply(int a, int b) {
    return (ll(a) * ll(b)) % mod;
}

int quick_pow(int a, int n, int acc = 1) {
    while(n) {
        if (n & 1) {
            acc = multiply(acc, a);
        }
        a = multiply(a, a);
        n >>= 1;
    }
    return acc;
}

void build(int v, int vl, int vr) {
    lazy_product[v] = 1;
    lazy_mask[v] = 0;
    if (vl == vr) {
        product[v] = a[vl];
        for (int i = 0; i < primes.size(); i++) {
            if (a[vl] % primes[i] == 0) {
                mask[v] |= ((1LL) << ll(i));
            }
        }
        return;
    }

    int mid = (vl + vr) / 2;
    build(lson);
    build(rson);

    product[v] = multiply(product[ls], product[rs]);
    mask[v] = mask[ls] | mask[rs];
}

void push(int v, int vl, int vr, string op_type = "") {

    //cout << op_type << " " << v << " " << vl << " " << vr << " " << lazy_product[v] << endl;
    int mid = (vl + vr) / 2;
    product[ls] = quick_pow(lazy_product[v], mid - vl + 1, product[ls]);
    product[rs] = quick_pow(lazy_product[v], vr - mid, product[rs]);
    mask[ls] |= lazy_mask[v];
    mask[rs] |= lazy_mask[v];

    lazy_product[ls] = multiply(lazy_product[ls], lazy_product[v]);
    lazy_product[rs] = multiply(lazy_product[rs], lazy_product[v]);
    lazy_mask[ls] |= lazy_mask[v];
    lazy_mask[rs] |= lazy_mask[v];

    lazy_product[v] = 1;
    lazy_mask[v] = 0;
}

pair<int, ll> query(int v, int vl, int vr, int l, int r) {
    //cout << v << "query " << vl << " " << vr << " " << l << " " << r << endl;
    if (l == vl && vr == r) {
        return make_pair(product[v], mask[v]);
    }
    push(v, vl, vr, "query");
    
    int mid = (vl + vr) / 2;
    if (r <= mid) {
        return query(lson, l, r);
    } else if (l > mid) {
        return query(rson, l, r);
    } else {
        auto l_query = query(lson, l, mid);
        auto r_query = query(rson, mid + 1, r);
        return make_pair(multiply(l_query.first, r_query.first), l_query.second | r_query.second);
    }
}

void update(int v, int vl, int vr, int l, int r, int x, ll x_mask) {
    //cout << v << "update " << vl << " " << vr << " " << l << " " << r << endl;
    if (l == vl and r == vr) {

        product[v] = quick_pow(x, r - l + 1, product[v]);
        mask[v] |= x_mask;

        lazy_product[v] = multiply(lazy_product[v], x);
        lazy_mask[v] |= x_mask;
        return;
    }
    
    push(v, vl, vr, "update");
    
    int mid = (vl + vr) / 2;

    if (r <= mid) {
        update(lson, l, r, x, x_mask);
    } else if (l > mid) {
        update(rson, l, r, x, x_mask);
    } else {
        update(lson, l, mid, x, x_mask);
        update(rson, mid + 1, r, x, x_mask);
    }

    product[v] = multiply(product[ls], product[rs]);
    mask[v] |= mask[ls];
    mask[v] |= mask[rs];
}

int main() {
    for (int i = 2; i <= 300; i++) {
        bool is_prime = true;
        for (int j = 2; j * j <= i; j++) {
            if (i % j == 0) {
                is_prime = false;
                break;
            }
        }
        if (is_prime) {
            primes.push_back(i);
            inverse_primes.push_back(quick_pow(i, mod - 2));
        }
    }
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    build(1, 1, n);

    int l, r, x;
    string cmd;
    while(q--) {
        cin >> cmd;
        if (cmd == "MULTIPLY") {
            cin >> l >> r >> x;
            ll x_mask = 0;
            for(int i = 0; i < primes.size(); i++) {
                if (x % primes[i] == 0) {
                    x_mask |= ((1LL) << ll(i));
                }
            }
            //auto qq = query(1, 1, n, l, r);
            //cout << qq.first << " " << qq.second << endl;
            update(1, 1, n, l, r, x, x_mask);
            //cout << query(1, 1, n, 5, 7).first << endl;
            //cout << query(1, 1, n, 5, 5).first << endl;
            //cout << l << " l r " << r << endl;
            //qq = query(1, 1, n, l, r);
            //cout << qq.first << " " << qq.second << endl;
        } else if (cmd == "TOTIENT") {
            cin >> l >> r;
            auto query_result = query(1, 1, n, l, r);
            int eluer_totient = query_result.first;
            for (int i = 0; i < primes.size(); i++) {
                if (query_result.second & ((1LL) << ll(i))) {
                    eluer_totient = multiply(multiply(eluer_totient, primes[i] - 1), inverse_primes[i]);
                }
            }
            cout << eluer_totient << endl;
        }
    }
    return 0;
}
