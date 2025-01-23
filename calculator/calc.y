%{
/* Dependencies */
#include <stdio.h>

void yyerror(const char *s);
int yylex(void);

%}

%union {
  int number;
  void* operator;
}

%token <number> INTEGER
%token <operator> PLUS MINUS MULTIPLY DIVIDE

%type <number> statement

%start program

%%

program: %empty | statement_list ;

statement_list: 
  statement
  | statement_list statement
  ;

statement:
  INTEGER
  | INTEGER PLUS INTEGER {
    printf("[BISON] Encountered %d + %d.\n", $1, $3);
    $$ = $1 + $3;
    printf("%d\n", $$);
  }
  | INTEGER MINUS INTEGER {
    printf("[BISON] Encountered %d - %d.\n", $1, $3);
    $$ = $1 - $3;
    printf("%d\n", $$);
  }
  | INTEGER MULTIPLY INTEGER {
    printf("[BISON] Encountered %d * %d.\n", $1, $3);
    $$ = $$ * $3;
    printf("%d\n", $$);
  }
  | INTEGER DIVIDE INTEGER {
    printf("[BISON] Encountered %d / %d.\n", $1, $3);
    $$ = $1 / $3;
    printf("%d\n", $$);
  }

%%

int main(int argc, char** argv) {
  yyparse();
}

void yyerror(const char *s) {
  fprintf(stderr, "%s\n", s);
}

