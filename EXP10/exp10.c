#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    char op;
    char arg1[10];
    char arg2[10];
    char result[10];
} Quadruple;

typedef struct {
    char op;
    char arg1[10];
    char arg2[10];
} Triple;

Quadruple quad[MAX];
Triple triple[MAX];
int tripleOrder[MAX];

int tempCount = 1;
int qIndex = 0;

// Stack to hold temporary values or operands
char stack[MAX][10];
int top = -1;

void push(char* str) {
    strcpy(stack[++top], str);
}

char* pop() {
    return stack[top--];
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Infix to Postfix conversion
void infixToPostfix(const char* infix, char* postfix) {
    char s[MAX];
    int top = -1, j = 0;
    for (int i = 0; infix[i]; i++) {
        char ch = infix[i];
        if (isalnum(ch)) {
            postfix[j++] = ch;
        } else if (ch == '(') {
            s[++top] = ch;
        } else if (ch == ')') {
            while (top != -1 && s[top] != '(')
                postfix[j++] = s[top--];
            top--;
        } else {
            while (top != -1 && precedence(s[top]) >= precedence(ch))
                postfix[j++] = s[top--];
            s[++top] = ch;
        }
    }
    while (top != -1)
        postfix[j++] = s[top--];
    postfix[j] = '\0';
}

// Generate intermediate code from postfix expression
void generateIntermediateCode(const char* postfix) {
    for (int i = 0; postfix[i]; i++) {
        char ch = postfix[i];
        if (isalnum(ch)) {
            char operand[2] = {ch, '\0'};
            push(operand);
        } else if (isOperator(ch)) {
            char* op2 = pop();
            char* op1 = pop();

            char temp[10];
            sprintf(temp, "t%d", tempCount++);

            // Fill Quadruple
            quad[qIndex].op = ch;
            strcpy(quad[qIndex].arg1, op1);
            strcpy(quad[qIndex].arg2, op2);
            strcpy(quad[qIndex].result, temp);

            // Fill Triple
            triple[qIndex].op = ch;
            strcpy(triple[qIndex].arg1, op1);
            strcpy(triple[qIndex].arg2, op2);
            tripleOrder[qIndex] = qIndex;

            push(temp);
            qIndex++;
        }
    }
}

// Print outputs
void printQuadruples() {
    printf("\nQUADRUPLES:\n%-5s %-5s %-5s %-7s\n", "Op", "Arg1", "Arg2", "Result");
    for (int i = 0; i < qIndex; i++) {
        printf("%-5c %-5s %-5s %-7s\n", quad[i].op, quad[i].arg1, quad[i].arg2, quad[i].result);
    }
}

void printTriples() {
    printf("\nTRIPLES:\n%-5s %-5s %-5s %-5s\n", "Idx", "Op", "Arg1", "Arg2");
    for (int i = 0; i < qIndex; i++) {
        printf("%-5d %-5c %-5s %-5s\n", i, triple[i].op, triple[i].arg1, triple[i].arg2);
    }
}

void printIndirectTriples() {
    printf("\nINDIRECT TRIPLES:\n%-5s %-5s %-5s %-5s\n", "Ptr", "Op", "Arg1", "Arg2");
    for (int i = 0; i < qIndex; i++) {
        int idx = tripleOrder[i];
        printf("%-5d %-5c %-5s %-5s\n", i, triple[idx].op, triple[idx].arg1, triple[idx].arg2);
    }
}

// Main
int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    generateIntermediateCode(postfix);

    printQuadruples();
    printTriples();
    printIndirectTriples();

    return 0;
}