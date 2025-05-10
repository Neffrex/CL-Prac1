#include "types.h"

bool isNullLiteral(literal* literal)
{ return literal->type == E_NULL_TYPE; }

bool isInteger(literal* literal)
{ return literal->type == E_INTEGER; }

bool isFloat(literal* literal)
{ return literal->type == E_FLOAT; }

bool isString(literal* literal)
{ return literal->type == E_STRING; }

bool isBoolean(literal* literal)
{ return literal->type == E_BOOLEAN; }

bool isNumber(literal* literal)
{ return literal->type == E_INTEGER || literal->type == E_FLOAT; }

void int2bin(char *buffer, size_t size, int value)
{
  if(size == 0) return;
  for(size_t i = 0; i < size-1; i++)
    buffer[i] = (value & (1U << (size-2-i))) ? '1' : '0';
  buffer[size-1] = '\0';
}

void int2str(char* buffer, size_t size, format_mode mode, int value) {
  switch(mode)
  {
    case E_HEX:       snprintf(buffer, size, "0c%o", value); break;
    case E_OCT:       snprintf(buffer, size, "0x%x", value); break;
    case E_BIN:       int2bin(buffer, size, value); break;
    case E_DEC | E_NULL_MODE:
    default:          snprintf(buffer, size, "%d", value); break;
  }
}

void val2str(char* buffer, size_t size, format_mode mode, literal* literal)
{
  switch(literal->type)
  {
    case E_INTEGER:   int2str(buffer, size, mode, literal->ivalue); break;
    case E_FLOAT:     snprintf(buffer, size, "%.3f", literal->fvalue); break;
    case E_STRING:    snprintf(buffer, size, "%s", literal->svalue ? literal->svalue : NULL_STR); break;
    case E_BOOLEAN:   snprintf(buffer, size, "%s", literal->bvalue ? "true" : "false"); break;
    case E_NULL_TYPE: snprintf(buffer, size, NULL_STR); break;
    default:          snprintf(buffer, size, UNDEFINED_STR);
  }
}

const char* type2str(data_type type) 
{
  switch(type)
  {
    case E_INTEGER:   return INTEGER_STR;
    case E_FLOAT:     return FLOAT_STR;
    case E_STRING:    return STRING_STR;
    case E_BOOLEAN:   return BOOLEAN_STR;
    case E_NULL_TYPE: return NULL_STR;
    default:          return UNDEFINED_STR;
  }
}

const char* op2str(op_type op)
{
  switch(op) 
  {
    case E_NEGATE:          return NEGATE_STR;
    case E_PLUS:            return PLUS_STR;
    case E_MINUS:           return MINUS_STR;
    case E_TIMES:           return TIMES_STR;
    case E_DIVIDE:          return DIVIDE_STR;
    case E_MOD:             return MOD_STR;
    case E_POW:             return POW_STR;
    case E_EQUALS:          return EQUALS_STR;
    case E_GREATER_THAN:    return GREATER_THAN_STR;
    case E_GREATER_EQUALS:  return GREATER_EQUALS_STR;
    case E_LOWER_THAN:      return LOWER_THAN_STR;
    case E_LOWER_EQUALS:    return LOWER_EQUALS_STR;
    case E_NOT_EQUALS:      return NOT_EQUALS_STR;
    case E_OR:              return OR_STR;
    case E_NOT:             return NOT_STR;
    case E_AND:             return AND_STR;
    default:                return NULL_STR;
  }
}
