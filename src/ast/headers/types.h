#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "log.h"

#define STR_MAX_LENGTH 256
#define MAX_VERBOSE_SIZE 64

// EMPTY VALUES
#define S_UNDEFINED "UNDEFINED"
#define S_NULL "NULL"
#define S_NAN "NaN"

// TYPES
#define S_INTEGER "integer"
#define S_FLOAT "float"
#define S_BOOLEAN "boolean"
#define S_STRING "string"

// BOOLEAN VALUES
#define S_TRUE "true"
#define S_FALSE "false"

// OPERATORS
#define S_NEGATE "negate"
#define S_PLUS "+"
#define S_MINUS "-"
#define S_TIMES "*"
#define S_DIVIDE "/"
#define S_MOD "%"
#define S_POW "**"
#define S_EQUALS "=="
#define S_GREATER_THAN ">"
#define S_GREATER_EQUALS ">="
#define S_LOWER_THAN "<"
#define S_LOWER_EQUALS "<="
#define S_NOT_EQUALS "<>"
#define S_AND "and"
#define S_OR "or"
#define S_NOT "not"
#define S_SIN "sin"
#define S_COS "cos"
#define S_TAN "tan"
#define S_LEN "len"
#define S_SUBSTR "substr"


typedef enum {
  TYPE_UNDEFINED,
  TYPE_INTEGER,
  TYPE_FLOAT,
  TYPE_STRING,
  TYPE_BOOLEAN
} type_t;

typedef enum {
  OP_UNDEFINED,
  OP_NEGATE,
  OP_PLUS,
  OP_MINUS,
  OP_TIMES,
  OP_DIVIDE,
  OP_MOD,
  OP_POW,
  OP_EQUALS,
  OP_GREATER_THAN,
  OP_GREATER_EQUALS,
  OP_LOWER_THAN,
  OP_LOWER_EQUALS,
  OP_NOT_EQUALS,
  OP_AND,
  OP_OR,
  OP_NOT,
} op_type;

// FIXME: Change "Function" system to an adequate one
typedef enum {
  FUNC_SIN,
  FUNC_COS,
  FUNC_TAN,
  FUNC_LEN,
  FUNC_SUBSTR
} funct_id;


typedef struct {
  type_t type;
	union {
		int ivalue;
		float fvalue;
		char* svalue;
		bool bvalue;
	};	
} literal;

typedef struct {
	char* name;
	type_t type;
	literal value;
	int lineno;
} identifier;

typedef struct identifier_node {
  identifier id;
  struct identifier_node* next;
} identifier_node;

bool isNullLiteral(literal*);
bool isInteger(literal*);
bool isFloat(literal*);
bool isString(literal*);
bool isBoolean(literal*);
bool isNumber(literal*);
char* literal2str(literal*);
const char* type2str(type_t);
const char* op2str(op_type);
const char* functid2str(funct_id);
const char* bool2str(bool value);
