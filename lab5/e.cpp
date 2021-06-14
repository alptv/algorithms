#include <iostream>
#include <string>
#include <random>
#include <time.h>

using namespace std;
struct node {
    node *left, *right;
    long long x,y, sum;

    node(long long k) {
        x = k;
        y = rand();
        sum = k;
        left = nullptr;
        right = nullptr;
    }
    node(){
        left = right = nullptr;
    }
};

node* root = nullptr;


long long trueVal(node *v) {
    if (!v) return 0;
    return v->sum;
}

pair<node*, node*> split(node *v, int key) {
    if (!v) {
        return make_pair(nullptr, nullptr);
    }
    if (v->x < key) {
        pair<node *, node *> cur = split(v->right, key);
        v->right = cur.first;
        if (v)
            v->sum =  trueVal(v->right) + trueVal(v->left) + v->x;
        return make_pair(v, cur.second);
    } else {
        pair<node *, node *> cur = split(v->left, key);
        v->left = cur.second;
        if (v)
            v->sum = trueVal(v->right) + trueVal(v->left) + v->x;
        return make_pair(cur.first, v);
    }
}


node* merge(node *a, node* b) {
    if (!a) return  b;
    if (!b) return a;
    if (b->y > a->y) {
        b->left = merge(a , b-> left);
        if (b)
            b->sum = trueVal(b->right) + trueVal(b->left) + b->x;
        return b;
    } else {
        a->right = merge(a->right, b);
        if (a)
            a->sum = trueVal(a->right) + trueVal(a->left) + a->x;
        return  a;
    }
}
bool exists(node* v, int key) {
    if (!v) return false;
    if (v->x == key) return true;
    if (v->x > key) return exists(v->left, key);
    else return exists(v->right, key);
}


void insert(long long key) {
    if (exists(root,key)) return;
    node* add = new node(key);
    node*ans;
    pair<node*,node*> cur = split(root,key);
    ans = merge(cur.first, add);
    ans = merge(ans, cur.second);
    root = ans;
}

void erase(int key) {
    pair<node*, node*> fir, sec;
    fir = split(root, key);
    sec = split(fir.second, key + 1);
    root = merge(fir.first, sec.second);
}


long long element(int l, int r) {
    pair<node* ,node*> temp = split(root, l), temp1;
    temp1 = split(temp.second, r + 1);
    long long ans = trueVal(temp1.first);
    node *temp2 = merge(temp1.first, temp1.second);
    temp2 = merge(temp.first, temp2);
    root = temp2;
    return ans;
}
void print(node *v){
    if (!v)return;
    print(v->left);
    cout << v->sum << " " << v->x <<"A "<< endl;
    print(v->right);
}


int main() {
    int n,x,l,r;
    long long last;
    char cur,prev;
    cin >> n;
    cin >> cur;
    if (cur == '+') {
        cin >> x;
        insert(x);
    } else {
        cin >> l >> r;
        last = element(l,r);
        cout << last << endl;
    }
    int com;
    int count = 0;
    for (int i = 1;i < n; i++){
        prev = cur;
        cin >> cur;
        if (cur == '+'){
            cin >> x;
            if (prev == '+'){
                insert(x);
            } else {
                last = last % 1000000000;
                insert((last + x) % 1000000000);
            }
        } else {
            cin >> l >> r;
            last = element(l,r);
            cout << last << endl;
        }
    }
}