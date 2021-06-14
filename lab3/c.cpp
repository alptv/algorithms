#include <iostream>
#include <vector>
#include <string>
using namespace std;
int max(int a, int b) {
    if (a>b) return a;
    else return b;
}
int main(){
    int n;
    cin >> n;
    vector <int> sequence(n);
    vector <int> F(n,1);
    vector <int> prev(n);
    vector <int> ans;

    for (int i = 0; i< n; i++){
        cin >> sequence[i];
        prev[i] = i;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++){
            if (sequence[i] > sequence[j] && (F[j] + 1)> F[i]) {
                F[i] = F[j] + 1;
                prev[i] = j;
        }
    }
    }
    int maximum = -1000000001;
    int index;
    for (int i = 0; i < n; i++) {
       if (F[i]>maximum) {
           maximum = F[i];
           index = i;
       }
    }
    cout << maximum;
   cout << endl;
    while (prev[index] != index) {
        ans.push_back(sequence[index]);
        index = prev[index];
    }
    cout << sequence[index] << " ";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[ans.size()-1 - i] << " ";
    }

    return 0;
}

 