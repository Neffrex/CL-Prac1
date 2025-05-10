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
  bool boolean;
  literal literal;
  identifier identifier;
  op_type operator;
  void* no_type;
}

%token <no_type> EOL LPAREN RPAREN ASSIGN
%token <no_type> SIN COS TAN TRUE FALSE
%token <no_type> PI E


%token <literal> INTEGER FLOAT STRING 
%token <operator> PLUS MINUS TIMES DIVIDE MOD POW
%token <operator> EQUALS GREATER_THAN GREATER_EQUALS LOWER_THAN LOWER_EQUALS NOT_EQUALS
%token <operator> NOT OR AND
%token <identifier> IDENTIFIER

%type <no_type> statement
%type <identifier> assignment

%type <literal> arithmeticExpression
%type <literal> arithmeticExpressionA
%type <literal> arithmeticExpressionM
%type <literal> arithmeticExpressionP
%type <literal> arithmeticExpressionX

%type <literal> booleanExpression
%type <boolean> booleanExpressionO
%type <boolean> booleanExpressionA
%type <boolean> booleanExpressionX
%type <boolean> relationalExpression

%define parse.error verbose

%start program

%%

program: statementList YYEOF;

statementList:
  %empty
| statementList statement
;

statement:
  assignment[id]
  { cprint(yyout, mode, "[type:%s] %s := %v\n", type2str($id.value.type), $id.name, &($id.value)); }
  | arithmeticExpression[e] 
  { cprint(yyout, mode, "[type:%s] %v\n", type2str($e.type), &$e); }
  | booleanExpression[e]
  { cprint(yyout, mode, "[type:%s] %v\n", type2str($e.type), &$e); }
;


assignment:
  IDENTIFIER[l] ASSIGN arithmeticExpression[r] 
  { $$ = assign(&$l, $r); }
  | IDENTIFIER[l] ASSIGN booleanExpression[r]
  { $$ = assign(&$l, $r); }
;

arithmeticExpression:
  arithmeticExpressionA 
;

arithmeticExpressionA:
  arithmeticExpressionM
  | arithmeticExpressionA[l] PLUS arithmeticExpressionM[r]
  { $$ = arithmeticExpressionPlus(&$l, &$r); }
  | arithmeticExpressionA[l] MINUS arithmeticExpressionM[r]
  { $$ = arithmeticExpressionMinus(&$l, &$r); }
  | MINUS arithmeticExpressionM[r]
  { $$ = arithmeticExpressionNegate(&$r); }
  | PLUS arithmeticExpressionM[r]
  { $$ = $r; }
;

arithmeticExpressionM:
  arithmeticExpressionP
  | arithmeticExpressionM[l] MOD arithmeticExpressionP[r]
  { $$ = arithmeticExpressionMod(&$l, &$r); }
  | arithmeticExpressionM[l] TIMES arithmeticExpressionP[r]
  { $$ = arithmeticExpressionTimes(&$l, &$r); }
  | arithmeticExpressionM[l] DIVIDE arithmeticExpressionP[r]
  { $$ = arithmeticExpressionDivide(&$l, &$r); }
;

arithmeticExpressionP:
  arithmeticExpressionX
  | arithmeticExpressionP[l] POW arithmeticExpressionX[r]
  { $$ = arithmeticExpressionPow(&$l, &$r); }
;

arithmeticExpressionX:
  INTEGER
  | FLOAT
  | STRING
  | IDENTIFIER[x]
  { $$ = arithmeticExpressionIdentifier(&$x); }
  | SIN LPAREN arithmeticExpression[x] RPAREN 
  { $$ = arithmeticExpressionSin(&$x); }
  | COS LPAREN arithmeticExpression[x] RPAREN 
  { $$ = arithmeticExpressionCos(&$x); }
  | TAN LPAREN arithmeticExpression[x] RPAREN 
  { $$ = arithmeticExpressionTan(&$x); }
  | LPAREN arithmeticExpression RPAREN 
  { $$ = $2; }
;

booleanExpression:
  booleanExpressionO[e]
  { $$ = booleanExpressionToLiteral($e); }
;

booleanExpressionO: 
  booleanExpressionA
  | booleanExpressionO[l] OR booleanExpressionA[r]
  { $$ = booleanExpressionOr($l, $r); }
;

booleanExpressionA:
  booleanExpressionX { $$ = $1; }
  | booleanExpressionA[l] AND booleanExpressionX[r]
  { $$ = booleanExpressionAnd($l, $r); }
  | NOT booleanExpressionX[r]
  { $$ = booleanExpressionNot($r); }
;

booleanExpressionX:
  relationalExpression
  | TRUE
  { $$ = booleanExpressionTrue(); }
  | FALSE
  { $$ = booleanExpressionFalse(); }
  | IDENTIFIER[id]
  { $$ = booleanExpressionIdentifier(&$id); }
  | LPAREN booleanExpressionO[e] RPAREN
  { $$ = $e; }
;

relationalExpression:
  arithmeticExpression[l] EQUALS arithmeticExpression[r]
  { $$ = relationalExpressionEquals(&$l, &$r); }
  | arithmeticExpression[l] GREATER_THAN arithmeticExpression[r]
  { $$ = relationalExpressionGreaterThan(&$l, &$r); }
  | arithmeticExpression[l] GREATER_EQUALS arithmeticExpression[r]
  { $$ = relationalExpressionGreaterEquals(&$l, &$r); }
  | arithmeticExpression[l] LOWER_THAN arithmeticExpression[r]
  { $$ = relationalExpressionLowerThan(&$l, &$r); }
  | arithmeticExpression[l] LOWER_EQUALS arithmeticExpression[r]
  { $$ = relationalExpressionLowerEquals(&$l, &$r); }
  | arithmeticExpression[l] NOT_EQUALS arithmeticExpression[r]
  { $$ = relationalExpressionNotEquals(&$l, &$r); }

%%

int main(int argc, char** argv) {
  init_log("debug.log");
  mode = E_DEC;
  yyparse();
  close_log();
  return 0;
}


