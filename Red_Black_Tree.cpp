#include <iostream>
#include <string>

using namespace std;

enum Color { RED, BLACK };

struct Node {
    int key;
    int value;
    Color color;
    Node* left;
    Node* right;
    Node* parent;

    Node(int k, int v) : key(k), value(v), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
private:
    Node* root;
    int rotations;
    int countBlackKeys;
    int countRedKeys;

    void leftRotate(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->left) x->parent->left = y;
        else x->parent->right = y;
        y->left = x;
        x->parent = y;
        rotations++;
    }

    void rightRotate(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr) root = y;
        else if (x == x->parent->right) x->parent->right = y;
        else x->parent->left = y;
        y->right = x;
        x->parent = y;
        rotations++;
    }

    void fixInsert(Node* node) {
        while (node != root && node->parent != nullptr && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;
                if (uncle != nullptr && uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }
        if (root != nullptr) root->color = BLACK;
    }

    Node* findNode(Node* node, int key) {
        if (node == nullptr || node->key == key) return node;
        return key < node->key ? findNode(node->left, key) : findNode(node->right, key);
    }

    void updateKeyCounts() {
        countBlackKeys = 0;
        countRedKeys = 0;
        countKeys(root);
    }

    void countKeys(Node* node) {
        if (node == nullptr) return;
        countKeys(node->left);
        if (node->color == BLACK) countBlackKeys++;
        else countRedKeys++;
        countKeys(node->right);
    }

    void transplant(Node* u, Node* v) {
        if (u->parent == nullptr) root = v;
        else if (u == u->parent->left) u->parent->left = v;
        else u->parent->right = v;
        if (v != nullptr) v->parent = u->parent;
    }

    Node* minimum(Node* node) {
        while (node != nullptr && node->left != nullptr) node = node->left;
        return node;
    }

    void deleteFixup(Node* x) {
        while (x != root && (x == nullptr || x->color == BLACK)) {
            if (x == x->parent->left) {
                Node* w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    leftRotate(x->parent);
                    w = x->parent->right;
                }
                if ((w->left == nullptr || w->left->color == BLACK) && (w->right == nullptr || w->right->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right == nullptr || w->right->color == BLACK) {
                        if (w->left != nullptr) w->left->color = BLACK;
                        w->color = RED;
                        rightRotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->right != nullptr) w->right->color = BLACK;
                    leftRotate(x->parent);
                    x = root;
                }
            } else {
                Node* w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rightRotate(x->parent);
                    w = x->parent->left;
                }
                if ((w->right == nullptr || w->right->color == BLACK) && (w->left == nullptr || w->left->color == BLACK)) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left == nullptr || w->left->color == BLACK) {
                        if (w->right != nullptr) w->right->color = BLACK;
                        w->color = RED;
                        leftRotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    if (w->left != nullptr) w->left->color = BLACK;
                    rightRotate(x->parent);
                    x = root;
                }
            }
        }
        if (x != nullptr) x->color = BLACK;
    }

public:
    RedBlackTree() : root(nullptr), rotations(0), countBlackKeys(0), countRedKeys(0) {}

    void add(int key, int value) {
        if (findNode(root, key) != nullptr) {
            cout << "KEY ALREADY EXISTS" << endl;
            return;
        }

        Node* newNode = new Node(key, value);
        Node* y = nullptr;
        Node* x = root;

        while (x != nullptr) {
            y = x;
            if (newNode->key < x->key) x = x->left;
            else x = x->right;
        }

        newNode->parent = y;
        if (y == nullptr) root = newNode;
        else if (newNode->key < y->key) y->left = newNode;
        else y->right = newNode;

        fixInsert(newNode);
        updateKeyCounts();
    }

    void deleteNode(int key) {
        Node* z = findNode(root, key);
        if (z == nullptr) {
            cout << "KEY NOT FOUND" << endl;
            return;
        }

        Node* y = z;
        Color yOriginalColor = y->color;
        Node* x = nullptr;

        if (z->left == nullptr) {
            x = z->right;
            transplant(z, z->right);
        } else if (z->right == nullptr) {
            x = z->left;
            transplant(z, z->left);
        } else {
            y = minimum(z->right);
            yOriginalColor = y->color;
            x = y->right;
            if (y->parent == z) {
                if (x != nullptr) x->parent = y;
            } else {
                transplant(y, y->right);
                if (y != nullptr) {
                    y->right = z->right;
                    if (y->right != nullptr) y->right->parent = y;
                }
            }
            transplant(z, y);
            if (y != nullptr) {
                y->left = z->left;
                if (y->left != nullptr) y->left->parent = y;
                y->color = z->color;
            }
        }

        if (x != nullptr && yOriginalColor == BLACK) {
            deleteFixup(x);
        }

        delete z;
        updateKeyCounts();
    }

    void lookup(int key) {
        Node* node = findNode(root, key);
        if (node == nullptr) {
            cout << "KEY NOT FOUND" << endl;
        } else {
            cout << node->value << endl;
        }
    }

    void printRotations() {
        cout << rotations << endl;
    }

    void printCountBlackKeys() {
        cout << countBlackKeys << endl;
    }

    void printCountRedKeys() {
        cout << countRedKeys << endl;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    RedBlackTree tree;

    for (int i = 0; i < N; ++i) {
        string operation;
        cin >> operation;

        if (operation == "ADD") {
            int key, value;
            cin >> key >> value;
            tree.add(key, value);
        } else if (operation == "LOOKUP") {
            int key;
            cin >> key;
            tree.lookup(key);
        } else if (operation == "DELETE") {
            int key;
            cin >> key;
            tree.deleteNode(key);
        } else if (operation == "PRINT_ROTATIONS") {
            tree.printRotations();
        } else if (operation == "PRINT_COUNT_BLACK_KEYS") {
            tree.printCountBlackKeys();
        } else if (operation == "PRINT_COUNT_RED_KEYS") {
            tree.printCountRedKeys();
        }
    }

    return 0;
}