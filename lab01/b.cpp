#include <iostream>
#include <vector>
using namespace std;
int main() {
	int n, x, count[101];
	vector <int> arr;
	while (cin >> x) arr.push_back(x);
	n = arr.size();
	vector <int> sort(n);

	for (int i = 0; i < 101; i++) count[i] = 0;

	for (int i = 0; i < n; i++) count[arr[i]]++;

	for (int i = 1; i < 101; i++) count[i] = count[i - 1] + count[i];

	for (int i = n - 1; i >= 0; i--) {
		sort[count[arr[i]] - 1] = arr[i];
		count[arr[i]]--;
	}
	for (int i = 0; i < n; i++) cout << sort[i] << " ";
	return(0);
}