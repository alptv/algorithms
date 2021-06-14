#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
using namespace std;

void makeset(int x, int* p) {
	p[x] = x;
}

int find(int x, int* p) {
	if (p[x] == x) return x;
	else return find(p[x], p);
}
void join(int x, int y, int* p, int* rank, int* exp) {
	int x1, y1;
	x1 = find(x, p);
	y1 = find(y, p);
	if (rank[x1] < rank[y1]) {
		p[x1] = y1;
		if (x1!=y1) exp[x1] = exp[x1] - exp[y1];
	}
	else {
		p[y1] = x1;
		if (x1!=y1) exp[y1] = exp[y1] - exp[x1];
		if (rank[x1] == rank[y1])
			rank[x1]++;
	}
}
void add(int x, int v, int* p, int* exp) {
	x = find(x, p);
	exp[x] += v;
}


int get(int x, int* exp, int &sum,int* p) {
	sum += exp[x];
	if (p[x] == x) return sum;
	else return get(p[x], exp,sum,p);
}


int main() {
	int p[200005], exp[200005], rank[200005];
	int n, t1, t2, m, sum = 0;
	string s;
	cin >> n;
	cin >> m;
	for (int i = 0; i < n; i++) {
		exp[i + 1] = 0;
		p[i + 1] = i + 1;
		rank[i + 1] = 1;
	}
	for (int i = 0;i < m; i++) {
		cin >> s;
		if (s == "join") {
			scanf("%d", &t1);
			scanf("%d", &t2);
			join(t1, t2, p, rank, exp);
		}
		if (s == "get") {
			scanf("%d", &t1);
			sum = 0;
			printf("%d\n", get(t1, exp, sum,  p));
		}
		if (s == "add") {
			scanf("%d", &t1);
			scanf("%d", &t2);
			add(t1, t2, p, exp);
		}
	}
	return 0;
}