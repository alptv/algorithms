#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;
long long ans[1000][10];
int main() {
    int mod = 1000000000;
	int n;
	cin >> n;
	map <int, string > map;
	map[0] = "46";
	map[1] = "86";
	map[2] = "79";
	map[3] = "48";
	map[4] = "390";
	map[5] = "";
	map[6] = "170";
	map[7] = "26";
	map[8] = "13";
	map[9] = "24";

	for (int i = 0; i < 10; i++) {
		ans[1][i] = 1;
	}
	ans[1][8] = 0;
	ans[1][0] = 0;

	for (int i = 2; i <= n; i++) {
		for (int j = 0; j < 10; j++) {
 			for (int h = 0; h < map[j].size();h++) {
				int num = map[j][h] - '0';
				ans[i][j] = (ans[i][j]+ ans[i - 1][num]) % mod;
			}
		}
	}
	long long res = 0;
	for (int i = 0; i <= 9; i++) {
		res = (res + ans[n][i]) % mod;
	}
	cout << res ;
	return 0;
}





 