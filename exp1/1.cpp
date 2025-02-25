#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <cmath>
#include <sstream>
using namespace std;

bool isOp(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }
int prec(char op) { return (op == '+' || op == '-') ? 1 : (op == '*' || op == '/') ? 2 : (op == '^') ? 3 : 0; }
double applyOp(double a, double b, char op) { return op == '+' ? a + b : op == '-' ? a - b : op == '*' ? a * b : op == '/' ? a / b : pow(a, b); }

string toPostfix(const string &expr) {
    stack<char> ops; string post;
    for (char c : expr) {
        if (isdigit(c) || c == '.') post += c;
        else if (c == '(') ops.push(c);
        else if (c == ')') {
            while (!ops.empty() && ops.top() != '(') post += ' ', post += ops.top(), ops.pop();
            ops.pop();
        } else if (isOp(c)) {
            post += ' ';
            while (!ops.empty() && prec(ops.top()) >= prec(c) && c != '^') post += ops.top(), ops.pop(), post += ' ';
            ops.push(c);
        }
    }
    while (!ops.empty()) post += ' ', post += ops.top(), ops.pop();
    return post;
}

double evalPostfix(const string &post) {
    stack<double> vals; stringstream ss(post); string tok;
    while (ss >> tok) {
        if (isdigit(tok[0]) || (tok[0] == '-' && tok.length() > 1)) vals.push(stod(tok));
        else {
            double b = vals.top(); vals.pop();
            double a = vals.top(); vals.pop();
            vals.push(applyOp(a, b, tok[0]));
        }
    }
    return vals.top();
}

bool isBal(const string &expr) {
    int bal = 0;
    for (char c : expr) {
        if (c == '(') bal++;
        else if (c == ')') {
            if (bal == 0) return false;
            bal--;
        }
    }
    return bal == 0;
}

int main() {
    string in;
    cout << "Enter an arithmetic expression (Ctrl+D to exit):\n";
    while (getline(cin, in)) {
        if (!isBal(in)) cout << "Error: Unbalanced parentheses\n";
        else try {
            cout << "Result: " << evalPostfix(toPostfix(in)) << "\n";
        } catch (...) {
            cout << "Error: Invalid expression\n";
        }
    }
    return 0;
}