%{
/* Dependencies */
#include <stdio.h>
#include "calc.tab.h"


extern FILE *yyout;
extern char *yytext;
extern int yylineno;
extern int yylex(void);
extern void yyerror(const char *s);

%}

%code requires {
  #include "../ast/headers/compiler.h"
}

%union {
  bool boolean;
  literal literal;
  identifier identifier;
  identifier_node* p_identifier_node;
  op_type operator;
	type_t type;
  void* no_type;
}

%token <no_type> EOL LPAREN RPAREN LBRACKET RBRACKET ASSIGN COMMA
%token <no_type> TRUE FALSE 
%token <no_type> SIN COS TAN LEN SUBSTR
%token <no_type> STRUCT
%token <type> TYPE

%token <literal> INTEGER FLOAT STRING CONSTANT
%token <operator> PLUS MINUS TIMES DIVIDE MOD POW
%token <operator> EQUALS GREATER_THAN GREATER_EQUALS LOWER_THAN LOWER_EQUALS NOT_EQUALS
%token <operator> NOT OR AND

%token <identifier> ARITHMETIC_IDENTIFIER BOOLEAN_IDENTIFIER UNTYPED_IDENTIFIER
%type <no_type> statement


%type <identifier> assignment
%type <p_identifier_node> declaration
%type <literal> expression

%type <p_identifier_node> identifierList

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
	| declaration[id]
	{ 
    for (identifier_node* current = $id; current != NULL; current = current->next) {
      cprint(yyout, "%s:%s", current->id.name, type2str(current->id.type));
      if (current->next != NULL) 
			{ cprint(yyout, ", "); }
			else
			{ cprint(yyout, "\n"); }
    }
  }
  | assignment[id]
  { cprint(yyout, "%s:%s = %v\n", $id.name, type2str($id.type), &($id.value)); }
  | expression[e]
  { cprint(yyout, "%v:%s\n", &$e, type2str($e.type)); }
;

declaration:
	TYPE[t] identifierList[node]
	{ $$ = declare($node, $t); }
;

identifierList:
  UNTYPED_IDENTIFIER[id]
  { $$ = createIdentifierNode(NULL, &$id, TYPE_UNDEFINED); }
  | identifierList COMMA UNTYPED_IDENTIFIER[id]
  { $$ = createIdentifierNode($1, &$id, TYPE_UNDEFINED); }
;

assignment:
  ARITHMETIC_IDENTIFIER[l] ASSIGN arithmeticExpression[r]
  { $$ = assign(&$l, $r); }
  | BOOLEAN_IDENTIFIER[l] ASSIGN booleanExpression[r]
  { $$ = assign(&$l, $r); }
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
  { $$ = $x.value; }
  | LPAREN arithmeticExpression RPAREN 
  { $$ = $2; }
;

arithmeticFunction:
  SIN[id] LPAREN arithmeticExpression[x] RPAREN 
  { $$ = arithmeticExpressionFunction(FUNC_SIN, &$x); }
  | COS[id] LPAREN arithmeticExpression[x] RPAREN 
  { $$ = arithmeticExpressionFunction(FUNC_COS, &$x); }
  | TAN[id] LPAREN arithmeticExpression[x] RPAREN 
  { $$ = arithmeticExpressionFunction(FUNC_TAN, &$x); }
  | LEN[id] LPAREN arithmeticExpression[x] RPAREN
  { $$ = arithmeticExpressionFunction(FUNC_LEN, &$x); }
  | SUBSTR[id] LPAREN arithmeticExpression[x] COMMA arithmeticExpression[start] COMMA arithmeticExpression[length] RPAREN
  { $$ = arithmeticExpressionFunction(FUNC_SUBSTR, &$x, &$start, &$length); }
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
  { $$ = $id.value.bvalue; }
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
  yyparse();
  close_log();
  return 0;
}


