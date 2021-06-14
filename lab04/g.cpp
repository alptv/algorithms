#include <iostream>
#include <algorithm>
using namespace std;

const int sd = 200000;
const int sz = 400000+100;
int t[10*sz];
int tAdd[10*sz];
int tCoord[10*sz];


struct Node {
    int x1;
    int x2;
    int y;
    bool isOpen;
    int i;
};

Node a[2000000];

bool operator < (Node a, Node b) {
    return (a.y < b.y) || (a.y == b.y && a.isOpen > b.isOpen) || (a.y == b.y && a.isOpen == b.isOpen && a.i > b.i);

}



void build(int l, int r, int v){
    if (l == r) {
        t[v] = 0;
        tAdd[v] = 0;
        tCoord[v] = l;
        return;
    }
    int m = (l + r) / 2;
    build (l , m , 2* v +1);
    build(m+1, r, 2 * v +2);
    tAdd[v] = 0;
    t[v] = 0;
    tCoord[v] = tCoord[2*v+1];

}

pair <int , int > allMin(){
    pair <int , int > ans;
    ans.first = t[0] + tAdd[0];
    ans.second = tCoord[0];
    return ans;
}

void update(int L, int R, int l, int r, int v, int x) {
    if (l >  R || r < L) {
        return;
    }
    if (l >= L && r <= R) {
        tAdd[v] += x;
        return;
    }
    t[v] = t[v] + tAdd[v];
    tAdd[2 * v + 1] += tAdd[v];
    tAdd[2 * v + 2] += tAdd[v];
    tAdd[v] = 0;
    int m = (l + r) / 2;
    update(L, R, l, m, 2 * v + 1, x);
    update(L, R, m + 1, r, 2 * v + 2, x);
    if (t[2 * v + 1] + tAdd[2 * v  +1] > t[2 * v + 2] + tAdd[2 * v + 2]) {
        t[v] = t[2 * v + 1] + tAdd[2 * v  + 1];
        tAdd[v] = 0;
        tCoord[v] = tCoord[2 * v + 1];
    } else {
        t[v] = t[2 * v + 2] + tAdd[2 * v  + 2];
        tAdd[v] = 0;
        tCoord[v] = tCoord[2 * v + 2];
    }
}



int main() {
    int n, x1, y1, x2,y2;
    cin >> n;
    for (int i = 0; i < 2 * n; i+=2) {
        cin >> x1 >> y1 >> x2 >> y2;
        Node first, second;
        first.x1 = x1 + sd; first.x2 = x2 + sd; first.y = y1; first.isOpen = true;
        second.x1 = x1 + sd; second.x2 = x2 + sd; second.y = y2; second.isOpen = false;
        first.i = i;
        second.i = i + 1;
        a[i] = first;
        a[i + 1] = second;
    }
    build(0,sz, 0);
    sort(a, a + 2*n);
    pair <int, pair <int, int >> ans;
    ans.first = -100000000;
    for (int i = 0; i < 2 * n; i++) {
        if (a[i].isOpen) {
            update(a[i].x1, a[i].x2, 0, sz, 0, 1);
            pair<int, int> res = allMin();
            if (res.first > ans.first) {
                ans.first = res.first;
                ans.second.first = res.second;
                ans.second.second = a[i].y;
            }
        } else {
            update(a[i].x1, a[i].x2, 0, sz, 0, -1);
        }
    }
    cout << ans.first << endl << ans.second.first - sd << " " << ans.second.second;

}