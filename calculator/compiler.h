#ifndef COMPILER_H
#define COMPILER_H

#include <stdbool.h>
#include <stdarg.h>
#include <math.h>

#define STR_MAX_LENGTH 200

extern const char* op_map[];

typedef enum {
  // ARITHMETIC OPERATORS
  PLUS,           // "+"
  MINUS,          // "-"
  TIMES,          // "*"
  DIVIDE,         // "/"
  MOD,            // "%"
  POW,            // "**"
  // BOOLEAN OPERATORS
  EQUALS,         // "="
  GREATER_THAN,   // ">"
  GREATER_EQUALS, // ">="
  LOWER_THAN,      // "<"
  LOWER_EQUALS,    // "<="
  NOT_EQUALS,     // "<>"
  UNDEFINED_OP
} op_type;

typedef enum {
  STRING,
  INTEGER,
  FLOAT,
  BOOLEAN,
  UNDEFINED_DATA
} data_type;

typedef enum {
  OCT,
  HEX,
  BIN,
  DEC
} mode;

typedef struct {
  data_type type;
  char* svalue;
  int ivalue;
  float fvalue;
  bool bvalue;
  mode mode;
} value_info;

typedef struct {
  char* name;
  int length;
  int line;
  value_info id_value;
} identifier;

bool value_format(char*, data_type, int);
int cprint(FILE*, const char*, ...);

/* Lexical Analysis */
bool init_lexical_analysis(char *);
bool finalize_lexical_analysis(void);
op_type operation_type(const char*);

/* Syntax Analysis */
bool init_syntax_analysis(char *);
bool end_syntax_analysis(void);
value_info arithmetic(const value_info, const op_type, const value_info);
value_info boolean_logic(const value_info, const op_type, const value_info);

/* Semantic Analysis */
bool semantic_analysis(void);

#endif
