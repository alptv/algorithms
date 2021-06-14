#include <iostream>
using namespace std;
int main() {
	long long x, y, n, tmin = 0, tmax, m, temp;
	cin >> n >> x >> y;
	if (x > y) {
		temp = x;
		x = y;
		y = temp;
	}
	tmax = (n - 1) * x;
	while (tmax > tmin + 1) {
		m = (tmax + tmin) / 2;
		if ((m / x) + (m / y) < n - 1) tmin = m;
		else tmax = m;
	}
	cout << tmax + x;
	return 0;
}