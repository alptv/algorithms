#include <iostream>;
using namespace std;

void pop(int &j) {
	j--;
}

void push(int* stek, int &j, int a, int* stekmin) {
	if (j == 0) stekmin[j] = a; {
		if (a < stekmin[j]) stekmin[++j] = a;
		else {
			stekmin[j + 1] = stekmin[j];
			j++;
		}
	}
	stek[j] = a;
}


int getmin (int &j, int* stekmin) {
	return stekmin[j];
}

int main() {
   
	int t1,t2, j = 0, stek[1000000], n, stekmin[1000000], k = 0;
	scanf("%d",&n);
	for (int i = 0; i < n; i++) {
		scanf("%d",&t1);
		if (t1 == 1) {
			scanf("%d",&t2);
			push(stek, j, t2, stekmin);
		}
		if (t1 == 2) pop(j);
		if (t1 == 3) {
		printf("%d\n",getmin(j,stekmin));
		}
	}

	return 0;


}