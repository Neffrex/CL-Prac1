#include "headers/types.h"

bool isNullLiteral(literal* literal)
{ return literal->type == TYPE_UNDEFINED; }

bool isInteger(literal* literal)
{ return literal->type == TYPE_INTEGER; }

bool isFloat(literal* literal)
{ return literal->type == TYPE_FLOAT; }

bool isString(literal* literal)
{ return literal->type == TYPE_STRING; }

bool isBoolean(literal* literal)
{ return literal->type == TYPE_BOOLEAN; }

bool isNumber(literal* literal)
{ return literal->type == TYPE_INTEGER || literal->type == TYPE_FLOAT; }

char* literal2str(literal* literal)
{
  char* buffer = malloc(STR_MAX_LENGTH);
  size_t size = STR_MAX_LENGTH;

  switch(literal->type)
  {
    case TYPE_INTEGER:   snprintf(buffer, size, "%d", literal->ivalue); break;
    case TYPE_FLOAT:     snprintf(buffer, size, "%.3f", literal->fvalue); break;
    case TYPE_STRING:    snprintf(buffer, size, "%s", literal->svalue ? literal->svalue : S_NULL); break;
    case TYPE_BOOLEAN:   snprintf(buffer, size, "%s", literal->bvalue ? S_TRUE : S_FALSE); break;
    default: snprintf(buffer, size, S_UNDEFINED);
  }

  return buffer;
}

const char* type2str(type_t type) 
{
  switch(type)
  {
    case TYPE_INTEGER:   return S_INTEGER;
    case TYPE_FLOAT:     return S_FLOAT;
    case TYPE_STRING:    return S_STRING;
    case TYPE_BOOLEAN:   return S_BOOLEAN;
    default: return S_UNDEFINED;
  }
}

const char* op2str(op_type op)
{
  switch(op) 
  {
    case OP_NEGATE:          return S_NEGATE;
    case OP_PLUS:            return S_PLUS;
    case OP_MINUS:           return S_MINUS;
    case OP_TIMES:           return S_TIMES;
    case OP_DIVIDE:          return S_DIVIDE;
    case OP_MOD:             return S_MOD;
    case OP_POW:             return S_POW;
    case OP_EQUALS:          return S_EQUALS;
    case OP_GREATER_THAN:    return S_GREATER_THAN;
    case OP_GREATER_EQUALS:  return S_GREATER_EQUALS;
    case OP_LOWER_THAN:      return S_LOWER_THAN;
    case OP_LOWER_EQUALS:    return S_LOWER_EQUALS;
    case OP_NOT_EQUALS:      return S_NOT_EQUALS;
    case OP_OR:              return S_OR;
    case OP_NOT:             return S_NOT;
    case OP_AND:             return S_AND;
    default: return S_NULL;
  }
}

const char* functid2str(funct_id funct_id)
{
  switch(funct_id) 
  {
    case FUNC_SIN:    return S_SIN;
    case FUNC_COS:    return S_COS;
    case FUNC_TAN:    return S_TAN;
    case FUNC_LEN:    return S_LEN;
    case FUNC_SUBSTR: return S_SUBSTR;
    default: return S_NULL;
  }
}


const char* bool2str(bool value) 
{
  return value ? S_TRUE : S_FALSE;
}