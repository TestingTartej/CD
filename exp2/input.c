#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char in[100];
    printf("Enter an arithmetic expression (Ctrl+D to exit):\n");
    while (fgets(in, 100, stdin)) {
        if (in[strlen(in) - 1] == '\n') in[strlen(in) - 1] = '\0';
        if (strlen(in) == 0) break;
        printf("You entered: %s\n", in);
    }
    return 0;
}