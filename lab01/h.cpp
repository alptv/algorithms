#include <iostream>
using namespace std;
int main() {
	long long w, h, n, l, r, max, m;
	cin >> w >> h >> n;
	if (w > h) max = w;
	else max = h;
	l = 0;
	r = n * max;
	while (r > l + 1) {
		m = (r + l) / 2;
		if ((m / w)*(m / h) < n) l = m;
		else r = m;
	}
	cout << r;
	return(0);

}