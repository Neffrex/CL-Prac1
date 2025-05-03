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
                    fprintf(stream, "%o", value->ivalue);
                    break;
                case HEX:
                    fprintf(stream, "%x", value->ivalue);
                    break;
                case BIN:
                    // TODO: Fix Binary Representation
                    fprintf(stream, "%x", value->ivalue);
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
            fprintf(stream, "(undefined:%d)", value->type);
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

op_type operation_type(const char* op) {
  if(!strcmp(op, "+")) {
    return PLUS;
  } else if(!strcmp(op, "-")) {
    return MINUS;
  } else if(!strcmp(op, "*")) {
    return TIMES;
  } else if(!strcmp(op, "/")) {
    return DIVIDE;
  } else if(!strcmp(op, "=")) {
     return EQUALS;
  } else if(!strcmp(op, ">")) {
    return GREATER_THAN;
  } else if(!strcmp(op, ">=")) {
     return GREATER_EQUALS;
  } else if(!strcmp(op, "<")) {
    return LOWER_THAN;
  } else if(!strcmp(op, "<=")) {
    return LOWER_EQUALS;
  } else if(!strcmp(op, "<>")) {
    return NOT_EQUALS;
  } else{
    return UNDEFINED_OP;
  }
}

value_info handle_integer_arithmetic(const value_info loperand, const op_type op, const value_info roperand) {
    value_info result;
    result.type = INTEGER;
    result.svalue = NULL;

    switch (op) {
        case PLUS: result.ivalue = loperand.ivalue + roperand.ivalue; break;
        case MINUS: result.ivalue = loperand.ivalue - roperand.ivalue; break;
        case TIMES: result.ivalue = loperand.ivalue * roperand.ivalue; break;
        case DIVIDE:
            if (roperand.ivalue != 0) {
                result.ivalue = loperand.ivalue / roperand.ivalue;
            } else {
                fprintf(stderr, "Error: Division by zero `%d/%d`\n", loperand.ivalue, roperand.ivalue);
                result.type = UNDEFINED_DATA;
            }
            break;
        default:
            fprintf(stderr, "Error: Unsupported operation `%d` for integers\n", op);
            result.type = UNDEFINED_DATA;
    }
    return result;
}

value_info handle_float_arithmetic(const value_info loperand, const op_type op, const value_info roperand) {
    value_info result;
    result.type = FLOAT;
    result.svalue = NULL;

    float left = (loperand.type == INTEGER) ? loperand.ivalue : loperand.fvalue;
    float right = (roperand.type == INTEGER) ? roperand.ivalue : roperand.fvalue;

    switch (op) {
        case PLUS: result.fvalue = left + right; break;
        case MINUS: result.fvalue = left - right; break;
        case TIMES: result.fvalue = left * right; break;
        case DIVIDE:
            if (right != 0) {
                result.fvalue = left / right;
            } else {
                fprintf(stderr, "Error: Division by zero `%f/%f`\n", left, right);
                result.type = UNDEFINED_DATA;
            }
            break;
        default:
            fprintf(stderr, "Error: Unsupported operation for floats\n");
            result.type = UNDEFINED_DATA;
    }
    return result;
}


value_info cast(value_info value, data_type type) {
  value_info result;
  result.svalue = "";
  result.ivalue = 0;
  result.fvalue = 0.0f;
  result.bvalue = false;
  result.type = type;

  if(value.type == STRING) {
    switch (type) {
      case STRING: result.svalue = strdup(value.svalue); break;
      case INTEGER: {
        result.svalue = malloc(16 * sizeof(value.ivalue));
				if (result.svalue != NULL) {
        	sprintf(result.svalue, "%i", value.ivalue);
				} else {
    			fprintf(stderr, "Error: Memory allocation failed for string concatenation\n");
			    result.type = UNDEFINED_DATA;		
				}
        break;
      }
      case FLOAT: {
				int flen = snprintf(NULL, 0, "%g", value.fvalue);
        result.svalue = malloc(flen + 1);
  			if (result.svalue != NULL) {
	        sprintf(result.svalue, "%g", value.fvalue);
				} else {
    			fprintf(stderr, "Error: Memory allocation failed for string concatenation\n");
			    result.type = UNDEFINED_DATA;		
				}
        break;
      }
      case BOOLEAN: result.svalue = (value.bvalue) ? "true" : "false"; break;
      default: result.type = UNDEFINED_DATA;
    }
  } else if(value.type == INTEGER) {
    switch (type) {
      case STRING: result.ivalue = atoi(value.svalue); break;
      case INTEGER: result.ivalue = value.ivalue; break;
      case FLOAT: result.ivalue = (int)value.fvalue; break;
      case BOOLEAN: result.ivalue = result.bvalue; break;
      default: result.type = UNDEFINED_DATA;
    }
  } else if (value.type == FLOAT) {
    switch (type) {
      case STRING: result.fvalue = atof(value.svalue); break;
      case INTEGER: result.fvalue = (float)value.ivalue; break;
      case FLOAT: result.fvalue = value.fvalue; break;
      case BOOLEAN: result.fvalue = (float)result.bvalue; break;
      default: result.type = UNDEFINED_DATA;
    }
  } else if (value.type == BOOLEAN) {
    switch (type) {
      case STRING: result.bvalue = value.svalue == "true" ? true : false; break;
      case INTEGER: result.bvalue = !!value.ivalue; break;
      case FLOAT: result.bvalue = !!((int)value.fvalue); break;
      case BOOLEAN: result.bvalue = result.bvalue; break;
      default: result.type = UNDEFINED_DATA;
    }
  } else {
    result.type = UNDEFINED_DATA;
  };

  return result;
}

value_info handle_string_concatenation(const value_info loperand, const value_info roperand) {
  value_info result;
  result.svalue = "";
  result.ivalue = 0;
  result.fvalue = 0.0f;
  result.bvalue = false;
  result.type = STRING;


	if(loperand.type == BOOLEAN || roperand.type == BOOLEAN) {
		result.type = UNDEFINED_DATA;
		return result;
	}

	value_info loper = cast(loperand, STRING);
	value_info roper = cast(roperand, STRING);
	if(loper.type == UNDEFINED_DATA || roper.type == UNDEFINED_DATA) {
		result.type = UNDEFINED_DATA;
		return result;
	}

  size_t len = strlen(loper.svalue) + strlen(roper.svalue) + 1;
  result.svalue = (char*)malloc(len);
  if (result.svalue != NULL) {
    strcpy(result.svalue, loper.svalue);
    strcat(result.svalue, roper.svalue);
  } else {
    fprintf(stderr, "Error: Memory allocation failed for string concatenation\n");
    result.type = UNDEFINED_DATA;
  }

  return result;
}

value_info arithmetic(const value_info loperand, const op_type op, const value_info roperand) {
    // Result object initialization
    value_info result;
    result.type = UNDEFINED_DATA;
    result.svalue = NULL;
    result.ivalue = 0;
    result.fvalue = 0.0f;
    result.bvalue = false;

    if (loperand.type == INTEGER && roperand.type == INTEGER) {
        result = handle_integer_arithmetic(loperand, op, roperand);
    } else if ((loperand.type == FLOAT || loperand.type == INTEGER) &&
               (roperand.type == FLOAT || roperand.type == INTEGER)) {
        result = handle_float_arithmetic(loperand, op, roperand);
    } else if ((loperand.type == STRING || roperand.type == STRING) && op == PLUS) {
        result = handle_string_concatenation(loperand, roperand);
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

