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
    ASSIGN = 261,                  /* ASSIGN  */
    COMMA = 262,                   /* COMMA  */
    TRUE = 263,                    /* TRUE  */
    FALSE = 264,                   /* FALSE  */
    SIN = 265,                     /* SIN  */
    COS = 266,                     /* COS  */
    TAN = 267,                     /* TAN  */
    LEN = 268,                     /* LEN  */
    SUBSTR = 269,                  /* SUBSTR  */
    INTEGER = 270,                 /* INTEGER  */
    FLOAT = 271,                   /* FLOAT  */
    STRING = 272,                  /* STRING  */
    CONSTANT = 273,                /* CONSTANT  */
    PLUS = 274,                    /* PLUS  */
    MINUS = 275,                   /* MINUS  */
    TIMES = 276,                   /* TIMES  */
    DIVIDE = 277,                  /* DIVIDE  */
    MOD = 278,                     /* MOD  */
    POW = 279,                     /* POW  */
    EQUALS = 280,                  /* EQUALS  */
    GREATER_THAN = 281,            /* GREATER_THAN  */
    GREATER_EQUALS = 282,          /* GREATER_EQUALS  */
    LOWER_THAN = 283,              /* LOWER_THAN  */
    LOWER_EQUALS = 284,            /* LOWER_EQUALS  */
    NOT_EQUALS = 285,              /* NOT_EQUALS  */
    NOT = 286,                     /* NOT  */
    OR = 287,                      /* OR  */
    AND = 288,                     /* AND  */
    UNDEFINED_IDENTIFIER = 289,    /* UNDEFINED_IDENTIFIER  */
    BOOLEAN_IDENTIFIER = 290,      /* BOOLEAN_IDENTIFIER  */
    ARITHMETIC_IDENTIFIER = 291    /* ARITHMETIC_IDENTIFIER  */
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

#line 114 "calc.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_CALC_TAB_H_INCLUDED  */
