#include <iostream>
#include <string>

using namespace std;

const int N = 2e5 + 5;
int k, a[N];
string s, t;

int main() {
    cin >> k >> s >> t;
    for (int i = k - 1; ~i; i--) {
        int index = k - i - 1;
        a[index] += s[i] + t[i] - 2 * 'a';
        if (a[index] > 25) {
            a[index + 1] += 1;
            a[index] -= 26;
        }
    }
    for (int i = k, carry = 0; ~i; i--) {
        int sum = carry * 26 + a[i];
        carry = sum & 1;
        a[i] = sum / 2;
    }
    for (int i = k - 1; ~i; i--) {
        cout << char(a[i] + 'a');
    }
    cout << endl;
    return 0;
}
