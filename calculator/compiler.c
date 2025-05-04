#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

const char* op_map[] = { "+", "-", "*", "/", "=", ">", ">=", "<", "<=", "<>" };

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
            switch (value->mode) {
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
        default:
            fprintf(stderr, "Error: Undefined type: %d", value->type);
            break;
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
            ptr += 2; // Move past "%v"
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

value_info arithmetic(value_info loperand, const op_type op, value_info roperand) {
  // Result object initialization
  value_info result;
  result.type = UNDEFINED_DATA;
  result.svalue = NULL;
  result.ivalue = 0;
  result.fvalue = 0.0f;
  result.bvalue = false;

  bool is_integer_arithmetic = (loperand.type == INTEGER && roperand.type == INTEGER);
  bool is_float_arithmetic =
    (loperand.type == FLOAT || loperand.type == INTEGER)
    && (roperand.type == FLOAT || roperand.type == INTEGER);
  bool is_string_concat = (op == PLUS)
    && (loperand.type == STRING || loperand.type == INTEGER || loperand.type == FLOAT)
    && (roperand.type == STRING || roperand.type == INTEGER || roperand.type == FLOAT);

  if (is_integer_arithmetic) {
    result = integer_arithmetic(loperand.ivalue, op, roperand.ivalue);
  } else if (is_float_arithmetic) {
    if(loperand.type == INTEGER) loperand.fvalue = (float)loperand.ivalue;
    if(roperand.type == INTEGER) roperand.fvalue = (float)roperand.ivalue;
    result = float_arithmetic(loperand.fvalue, op, roperand.fvalue);
  } else if (is_string_concat) {
    result = concat(loperand, roperand);
  } else {
    fprintf(stderr, "Error: Unsupported operation or mismatched types\n");
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

value_info concat(value_info loperand, value_info roperand) {
  value_info result;
  result.type = STRING;

  char *lstr = val2str(loperand);
  char *rstr = val2str(roperand);

  size_t len = strlen(lstr) + strlen(rstr) + 1;
  result.svalue = malloc(len);
  if(result.svalue != NULL) {
    strcpy(result.svalue, lstr);
    strcat(result.svalue, rstr);
  }

  free(lstr);
  free(rstr);

  return result;
}

char* val2str(value_info value) {
  char buffer[64];

  switch (value.type) {
    case INTEGER:
      snprintf(buffer, sizeof(buffer), "%d", value.ivalue);
      return strdup(buffer);
    case FLOAT:
      snprintf(buffer, sizeof(buffer), "%.3f", value.fvalue);
      return strdup(buffer);
    case STRING:
      if(value.svalue == NULL) return strdup("");
      return strdup(value.svalue);
    default:
      return strdup("");
  }
}


value_info assign(identifier_t id, value_info value) {
  fprintf(stderr, "[!] LOG | assign()\n");
  id.value = value;
  sym_enter(id.name, &id);
  return value;
}

value_info identifier_value(identifier_t id) {
  fprintf(stderr, "[!] LOG | identifier_value()\n");
  identifier_t result;
  if(sym_lookup(id.name, &result) == SYMTAB_NOT_FOUND) {
    char err_msg[128];
    sprintf(err_msg, "Error: Cannot find `%s` declaration, first use in line: %d\n", id.name, id.line);
    yyerror(err_msg);
  }
  return result.value;
}
