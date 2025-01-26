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
  op_type operator;
}

%token <literal> NUMBER_LITERAL STRING_LITERAL BOOLEAN_LITERAL
%token <operator> AUOP ABOP BUOP BBOP

%type <literal> statement arith_expr bool_expr 

%start program

%%

program: %empty | statement_list ;

statement_list: 
  statement
  | statement_list statement
  ;

statement:
  arith_expr { cprint(yyout, "%v\n", &$1);} 
  | bool_expr { cprint(yyout, "%v\n", &$1); }
  ;

arith_expr:
  NUMBER_LITERAL { $$ = $1; }
  | STRING_LITERAL { $$ = $1; }
  | arith_expr ABOP arith_expr { $$ = arithmetic($1, $2, $3); }
  ;

bool_expr:
  BOOLEAN_LITERAL
  | arith_expr BBOP arith_expr { $$ = boolean_logic($1, $2, $3); }
  ;

%%

int main(int argc, char** argv) {
  yyparse();
}

void yyerror(const char *s) {
  fprintf(stderr, "%s\n", s);
}

