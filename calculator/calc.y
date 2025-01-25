%{
/* Dependencies */
#include <stdio.h>
#include "compiler.h"

extern FILE *yyout;
extern int yylineno;
extern int yylex(void);
extern void yyerror(const char *s);

%}

%code requires {
  #include "compiler.h"
}

%union {
  value_info literal;
  operator_t operator;
}

%token <literal> NUMBER
%token <operator> BINARY_OPERATOR UNARY_OPERATOR

%type <literal> statement

%start program

%%

program: %empty | statement_list ;

statement_list: 
  statement
  | statement_list statement
  ;

statement:
  NUMBER { 
    cprint(yyout, "%v\n", &$1);
  } | NUMBER BINARY_OPERATOR NUMBER {
    $$ = arithmetic($1, $2, $3);
    cprint(yyout, "%v\n", &$$);
  }

%%

int main(int argc, char** argv) {
  yyparse();
}

void yyerror(const char *s) {
  fprintf(stderr, "%s\n", s);
}

