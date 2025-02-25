
%{
    int charCount = 0;
%}

%%
. { charCount++; }
\n { charCount++; }
%%

int main() {
    yylex();
    printf("Total number of characters: %d\n", charCount);
    return 0;
}