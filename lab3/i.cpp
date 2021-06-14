#include <iostream>
using namespace std;

bool good(int x, int y, int n) {
	if ((x & y) > 0) return 0;
	for (int i = 0; i < n; i++) {
		if (i == n - 1) {
			if ( ((1 << i) & x) == 0 && ((1 << i) & y) == 0  )
				return 0;
		}
		if ((((1 << i) & x) == 0) && (((1 << i) & y) == 0)) {
			if ((1 << (i + 1) & x) != 0 || (1 << (i + 1) & y) != 0) {
				return 0;
			}
				i++;
		}
	}
		return 1;
}

int dp[13][1 << 13];
int possible[1 << 12][1 << 12];
int n;
int m;
int profiles[13];
int field[13][13];

int main() {

	cin >> n >> m;

	for (int i = 0; i < 1 << n; i++) {
		for (int j = 0; j < 1 << n; j++) {
			possible[i][j] = good(i, j, n);
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			char c;
			cin >> c;
			if (c == 'X') field[i][j] = 1;
			else field[i][j] = 0;
		}
	}

	for (int i = 0; i < m; i++) {
		int profile = 0;
		for (int j = 0; j < n; j++) {
			if (field[j][i] == 1)
			profile = (1 << j) | profile;
		}
		profiles[i] = profile;
	}
	profiles[m] = 0;
	dp[profiles[0]][0] = 1;
	for (int i = 1; i <= m; i++) {
		for (int j = 0; j < (1 << n); j++) {
			for (int k = 0; k < (1 << n); k++) {
				if ((profiles[i] & j) >0) continue;
				dp[i][j | profiles[i]] += (dp[i - 1][k]) * possible[k][j];
			}
		}
	}
	cout << dp[m][0];
	return 0;
}