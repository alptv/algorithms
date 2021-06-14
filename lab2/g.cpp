#include <iostream>
#include <vector> 
#include <algorithm>
#include <string>
using namespace std;
int maximum(int a, int b) {
	if (a > b) return a;
	return b;
}

int minimum(int a, int b) {
	if (a > b) return b;
	return a;
}



void makeset(int x,int* p) {
	p[x] = x;
 }

int find(int x,int* p) {
	if (p[x] == x) return x;
	else return find(p[x], p);
}
void join(int x, int y, int* p,int* max,int* min, int* count) {
	int x1, y1;
	x1 = find(x, p);
	y1 = find(y, p);
	if (x1!=y1) {
	p[x1] = y1;
	count[y1] = count[x1] + count[y1];
	max[y1] = maximum(max[x1], max[y1]);
	min[y1] = minimum(min[x1], min[y1]);
 }
}

int getmin(int x, int* min,int* p) {
	return min[find(x,p)];
}
int getmax(int x, int* max, int* p) {
	return max[find(x,p)];
}

int getcount(int x, int* count,int* p) {
	return count[find(x,p)];
}


int main() {
	int count[300000], max[300000], min[300000], p[300000];
	int n, t1,t2;
	string s;
	cin >> n;
	for (int i = 1; i <= n; i++) {
		count[i] = 1;
		max[i] = i;
		min[i] = i;
		p[i] = i;
	}
	while (cin >> s) {
		if (s == "union") {
			cin >> t1;
			cin >> t2;
			join(t1, t2, p, max, min, count);
		}
		if (s == "get") {
			cin >> t1;
			cout << getmin(t1, min,p)<< " " << getmax(t1, max,p)<<" " << getcount(t1, count,p) << endl;
		}
	}
	return 0;
}