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

void yyerror(const char *s);
%}

%option yylineno
%option noyywrap
%x COMMENT

/* DEFINITIONS */
DIGIT [0-9]
INTEGER {DIGIT}+
REAL {DIGIT}+"."{DIGIT}+
STRING \"[^\"]*\"
BOOLEAN "true"|"false"
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]* */
WHITESPACE [ \t\n]
%%

 /* Data types */
{INTEGER} {
  /* printf("Encountered digit: %s\n", yytext); */
  yylval.literal.type = INTEGER;
  yylval.literal.ivalue = atoi(yytext);
	sprintf(yylval.literal.svalue, "%s", yytext);
  return NUMBER_LITERAL; 
}
{REAL} {
  /* printf("Encountered float: %s", yytext); */
  yylval.literal.type = FLOAT;
  yylval.literal.fvalue = atof(yytext);
	sprintf(yylval.literal.svalue, "%s", yytext);
  return NUMBER_LITERAL;
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

 /* Arithmetic Binary Operators ABOP */
"+" {
	yylval.operator = PLUS;
	return ABOP;
}
"-" {
	yylval.operator = MINUS;
	return ABOP;
}
"*" {
	yylval.operator = TIMES;
	return ABOP;
}
"/" {
  yylval.operator = DIVIDE;
  return ABOP;
}
"%" {
	yylval.operator = MOD;
	return ABOP;
}
"**" {
	yylval.operator = POW;
	return ABOP;
}


 /* Boolean Binary Operators BBOP */
"=" {
	yylval.operator = EQUALS;
	return BBOP;
}
">" {
	yylval.operator = GREATER_THAN;
	return BBOP;
}
">=" {
	yylval.operator = GREATER_EQUALS;
	return BBOP;
}
"<" {
	yylval.operator = LOWER_THAN;
	return BBOP;
}
"<=" {
	yylval.operator = LOWER_EQUALS;
	return BBOP;
}
"<>" {
	yylval.operator = NOT_EQUALS;
	return BBOP;
}

 /* Multiline comment */
"/*" { BEGIN(COMMENT); }
<COMMENT>"*/" { BEGIN(INITIAL); }
<COMMENT>. { /* Skip comment content*/ }
<COMMENT>\n { /* Skip comment lines */}

 /* Empty Spaces */
[ \t\n] { /* Skip whitespace sequences */ }

 /* Undefined Sequence */
. { printf("Undefined sequence: %s", yytext); }

