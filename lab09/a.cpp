#include <iostream>
#include <vector>


using namespace std;

typedef long long ll;


const ll M = 1000000123;

const ll p = 991;

int main() {
    string s;
    cin >> s;
    int m; cin >> m;
    vector<ll> prefixHash(s.size() + 1, 0);
    vector<ll> powers(s.size(), 1);
    for (int i = 1; i < powers.size(); i++) {
        powers[i] = (powers[i - 1] * p) % M;
    }

    for (int i = 1; i <= s.size(); i++) {
        prefixHash[i] = (prefixHash[i - 1] * p + (int) s[i - 1]) % M;
    }
    for (int i = 0; i < m; i++) {
        int l1,r1,l2,r2;
        cin >> l1 >> r1 >> l2 >> r2;
        if ((r1 - l1) != (r2 - l2)) {
            cout << "No\n";
            continue;
        }
        ll h1 = (prefixHash[r1] - (prefixHash[l1 - 1] * powers[r1 - l1 + 1] % M) + M) % M;
        ll h2 = (prefixHash[r2] - (prefixHash[l2 - 1] * powers[r2 - l2 + 1] % M) + M) % M;
        if (h1 != h2) cout << "No\n";
        else {
            for (int j = 0; j < r1 - l1 + 1; j++) {
                if (s[j + l1 - 1] != s[j + l2 - 1]) {
                    cout << "No\n";
                    break;
                }
            }
            cout << "Yes\n";
        }
    }

}