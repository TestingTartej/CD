#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <sstream>

using namespace std;

class Grammar {
public:
    map<char, vector<string>> productions;
    void inputGrammar(int n);
    void removeLeftRecursion();
    void leftFactoring();
    void displayGrammar();
};

void Grammar::inputGrammar(int n) {
    cout << "Enter productions (e.g., A->Aa|b):\n";
    for (int i = 0; i < n; i++) {
        string input;
        cin >> input;
        char nonTerminal = input[0];
        string rhs = input.substr(3);
        stringstream ss(rhs);
        string token;
        while (getline(ss, token, '|')) {
            productions[nonTerminal].push_back(token);
        }
    }
}

void Grammar::removeLeftRecursion() {
    map<char, vector<string>> newProductions;
    for (auto &entry : productions) {
        char A = entry.first;
        vector<string> alpha, beta;
        
        for (string rule : entry.second) {
            if (rule[0] == A) 
                alpha.push_back(rule.substr(1));
            else 
                beta.push_back(rule);
        }

        if (!alpha.empty()) {
            string newNonTerminal = string(1, A) + "'";
            for (string b : beta)
                newProductions[A].push_back(b + newNonTerminal);
            for (string a : alpha)
                newProductions[newNonTerminal[0]].push_back(a + newNonTerminal);
            newProductions[newNonTerminal[0]].push_back("EPS"); 
        } else {
            newProductions[A] = entry.second;
        }
    }
    productions = newProductions;
}

void Grammar::leftFactoring() {
    map<char, vector<string>> newProductions;
    for (auto &entry : productions) {
        char A = entry.first;
        map<string, vector<string>> prefixGroups;
        
        for (string rule : entry.second) {
            string prefix = rule.substr(0, 1);
            prefixGroups[prefix].push_back(rule.substr(1));
        }
        
        for (auto &group : prefixGroups) {
            if (group.second.size() > 1) {
                string newNonTerminal = string(1, A) + "_F";
                newProductions[A].push_back(group.first + newNonTerminal);
                for (string suffix : group.second)
                    newProductions[newNonTerminal[0]].push_back(suffix.empty() ? "EPS" : suffix);
            } else {
                newProductions[A].push_back(group.first + group.second[0]);
            }
        }
    }
    productions = newProductions;
}

void Grammar::displayGrammar() {
    for (auto &entry : productions) {
        cout << entry.first << " -> ";
        for (size_t i = 0; i < entry.second.size(); i++) {
            cout << entry.second[i];
            if (i < entry.second.size() - 1) cout << " | ";
        }
        cout << endl;
    }
}

int main() {
    Grammar g;
    int n;
    cout << "Enter number of productions: ";
    cin >> n;
    g.inputGrammar(n);
    
    cout << "\nOriginal Grammar:\n";
    g.displayGrammar();
    
    g.removeLeftRecursion();
    cout << "\nAfter Removing Left Recursion:\n";
    g.displayGrammar();
    
    g.leftFactoring();
    cout << "\nAfter Left Factoring:\n";
    g.displayGrammar();
    
    return 0;
}