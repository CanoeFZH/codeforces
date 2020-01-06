#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

struct Event {
	Event(int t_, int s_, int e_, int isIn_) : t(t_), s(s_), e(e_), isIn(isIn_) {}
	int t, s, e, isIn;

	bool operator < (const Event & rhs) {
		if (t == rhs.t) {
			return isIn < rhs.isIn;
		}
		
		return t < rhs.t;
	}
};

bool check(int n, vector<int> &sa, vector<int> &ea, vector<int> &sb, vector<int> &eb) {
	multiset<int> s, e;
	vector<Event> events;

	for(int i = 0; i < n; i++) {
		events.emplace_back(sa[i], sb[i], eb[i], 1);
		events.emplace_back(ea[i] + 1, sb[i], eb[i], 0);
	}

	sort(events.begin(), events.end());

	for (auto event: events) {
		if (event.isIn) {
			if (!s.empty()) {
				if (*s.rbegin() > event.e || *e.begin() < event.s) {
					return false;
				}
			}

			s.insert(event.s);
			e.insert(event.e);
		} else {
			s.erase(s.find(event.s));
			e.erase(e.find(event.e));
		}
	}
	
	return true;
}

int main() {
	int n;
	cin >> n;

	vector <int> sa(n), ea(n), sb(n), eb(n);

	for (int i = 0; i < n; i++) {
		cin >> sa[i] >> ea[i] >> sb[i] >> eb[i];
	}

	if (check(n, sa, ea, sb, eb) && check(n, sb, eb, sa, ea)) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}
	return 0;
}
