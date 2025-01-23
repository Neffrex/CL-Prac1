%{
#include <math.h>
#include "parser.h" // Define los tokens para Bison
#include "symtab.h" // Incluye la tabla de símbolos
%}

%%
[ \t]+          					; /* Ignorar espacios en blanco y tabulaciones */
"//".*            				; /* Ignorar comentarios de una línea */
"/*"([^*]|\*+[^*/])*\*/ 	;	/* Ignorar comentarios de múltiples líneas */

"true"            { yylval.literal.bval = true;  return BOOLEAN; }
"false"           { yylval.literal.bval = false; return BOOLEAN; }
[0-9]+            { yylval.literal.ival = atoi(yytext);   return INTEGER; }
[0-9]+"."[0-9]+   { yylval.literal.fval = atof(yytext);   return FLOAT;   }
\"[^\"]*\"        { yylval.literal.sval = strdup(yytext); return STRING;  }
"PI"              { yylval.literal.fvalue = CONST_PI; return FLOAT; }
"E"               { yylval.literal.fvalue = CONST_E;  return FLOAT; }
"sin"             { return SIN; }
"cos"             { return COS; }
"tan"             { return TAN; }
":="              { return ASSIGN; }
"+"               { return PLUS;   }
"-"               { return MINUS;  }
"*"               { return TIMES;  }
"/"               { return DIVIDE; }
"%"               { return MOD;    }
"**"              { return POW;    }
">"               { return GT;  }
">="              { return GE;  }
"<"               { return LT;  }
"<="              { return LE;  }
"="               { return EQ;  }
"<>"              { return NEQ; }
"not"             { return NOT; }
"and"             { return AND; }
"or"              { return OR;  }
"LEN"             { return LEN;    }
"SUBSTR"          { return SUBSTR; }
"\n"							{ return EOL;    }

[a-zA-Z_][a-zA-Z0-9_]* { 
	yylval.symbol.name = (char *) malloc(sizeof(char) * yyleng + 1);
	sprintf(yylval.symbol.name, "%s", yytext);

	sym_value_type symbol;
	if(sym_lookup(yytext, &symbol) != SYMTAB_NOT_FOUND) {
		return UNDEFINED
	}
	
	return IDENTIFIER;
}

.                 { fprintf(stderr, "Error: Caracter desconocido '%s'\n", yytext); }

%%
int yywrap() {
    return 1;
}

