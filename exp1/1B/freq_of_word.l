
%{
    #include <string.h>
    int count = 0;
    char word[100];
%}
%option noyywrap
%%
[a-zA-Z0-9]+ {
    if(strcmp(yytext, word) == 0)
        count++;
}
%%

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <word>\n", argv[0]);
        return 1;
    }
    
    strcpy(word, argv[1]);
    yylex();
    printf("Frequency of word '%s': %d\n", word, count);
    return 0;
}
