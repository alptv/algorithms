#include <iostream>
#include <vector>
using namespace std;
void merge(vector <int> &a, int l, int r, int m) {
	vector <int> b;
	int i, j, k;
	i = l;
	j = m + 1;
	k = r;
	while (i <= m && j <= r) {
		if (a[i] <= a[j]) {
			b.push_back(a[i]);
			i++;
		}
		else {
			b.push_back(a[j]);
			j++;
		}
		
	}
	if (i == m + 1) {
		for (int h = j; h <= r; h++) b.push_back(a[h]);
	}
	else {
		for (int h = i; h <= m; h++) b.push_back(a[h]);
	}
	for (int h = l; h <= r; h++) a[h] = b[h-l];
}



void mergesort(vector <int> &a, int l, int r) { 
	if (l < r) {
		int m;
		m = (l + r) / 2;
		mergesort(a, l, m);
		mergesort(a, m + 1, r);
		merge(a, l, r, m);
	}
}


int main() {
	int n, l, r;
	cin >> n;
	vector <int> a(n);
	for (int i = 0; i < n; i++) cin >> a[i];
	mergesort(a, 0, a.size()-1);
	for (int i = 0; i < n; i++) cout << a[i] << " ";
	return 0;
}


	