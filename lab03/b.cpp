#include <iostream>
#include <vector>
using namespace std;
int minimal =-2147483648;
int max(int a , int b) {
    if (a > b) return a;
    return b;
}
int main() {
  freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
    int  n , m;
    cin >> n >> m;
    vector <vector <int> > cost(n+2,vector <int>(m+2));
    vector <vector <int> > field(n+2,vector <int>(m+2));
    vector <char> ans;
    for (int i = 0; i < n+2;i++) {
            for (int j = 0; j < m+2;j++){
                if (i==0 || j==0 || j == m+1 || i == n+1) {
                    field[i][j] = minimal;
                    cost[i][j] = 0;
                } else {
                    cin >> cost[i][j];
                    field[i][j] = minimal;
                }
            }
    }

    for (int i = 1; i <= n; i++){
        for (int j = 1; j <= m; j++) {
                if (i==1 && j==1) {
                    field[i][j] = cost[i][j];
                    continue;
                }
            field[i][j] = max(field[i-1][j],field[i][j-1]);
            field[i][j]+=cost[i][j];
        }
    }
    int f = 0;
    cout << field[n][m];
    cout << endl;
    while (n!=1 || m!=1){
        if (m==1) {
            ans.push_back('D');
            n--;
            continue;
        }
        if(n==1) {
            ans.push_back('R');
            m--;
            continue;
        }

        if (field[n-1][m]> field[n][m-1]) {
            ans.push_back('D');
            n--;
        }
        else {
        ans.push_back('R');
        m--;
    }
    }
    for (int i =0; i < ans.size(); i++) {
        cout << ans[ans.size()-1-i];
    }
return 0;
}

 