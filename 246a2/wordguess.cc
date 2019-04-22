#include <iostream>
#include <fstream>

using namespace std;

bool valid(string s) {
	int n = 5;
	if (s.length() != n) return false;
	int i, j;
	for (i = 0; i < n - 1; ++i)
		for (j = i + 1; j < n; ++j)
			if (s[i] == s[j]) 
				return false;
	for (i = 0; i < n; ++i)
		if ((s[i] < 'A' || s[i] > 'Z') && 
			(s[i] < 'a' || s[i] > 'z'))
			return false;
	return true;
}

int main(int argc, char *argv[]) {
	int n = 5;
	if (argc != 2) {
		cerr << "usage: wordguess [filename]" << endl;
		return 0;
	}
	ifstream infile(argv[1]);
	if (infile.fail()) {
		cerr << argv[1] << " cannot be opened" << endl;
		return 0;
	}
	string word;
	infile >> word;
	infile.close();
	if (!valid(word)) {
		cerr << "the secret word is invalid" << endl;
		return 0;
	}
	string guess;
	int ct, i, j;
	bool okay;
	while (cin >> guess) {
		if (!valid(guess)) {
			cout << "invalid guess" << endl;
		} else {
			okay = true;
			for (i = 0; i < n; ++i) 
				if (guess[i] != word[i])
					okay = false;
			if (okay) {
				cout << "you guessed correctly!" << endl;
				return 0;
			}
			ct = 0;
			for (i = 0; i < n; ++i)
				for (j = 0; j < n; ++j) 
					if (guess[i] == word[j]) {
						ct++;
						break;
					}
			cout << ct << " letters match" << endl;
		}
	}
}
