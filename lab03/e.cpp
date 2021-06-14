#include <iostream>
#include <vector>
#include <string>
using namespace std;
int ans[1005][1005];
int min1(int  a,int b){
    if (a > b) return b;
    return a;
}
int min(int a,int b, int c) {
    a = min(a,b);
    a = min(a,c);
    return a;
}
int main() {
    string first;
    string second;
    cin >> first >> second;
    for (int i = 0; i <= first.length(); i++) {
        for (int j = 0; j <= second.length(); j++) {
            if (i==0 && j ==0) {
                    ans[i][j] = 0;
                    continue;
            }
            if (i>0 && j>0 && first[i-1] == second[j-1]) {
                ans[i][j] = ans[i-1][j-1];
                continue;
            }
            if (i>0 && j>0){
                ans[i][j] = min(ans[i-1][j-1] + 1,ans[i-1][j]+1,ans[i][j-1] + 1);
                continue;
            }
            if (i>0){
                ans[i][j] = ans[i-1][j]+1;
                continue;
            }
            if (j>0) {
                ans[i][j] = ans[i][j-1] + 1;
            }
        }
    }
    cout << ans[first.length()][second.length()];
}