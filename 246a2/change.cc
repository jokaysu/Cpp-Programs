#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char *argv[]) {
	if (argc < 3) {
		cout << "Usage: change [denominations] [amount]";
		return 0;
	}
	int total;
	stringstream st;
	st << argv[argc - 1];
	st >> total;
	int n = argc - 2;
	int a[n], i;
	for (i = 0; i < n; ++i) {
		stringstream st2;
		st2 << argv[i + 1];
		st2 >> a[i];
	}
	int j, t;
	//sorting
	for (i = 0; i < n - 1; ++i) 
		for (j = i + 1; j < n; ++j) 
			if (a[j] > a[i]) {
				t = a[i];
				a[i] = a[j];
				a[j] = t;
			}
	int ans[n];
	for (i = 0; i < n; ++i) {
		ans[i] = total / a[i];
		total = total % a[i];
	}
	if (total != 0) {
		cout << "Impossible";
		return 0;
	};
	for (i = 0; i < n; ++i) 
		if (ans[i] != 0) {
			cout << ans[i] << " x " << a[i] << endl;
		}
}

//strtol(argv[i + 1], NULL, 10)
