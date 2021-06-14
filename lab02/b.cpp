#include <iostream>;
using namespace std;

void pop(int &j) {
	j--;
}

void push(int* stek, int &j, int a) {
	stek[++j] = a;
}
void shariki(int* stek, int &j, int &res) {

	if (j >= 2 && stek[j] == stek[j - 1] && stek[j - 2] == stek[j]) {
		while (stek[j] == stek[j - 1] && j >= 1) {
			j--;
			res++;
		}
		j--;
		res++;
	}
}



int main() {

	int t1, j = -1, stek[1000000], n, res = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		scanf("%d" ,&t1);
		if (j <= 1) stek[++j] = t1;
		else {
			if (t1 == stek[j - 1]) push(stek, j, t1);
			else {
				shariki(stek, j, res);
				push(stek, j, t1);
			}
		}
	}
	shariki(stek, j, res);
	
	cout << res;
	return 0;
}



	
 