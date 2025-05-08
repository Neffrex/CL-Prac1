#ifndef COMPILER_H
#define COMPILER_H

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <math.h>
#include "symtab.h"
#include "log.h"

#define STR_MAX_LENGTH 200
#define SVALUE_MAX_LENGTH 64

extern const char* op_map[];
extern void yyerror(const char *msg);
extern format_mode mode;

typedef enum {
  // ARITHMETIC OPERATORS
  PLUS,           // "+"
  MINUS,          // "-"
  TIMES,          // "*"
  DIVIDE,         // "/"
  MOD,            // "%"
  POW,            // "**"
  // BOOLEAN ARITHMETIC OPERATORS
  EQUALS,         // "="
  GREATER_THAN,   // ">"
  GREATER_EQUALS, // ">="
  LOWER_THAN,      // "<"
  LOWER_EQUALS,    // "<="
  NOT_EQUALS,     // "<>"
  // BOOLEAN OPERATORS
  NOT,
  OR,
  AND
} op_type;

typedef enum {
  E_SIN,
  E_COS,
  E_TAN
} native_function_enum;

/* Auxiliary functions */
bool value_format(char*, data_type, int);
int cprint(FILE*, const char*, ...);
void val2str(const value_info*, char*, size_t);
const char* op2str(op_type);
const char* type2str(data_type);
const char* nativefunct2str(native_function_enum);
format_mode format2mode(char);


/* Lexical Analysis */
bool init_lexical_analysis(char *);
bool finalize_lexical_analysis(void);

/* Syntax Analysis */
bool init_syntax_analysis(char *);
bool end_syntax_analysis(void);
value_info arithmetic(value_info*, const op_type, value_info*);
value_info integer_arithmetic(int, const op_type, int);
value_info float_arithmetic(float, const op_type, float);
value_info trigonometry(native_function_enum, value_info*);
value_info concat(value_info*, value_info*);
value_info boolean_logic(const value_info, const op_type, const value_info);
value_info boolean_logic_unary(const op_type, const value_info);

value_info assign(identifier_t*, value_info);
value_info identifier_value(identifier_t);

/* Semantic Analysis */
bool semantic_analysis(void);

#endif
