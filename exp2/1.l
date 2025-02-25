%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%%
"int"               { printf("Keyword: int\n"); }
"unsigned"          { printf("Keyword: unsigned\n"); }
"long"              { printf("Keyword: long\n"); }
"if"                { printf("Keyword: if\n"); }
"else"              { printf("Keyword: else\n"); }
"for"               { printf("Keyword: for\n"); }
"return"            { printf("Keyword: return\n"); }
"printf"            { printf("Keyword: printf\n"); }
"scanf"             { printf("Keyword: scanf\n"); }
"#"                 { printf("Preprocessor: #\n"); }
"include"           { printf("Keyword: include\n"); }

[0-9]+              { printf("Integer: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("Identifier: %s\n", yytext); }
\"[^\"]*\"          { printf("String: %s\n", yytext); }

"="                 { printf("Assignment Operator: =\n"); }
"<"                 { printf("Relational Operator: <\n"); }
"*"                 { printf("Operator: *\n"); }
"+="                { printf("Compound Assignment Operator: +=\n"); }
"++"                { printf("Increment Operator: ++\n"); }
"%"                 { printf("Format Specifier: %%\n"); }
"&"                 { printf("Address Operator: &\n"); }
">"                 { printf("Relational Operator: >\n"); }

"("                 { printf("Special Symbol: (\n"); }
")"                 { printf("Special Symbol: )\n"); }
"{"                 { printf("Special Symbol: {\n"); }
"}"                 { printf("Special Symbol: }\n"); }
";"                 { printf("Special Symbol: ;\n"); }
","                 { printf("Special Symbol: ,\n"); }

[ \t\n]             { /* Ignore whitespace */ }

.                   { printf("Unrecognized character: %s\n", yytext); }
%%

int main(int argc, char *argv[]) {
    FILE *fp;
    if (argc > 1) {
        fp = fopen(argv[1], "r");
        if (!fp) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }
        yyin = fp;
    } else {
        printf("Enter the filename: ");
        char filename[100];
        scanf("%s", filename);
        fp = fopen(filename, "r");
        if (!fp) {
            perror("Error opening file");
            return EXIT_FAILURE;
        }
        yyin = fp;
    }

    printf("Starting lexical analysis...\n");
    yylex();  
    printf("Lexical analysis completed.\n");

    fclose(fp);
    return 0;
}

int yywrap() {
    return 1;
}
