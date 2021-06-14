#include <iostream>
#include <vector>
using namespace std;

int bin(int* a, int x, int l, int r) {
	int m;
	while (r > l + 1) {
		m = (l + r) / 2;
		if (a[m] <= x) l = m;
		else r = m;
	}
	if (a[l] == x) return(x);
	else {
		if ((a[r] - x) < (x - a[l])) return(a[r]);
		else return a[l];
	}
}
int main() {
	int n, k, a[100001], b[100001];
	cin >> n >> k;
	for (int i = 0; i < n; i++) cin >> a[i];
	for (int i = 0; i < k; i++) cin >> b[i];
	for (int i = 0; i < k; i++) cout << bin(a, b[i], 0, n - 1) << " ";
	return(0);
}