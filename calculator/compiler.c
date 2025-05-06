#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

const char* op_map[] = { "+", "-", "*", "/", "=", ">", ">=", "<", "<=", "<>" };

void val2str(const value_info *v, char* buffer, size_t size) {
	switch (v->type) {
  	case INTEGER:
			snprintf(buffer, size, "%d", v->ivalue);
      break;
    case FLOAT:
      snprintf(buffer, size, "%.3f", v->fvalue);
      break;
    case BOOLEAN:
      snprintf(buffer, size, "%s", v->bvalue ? "true" : "false");
      break;
    case STRING:
      snprintf(buffer, size, "%s", v->svalue ? v->svalue : "(null)");
      break;
    case UNDEFINED_DATA:
    default:
      snprintf(buffer, size, "<undefined>");
      break;
  }
}

const char* type2str(data_type type) {
    switch (type) {
        case INTEGER: return "integer";
        case FLOAT:   return "float";
        case STRING:  return "string";
        case BOOLEAN: return "boolean";
        default:      return "<no_type>";
    }
}

const char* op2str(op_type op) {
  switch(op) {
    case PLUS: return "+";
		case MINUS: return "-";
		case TIMES: return "*";
		case DIVIDE: return "/";
		case MOD: return "%";
		case POW: return "**";
		case EQUALS: return "=";
		case GREATER_THAN: return ">";
		case GREATER_EQUALS: return ">=";
		case LOWER_THAN: return "<";
		case LOWER_EQUALS: return "<=";
		case NOT_EQUALS: return "<>";
		case NOT: return "not";
		case OR: return "or";
		case AND: return "and";
		default: return "<no_op>";
  }
}

void print_value_info(FILE* stream, value_info* value) {
   if (value == NULL) {
        fprintf(stream, "(null)");
        return;
    }

    switch (value->type) {
        case STRING:
            fprintf(stream, "%s", value->svalue ? value->svalue : "(null)");
            break;
        case INTEGER:
            switch (mode) {
                case OCT:
                    fprintf(stream, "0c%o", value->ivalue);
                    break;
                case HEX:
                    fprintf(stream, "0x%x", value->ivalue);
                    break;
                case BIN:
                    // TODO: Fix Binary Representation
                    fprintf(stream, "0b%x", value->ivalue);
                    break;
                case DEC:
                    fprintf(stream, "%d", value->ivalue);
                    break;
                default:
                    fprintf(stream, "%d", value->ivalue);
            }
            break;
        case FLOAT:
            fprintf(stream, "%.3f", value->fvalue);
            break;
        case BOOLEAN:
            fprintf(stream, "%s", (value->bvalue) ? "true" : "false");
            break;
        case UNDEFINED_DATA:
        default:
						log_message(LOG_ERROR, "cannot print invalid typed value (type:%d)", value->type);
    }
}

format_mode format2mode(char format) {
  switch(format) {
    case 'o': return OCT;
    case 'x': return HEX;
    case 'd': return DEC;
    case 'b': return BIN;
    default: return DEC;
  }
}

// Custom fprintf wrapper
int cprint(FILE* stream, const char* format, ...) {
  va_list args;
    va_start(args, format);

    const char* ptr = format;
    int written = 0;

    while (*ptr) {
        if (*ptr == '%' && *(ptr + 1) == 'v') {
            // Handle %v
            value_info* value = va_arg(args, value_info*);
            print_value_info(stream, value);
            ptr += 2;
        } else if (*ptr == '%') {
            // Handle other format specifiers
            ptr++; // Skip '%'

            // Pass format specifier to vfprintf
            if (*ptr) {
                char specifier[3] = { '%', *ptr, '\0' }; // Create "%x" format string
                if (*ptr == '%') { // Handle "%%"
                    fputc('%', stream);
                    written++;
                } else {
                    // Use va_arg with the correct type based on the specifier
                    switch (*ptr) {
                        case 'd': // Integer
                            written += fprintf(stream, specifier, va_arg(args, int));
                            break;
                        case 'f': // Float
                            written += fprintf(stream, specifier, va_arg(args, double));
                            break;
                        case 'c': // Character
                            written += fprintf(stream, specifier, (char)va_arg(args, int));
                            break;
                        case 's': // String
                            written += fprintf(stream, specifier, va_arg(args, char*));
                            break;
                        default: // Unknown specifier, just print it
                            fputc('%', stream);
                            fputc(*ptr, stream);
                            written += 2;
                            break;
                    }
                }
                ptr++; // Move past the format specifier
            }
        } else {
            // Print regular characters
            fputc(*ptr, stream);
            written++;
            ptr++;
        }
    }

    va_end(args);
    return written;
}

bool value_format(char* format_out, data_type type, int pos) {
  format_out[pos++] = '%';
  switch (type) {
    case STRING:
      format_out[pos] = 's';
      return true;
    case INTEGER:
      format_out[pos] = 'i';
      return true;
    case FLOAT:
      format_out[pos] = 'f';
      return true;
    case BOOLEAN:
      format_out[pos] = 's';
      return true;
    default: return false;
  }
}

value_info arithmetic(value_info *loperand, const op_type op, value_info *roperand) {
  // Result object initialization
  value_info result;
  result.type = UNDEFINED_DATA;
  result.svalue = NULL;
  result.ivalue = 0;
  result.fvalue = 0.0f;
  result.bvalue = false;

  bool is_integer_arithmetic = (loperand->type == INTEGER && roperand->type == INTEGER);
  bool is_float_arithmetic =
    (loperand->type == FLOAT || loperand->type == INTEGER)
    && (roperand->type == FLOAT || roperand->type == INTEGER);
  bool is_string_concat = (op == PLUS)
    && (loperand->type == STRING || loperand->type == INTEGER || loperand->type == FLOAT)
    && (roperand->type == STRING || roperand->type == INTEGER || roperand->type == FLOAT);

  if (is_integer_arithmetic) {
    result = integer_arithmetic(loperand->ivalue, op, roperand->ivalue);
  } else if (is_float_arithmetic) {
    if(loperand->type == INTEGER) loperand->fvalue = (float)loperand->ivalue;
    if(roperand->type == INTEGER) roperand->fvalue = (float)roperand->ivalue;
    result = float_arithmetic(loperand->fvalue, op, roperand->fvalue);
  } else if (is_string_concat) {
    result = concat(loperand, roperand);
  } else {
		char lval_str[STR_MAX_LENGTH];
		char rval_str[STR_MAX_LENGTH];
		val2str(loperand, lval_str, sizeof(lval_str));
		val2str(roperand, rval_str, sizeof(rval_str));
    const char* ltype_str = type2str(loperand->type);
    const char* rtype_str = type2str(roperand->type);
    const char* op_str = op2str(op);
    log_message(LOG_ERROR, "syntax error, unsupported operation or mismatched types %s %s %s:\n\t'%s' %s '%s'\n",
      ltype_str, op_str, rtype_str, lval_str, op_str, rval_str);
  }

  return result;
}



value_info boolean_logic_unary(op_type op, value_info operand) {
  value_info result;
  result.type = BOOLEAN;
  result.svalue = NULL;
  result.ivalue = 0;
  result.fvalue = 0.0f;
  result.bvalue = false;

  // UNARY OPERATIONS
  if(operand.type == BOOLEAN) {
    switch (op) {
      case NOT: result.bvalue = !operand.bvalue; break;
      default: result.type = UNDEFINED_DATA;
    }
  }
  
  return result;
}

value_info boolean_logic(value_info loperand, op_type op, value_info roperand) {
  value_info result;
  result.type = BOOLEAN;
  result.svalue = NULL;
  result.ivalue = 0;
  result.fvalue = 0.0f;
  result.bvalue = false;
  
  if (loperand.type == INTEGER && roperand.type == INTEGER) {
    switch (op) {
      case EQUALS: result.bvalue = loperand.ivalue == roperand.ivalue; break;
      case GREATER_THAN: result.bvalue = loperand.ivalue > roperand.ivalue; break;
      case GREATER_EQUALS: result.bvalue = loperand.ivalue >= roperand.ivalue; break;
      case LOWER_THAN: result.bvalue = loperand.ivalue < roperand.ivalue; break;
      case LOWER_EQUALS: result.bvalue = loperand.ivalue <= roperand.ivalue; break;
      case NOT_EQUALS: result.bvalue = loperand.ivalue != roperand.ivalue; break;
      default: result.type = UNDEFINED_DATA;
      }
  } else if (loperand.type == FLOAT && loperand.type == INTEGER) {
    switch (op) {
      case EQUALS: result.bvalue = loperand.fvalue == roperand.ivalue; break;
      case GREATER_THAN: result.bvalue = loperand.fvalue > roperand.ivalue; break;
      case GREATER_EQUALS: result.bvalue = loperand.fvalue >= roperand.ivalue; break;
      case LOWER_THAN: result.bvalue = loperand.fvalue < roperand.ivalue; break;
      case LOWER_EQUALS: result.bvalue = loperand.fvalue <= roperand.ivalue; break;
      case NOT_EQUALS: result.bvalue = loperand.fvalue != roperand.ivalue; break;
      default: result.type = UNDEFINED_DATA;
    }
  } else if (loperand.type == INTEGER && roperand.type == FLOAT) {
    switch (op) {
      case EQUALS: result.bvalue = loperand.ivalue == roperand.fvalue; break;
      case GREATER_THAN: result.bvalue = loperand.ivalue > roperand.fvalue; break;
      case GREATER_EQUALS: result.bvalue = loperand.ivalue >= roperand.fvalue; break;
      case LOWER_THAN: result.bvalue = loperand.ivalue < roperand.fvalue; break;
      case LOWER_EQUALS: result.bvalue = loperand.ivalue <= roperand.fvalue; break;
      case NOT_EQUALS: result.bvalue = loperand.ivalue != roperand.fvalue; break;
      default: result.type = UNDEFINED_DATA;
    }
  } else if (loperand.type == FLOAT && roperand.type == FLOAT) {
    switch (op) {
      case EQUALS: result.bvalue = loperand.fvalue == roperand.fvalue; break;
      case GREATER_THAN: result.bvalue = loperand.fvalue > roperand.fvalue; break;
      case GREATER_EQUALS: result.bvalue = loperand.fvalue >= roperand.fvalue; break;
      case LOWER_THAN: result.bvalue = loperand.fvalue < roperand.fvalue; break;
      case LOWER_EQUALS: result.bvalue = loperand.fvalue <= roperand.fvalue; break;
      case NOT_EQUALS: result.bvalue = loperand.fvalue != roperand.fvalue; break;
      default: result.type = UNDEFINED_DATA;
    }
  } else if (loperand.type == BOOLEAN && roperand.type == BOOLEAN) {
    switch (op) {
      case OR: result.bvalue = loperand.bvalue || roperand.bvalue; break;
      case AND: result.bvalue = loperand.bvalue && roperand.bvalue; break;
      default: result.type = UNDEFINED_DATA;
    }
  }


  return result;
}


value_info integer_arithmetic(int lvalue, op_type op, int rvalue) {
  value_info result;
  result.type = INTEGER;
  result.ivalue = UNDEFINED_DATA;

  switch(op) {
    case PLUS: result.ivalue = lvalue + rvalue; break;
    case MINUS: result.ivalue = lvalue - rvalue; break;
    case TIMES: result.ivalue = lvalue * rvalue; break;
    case DIVIDE: 
      if(rvalue != 0) {
        result.ivalue = lvalue / rvalue;
      } else {
        fprintf(stderr, "Error: Division by 0 (%d/%d)\n", lvalue, rvalue);
      }
      break;
    case MOD: result.ivalue = lvalue % rvalue; break;
    case POW: result.ivalue = pow(lvalue, rvalue); break;
    default:
      fprintf(stderr, "Error: Invalid operation `%d` for integer arithmetic\n", op);
  }

  return result;
}

value_info float_arithmetic(float lvalue, op_type op, float rvalue) {
  value_info result;
  result.type = FLOAT;
  result.fvalue = UNDEFINED_DATA;

  switch(op) {
    case PLUS: result.fvalue = lvalue + rvalue; break;
    case MINUS: result.fvalue = lvalue - rvalue; break;
    case TIMES: result.fvalue = lvalue * rvalue; break;
    case DIVIDE: 
      if(rvalue != 0) {
        result.fvalue = lvalue / rvalue;
      } else {
        fprintf(stderr, "Error: Division by 0 (%f/%f)\n", lvalue, rvalue);
      }
      break;
    case MOD: result.fvalue = fmod(lvalue, rvalue); break;
    case POW: result.fvalue = pow(lvalue, rvalue); break;
    default:
      fprintf(stderr, "Error: Invalid operation `%d` for float arithmetic\n", op);
  }

  return result;
}

value_info concat(value_info *loperand, value_info *roperand) {
  value_info result;
  result.type = STRING;

	char lstr[STR_MAX_LENGTH];
	char rstr[STR_MAX_LENGTH];
	val2str(loperand, lstr, sizeof(lstr));
	val2str(roperand, rstr, sizeof(rstr));

  size_t len = strlen(lstr) + strlen(rstr) + 1;
  result.svalue = malloc(len);
  if(result.svalue != NULL) {
    strcpy(result.svalue, lstr);
    strcat(result.svalue, rstr);
  }

  return result;
}

value_info assign(identifier_t* id, value_info value) {
	char str_value[STR_MAX_LENGTH];
	val2str(&value, str_value, sizeof(str_value));
  log_message(LOG_INFO, "Assigned value '%s' to identifier %s", str_value, id->name);
  id->value = value;
	id->type = value.type;
  sym_enter(id->name, id);
  return value;
}

value_info identifier_value(identifier_t id) {
  identifier_t result;
  result.value.type = UNDEFINED_DATA;
  if(sym_lookup(id.name, &result) == SYMTAB_NOT_FOUND) {
    char format[] = "semantic error, cannot find declaration of identifier '%s', first use in line: %d";
    log_message(LOG_ERROR, format, id.name, id.line);
  }

  char format[] = "Retrieved value of identifier '%s': '%s'";
  char str_value[STR_MAX_LENGTH];
  val2str(&result.value, str_value, sizeof(str_value));
  log_message(LOG_INFO, format, id.name, str_value);
  return result.value;
}
