#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cmath>
#include <deque>
#include <queue>
#include <cassert>
#include <stack>
#include <iomanip>
#include <utility>
#include <math.h>

using namespace std;
typedef long long ll;
typedef unsigned long long ull;

ll p[2*1000000 + 5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (ll i = 2; i <= 2*1000000; i++) {
        if (!p[i]) {
            for (ll j = i * i ; j <=  2*1000000; j += i) {
                if (p[j] == 0) p[j] = i;
            }
        }
    }
    int n;
    cin >> n;
    while (n--) {
        ll x; cin >> x;
        while (p[x] != 0) {
            cout << p[x] << ' ';
            x = x / p[x];
        }
        cout << x;
        cout << '\n';
    }
}