#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define STR_MAX_LENGTH 256
#define NULL_STR "<null>"
#define UNDEFINED_STR "<undefined>"
#define INTEGER_STR "integer"
#define FLOAT_STR "float"
#define BOOLEAN_STR "boolean"
#define STRING_STR "string"
#define NEGATE_STR "negate"
#define PLUS_STR "plus"
#define MINUS_STR "minus" 
#define TIMES_STR "times" 
#define DIVIDE_STR "divide" 
#define MOD_STR "mod" 
#define POW_STR "pow" 
#define EQUALS_STR "equals" 
#define GREATER_THAN_STR "greater_than" 
#define GREATER_EQUALS_STR "greater_equals" 
#define LOWER_THAN_STR "lower_than" 
#define LOWER_EQUALS_STR "lower_equals" 
#define NOT_EQUALS_STR "not_equals" 
#define AND_STR "and" 
#define OR_STR "or" 
#define NOT_STR "not"

typedef enum {
  E_NULL_TYPE,
  E_INTEGER,
  E_FLOAT,
  E_STRING,
  E_BOOLEAN
} data_type;

typedef enum {
  E_NULL_MODE,
  E_DEC,
  E_HEX,
  E_OCT,
  E_BIN
} format_mode;

typedef enum {
  E_NULL_OP,
  E_NEGATE,
  E_PLUS,
  E_MINUS,
  E_TIMES,
  E_DIVIDE,
  E_MOD,
  E_POW,
  E_EQUALS,
  E_GREATER_THAN,
  E_GREATER_EQUALS,
  E_LOWER_THAN,
  E_LOWER_EQUALS,
  E_NOT_EQUALS,
  E_AND,
  E_OR,
  E_NOT,
} op_type;

typedef struct {
  data_type type;
  int ivalue;
  float fvalue;
  char* svalue;
  int bvalue;
} literal;

typedef struct {
  char* name;
  int lineno;
  literal value;
} identifier;

bool isInteger(literal*);
bool isFloat(literal*);
bool isString(literal*);
bool isBoolean(literal*);
bool isNumber(literal*);
void int2bin(char*, size_t, int);
void int2str(char*, size_t, format_mode, int);
void val2str(char*, size_t, format_mode, literal*);
const char* type2str(data_type);
const char* op2str(op_type);
