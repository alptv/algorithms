#include <iostream>
#include <deque> 
using namespace std;

int main() {
	deque <int> deque;
	int n,temp, id,q;
	cin >> n;
	for (int i = 0; i < n; i++) {
		scanf("%d", &temp);
		if (temp == 1) {
			cin >> id;
			deque.push_back(id);
		}
		if (temp == 2) deque.pop_front();
		if (temp == 3) deque.pop_back();
		if (temp == 5) cout << deque[0] << endl;
		if (temp == 4) {
			cin >> q;
			for (int j = 0; j < deque.size(); j++) {
				if (deque[j] == q) cout << j << endl;
			}
		}
	}
	return(0);
}