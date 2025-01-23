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
#include "calc.tab.h"

void yyerror(const char *s);
%}

/* DEFINITIONS */
DIGIT [0-9]
/* IDENTIFIER [a-zA-Z_-][a-zA-Z0-9_-]* */

%%

{DIGIT}+ {
  /* printf("Encountered digit: %s\n", yytext); */
  yylval.number = atoi(yytext);
  return INTEGER; 
}
"+" {
  /* printf("Encountered operator %s\n", yytext); */
  return PLUS;
}
"-" {
  /* printf("Encountered operator %s\n", yytext); */
  return MINUS;
}
"*" {
  /* printf("Encountered operator %s\n", yytext); */
  return MULTIPLY;
}
"/" {
  /* printf("Encountered operator %s\n", yytext); */
  return DIVIDE;
}
[ \t\n] { /* Skip whitespace sequences */ }
. { printf("Undefined sequence: %s", yytext); }

