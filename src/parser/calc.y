%{
/* Dependencies */
#include <stdio.h>
#include "calc.tab.h"


extern FILE *yyout;
extern char *yytext;
extern int yylineno;
extern int yylex(void);
extern void yyerror(const char *s);
extern format_mode mode;

%}

%code requires {
  #include "../ast/headers/compiler.h"
}

%union {
  bool boolean;
  literal literal;
  identifier identifier;
  op_type operator;
  void* no_type;
}

%token <no_type> EOL LPAREN RPAREN ASSIGN COMMA
%token <no_type> TRUE FALSE 
%token <no_type> SIN COS TAN LEN SUBSTR


%token <literal> INTEGER FLOAT STRING CONSTANT
%token <operator> PLUS MINUS TIMES DIVIDE MOD POW
%token <operator> EQUALS GREATER_THAN GREATER_EQUALS LOWER_THAN LOWER_EQUALS NOT_EQUALS
%token <operator> NOT OR AND
%token <identifier> UNDEFINED_IDENTIFIER BOOLEAN_IDENTIFIER ARITHMETIC_IDENTIFIER

%type <no_type> statement

%type <identifier> assignment
%type <identifier> identifier_complete identifier_incomplete

%type <literal> expression

%type <literal> arithmeticExpression
%type <literal> arithmeticExpressionA
%type <literal> arithmeticExpressionM
%type <literal> arithmeticExpressionP
%type <literal> arithmeticExpressionX
%type <literal> arithmeticFunction

%type <literal> booleanExpression
%type <boolean> booleanExpressionO
%type <boolean> booleanExpressionA
%type <boolean> booleanExpressionX
%type <boolean> relationalExpression

%define parse.error verbose

%start program

%%

program: 
  statementList YYEOF
  { log_message(LOG_INFO, LOG_MSG_END_OF_PROGRAM); }
;

statementList:
  %empty
| statementList statement EOL
{ log_message(LOG_INFO, LOG_MSG_END_OF_STATEMENT);}
;

statement:
  %empty
  | assignment[id]
  { cprint(yyout, mode, "[type:%s] %s := %v\n", type2str($id.value.type), $id.name, &($id.value)); }
  | expression[e]
  { cprint(yyout, mode, "[type:%s] %v\n", type2str($e.type), &$e); }
;

assignment:
  identifier_complete[l] ASSIGN expression[r] 
  { $$ = assign(&$l, $r); }
  | identifier_incomplete[l] ASSIGN expression[r]
  { $$ = assign(&$l, $r); }
;

identifier_complete:
  BOOLEAN_IDENTIFIER[id]
  { log_message(LOG_INFO, "Boolean Identifier: %s", $id.name); }
  | ARITHMETIC_IDENTIFIER[id]
  { log_message(LOG_INFO, "Arithmetic Identifier: %s", $id.name); }
;

identifier_incomplete:
  UNDEFINED_IDENTIFIER[id]
  { log_message(LOG_INFO, "Undefined Identifier: %s", $id.name); }
;

expression:
  arithmeticExpression[e]
  | booleanExpression

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
  | CONSTANT
  | arithmeticFunction
  | ARITHMETIC_IDENTIFIER[x]
  { $$ = arithmeticExpressionIdentifier(&$x); }
  | LPAREN arithmeticExpression RPAREN 
  { $$ = $2; }
;

arithmeticFunction:
  SIN[id] LPAREN arithmeticExpression[x] RPAREN 
  { $$ = arithmeticExpressionFunction(E_SIN, &$x); }
  | COS[id] LPAREN arithmeticExpression[x] RPAREN 
  { $$ = arithmeticExpressionFunction(E_COS, &$x); }
  | TAN[id] LPAREN arithmeticExpression[x] RPAREN 
  { $$ = arithmeticExpressionFunction(E_TAN, &$x); }
  | LEN[id] LPAREN arithmeticExpression[string] RPAREN
  { $$ = arithmeticExpressionFunction(E_LEN, &$string); }
  | SUBSTR[id] LPAREN arithmeticExpression[string] COMMA arithmeticExpression[start] COMMA arithmeticExpression[length] RPAREN
  { $$ = arithmeticExpressionFunction(E_SUBSTR, &$string, &$start, &$length); }
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
  | BOOLEAN_IDENTIFIER[id]
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


