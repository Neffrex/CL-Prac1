/*
 * Scanner for a basic calculator compiler
 * author: Jose Luis Pueyo Viltres
 * e-mail: joseluis.pueyo@estudiants.urv.cat
 */

%{
/* Dependencies */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "calc.tab.h"
#include "compiler.h"
#include "log.h"

void yyerror(const char *s);
format_mode mode;

%}

%option noyywrap
%x COMMENT

/* DEFINITIONS */
DIGIT [0-9]
INTEGER {DIGIT}+
REAL {DIGIT}+"."{DIGIT}+
STRING \"[^\"]*\"
BOOLEAN "true"|"false"
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
WHITESPACE [ \t]
SINGLE_LINE_COMMENT "#".*[\n]|"//".*[\n]
EOL [\n]
%%

"(" {
	return LPAREN;
}
")" {
	return RPAREN;
}

":=" {
  return ASSIGN;
}

 /* Arithmetic Binary Operators ABOP */
"+" {
	yylval.operator = PLUS;
	return PLUS_OP;
}
"-" {
	yylval.operator = MINUS;
	return MINUS_OP;
}
"*" {
	yylval.operator = TIMES;
	return TIMES_OP;
}
"/" {
  yylval.operator = DIVIDE;
  return DIVIDE_OP;
}
"%" {
	yylval.operator = MOD;
	return MOD_OP;
}
"**" {
	yylval.operator = POW;
	return POW_OP;
}

 /* Boolean Binary Operators BBOP */
"=" {
	yylval.operator = EQUALS;
	return EQUALS_OP;
}
">" {
	yylval.operator = GREATER_THAN;
	return GREATER_THAN_OP;
}
">=" {
	yylval.operator = GREATER_EQUALS;
	return GREATER_EQUALS_OP;
}
"<" {
	yylval.operator = LOWER_THAN;
	return LOWER_THAN_OP;
}
"<=" {
	yylval.operator = LOWER_EQUALS;
	return LOWER_EQUALS_OP;
}
"<>" {
	yylval.operator = NOT_EQUALS;
	return NOT_EQUALS_OP;
}

"not" {
	yylval.operator = NOT;
	return NOT_OP;
}
"or" {
	yylval.operator = OR;
	return OR_OP;
}
"and" {
	yylval.operator = AND;
	return AND_OP;
}

 /* Constants */
"PI" {
	yylval.literal.type = FLOAT;
	yylval.literal.fvalue = M_PI;
	return FLOAT_LITERAL;
}
"E" {
	yylval.literal.type = FLOAT;
	yylval.literal.fvalue = M_E;
	return FLOAT_LITERAL;
}

"DEC" { mode = DEC; }
"OCT" { mode = OCT; }
"HEX" { mode = HEX; }
"BIN" { mode = BIN; }

 /* Data types */
{INTEGER} {
  // printf("Encountered digit: %s\n", yytext);
  yylval.literal.type = INTEGER;
  yylval.literal.ivalue = atoi(yytext);
  return INTEGER_LITERAL; 
}
{REAL} {
  // printf("Encountered float: %s\n", yytext);
  yylval.literal.type = FLOAT;
  yylval.literal.fvalue = atof(yytext);
  return FLOAT_LITERAL;
}
{STRING} {
	yylval.literal.type = STRING;
  yylval.literal.svalue = strndup(yytext + 1, yyleng - 2);
  return STRING_LITERAL;
}
{BOOLEAN} {
  yylval.literal.type = BOOLEAN;
  yylval.literal.bvalue = !strcmp(yytext, "true");
  return BOOLEAN_LITERAL;
}
{IDENTIFIER} {
  // printf("Encountered ID: %s\n", yytext);
  yylval.identifier.name = strndup(yytext, yyleng);
  yylval.identifier.line = yylineno;
  yylval.identifier.type = UNDEFINED_DATA;
  return IDENTIFIER;
}

 /* Single Line Comment */
{SINGLE_LINE_COMMENT} { 
  yylineno++;
}

 /* Multiline comment */
"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>. { /* Skip comment content*/ }
<COMMENT>\n {
  yylineno++;
}

 /* Empty Spaces */
{WHITESPACE} { /* Skip whitespace sequences */ }
^{EOL} { yylineno++; }
{EOL} {
  yylineno++;
  return EOL;
}
 /* Undefined Sequence */
. { log_message(LOG_ERROR, "lexical error, undefined sequence: %s", yytext); }

%% 

void yyerror(const char *msg) {
	fprintf(stderr, "\033[31mERROR:%d:\033[0m %s\n", yylineno, msg);
  exit(EXIT_FAILURE);
}

