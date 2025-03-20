#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTIONS 10
#define MAX_ITEMS 100
#define MAX_STATES 50

typedef struct {
    char lhs;
    char rhs[10];
} Production;

typedef struct {
    char lhs;
    char rhs[10];
    int dotPosition;
} Item;

typedef struct {
    Item items[MAX_ITEMS];
    int itemCount;
} State;

Production productions[MAX_PRODUCTIONS];
State states[MAX_STATES];
int numProductions = 0, numStates = 0;

// Add item to a state if not already present
void addItem(State *state, char lhs, char *rhs, int dotPos) {
    for (int i = 0; i < state->itemCount; i++) {
        if (state->items[i].lhs == lhs &&
            strcmp(state->items[i].rhs, rhs) == 0 &&
            state->items[i].dotPosition == dotPos) {
            return;
        }
    }
    state->items[state->itemCount].lhs = lhs;
    strcpy(state->items[state->itemCount].rhs, rhs);
    state->items[state->itemCount].dotPosition = dotPos;
    state->itemCount++;
}

// Compute closure of a state
void closure(State *state) {
    int added = 1;
    while (added) {
        added = 0;
        for (int i = 0; i < state->itemCount; i++) {
            Item current = state->items[i];
            if (current.dotPosition < strlen(current.rhs)) {
                char nextSymbol = current.rhs[current.dotPosition];
                for (int j = 0; j < numProductions; j++) {
                    if (productions[j].lhs == nextSymbol) {
                        int exists = 0;
                        for (int k = 0; k < state->itemCount; k++) {
                            if (state->items[k].lhs == nextSymbol &&
                                strcmp(state->items[k].rhs, productions[j].rhs) == 0 &&
                                state->items[k].dotPosition == 0) {
                                exists = 1;
                                break;
                            }
                        }
                        if (!exists) {
                            addItem(state, productions[j].lhs, productions[j].rhs, 0);
                            added = 1;
                        }
                    }
                }
            }
        }
    }
}

// Compute GOTO function
int goTo(int stateIndex, char symbol) {
    State newState = {0};

    for (int i = 0; i < states[stateIndex].itemCount; i++) {
        Item current = states[stateIndex].items[i];
        if (current.dotPosition < strlen(current.rhs) && current.rhs[current.dotPosition] == symbol) {
            addItem(&newState, current.lhs, current.rhs, current.dotPosition + 1);
        }
    }
    
    closure(&newState);

    // Check if the state already exists
    for (int i = 0; i < numStates; i++) {
        if (newState.itemCount == states[i].itemCount) {
            int same = 1;
            for (int j = 0; j < newState.itemCount; j++) {
                if (newState.items[j].lhs != states[i].items[j].lhs ||
                    strcmp(newState.items[j].rhs, states[i].items[j].rhs) != 0 ||
                    newState.items[j].dotPosition != states[i].items[j].dotPosition) {
                    same = 0;
                    break;
                }
            }
            if (same) return i;
        }
    }

    // Add the new state if it doesn't exist
    states[numStates] = newState;
    return numStates++;
}

// Print items in a state
void printState(int stateIndex) {
    printf("State %d:\n", stateIndex);
    for (int i = 0; i < states[stateIndex].itemCount; i++) {
        Item item = states[stateIndex].items[i];
        printf("%c -> ", item.lhs);
        for (int j = 0; j < strlen(item.rhs); j++) {
            if (j == item.dotPosition) printf(".");
            printf("%c", item.rhs[j]);
        }
        if (item.dotPosition == strlen(item.rhs)) printf(".");
        printf("\n");
    }
    printf("\n");
}

// Construct the LR(0) automaton
void constructLR0Automaton() {
    // Initial augmented production S' -> S
    addItem(&states[numStates], 'Z', "S", 0);  // Augmented production (Z -> S)
    closure(&states[numStates]);
    numStates++;

    // Build all states using GOTO
    int i = 0;
    while (i < numStates) {
        for (int j = 0; j < states[i].itemCount; j++) {
            Item item = states[i].items[j];
            if (item.dotPosition < strlen(item.rhs)) {
                char symbol = item.rhs[item.dotPosition];
                int nextState = goTo(i, symbol);
            }
        }
        i++;
    }
}

// Print LR(0) automaton
void printLR0Automaton() {
    printf("LR(0) Automaton:\n\n");
    for (int i = 0; i < numStates; i++) {
        printState(i);
    }
}

int main() {
    // Input number of productions
    printf("Enter number of productions: ");
    scanf("%d", &numProductions);

    // Input productions
    printf("Enter productions (format: A->BC):\n");
    for (int i = 0; i < numProductions; i++) {
        char input[20];
        scanf("%s", input);
        productions[i].lhs = input[0];
        strcpy(productions[i].rhs, input + 3);
    }

    // Construct LR(0) Automaton
    constructLR0Automaton();

    // Print LR(0) Automaton
    printLR0Automaton();

    return 0;
}