#include <iostream>
using namespace std;
void insert(int*a, int x, int &end) {
	end++;
	a[end] = x;
	int i = end, t = 0;
	while ((i - 1) / 2 >= 0) {
		if (a[(i - 1) / 2] < a[i]) {
			t = a[(i - 1) / 2];
			a[(i - 1) / 2] = a[i];
			a[i] = t;
			i = (i - 1) / 2;

		}
		else break;
	}

}
int removemax(int*a, int &end) {
	int t, i = 0, max;
	t = a[0];
	a[0] = a[end];
	a[end] = t;
	end--;
	while (2 * i + 1 <= end) {
		if (2 * i + 2 <= end) {
			if (a[i] < a[2 * i + 1] || a[i] < a[2 * i + 2]) {
				if (a[2 * i + 1] < a[2 * i + 2]) {
					t = a[i];
					a[i] = a[2 * i + 2];
					a[2 * i + 2] = t;
					i = 2 * i + 2;
				}
				else {
					t = a[i];
					a[i] = a[2 * i + 1];
					a[2 * i + 1] = t;
					i = 2 * i + 1;
				}
			}
			else break;
		}
		else {
			if (a[i] < a[2 * i + 1]) {
				t = a[i];
				a[i] = a[2 * i + 1];
				a[2 * i + 1] = t;
				i = 2 * i + 1;
			}
			else break;
		}
	}

	max = a[end + 1];
	a[end + 1] = 0;
	return(max);
}



int main() {
	int end = -1, a[100000], b[100000], n, x, y, j = 0;
	for (int i = 0;i < 100000;i++) a[i] = 0;
	cin >> n;
	for (int i = 0; i < n;i++) {
		cin >> x;
		if (x == 0) {
			cin >> y;
			insert(a, y, end);
		}
		else {
			b[j] = removemax(a, end);
			j++;
		}
	}
	for (int i = 0;i < j;i++) cout << b[i] << endl;
	return 0;
}