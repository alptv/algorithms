#include <iostream>
#include <vector>

using namespace std;

const int MAXN =100000+10;


int parents[MAXN];

int dp[MAXN][100];

int main(){
    int n;

    cin >> n;
    int root;
    for (int i = 1; i <= n; i++){
        int p;
        cin >> p;
        if (p == 0) {
            root = i;
            continue;
        }
        parents[i] = p;
    }
    dp[root][0] = root;

    for (int i = 1; i <= n; i++){
        dp[i][0] = parents[i];
    }

    for (int i = 1;  (1 << i) <= n; i++){
        for (int  v = 1; v <=n; v++){
            dp[v][i] = dp[dp[v][i - 1]][i -1];
        }
    }
    for (int v = 1; v <= n; v++){
        cout << v << ": ";
        int i = 0;
        while((1 << i) <= n) {
            if (dp[v][i] == 0) break;
            cout << dp[v][i] << " ";
            i++;
        }
        cout << '\n';
    }


}