
%{
    int lineNum = 1;
%}
%option noyywrap
%%
^.*$ { printf("%4d: %s\n", lineNum++, yytext); }
%%

int main() {
    yylex();
    return 0;
}
