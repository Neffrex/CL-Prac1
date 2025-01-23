%{

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exemple.tab.h"
#include "exemple_funcions.h"

%}

%option yylineno
%option noyywrap
%option noinput
%option nounput

lletra  [a-zA-Z]
digit   [0-9]

%%


{lletra}({lletra}|{digit})* {
                              yylval.ident.lexema = strdup(yytext);
                              yylval.ident.lenght = yyleng;
                              yylval.ident.line = yylineno;
                              yylval.ident.id_val.val_type = UNKNOWN_TYPE;
                              return ID;
                            }

"="                         { return ASSIGN; }

{digit}({digit})*           {
                              yylval.enter = atoi(yytext);
                              return INTEGER;
                            }

^[ \t]*[\n]                 {}

[\n]                        { return ENDLINE; }

.                           {}

%%

