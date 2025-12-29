/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

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

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_CALC_TAB_H_INCLUDED
# define YY_YY_CALC_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif
/* "%code requires" blocks.  */
#line 16 "src/parser/calc.y"

  #include "../ast/headers/compiler.h"

#line 53 "calc.tab.h"

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    EOL = 258,                     /* EOL  */
    LPAREN = 259,                  /* LPAREN  */
    RPAREN = 260,                  /* RPAREN  */
    LBRACKET = 261,                /* LBRACKET  */
    RBRACKET = 262,                /* RBRACKET  */
    ASSIGN = 263,                  /* ASSIGN  */
    COMMA = 264,                   /* COMMA  */
    TRUE = 265,                    /* TRUE  */
    FALSE = 266,                   /* FALSE  */
    SIN = 267,                     /* SIN  */
    COS = 268,                     /* COS  */
    TAN = 269,                     /* TAN  */
    LEN = 270,                     /* LEN  */
    SUBSTR = 271,                  /* SUBSTR  */
    STRUCT = 272,                  /* STRUCT  */
    TYPE_INTEGER = 273,            /* TYPE_INTEGER  */
    TYPE_FLOAT = 274,              /* TYPE_FLOAT  */
    TYPE_STRING = 275,             /* TYPE_STRING  */
    INTEGER = 276,                 /* INTEGER  */
    FLOAT = 277,                   /* FLOAT  */
    STRING = 278,                  /* STRING  */
    CONSTANT = 279,                /* CONSTANT  */
    PLUS = 280,                    /* PLUS  */
    MINUS = 281,                   /* MINUS  */
    TIMES = 282,                   /* TIMES  */
    DIVIDE = 283,                  /* DIVIDE  */
    MOD = 284,                     /* MOD  */
    POW = 285,                     /* POW  */
    EQUALS = 286,                  /* EQUALS  */
    GREATER_THAN = 287,            /* GREATER_THAN  */
    GREATER_EQUALS = 288,          /* GREATER_EQUALS  */
    LOWER_THAN = 289,              /* LOWER_THAN  */
    LOWER_EQUALS = 290,            /* LOWER_EQUALS  */
    NOT_EQUALS = 291,              /* NOT_EQUALS  */
    NOT = 292,                     /* NOT  */
    OR = 293,                      /* OR  */
    AND = 294,                     /* AND  */
    UNDEFINED_IDENTIFIER = 295,    /* UNDEFINED_IDENTIFIER  */
    BOOLEAN_IDENTIFIER = 296,      /* BOOLEAN_IDENTIFIER  */
    ARITHMETIC_IDENTIFIER = 297    /* ARITHMETIC_IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "src/parser/calc.y"

  bool boolean;
  literal literal;
  identifier identifier;
  op_type operator;
  void* no_type;

#line 120 "calc.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_CALC_TAB_H_INCLUDED  */
