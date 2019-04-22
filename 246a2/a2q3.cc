#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
	string s, sp;
	int ct = 0, i;
	if (!(cin >> sp)) return 0;
	string ll;
	while (sp == "//") {
		getline(cin, ll, '\n');
		cout << sp << ll << endl;
		for (i = 0; i < ct; ++i) 
			cout << " ";
		cin >> sp;
	} 
	bool flag = false;
	while (cin >> s) {
		if (sp == ";") {
			if (s == "}") 
				ct--; 
			cout << sp << endl;
			for (i = 0; i < ct; ++i) 
				cout << " ";
		} else if (sp == "{") {
			if (s == "}") 
				ct--; 
			cout << sp << endl;
			ct++;
			for (i = 0; i < ct; ++i) 
				cout << " ";
		} else if (sp == "}") {
			cout << sp << endl;
			if (s == "}") 
				ct--; 
			for (i = 0; i < ct; ++i) 
				cout << " ";
		} else {
			if (s == "}") {
				cout << sp << endl;
				ct--;
				for (i = 0; i < ct; ++i) 
					cout << " ";
			} else cout << sp << " ";
		}
		sp = s;
		while (sp == "//") {
			getline(cin, ll, '\n');
			cout << sp << ll;
			if (!(cin >> sp)) {
				flag = true;
				break;
			}
			cout << endl;
			for (i = 0; i < ct; ++i) 
				cout << " ";
		} 
		if (flag) break;
	}
	if (!flag) cout << sp;
	return 0;
}
