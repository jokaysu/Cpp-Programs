#include <iostream>
#include <string>

using namespace std;

//support 10000 length of sequence
int a[2][10002][10002];
string str1, str2;
struct op{
	string s1;
	string s2;
	string s3;
};

struct op retract(int x, int y) {
	op rc;
	if (x == 0 && y == 0) {
		rc.s1 = rc.s2 = rc.s3 = "";
		return rc;
	}
	op pr;
	if (a[1][x][y] == 1) {
		pr = retract(x - 1, y - 1);
		rc.s1 = pr.s1 + str1[x - 1];
		rc.s2 = pr.s2 + "|";
		rc.s3 = pr.s3 + str2[y - 1];
	} else if (a[1][x][y] == 2) {
		pr = retract(x - 1, y);
		rc.s1 = pr.s1 + str1[x - 1];
		rc.s2 = pr.s2 + " ";
		rc.s3 = pr.s3 + "-";
	} else if (a[1][x][y] == 3) {
		pr = retract(x, y - 1);
		rc.s1 = pr.s1 + "-";
		rc.s2 = pr.s2 + " ";
		rc.s3 = pr.s3 + str2[y - 1];
	} else if (a[1][x][y] == 4) {
		pr = retract(x - 1, y - 1);
		rc.s1 = pr.s1 + str1[x - 1];
		rc.s2 = pr.s2 + " ";
		rc.s3 = pr.s3 + str2[y - 1];
	}
	return rc;
}

int main() {
	int n, m;
	int sig, pen;
	cin >> str1 >> str2 >> sig >> pen;
	n = str1.length();
	m = str2.length();
	for (int i = 0; i <= n; ++i) {
		for (int j = 0; j <= m; ++j) {
			if (i == 0) {
				a[0][i][j] = j * sig;
				a[1][i][j] = 3;
				continue;
			} else if (j == 0) {
				a[0][i][j] = i * sig;
				a[1][i][j] = 2;
				continue;
			}
			int rs1, rs2, rs3;
			if (str1[i - 1] == str2[j - 1]) 
				rs1 = a[0][i - 1][j - 1];
			else rs1 = a[0][i - 1][j - 1] + pen;
			rs2 = a[0][i - 1][j] + sig;
			rs3 = a[0][i][j - 1] + sig;
			if (rs1 <= rs2 && rs1 <= rs3) {
				a[0][i][j] = rs1;
				a[1][i][j] = 1;
				if (str1[i - 1] != str2[j - 1]) a[1][i][j] = 4;
			} else if (rs2 <= rs1 && rs2 <= rs3) {
				a[0][i][j] = rs2;
				a[1][i][j] = 2;
			} else {
				a[0][i][j] = rs3;
				a[1][i][j] = 3;
			}
			//cout << a[1][i][j] << " ";
		}
		//cout << endl;
	}
	op rc = retract(n, m);
	cout << rc.s1 << endl;
	cout << rc.s2 << endl;
	cout << rc.s3 << endl;
}