%{
    #include <stdio.h>
    #include <string.h>

    int count = 0;
    char *word;
%}

%option noyywrap

%%

[a-zA-Z0-9]+ {
    if(strcmp(yytext, word) == 0)
        count++;
}

\n  ;
.    ;

%%

int main(int argc, char *argv[]) {
    if(argc != 3) {
        printf("Usage: %s <word> <filename>\n", argv[0]);
        return 1;
    }

    word = argv[1];
    FILE *file = fopen(argv[2], "r");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    yyin = file;
    yylex();
    fclose(file);

    printf("Frequency of word '%s': %d\n", word, count);
    return 0;
}
