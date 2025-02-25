
%{
    int lineNum = 1;
%}

%%
^.*$ { printf("%4d: %s\n", lineNum++, yytext); }
%%

int main() {
    yylex();
    return 0;
}