
%{
    int wordCount = 0;
%}
%option noyywrap
%%
[a-zA-Z0-9]+ { wordCount++; }
%%

int main() {
    yylex();
    printf("Total number of words: %d\n", wordCount);
    return 0;
}
