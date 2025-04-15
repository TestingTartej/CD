#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Simulated symbol table
struct Symbol {
    char name;
    char address[10];
} table[] = {
    {'a', "0x100"}, {'b', "0x104"}, {'c', "0x108"},
    {'d', "0x10C"}, {'e', "0x110"}, {'f', "0x114"},
    {'g', "0x118"}, {'h', "0x11C"}, {'i', "0x120"}
};

char* getAddress(char var) {
    for (int i = 0; i < sizeof(table) / sizeof(table[0]); i++) {
        if (table[i].name == var)
            return table[i].address;
    }
    return "Unknown";
}

int main() {
    char statement[100];
    printf("Enter a statement (e.g., c = d * e + f - g): ");
    fgets(statement, sizeof(statement), stdin);
    statement[strcspn(statement, "\n")] = 0;

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

    // Get first operand
    char curr_var = statement[i++];
    char *curr_addr = getAddress(curr_var);

    printf("\nGenerated Assembly:\n");
    printf("MOV EAX, [%s]      ; Load %c\n", curr_addr, curr_var);

    // Handle the rest
    while (statement[i] != '\0') {
        while (statement[i] == ' ') i++;
        char op = statement[i++];

        while (statement[i] == ' ') i++;
        if (!isalpha(statement[i])) break;

        char next_var = statement[i++];
        char *next_addr = getAddress(next_var);

        switch (op) {
            case '+':
                printf("ADD EAX, [%s]      ; result + %c\n", next_addr, next_var);
                break;
            case '-':
                printf("SUB EAX, [%s]      ; result - %c\n", next_addr, next_var);
                break;
            case '*':
                printf("MUL EAX, [%s]      ; result * %c\n", next_addr, next_var);
                break;
            default:
                printf("Unsupported operator: %c\n", op);
                return 1;
        }
    }

    char *lhs_addr = getAddress(lhs);
    printf("MOV [%s], EAX      ; Store result in %c\n", lhs_addr, lhs);

    return 0;
}
