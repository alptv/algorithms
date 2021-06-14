#include <iostream>
#include <vector>
using namespace std;
int min(int a,int b) {
    if (a<b) return a;
    return b;
}
int inf  = 1000000000;
int distanse[15][15];
int F[1 << 15][15];
int res[15];
int pre[1 << 15][15];
int pre_mask[1 << 15][15];

int main() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j =0; j < n; j++) {
    cin >> distanse[i][j];
        }
    }
    for (int i =0; i < 1 << n; i++){
        for (int j = 0;j < n; j++){
            F[i][j] = inf;
            F[i][15] = inf;
        }
    }



    for (int i = 0; i < (1 << n); i++) {
        for (int j = 0; j < n; j++) {
                 if ((i &(i-1))==0 ) {
                        F[i][j] = 0;
                        continue;
                    }
                if (((1 << j) & i) == 0) {
                    F[i][j] = inf;
                    continue;
                }
            for (int k = 0; k  < n; k++){
                    if (k == j) continue;
                    int c = i^(1<<j);
                    if ((c&(c-1)) ==0 && ((1 << k)& i)!=0) {
                            F[i][j] = F[i^(1<<j)][k]+distanse[j][k];
                            pre[i][j] = k;
                            pre_mask[i][j] = i^(1 << j);
                            continue;
                    }

                    if (F[i][j] > F[i^(1<<j)][k]+distanse[j][k] && ((1 << k)& i)!=0) {
                        F[i][j] = F[i^(1<<j)][k] +distanse[j][k];
                       pre[i][j] = k;
                       pre_mask[i][j] = i^(1 << j);
                    }
            }
        }
    }
    int ans = inf;
    int ind = 0;
    for (int i =0; i < n; i++){
            if (F[(1 << n) -1][i] <= ans) {
                ans = F[(1<< n) - 1][i];
                ind = i;
            }

    }

     cout << ans << endl;
     int mask = (1 << n) - 1;
     for (int i = 0 ; i < n; i++ ) {
        cout << ind+1 << " ";
        int t = ind;
        ind = pre[mask][ind];
        mask = pre_mask[mask][t];
     }
}
