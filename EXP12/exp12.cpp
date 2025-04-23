#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Structure for a list of line numbers to be backpatched
struct List {
    vector<int> lines;
};

// Structure to store expression result
struct Expression {
    List truelist;
    List falselist;
};

// Global list of generated code
vector<string> code;

// Create a new list containing a single line number
List makelist(int line) {
    List l;
    l.lines.push_back(line);
    return l;
}

// Merge two lists
List merge(List l1, List l2) {
    l1.lines.insert(l1.lines.end(), l2.lines.begin(), l2.lines.end());
    return l1;
}

// Backpatching: insert a target to all lines in the list
void backpatch(List l, int target) {
    for (int i : l.lines) {
        code[i] += " " + to_string(target); // Fill in the target address
    }
}

// Generate code and return the line number
int gen(string instruction) {
    code.push_back(instruction);
    return code.size() - 1; // Return the line number of the instruction
}

int main() {
    cout << "Enter boolean condition (e.g., a < b, a == b): ";
    string condition;
    getline(cin, condition);

    // Simulate parsing the condition and generating code
    Expression expr;
    int lineTrue = gen("if " + condition + " goto ___"); // Placeholder for true jump
    int lineFalse = gen("goto ___"); // Placeholder for false jump

    expr.truelist = makelist(lineTrue);
    expr.falselist = makelist(lineFalse);

    // Simulate true block
    int trueStart = code.size(); // Where the true block starts
    gen("x = 10");  // Statement in the true block
    gen("goto ___"); // Jump to end (placeholder)
    List truelabel = makelist(code.size() - 1); // Keep track of the end of true block

    // Simulate false block
    int falseStart = code.size(); // Where the false block starts
    gen("x = 20");  // Statement in the false block

    // Backpatching after true/false labels are determined
    backpatch(expr.truelist, trueStart);  // Fill in true jump addresses
    backpatch(expr.falselist, falseStart); // Fill in false jump addresses
    backpatch(truelabel, code.size());  // Fill in the jump from true block to end

    cout << "\nGenerated Code with Backpatching:\n";
    for (int i = 0; i < code.size(); ++i) {
        cout << i << ": " << code[i] << endl;
    }

    return 0;
}
