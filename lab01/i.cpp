#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double f(double x) {
	return (x*x + sqrt(x));
}
int main() {
	double l,r,x,c,m;
	cin >> c;
	l = 0;
	r = c;
	while ((r-l)>=0.00000001){
		m = (l + r) / 2;
		if (f(m) <= c) l = m;
		else r = m;
	}
	cout << setprecision(7) << fixed;
	cout << (l + r) / 2;
	return(0);
}

 