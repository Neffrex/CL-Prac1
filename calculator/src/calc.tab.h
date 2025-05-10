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
#line 16 "calc.y"

  #include "compiler.h"

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
    SIN = 262,                     /* SIN  */
    COS = 263,                     /* COS  */
    TAN = 264,                     /* TAN  */
    TRUE = 265,                    /* TRUE  */
    FALSE = 266,                   /* FALSE  */
    PI = 267,                      /* PI  */
    E = 268,                       /* E  */
    INTEGER = 269,                 /* INTEGER  */
    FLOAT = 270,                   /* FLOAT  */
    STRING = 271,                  /* STRING  */
    PLUS = 272,                    /* PLUS  */
    MINUS = 273,                   /* MINUS  */
    TIMES = 274,                   /* TIMES  */
    DIVIDE = 275,                  /* DIVIDE  */
    MOD = 276,                     /* MOD  */
    POW = 277,                     /* POW  */
    EQUALS = 278,                  /* EQUALS  */
    GREATER_THAN = 279,            /* GREATER_THAN  */
    GREATER_EQUALS = 280,          /* GREATER_EQUALS  */
    LOWER_THAN = 281,              /* LOWER_THAN  */
    LOWER_EQUALS = 282,            /* LOWER_EQUALS  */
    NOT_EQUALS = 283,              /* NOT_EQUALS  */
    NOT = 284,                     /* NOT  */
    OR = 285,                      /* OR  */
    AND = 286,                     /* AND  */
    IDENTIFIER = 287               /* IDENTIFIER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 20 "calc.y"

  bool boolean;
  literal literal;
  identifier identifier;
  op_type operator;
  void* no_type;

#line 110 "calc.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_CALC_TAB_H_INCLUDED  */
