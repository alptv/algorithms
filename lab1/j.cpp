#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double f(double x, int v1, int v2, double a) {
	return (sqrt(x*x + (a - 1)*(a - 1))/v1 +  sqrt((x - 1)*(x - 1) + a * a)/ v2);
}
int main() {
	int v1, v2;
	double a, x, m1, m2, l, r;
	cin >> v1 >> v2 >> a;
	l = 0;
	r = 1;
	while ((r - l) >= 0.000001) {
		m1 = (r + 2 * l) / 3;
		m2 = (2 * r + l) / 3;
		if (f(m1, v1, v2, a) < f(m2, v1, v2, a)) r = m2;
		else l = m1;
	}
	cout << setprecision(7) << fixed;
	cout << (l + r) / 2;
	return(0);
}



 