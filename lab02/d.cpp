#include <iostream>
#include <deque> 
using namespace std;

int main() {
	deque <int> deque1;
	deque <int> deque2;
	int n, temp, id, j;
	char c;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> c;
		if (c == '+') {
			cin >> j;
			if (deque2.size() == deque1.size()) {
			    deque2.push_back(j);
			    deque1.push_back(deque2[0]);
			    deque2.pop_front();
			}
			else {
			deque2.push_back(j);
			}
		}
		if (c == '*') {
			cin >> j;
	if(deque2.size()==deque1.size()) {
	    deque1.push_back(j);
		} else {
		    deque2.push_front(j);
		}
		}
		if (c == '-') {
		   cout << deque1[0];
		   cout << endl;
		   deque1.pop_front();
		   if (deque1.size() !=deque2.size()) {
		       deque1.push_back(deque2[0]);
		       deque2.pop_front();
		   }
		}
	}
	
	return 0;
}
		
		