/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     T_FLOAT = 258,
     T_INT = 259,
     OP_EQL = 260,
     EOL = 261,
     SYM_PRNL = 262,
     SYM_PRNR = 263,
     SYM_COMMA = 264,
     FUNC_L = 265,
     FUNC_R = 266,
     FUNC_ABS = 267,
     FUNC_SIN = 268,
     FUNC_COS = 269,
     FUNC_SQRT = 270,
     FUNC_EXP = 271,
     FUNC_COSH = 272,
     FUNC_SINH = 273,
     CMD_EXT = 274,
     T_IDEN = 275,
     OP_SUB = 276,
     OP_ADD = 277,
     OP_DIV = 278,
     OP_MUL = 279,
     OP_POW = 280
   };
#endif
/* Tokens.  */
#define T_FLOAT 258
#define T_INT 259
#define OP_EQL 260
#define EOL 261
#define SYM_PRNL 262
#define SYM_PRNR 263
#define SYM_COMMA 264
#define FUNC_L 265
#define FUNC_R 266
#define FUNC_ABS 267
#define FUNC_SIN 268
#define FUNC_COS 269
#define FUNC_SQRT 270
#define FUNC_EXP 271
#define FUNC_COSH 272
#define FUNC_SINH 273
#define CMD_EXT 274
#define T_IDEN 275
#define OP_SUB 276
#define OP_ADD 277
#define OP_DIV 278
#define OP_MUL 279
#define OP_POW 280




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

