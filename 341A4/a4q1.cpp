//a4q1.cpp

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<int, vector<int>> iedge;
map<int, vector<int>> oedge;
vector<int> dfsList;
map<int, int> cc;

void visit(int i, bool *visited) {
	if (!visited[i]) {
		visited[i] = true;
		for (auto it = oedge[i].begin(); it != oedge[i].end(); ++it)
			visit(*it, visited);
		dfsList.push_back(i);
	}
}

void assign(int i, int ccNum) {
	if (cc[i] == 0) {
		cc[i] = ccNum;
		for (auto it = iedge[i].begin(); it != iedge[i].end(); ++it)
			assign(*it, ccNum);
	}
}

bool comp(int x, int y) {return (x > y);}

int main() {
	//read input
	int n, m;
	cin >> n >> m;
	int u, v;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v;
		oedge[u].push_back(v);
		iedge[v].push_back(u);
	}

	//init
	bool visited[n + 1];
	for (int i = 1; i <= n; ++i) {
		visited[i] = false;
		cc[i] = 0;
	}

	//visit
	for (int i = 1; i <= n; ++i) 
		visit(i, visited);

	//reverse
	int ccNum = 0;
	for (auto it = dfsList.rbegin(); it != dfsList.rend(); ++it) {
		if (cc[*it] == 0) {
			ccNum++;
			assign(*it, ccNum);
		}
	}

	//count cc
	int count[ccNum + 1];
	for (int i = 1; i <= ccNum; ++i) 
		count[i] = 0;
	for (int i = 1; i <= n; ++i) 
		count[cc[i]]++;
	sort(count + 1, count + ccNum + 1, comp);

	//output   ----------pretty tricky to avoid the tab at last
	if (ccNum < 5) {
		for (int i = 1; i <= ccNum; ++i)
			cout << count[i] << "\t";
		for (int i = 1; i < 5 - ccNum; ++i)
			cout << "0\t";
		cout << "0" << endl;
	} else {
		for (int i = 1; i < 5; ++i)
			cout << count[i] << "\t";
		cout << count[5] << endl;
	}
}