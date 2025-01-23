%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "symtab.h"

void yyerror(const char *s);
int yylex(void);

%}

%union {
	sym_value_type symbol;
	var_type literal;
  void* no_type;
}

%token <var_type> INTEGER FLOAT STRING BOOLEAN UNDEFINED
%token <sym_value_type> IDENTIFIER
%token <no_type> SIN COS TAN
%token ASSIGN PLUS MINUS TIMES DIVIDE MOD POW
%token GT GE LT LE EQ NEQ NOT AND OR
%token LEN SUBSTR EOL

%type <>

%%

program:
    statement_list ;

statement_list:
		statement_list statement | statement ;

statement:
		assignation | expression;

assignation:
	IDENTIFIER ASSIGN expression EOL {
		if($3.type != UNDEFINED) {
			sym_enter($1.name, &$3);
		}
	}

expression:
		expression EOL
		| arithmetic
		| logic
    ;

arithmetic:
		arithmetic PLUS arithmetic			{ $$ = add($1, $3)      }
		| arithmetic MINUS arithmetic		{ $$ = subtract($1, $3) }
		| arithmetic TIMES arithmetic		{ $$ = multiply($1, $3) }
		| arithmetic DIVIDE arithmetic	{ $$ = divide($1, $3)   }
		| arithmetic MOD arithmetic			{ $$ = mod($1, $3)      }
		| arithmetic POW arithmetic			{ $$ = pow($1, $3)      }
		| number
		| IDENTIFIER
		;

logic:
		logic GT logic
		| logic GE logic  { $$ = $1 >= $3 }
		| logic LT logic  { $$ = $1 <  $3 }
		| logic LE logic  { $$ = $1 <= $3 }
		| logic EQ logic  { $$ = $1 == $3 }
		| logic NEQ logic { $$ = $1 != $3 }
		| logic AND logic { $$ = $1 && $3 }
		| logic OR logic  { $$ = $1 || $3 }
		| NOT logic       { $$ = !$1 }
		| BOOLEAN
		| IDENTIFIER

number:
	INTEGER | FLOAT

literal:
	INTEGER | FLOAT | STRING | BOOLEAN ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

