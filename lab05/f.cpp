#include <iostream>
#include <string>
#include <random>
#include <time.h>

using namespace std;
struct node {
    node *left, *right;
    int x,y, size;

    node(int k) {
        x = k;
        y = rand();
        size = 1;
        left = nullptr;
        right = nullptr;
    }
    node(){
        left = right = nullptr;
    }
};

node* root = nullptr;


int trueVal(node *v) {
    if (!v) return 0;
    return v->size;
}

pair<node*, node*> split(node *v, int key) {
    if (!v) {
        return make_pair(nullptr, nullptr);
    }
    if (v->x < key) {
        pair<node *, node *> cur = split(v->right, key);
        v->right = cur.first;
        if (v)
        v->size =  trueVal(v->right) + trueVal(v->left) + 1;
        return make_pair(v, cur.second);
    } else {
        pair<node *, node *> cur = split(v->left, key);
        v->left = cur.second;
        if (v)
        v->size = trueVal(v->right) + trueVal(v->left) + 1;
        return make_pair(cur.first, v);
    }
}


node* merge(node *a, node* b) {
    if (!a) return  b;
    if (!b) return a;
    if (b->y > a->y) {
        b->left = merge(a , b-> left);
        if (b)
        b->size = trueVal(b->right) + trueVal(b->left) + 1;
        return b;
    } else {
        a->right = merge(a->right, b);
        if (a)
        a->size = trueVal(a->right) + trueVal(a->left) + 1;
        return  a;
    }
}

int element(node *v, int k) {
    if (!v) {
        cout << " pizec " << k << endl;
        return 0;
    }
    if (trueVal(v->left) + 1 == k) return v->x;
    if (trueVal(v->left) >= k) return element(v->left,k);
    else return element(v->right, k - 1 - trueVal(v->left));
}

void insert(int key) {
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

bool exists(node* v, int key) {
    if (!v) return false;
    if (v->x == key) return true;
    if (v->x > key) return exists(v->left, key);
    else return exists(v->right, key);
}
void print(node *v){
    if (!v)return;
    print(v->left);
    cout << v->size << " " << v->x << endl;
    print(v->right);
}


int main() {
    int n;
    cin >> n;
    int com;
    int count = 0;
    for (int i = 0;i < n; i++){
        cin >> com;
        if (com == 0) {
            int k;
            cin >> k;
            cout << element(root, count- k + 1) << endl;
        }
        if (com == 1) {
            count++;
            int x;
            cin >> x;
            insert(x);
        }
        if (com == -1) {
            count--;
            int x;
            cin >> x;
            erase(x);
        }
    }
}