#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Simulated symbol table
struct Symbol {
    char name;
    char address[10];
} table[] = {
    {'a', "0x100"}, {'b', "0x104"}, {'c', "0x108"},
    {'d', "0x10C"}, {'e', "0x110"}, {'f', "0x114"},
    {'g', "0x118"}, {'h', "0x11C"}, {'i', "0x120"}
};

// Function to get the address of a variable from the symbol table
char* getAddress(char var) {
    for (int i = 0; i < sizeof(table) / sizeof(table[0]); i++) {
        if (table[i].name == var)
            return table[i].address;
    }
    return "Unknown";
}

// Function to check precedence of operators
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char* infix, char* postfix) {
    char stack[100];
    int top = -1, k = 0;
    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[k++] = ch;  // Directly add operands to postfix expression
        }
        else if (ch == '(') {
            stack[++top] = ch;
        }
        else if (ch == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[k++] = stack[top--];
            top--;  // Pop '(' from the stack
        }
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            while (top != -1 && precedence(stack[top]) >= precedence(ch))
                postfix[k++] = stack[top--];
            stack[++top] = ch;  // Push the current operator to the stack
        }
    }

    // Pop all remaining operators from the stack
    while (top != -1)
        postfix[k++] = stack[top--];

    postfix[k] = '\0';  // Null-terminate the postfix expression
}

// Function prototypes for push and pop
void push(char stack[100][10], int* top, char* value);
char* pop(char stack[100][10], int* top);

int main() {
    char statement[100];
    printf("Enter a statement (e.g., c = d * e + f - g): ");
    fgets(statement, sizeof(statement), stdin);
    statement[strcspn(statement, "\n")] = 0;  // Remove newline character

    // Parse LHS
    char lhs;
    int i = 0;

    while (statement[i] == ' ') i++;
    lhs = statement[i++];

    // Skip to '='
    while (statement[i] != '=' && statement[i] != '\0') i++;
    if (statement[i] == '=') i++;

    // Skip spaces after '='
    while (statement[i] == ' ') i++;

    // Extract infix expression and convert it to postfix
    char infix[100], postfix[100];
    int j = 0;
    while (statement[i] != '\0') {
        if (statement[i] != ' ' && statement[i] != '=') {
            infix[j++] = statement[i];
        }
        i++;
    }
    infix[j] = '\0';

    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    // Process the postfix expression and generate assembly code
    printf("\nGenerated Assembly:\n");

    char tempVar[10];
    int tempCount = 1;
    char stack[100][10];
    int top = -1;

    for (int i = 0; postfix[i] != '\0'; i++) {
        char ch = postfix[i];

        if (isalnum(ch)) {
            char* addr = getAddress(ch);
            push(stack, &top, addr);
            printf("MOV EAX, [%s]        ; Load %c\n", addr, ch);
        }
        else {
            char* op2 = pop(stack, &top);
            char* op1 = pop(stack, &top);

            sprintf(tempVar, "t%d", tempCount++);

            switch (ch) {
                case '+':
                    printf("ADD EAX, [%s]        ; result + operand\n", op2);
                    break;
                case '-':
                    printf("SUB EAX, [%s]        ; result - operand\n", op2);
                    break;
                case '*':
                    printf("MUL EAX, [%s]        ; result * operand\n", op2);
                    break;
                case '/':
                    printf("DIV EAX, [%s]        ; result / operand\n", op2);
                    break;
                default:
                    printf("Unsupported operator: %c\n", ch);
                    return 1;
            }

            printf("MOV [%s], EAX        ; Store result in temporary variable\n", tempVar);
            push(stack, &top, tempVar);  // Push the result back to stack
        }
    }

    char* lhsAddr = getAddress(lhs);
    printf("MOV [%s], EAX        ; Store result in %c\n", lhsAddr, lhs);

    return 0;
}

// Push function for stack
void push(char stack[100][10], int* top, char* value) {
    strcpy(stack[++(*top)], value);
}

// Pop function for stack
char* pop(char stack[100][10], int* top) {
    return stack[(*top)--];
}
