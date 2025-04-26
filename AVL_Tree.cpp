#include <iostream>
#include <string>
#include <sstream>

using namespace std;

template <typename KeyType>
struct Node {
    KeyType key;
    int value;
    int height = 1;
    Node *left = nullptr, *right = nullptr;

    Node(KeyType k, int v) : key(k), value(v) {}
};

template <typename KeyType>
class AVLTree {
protected:
    Node<KeyType>* root = nullptr;
    int rotations = 0;

    int getHeight(Node<KeyType>* n) { return n ? n->height : 0; }
    int max(int a, int b) { return a > b ? a : b; }
    void updateHeight(Node<KeyType>* n) { if (n) n->height = 1 + max(getHeight(n->left), getHeight(n->right)); }
    int getBalance(Node<KeyType>* n) { return n ? getHeight(n->left) - getHeight(n->right) : 0; }

    Node<KeyType>* rotateRight(Node<KeyType>* y) {
        Node<KeyType>* x = y->left, *T2 = x->right;
        x->right = y, y->left = T2;
        updateHeight(y), updateHeight(x);
        rotations++;
        return x;
    }

    Node<KeyType>* rotateLeft(Node<KeyType>* x) {
        Node<KeyType>* y = x->right, *T2 = y->left;
        y->left = x, x->right = T2;
        updateHeight(x), updateHeight(y);
        rotations++;
        return y;
    }

    Node<KeyType>* balance(Node<KeyType>* n) {
        if (!n) return nullptr;
        updateHeight(n);
        int bal = getBalance(n);
        if (bal > 1) return getBalance(n->left) >= 0 ? rotateRight(n) : (n->left = rotateLeft(n->left), rotateRight(n));
        if (bal < -1) return getBalance(n->right) <= 0 ? rotateLeft(n) : (n->right = rotateRight(n->right), rotateLeft(n));
        return n;
    }

    Node<KeyType>* insert(Node<KeyType>* n, KeyType k, int v, bool& i) {
        if (!n) return i = true, new Node<KeyType>(k, v);
        if (k == n->key) return i = false, n;
        if (k < n->key) n->left = insert(n->left, k, v, i);
        else n->right = insert(n->right, k, v, i);
        return i ? balance(n) : n;
    }

    Node<KeyType>* erase(Node<KeyType>* n, KeyType k, bool& f) {
        if (!n) return f = false, nullptr;
        if (k < n->key) n->left = erase(n->left, k, f);
        else if (k > n->key) n->right = erase(n->right, k, f);
        else {
            f = true;
            if (!n->left || !n->right) { Node<KeyType>* t = n->left ? n->left : n->right; delete n; return t; }
            Node<KeyType>* s = n->right; while (s->left) s = s->left;
            n->key = s->key, n->value = s->value;
            n->right = erase(n->right, s->key, f);
        }
        return balance(n);
    }

public:
    bool add(KeyType k, int v) { bool i; return root = insert(root, k, v, i), i; }

    bool remove(KeyType k) { bool f; return root = erase(root, k, f), f; }

    bool find(KeyType k, int& v) {
        Node<KeyType>* n = root;
        while (n) {
            if (k == n->key) return v = n->value, true;
            n = k < n->key ? n->left : n->right;
        }
        return false;
    }

    int getRotations() { return rotations; }
};

int main() {
    ios::sync_with_stdio(false), cin.tie(nullptr);

    AVLTree<int> avl;
    int N;
    cin >> N, cin.ignore();
    while (N--) {
        string line;
        getline(cin, line);
        istringstream iss(line);
        string op;
        iss >> op;
        if (op == "ADD") {
            int k, v;
            if (iss >> k >> v) cout << (avl.add(k, v) ? "" : "KEY ALREADY EXISTS\n");
        } else if (op == "LOOKUP") {
            int k, v;
            if (iss >> k) cout << (avl.find(k, v) ? to_string(v) + "\n" : "KEY NOT FOUND\n");
        } else if (op == "DELETE") {
            int k;
            if (iss >> k) cout << (avl.remove(k) ? "" : "KEY NOT FOUND\n");
        } else if (op == "PRINT_ROTATIONS") {
            cout << avl.getRotations() << '\n';
        }
    }
}