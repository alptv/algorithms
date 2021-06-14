#include <iostream>
#include <string>
using namespace std;

long long t[4 * 500000];

void build(long long l, long long r , long long v, long long a[]) {
    if (l == r) {
        t[v] = a[r];
        return;
    }
    int m = (l+r)/2;
    build(l, m , 2 * v + 1, a);
    build(m + 1, r , 2 * v + 2, a);
    t[v] = t[2 * v + 1] + t[2 * v + 2];

}

long long get(long long L, long long R,long long l , long long r, long long v) {
     if (l > R || r < L) {
            return 0;
        }
        if (l >= L && r <= R) {
            return t[v];
        }
        int m = (l + r) / 2;
        long long a = get(L, R, l , m, 2 * v + 1);
        long long b = get(L, R, m + 1 , r, 2 * v + 2);
        return a + b;

}

void make(long long i, long long v, long long x, long long l, long long r) {
        if (l == r) {
            t[v] = x;
            return;
        }
        int m = (l+r) / 2;
        if (i <= m) {
            make(i,2 * v + 1, x, l, m);
        } else {
            make(i,2 * v + 2,x,m + 1,r);
        }
        t[v] = t[2 * v + 1] + t[2 * v + 2];
    }


    int main() {


        int n;
        long long a[5000001];
        cin >> n;
        for (int i = 0; i < n; i++){
        cin >> a[i];
        }
        build(0, n - 1, 0, a);
        string s;
        while (cin >> s) {
            long long x;
            long long y;
            cin >> x;
            cin >> y;
            if (s == "set") {
                make(x - 1, 0, y , 0, n - 1);
            } else {
                cout << get(x - 1, y - 1, 0, n - 1, 0) << '\n';
            }
        }
        return 0;
    }
 