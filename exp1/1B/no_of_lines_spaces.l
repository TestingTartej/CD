
%{
    int lineCount = 0;
    int spaceCount = 0;
    int tabCount = 0;
%}

%%
\n      { lineCount++; }
" "     { spaceCount++; }
\t      { tabCount++; }
.       { }
%%

int main() {
    yylex();
    printf("Number of lines: %d\n", lineCount);
    printf("Number of spaces: %d\n", spaceCount);
    printf("Number of tabs: %d\n", tabCount);
    return 0;
}