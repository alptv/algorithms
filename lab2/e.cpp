#include <iostream>
#include <deque> 
using namespace std;
int pop(int* stek, int &j) {
	return stek[j--];
}

void push(int* stek, int &j, int a) {
	stek[++j] = a;
}



int main() {
	int arr[1000000];
	char x;
	int num1, num2,num3 = 0;
	int j = -1;
	while (cin >> x) {
		if (x >= '0' && x <= '9') {
		    int y = x -'0';
			push(arr, j, y);
		}
		else {
			num1 = pop(arr, j);
			num2 = pop(arr, j);
			if (x == '+') num3 = num1 + num2;
			if (x == '-') num3 = num2 - num1;
			if (x == '*') num3 = num1 * num2;
			push(arr, j, num3);
		}
	}
	cout << pop(arr,j);
	return 0;
}