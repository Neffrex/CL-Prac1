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
#include "calc.tab.h"
#include "compiler.h"

#define TOKEN(X) return X

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
SIN "SIN"|"sin"
COS "COS"|"cos"
TAN "TAN"|"tan"
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
"PI"        { TOKEN(PI);  }
"E"         { TOKEN(E);   }
"DEC"       { mode = E_DEC; }
"OCT"       { mode = E_OCT; }
"HEX"       { mode = E_HEX; }
"BIN"       { mode = E_BIN; }
{SIN}       { TOKEN(SIN); }
{COS}       { TOKEN(COS); }
{TAN}       { TOKEN(TAN); }
"true"      { TOKEN(TRUE); }
"false"     { TOKEN(FALSE); }
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
  yylval.literal.svalue = strndup(yytext+1, yyleng-2);
  TOKEN(STRING);
}
{IDENTIFIER} {
  yylval.identifier.name = strndup(yytext, yyleng);
  yylval.identifier.lineno = yylineno;
  TOKEN(IDENTIFIER);
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

