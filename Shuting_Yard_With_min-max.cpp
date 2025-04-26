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

bool isNumber(const string &s) {
    return !s.empty() && (isdigit(s[0]) || (s[0] == '-' && s.size() > 1));
}

bool isOperator(const string &s) {
    return precedence.find(s) != precedence.end();
}

queue<string> shuntingYard(queue<string> tokens) {
    queue<string> output;
    stack<string> operators;
    
    while (!tokens.empty()) {
        string token = tokens.front();
        tokens.pop();
        
        if (isNumber(token)) {
            output.push(token);
        } else if (token == "min" || token == "max") {
            operators.push(token);
        } else if (isOperator(token)) {
            while (!operators.empty() && isOperator(operators.top()) && 
                   precedence[operators.top()] >= precedence[token]) {
                output.push(operators.top());
                operators.pop();
            }
            operators.push(token);
        } else if (token == "(") {
            operators.push(token);
        } else if (token == ",") {
            while (!operators.empty() && operators.top() != "(") {
                output.push(operators.top());
                operators.pop();
            }
        } else if (token == ")") {
            while (!operators.empty() && operators.top() != "(") {
                output.push(operators.top());
                operators.pop();
            }
            operators.pop();
            if (!operators.empty() && (operators.top() == "min" || operators.top() == "max")) {
                output.push(operators.top());
                operators.pop();
            }
        }
    }
    
    while (!operators.empty()) {
        output.push(operators.top());
        operators.pop();
    }
    
    return output;
}

queue<string> tokenize(string expr) {
    queue<string> tokens;
    string token;
    
    for (size_t i = 0; i < expr.size(); i++) {
        if (isalnum(expr[i])) {
            token += expr[i];
        } else {
            if (!token.empty()) {
                tokens.push(token);
                token.clear();
            }
            if (!isspace(expr[i])) {
                tokens.push(string(1, expr[i]));
            }
        }
    }
    
    if (!token.empty()) {
        tokens.push(token);
    }
    
    return tokens;
}

int main() {
    string expression;
    getline(cin, expression);
    
    queue<string> tokens = tokenize(expression);
    queue<string> postfix = shuntingYard(tokens);
    
    queue<string> temp = postfix;
    while (!temp.empty()) {
        cout << temp.front() << " ";
        temp.pop();
    }
    cout << endl;
    
    return 0;
}