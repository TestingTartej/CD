
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 10

typedef struct {
    char nonTerminal;
    char productions[MAX][MAX];
    int productionCount;
} Grammar;

char leading[MAX][MAX], trailing[MAX][MAX];
int leadingCount[MAX], trailingCount[MAX];
int n;
Grammar grammar[MAX];

void addToSet(char set[MAX][MAX], int *count, char nonTerminal, char symbol) {
    int i, index = nonTerminal - 'A';
    for (i = 0; i < count[index]; i++) {
        if (set[index][i] == symbol)
            return;
    }
    set[index][count[index]++] = symbol;
}

void computeLeading() {
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < n; i++) {
            char A = grammar[i].nonTerminal;
            int indexA = A - 'A';
            for (int j = 0; j < grammar[i].productionCount; j++) {
                char *prod = grammar[i].productions[j];
                if (isalpha(prod[0]) && isupper(prod[0])) {
                    int indexB = prod[0] - 'A';
                    for (int k = 0; k < leadingCount[indexB]; k++) {
                        if (!strchr(leading[indexA], leading[indexB][k])) {
                            addToSet(leading, leadingCount, A, leading[indexB][k]);
                            changed = 1;
                        }
                    }
                } else {
                    if (!strchr(leading[indexA], prod[0])) {
                        addToSet(leading, leadingCount, A, prod[0]);
                        changed = 1;
                    }
                }
            }
        }
    } while (changed);
}

void computeTrailing() {
    int changed;
    do {
        changed = 0;
        for (int i = 0; i < n; i++) {
            char A = grammar[i].nonTerminal;
            int indexA = A - 'A';
            for (int j = 0; j < grammar[i].productionCount; j++) {
                char *prod = grammar[i].productions[j];
                int len = strlen(prod);
                if (isalpha(prod[len - 1]) && isupper(prod[len - 1])) {
                    int indexB = prod[len - 1] - 'A';
                    for (int k = 0; k < trailingCount[indexB]; k++) {
                        if (!strchr(trailing[indexA], trailing[indexB][k])) {
                            addToSet(trailing, trailingCount, A, trailing[indexB][k]);
                            changed = 1;
                        }
                    }
                } else {
                    if (!strchr(trailing[indexA], prod[len - 1])) {
                        addToSet(trailing, trailingCount, A, prod[len - 1]);
                        changed = 1;
                    }
                }
            }
        }
    } while (changed);
}

void displaySet(char set[MAX][MAX], int count[MAX], const char *setName) {
    for (int i = 0; i < n; i++) {
        printf("%s(%c) = { ", setName, grammar[i].nonTerminal);
        for (int j = 0; j < count[grammar[i].nonTerminal - 'A']; j++) {
            printf("%c ", set[grammar[i].nonTerminal - 'A'][j]);
        }
        printf("}\n");
    }
}

int main() {
    printf("Enter number of productions: ");
    scanf("%d", &n);
    getchar();
    
    for (int i = 0; i < n; i++) {
        printf("Enter production for non-terminal (Format: A=alpha|beta): ");
        char input[MAX];
        fgets(input, MAX, stdin);
        input[strcspn(input, "\n")] = 0;
        grammar[i].nonTerminal = input[0];
        char *token = strtok(input + 2, "|");
        grammar[i].productionCount = 0;
        while (token) {
            strcpy(grammar[i].productions[grammar[i].productionCount++], token);
            token = strtok(NULL, "|");
        }
    }
    
    memset(leadingCount, 0, sizeof(leadingCount));
    memset(trailingCount, 0, sizeof(trailingCount));
    
    computeLeading();
    computeTrailing();
    
    printf("\nLeading Sets:\n");
    displaySet(leading, leadingCount, "LEADING");
    
    printf("\nTrailing Sets:\n");
    displaySet(trailing, trailingCount, "TRAILING");
    
    return 0;
}

