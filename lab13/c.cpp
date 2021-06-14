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

ll mul(ll a, ll b, ll m ) {
    ll q = (ll)((long double)a * (long double)b / (long double)m);
    ll r = a * b - q * m;
    return (r + 5 * m) % m;
}

ll power(ll x, ll n, ll s) {
    ll ans = 1;
    while (n != 0) {
        if (n % 2 == 1) {
            ans = mul(ans, x, s);
            n--;
        } else {
            x = mul(x, x, s);
            n /= 2;
        }
    }
    return ans;
}


bool test(ll p) {
    p--;
    ll s = p + 1;
    ll k = 0;
    while (p % 2 != 1) {p/=2; k++;}
    ll r = rand() % s;
    r += (r == 0);
    ll x = power(r,p, s);
    if (x == 1) return true;
    for (int i = 0; i < k; i++) {
        if (x == s - 1) return true;
        x = mul(x, x, s);
    }
    return false;
}



int main() {
    srand(time(0));
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    while (n--) {
        ull x; cin >> x;
        if (x == 1) {
            cout << "NO\n";
            continue;
        }
        int c = 1;
        for (int  i = 0; i < 10; i++) {
            if (!test(x)) {
                cout << "NO\n";
                c= 0;
                break;
            }
        }
        if (c)cout << "YES\n";
    }

}