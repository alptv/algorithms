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

int p[2*10000000 + 5];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    for (ll i = 2; i <= 2*10000000; i++) {
        if (!p[i]) {
            for (ll j = i * i ; j <=  2*10000000; j += i) p[j] = 1;
        }
    }
    int n;
    cin >> n;
    while (n--) {
        int x; cin >> x;
        if (p[x]) cout << "NO\n";
        else cout << "YES\n";
    }
}