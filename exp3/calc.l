%{
#include <stdlib.h>
#include <stdio.h>
#include "calc.tab.c"
extern YYSTYPE yylval;
void yyerror(char*);
%}

%%
"+" {

	return OP_ADD;
}
"-" {

	return OP_SUB;
}
"*" {

	return OP_MUL;
}
"/" {

	return OP_DIV;
}
"^" {

	return OP_POW;
}
"=" {

	return OP_EQL;
}
"(" {

	return SYM_PRNL;
}
")" {

	return SYM_PRNR;
}
"sin"|"SIN" {

	return FUNC_SIN;
}
"cos"|"COS" {

	return FUNC_COS;
}
"sqrt"|"SQRT" {

	return FUNC_SQRT;
}
"exp"|"EXP" {

    return FUNC_EXP;
}
"cosh"|"COSH" {

    return FUNC_COSH;
}
"sinh"|"SINH" {

    return FUNC_SINH;
}
"abs"|"fabs"|"ABS"|"FABS" {

	return FUNC_ABS;
}


[0-9]+ {

	sscanf(yytext, "%lf", &yylval);
	return T_INT;
}
[0-9]+(\.?[0-9]*e?-?[0-9]*)?  {
	sscanf(yytext, "%lf", &yylval);

	return T_FLOAT;
}
[a-zA-Z]([a-zA-Z]|[0-9])* {


return T_IDEN;
}
\n {
	return EOL;
}
[ \t]+ {}
"quit"|"exit" {
	return CMD_EXT;
}
. {
	yyerror("ERROR: Unrecognized input!");
}

%%

int yywrap()
{
	return 1;
}
