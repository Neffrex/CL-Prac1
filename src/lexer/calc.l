/*
 * Scanner for a basic calculator compiler
 * author: Jose Luis Pueyo Viltres
 * e-mail: joseluis.pueyo@estudiants.urv.cat
 */

%{
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../parser/calc.tab.h"
#include "../ast/headers/compiler.h"

#define TOKEN(X) log_message(LOG_INFO, "Token: %s", #X); return X; 

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
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
SIN "sin"
COS "cos"
TAN "tan"
SUBSTR "substr"
LEN "len"
TRUE "TRUE"|"true"
FALSE "FALSE"|"false"
DEC "DEC"|"dec"
OCT "OCT"|"oct"
HEX "HEX"|"hex"
BIN "BIN"|"bin"
WHITESPACE [ \t]
SINGLE_LINE_COMMENT "#".*[\n]|"//".*[\n]
EOL [\n]

%%

"("         { TOKEN(LPAREN);  }
")"         { TOKEN(RPAREN);  }
":="        { TOKEN(ASSIGN);  }
"+"         {	TOKEN(PLUS);    }
"-"         {	TOKEN(MINUS);   }
"*"         { TOKEN(TIMES);   }
"/"         { TOKEN(DIVIDE);  }
"%"         { TOKEN(MOD);     }
"**"        { TOKEN(POW);  }
"="         {	TOKEN(EQUALS);  }
">"         { TOKEN(GREATER_THAN);    }
">="        {	TOKEN(GREATER_EQUALS);  }
"<"         { TOKEN(LOWER_THAN);      }
"<="        { TOKEN(LOWER_EQUALS);    }
"<>"        { TOKEN(NOT_EQUALS);   }
"not"       { TOKEN(NOT);          }
"or"        { TOKEN(OR);  }
"and"       { TOKEN(AND); }
","         { TOKEN(COMMA); }
"PI"        {
  yylval.literal.type = E_FLOAT;
  yylval.literal.fvalue = M_PI;
  TOKEN(CONSTANT);
}
"E"         {
  yylval.literal.type = E_FLOAT;
  yylval.literal.fvalue = M_E;
  TOKEN(CONSTANT);
}
{DEC}       { mode = E_DEC; }
{OCT}       { mode = E_OCT; }
{HEX}       { mode = E_HEX; }
{BIN}       { mode = E_BIN; }
{LEN}       { TOKEN(LEN); }
{SUBSTR}    { TOKEN(SUBSTR); }
{SIN}       { TOKEN(SIN); }
{COS}       { TOKEN(COS); }
{TAN}       { TOKEN(TAN); }
{TRUE}      { TOKEN(TRUE); }
{FALSE}     { TOKEN(FALSE); }
{INTEGER} {
  yylval.literal.type = E_INTEGER;
  yylval.literal.ivalue = atoi(yytext);
  TOKEN(INTEGER);
}
{REAL} {
  yylval.literal.type = E_FLOAT;
  yylval.literal.fvalue = atof(yytext);
  TOKEN(FLOAT);
}
{STRING} {
  yylval.literal.type = E_STRING;
  yylval.literal.svalue = strndup(yytext+1, yyleng-2);
  TOKEN(STRING);
}
{IDENTIFIER} {
  identifier id;
  id.name = strndup(yytext, yyleng);
  id.lineno = yylineno;
  literal literal = getIdentifierValue(&id);
  yylval.identifier = id;

  if(isBoolean(&literal))
  { TOKEN(BOOLEAN_IDENTIFIER); }
  else if(isNumber(&literal) || isString(&literal))
  { TOKEN(ARITHMETIC_IDENTIFIER); }
  else
  { TOKEN(UNDEFINED_IDENTIFIER); }
}

{SINGLE_LINE_COMMENT} { yylineno++; }
"/*"                  { BEGIN(COMMENT); }
<COMMENT>"*/"         { BEGIN(INITIAL); }
<COMMENT>.            { }
<COMMENT>\n           { yylineno++; }

{EOL} {
  yylineno++;
  TOKEN(EOL);
}
{WHITESPACE}  { }
<<EOF>>       { TOKEN(YYEOF); }
.             { log_message(LOG_ERROR, "lexical error, undefined sequence: %s", yytext); }

%%

void yyerror(const char *msg) {
	fprintf(stderr, "\033[31mERROR:%d:\033[0m %s\n", yylineno, msg);
  exit(EXIT_FAILURE);
}

