#include <iostream>
#include <string>
#include <utility>
#include "vector"
#include "string"
using namespace std;


long long const pl = 500000;
struct Node {
    int count;
    int length;
    bool pref;
    bool suf;
    int  isBlack;

    Node(int a,int b, bool c, bool d, int f) {
        count = a;
        length = b;
        pref = c;
        suf = d;
        isBlack = f;
    }
};

Node zero(0,0,false,false, 0);

vector <Node> t(4*1000005, zero);

Node trueValue(Node a, long long l, long long r) {
    if (a.isBlack == 1) {
        Node res(1,r - l + 1,true,true,true);
        return res;
    }
    if (a.isBlack == 0) {
        return  zero;
    }
    return a;
}

Node mov(Node a, Node b) {
    Node res = zero;
    res.length = a.length + b.length;
    if (a.suf && b.pref) {
        res.count = a.count + b.count - 1;
    } else {
        res.count = a.count + b.count;
    }
    res.suf = b.suf;
    res.pref = a.pref;
    if (a.isBlack == 1 &&  b.isBlack == 1) {
        res.isBlack = 1;
    } else {
        if (a.isBlack == 0 && b.isBlack == 0) {
            res.isBlack = 0;
        } else {
            res.isBlack = 2;
        }
    }

    return res;

}

void push(long long v,long long l,long long r) {
    if (l == r) {
        t[v] = trueValue(t[v], l ,r);
    }
    if (t[v].isBlack == 1) {
        t[v] = trueValue(t[v],l,r);
        t[2*v + 1].isBlack = 1;
        t[2*v + 2].isBlack = 1;
        return;
    }
    if (t[v].isBlack == 0) {
        t[v] = trueValue(t[v],l,r);
        t[2*v + 1].isBlack = 0;
        t[2*v + 2].isBlack = 0;
    }
}

Node get(long long L, long long R,long long l , long long r, long long v) {
    if (l > R || r < L) {
        return zero;
    }
    if (l >= L && r <= R) {
        return trueValue(t[v], l , r);
    }
    long long m = (l + r) / 2;
    push(v,l,r);
    Node a = get(L, R, l , m, 2 * v + 1);
    Node b = get(L, R, m + 1 , r, 2 * v + 2);
    return mov(a,b);

}

void set(long long L, long long R,long long l , long long r, long long v, long long x) {
    if (l > R || r < L) {
        return;
    }
    if (l >= L && r <= R) {
        t[v].isBlack = x;
        return;
    }
    long long m = (l + r) / 2;
    push(v,l,r);
    set(L, R, l , m, 2 * v + 1,x);
    set(L, R, m + 1 , r, 2 * v + 2,x);
    t[v] = mov(trueValue(t[2*v+1],l ,m), trueValue(t[2*v+2],m +1 ,r));
}




int main() {
    int n;
    cin >> n;
    string check;
    int x, y;
    for (int i = 0; i < n; i++) {
        cin >> check;
        cin >> x >> y;
        if (check == "B") {
            set(x + pl ,x + y - 1 +pl ,0,2*pl+1,0,1);
            Node a = get(0,2*pl+1,0,2*pl+1,0);
            cout << a.count << " " << a.length << endl;
        } else {
            set(x + pl ,x + y - 1 + pl,0,2*pl+1,0,0);
            Node a = get(0,2*pl+1,0,2*pl+1,0);
            cout << a.count << " " << a.length << endl;
        }
    }
}