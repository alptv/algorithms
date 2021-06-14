#include <iostream>
#include <vector>;
using namespace std;
void merge(int* a, int l, int r, int m) {
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
	for (int h = l; h <= r; h++) a[h] = b[h - l];
}



void mergesort(int* a, int l, int r) {
	if (l < r) {
		int m;
		m = (l + r) / 2;
		mergesort(a, l, m);
		mergesort(a, m + 1, r);
		merge(a, l, r, m);
	}
}


int binright(int* a, int x,int l, int r) {
	int m;
	while (r > l + 1) {
		m = (l + r) / 2;
		if (a[m] <= x) l = m;
		else r = m;
	}
	return(l);

}

int binleft(int* a, int x,int l,int r) {
	int m;
	while (r > l + 1) {
		m = (l + r) / 2;
		if (a[m] < x) l = m;
		else r = m;
	}
	return(r);
}

int main() {
	int n, k, l, r, a[100000];
	cin >> n;
	for (int i = 0; i < n; i++) cin >> a[i];
	mergesort(a, 0, n - 1);
	cin >> k;
	vector <int> b(2*k);

	for (int i = 0; i < 2 * k; i++) cin >> b[i];
	for (int i = 0; i < 2 * k; i += 2)  cout << binright(a, b[i + 1],-1,n) - binleft(a, b[i],-1,n) +1 << " ";

	return(0);
}