#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;
bool find(vector <int> a, int x,int &temp) {
	for (int i = 0; i < a.size(); i++) {
		if (a[i] == x){
		    temp = i;
		 return true;
		}
	}
	return false;
}

int main() {
	int n, temp, index = 0, uk1 = 0, uk2 = 0, temp2;
	bool bo;
	cin >> n;
	vector <int> sorted;
	vector <int> arr1;
	vector <int> arr2;
	vector <string> res;
	for (int i = 0; i < n; i++) {
		cin >> temp;
		arr2.push_back(temp);
		sorted.push_back(temp);
	}
	sort(sorted.begin(), sorted.end());
	reverse(arr2.begin(), arr2.end());
	while (true) {
		bo = find(arr1, sorted[index],temp);
		if (bo)  {
			if (temp != arr1.size() - 1) {
				cout << "impossible";
				return 0;
			}
			else {
				arr1.pop_back();
				res.push_back("pop");
			}
		}
		else {
			bo = find(arr2, sorted[index], temp);
			temp = arr2.size() - temp - 1;
			for (int j = 0; j <= temp; j++) {
				arr1.push_back(arr2[arr2.size()-1]);
				arr2.pop_back();
				res.push_back("push");
			}
			arr1.pop_back();
			res.push_back("pop");
		}
		if (index == (n - 1)) break;
		index = index +1;
	}
	for (int i = 0; i < res.size(); i++) cout << res[i] + "\n";
	return 0;
}
 