#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main() {
	int q;
	cin >> q;

	while(q--) {
		int a, b;
		string s;
		cin >> a >> b >> s;

		vector <int> v;
		int l = 0;
		while(l < s.size()) {
			if (s[l] == 'X') {
				l++;
				continue;
			}

			int r = l + 1;
			while (r < s.size() && s[r] == '.') r++;
			v.push_back(r - l);
			l = r;
		}

		bool alice_win = true;
		int cnt_2b_case = 0, cnt_ab_case = 0, _2b_length = -1;

		for (auto len: v) {
			if (b <= len && len < a) {
				// alice always lose
				alice_win = false; 
				break;
			}

			if (2 * b <= len) {
				cnt_2b_case++;
				_2b_length = len;
				// bob always win
				if (cnt_2b_case > 1) {
					alice_win = false;
					break;
				}
			}

			if (a <= len && len < 2 * b) {
				cnt_ab_case++;
			}
		}

		if (!alice_win) {
			cout << "NO" << endl;
			continue;
		}
		
		// no 2b case;	
		if (cnt_2b_case == 0) {
			if (cnt_ab_case & 1) {
				// alternate a b a case
				cout << "YES" << endl;
			} else {
				cout << "NO" << endl;
			}
			continue;
		}

		alice_win = false;
		
		// only one 2b case;
		int length = _2b_length;
		for(int r1 = 0; length - a - r1 >= 0; r1++) {
			int r2 = length - a - r1;
			int more_cnt_ab_case = cnt_ab_case;

			if (r1 >= 2 * b || (b <= r1 && r1 < a)) {
				// can not win;
				continue;
			}

			if (r2 >= 2 * b || (b <= r2 && r2 < a)) {
				// can not win;
				continue;
			}
			
			//case ab
			if (r1 >= a) {
				more_cnt_ab_case++; 
			}

			//case ab
			if (r2 >= a) {
				more_cnt_ab_case++;
			}
			
			// alternate b a
			if (!(more_cnt_ab_case & 1)) {
				alice_win = true;
				break;
			}
		}

		if (alice_win) {
			cout << "YES" << endl;
		} else {
			cout << "NO" << endl;
		}
	}

	return 0;
}
