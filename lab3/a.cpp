 #include <iostream>
#include <vector>
using namespace std;
int main() {
    freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
    int n, k;
    cin >> n >> k;
    vector <int> F(n);
    vector <int> cost(n,0);
    vector <int> res(n);
    vector <int> jump(n);
    vector <int> ans(n);
    for (int i = 1; i < n - 1; i++) {
        cin >> cost[i];
    }

    for (int i = 0; i < n; i++) {
        F[i]= -1000000000;
    }

    F[0] = 0;
    F[n-1] = -1000000000;
    jump[0] = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 1;j <= k; j++){
            if (i-j>=0) {
                if (F[i] <= F[i-j]+cost[i]) {
                F[i] = F[i-j] + cost[i];
                res[i] = i - j;
                jump[i] = jump[i - j] +1;
               }
            }
        }
    }
    int l = jump[n-1];
    k = jump[n-1];
    cout << F[n-1] << endl <<  jump[n-1] << endl;
    n--;
    while (l >= 0){
        ans[l] = n + 1;
        n = res[n];
        l--;
    }
    for (int i = 0; i <= k; i++) {
        cout << ans[i] << " ";
    }
    return 0;
}