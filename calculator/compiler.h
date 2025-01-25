#ifndef COMPILER_H
#define COMPILER_H

#include <stdbool.h>
#include <stdarg.h>

#define STR_MAX_LENGTH 200

extern const char* op_map[];

typedef enum {
  PLUS,          // "+"
  MINUS,         // "-"
  TIMES,         // "*"
  DIVIDE,        // "/"
  COMPARE,       // "=="
  GREATER_THAN,  // ">"
  GREATER_EQUAL, // ">="
  LESS_THAN,     // "<"
  LESS_EQUAL,    // "<="
  UNDEFINED_OP
} op_type;

typedef struct {
  op_type type;
  char* value;
} operator_t;

typedef enum {
  STRING,
  INTEGER,
  FLOAT,
  BOOLEAN,
  UNDEFINED_DATA
} data_type;

typedef struct {
  data_type type;
  char* svalue;
  int ivalue;
  float fvalue;
  bool bvalue;
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
value_info arithmetic(const value_info, const operator_t, const value_info);

/* Semantic Analysis */
bool semantic_analysis(void);

#endif
