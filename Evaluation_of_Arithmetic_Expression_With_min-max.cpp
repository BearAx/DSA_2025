#include <iostream>
#include <stack>
#include <queue>
#include <sstream>
#include <map>
#include <cctype>
#include <cmath>

using namespace std;

map<string, int> precedence = {
    {"+", 1}, {"-", 1},
    {"*", 2}, {"/", 2},
    {"^", 3}
};

class Stack {
public:
    virtual ~Stack() {}
    virtual void push(const string& value) = 0;
    virtual void pop() = 0;
    virtual string top() const = 0;
    virtual bool isEmpty() const = 0;
};

class LinkedStack : public Stack {
private:
    struct Node {
        string data;
        Node* next;
        Node(const string& d) : data(d), next(nullptr) {}
    };
    Node* head;

public:
    LinkedStack() : head(nullptr) {}

    ~LinkedStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    void push(const string& value) override {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    void pop() override {
        if (isEmpty()) {
            throw out_of_range("Stack underflow");
        }
        Node* temp = head;
        head = head->next;
        delete temp;
    }

    string top() const override {
        if (isEmpty()) {
            throw out_of_range("Stack is empty");
        }
        return head->data;
    }

    bool isEmpty() const override {
        return head == nullptr;
    }
};

bool isNumber(const string &s) {
    if (s.empty()) return false;
    size_t start = 0;
    if (s[0] == '-' && s.size() > 1) {
        start = 1;
    }
    for (size_t i = start; i < s.size(); ++i) {
        if (!isdigit(s[i])) {
            return false;
        }
    }
    return true;
}

bool isOperator(const string &s) {
    return precedence.find(s) != precedence.end();
}

queue<string> shuntingYard(queue<string> tokens) {
    queue<string> output;
    LinkedStack operators;

    while (!tokens.empty()) {
        string token = tokens.front();
        tokens.pop();

        if (isNumber(token)) {
            output.push(token);
        } else if (token == "min" || token == "max") {
            operators.push(token);
        } else if (isOperator(token)) {
            while (!operators.isEmpty()) {
                string topOp = operators.top();
                if (isOperator(topOp)) {
                    bool condition;
                    if (token == "^") {
                        condition = precedence[topOp] > precedence[token];
                    } else {
                        condition = precedence[topOp] >= precedence[token];
                    }
                    if (condition) {
                        output.push(topOp);
                        operators.pop();
                    } else {
                        break;
                    }
                } else {
                    break;
                }
            }
            operators.push(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ",") {
            while (!operators.isEmpty() && operators.top() != "(") {
                output.push(operators.top());
                operators.pop();
            }
        } else if (token == ")") {
            while (!operators.isEmpty() && operators.top() != "(") {
                output.push(operators.top());
                operators.pop();
            }
            if (!operators.isEmpty()) {
                operators.pop(); // Pop the "("
            }
            if (!operators.isEmpty() && (operators.top() == "min" || operators.top() == "max")) {
                output.push(operators.top());
                operators.pop();
            }
        }
    }

    while (!operators.isEmpty()) {
        output.push(operators.top());
        operators.pop();
    }

    return output;
}

queue<string> tokenize(string expr) {
    queue<string> tokens;
    istringstream iss(expr);
    string token;
    while (iss >> token) {
        tokens.push(token);
    }
    return tokens;
}

int evaluate(queue<string> postfix) {
    stack<int> evalStack;

    while (!postfix.empty()) {
        string token = postfix.front();
        postfix.pop();

        if (isNumber(token)) {
            evalStack.push(stoi(token));
        } else {
            if (token == "+" || token == "-" || token == "*" || token == "/" || token == "^") {
                int b = evalStack.top(); evalStack.pop();
                int a = evalStack.top(); evalStack.pop();
                if (token == "+") {
                    evalStack.push(a + b);
                } else if (token == "-") {
                    evalStack.push(a - b);
                } else if (token == "*") {
                    evalStack.push(a * b);
                } else if (token == "/") {
                    evalStack.push(a / b);
                } else if (token == "^") {
                    evalStack.push(static_cast<int>(pow(a, b)));
                }
            } else if (token == "min" || token == "max") {
                int b = evalStack.top(); evalStack.pop();
                int a = evalStack.top(); evalStack.pop();
                if (token == "min") {
                    evalStack.push(min(a, b));
                } else {
                    evalStack.push(max(a, b));
                }
            }
        }
    }

    return evalStack.top();
}

int main() {
    string expression;
    getline(cin, expression);

    queue<string> tokens = tokenize(expression);
    queue<string> postfix = shuntingYard(tokens);
    int result = evaluate(postfix);

    cout << result << endl;

    return 0;
}