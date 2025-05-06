%{
/* Dependencies */
#include <stdio.h>
#include "compiler.h"
#include "calc.tab.h"

extern FILE *yyout;
extern char *yytext;
extern int yylineno;
extern int yylex(void);
extern void yyerror(const char *s);
extern format_mode mode;

%}

%code requires {
  #include "compiler.h"
}

%union {
  value_info literal;
  identifier_t identifier;
  op_type operator;
  void* no_type;
}

%token <literal> INTEGER_LITERAL FLOAT_LITERAL STRING_LITERAL BOOLEAN_LITERAL
%token <operator> PLUS_OP MINUS_OP TIMES_OP DIVIDE_OP MOD_OP POW_OP
%token <operator> EQUALS_OP GREATER_THAN_OP GREATER_EQUALS_OP LOWER_THAN_OP LOWER_EQUALS_OP NOT_EQUALS_OP
%token <operator> NOT_OP OR_OP AND_OP
%token <identifier> IDENTIFIER
%token <no_type> EOL LPAREN RPAREN ASSIGN

%type <literal> statement 
%type <literal> arith_expr arith_plus_minus arith_mod_times_div arith_pow arith_literal 
%type <literal> bool_expr bool_expr_or bool_expr_and bool_expr_literal
%type <literal> assignment

%define parse.error verbose

%start program

%%

program: statement_list;

statement_list:
  %empty
| statement_list statement
;

statement:
  EOL
| assignment EOL
| arith_expr EOL { cprint(yyout, "%v\n", &$1); } 
| bool_expr EOL { cprint(yyout, "%v\n", &$1); }
;

assignment:
  IDENTIFIER ASSIGN arith_plus_minus { $$ = assign($1, $3); }
| IDENTIFIER ASSIGN bool_expr_or { $$ = assign($1, $3); }

arith_expr: arith_plus_minus { $$ = $1; };

 /* Precedence Level 1: '+' AND '-' */
arith_plus_minus:
  arith_plus_minus PLUS_OP arith_mod_times_div { $$ = arithmetic(&$1, $2, &$3); }
| arith_plus_minus MINUS_OP arith_mod_times_div { $$ = arithmetic(&$1, $2, &$3); }
| arith_mod_times_div 
;

 /* Precedence Level 2: '%', '*' and '/' */
arith_mod_times_div:
  arith_mod_times_div MOD_OP arith_pow { $$ = arithmetic(&$1, $2, &$3); }
| arith_mod_times_div TIMES_OP arith_pow { $$ = arithmetic(&$1, $2, &$3); }
| arith_mod_times_div DIVIDE_OP arith_pow { $$ = arithmetic(&$1, $2, &$3); }
| arith_pow 
;

 /* Precedence Level 3: '**' */
arith_pow:
  arith_pow POW_OP arith_literal { $$ = arithmetic(&$1, $2, &$3); }
| arith_literal
;

 /* Precedence Level 4: FLOAT INTEGER STRING */
arith_literal:
  FLOAT_LITERAL { $$ = $1; }
| INTEGER_LITERAL { $$ = $1; }
| STRING_LITERAL { $$ = $1; }
| IDENTIFIER { $$ = identifier_value($1); }
| LPAREN arith_plus_minus RPAREN { $$ = $2; }
;

bool_expr: bool_expr_or { $$ = $1; };

 /* Precedence Level 1: 'or' */
bool_expr_or: 
  bool_expr_or OR_OP bool_expr_and { $$ = boolean_logic($1, $2, $3); }
| bool_expr_and 
;

 /* Precedence Level 2: 'and' */
bool_expr_and:
  bool_expr_and AND_OP bool_expr_literal { $$ = boolean_logic($1, $2, $3); }
| NOT_OP bool_expr_literal { $$ = boolean_logic_unary($1, $2); }
| bool_expr_literal { $$ = $1; }
;

 /* Precedence Level 3: BOOLEAN and Boolean Arithmetic Operations */
bool_expr_literal:
  BOOLEAN_LITERAL
| LPAREN bool_expr_or RPAREN { $$ = $2; }
| arith_plus_minus EQUALS_OP arith_plus_minus { $$ = boolean_logic($1, $2, $3); }
| arith_plus_minus GREATER_THAN_OP arith_plus_minus { $$ = boolean_logic($1, $2, $3); }
| arith_plus_minus GREATER_EQUALS_OP arith_plus_minus { $$ = boolean_logic($1, $2, $3); }
| arith_plus_minus LOWER_THAN_OP arith_plus_minus { $$ = boolean_logic($1, $2, $3); }
| arith_plus_minus LOWER_EQUALS_OP arith_plus_minus { $$ = boolean_logic($1, $2, $3); }
| arith_plus_minus NOT_EQUALS_OP arith_plus_minus { $$ = boolean_logic($1, $2, $3); }
;

%%

int main(int argc, char** argv) {
  init_log("debug.log");
  mode = DEC;
  yyparse();
  close_log();
  return 0;
}


