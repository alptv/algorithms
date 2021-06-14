#include <iostream>
#include <string>
#include <random>
#include <time.h>

using namespace std;
struct node {
    node *left, *right;
    int x,y;

    node(int k) {
        x = k;
        y = rand();
        left = nullptr;
        right = nullptr;
    }
    node(){
        left = right = nullptr;
    }
};

node* root = nullptr;

pair<node*, node*> split(node *v, int key) {
    if (!v) {
        return make_pair(nullptr, nullptr);
    }
    if (v->x < key) {
        pair<node *, node *> cur = split(v->right, key);
        v->right = cur.first;
        return make_pair(v, cur.second);
    } else {
        pair<node *, node *> cur = split(v->left, key);
        v->left = cur.second;
        return make_pair(cur.first, v);
    }
}

node* merge(node *a, node* b) {
    if (!a) return  b;
    if (!b) return a;
    if (b->y > a->y) {
        b->left = merge(a , b-> left);
        return b;
    } else {
        a->right = merge(a->right, b);
        return  a;
    }
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

string next(int val){
    node * curr = root, *ans = nullptr;
    while (curr != nullptr) {
        if (val < curr-> x) {
            ans = curr;
            curr = curr ->left;
        } else {
            curr = curr ->right;
        }
    }
    if (ans == nullptr || ans ->x <= val) return "none";
    return to_string(ans -> x);
}

string prev(int val){
    node * curr = root, *ans = nullptr;
    while (curr != nullptr) {
        if (val > (curr-> x)) {
            ans = curr;
            curr = curr ->right;
        } else {
            curr = curr ->left;
        }
    }
    if (ans == nullptr || (ans ->x >= val)) return "none";
    return to_string(ans -> x);
}

int main() {
    string s;
    while (cin >> s) {
        int x;
        if (s == "exists") {
            cin >> x;
            if (exists(root,x)) cout << "true" << endl;
            else cout << "false" << endl;
        }
        if (s == "insert") {
            cin >> x;
            insert(x);
        }
        if (s == "delete") {
            cin >> x;
            erase(x);
        }
        if (s == "next") {
            cin >> x;
            cout << next(x) << endl;
        }
        if (s == "prev") {
            cin >> x;
            cout << prev(x) << endl;
        }
    }
}