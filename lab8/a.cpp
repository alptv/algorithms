#include <iostream>

using namespace std;

const int MAXN = 105;
const int INF = (int)-10e9;

int dp[MAXN][MAXN];

int min(int a, int b) {
    return a > b ? b : a;
}


int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> dp[i][j];
        }
    }
    for (int k = 0; k  < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                dp[i][j] = min(dp[i][j], dp[i][k] + dp[k][j]);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << dp[i][j] << ' ';
        }
        cout << '\n';
    }

}