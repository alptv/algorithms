#include <iostream>
#include <vector>


using  namespace std;



int main() {
    string ptr, str;
    cin >> ptr >> str;
    int n =(int) str.size();
    int m = (int) ptr.size();

    vector<int> prefix(m, 0);
    for (int i = 1; i < m; i++) {
        int p = prefix[i - 1];
        while (p > 0 && ptr[p] != ptr[i]) {
            p = prefix[p - 1];
        }
        prefix[i] = p;
        if (ptr[p] == ptr[i]) prefix[i]++;
    }
    int pos = 0;
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (pos != m && str[i] == ptr[pos]) {
            pos++;
            if (pos == m) ans.push_back(i);
            continue;
        }
        if (pos == 0) continue;
        pos  = prefix[pos - 1];
        while (pos > 0 && ptr[pos] != str[i]) {
            pos = prefix[pos - 1];
        }
        if (ptr[pos] == str[i]) {
            pos++;
            if (pos == m) ans.push_back(i);
        }
    }
    cout << ans.size() << "\n";
    for (int x : ans) cout << x + 2 - m<< " ";
}