#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compiler.h"

const char* op_map[] = { "+", "-", "*", "/", "==", ">", ">=", "<", "<=" };

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
            fprintf(stream, "%d", value->ivalue);
            break;
        case FLOAT:
            fprintf(stream, "%f", value->fvalue);
            break;
        case BOOLEAN:
            fprintf(stream, "%s", value->bvalue ? "true" : "false");
            break;
        default:
            fprintf(stream, "(undefined)");
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
  } else if(!strcmp(op, "==")) {
     return COMPARE;
  } else if(!strcmp(op, ">")) {
    return GREATER_THAN;
  } else if(!strcmp(op, ">=")) {
     return GREATER_EQUAL;
  } else if(!strcmp(op, "<")) {
    return LESS_THAN;
  } else if(!strcmp(op, "<=")) {
     return LESS_EQUAL;
  } else {
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
                fprintf(stderr, "Error: Division by zero\n");
                result.type = UNDEFINED_DATA;
            }
            break;
        default:
            fprintf(stderr, "Error: Unsupported operation for integers\n");
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
                fprintf(stderr, "Error: Division by zero\n");
                result.type = UNDEFINED_DATA;
            }
            break;
        default:
            fprintf(stderr, "Error: Unsupported operation for floats\n");
            result.type = UNDEFINED_DATA;
    }
    return result;
}

value_info handle_string_concatenation(const value_info loperand, const value_info roperand) {
    value_info result;
    result.type = STRING;
    size_t len = strlen(loperand.svalue) + strlen(roperand.svalue) + 1;

    result.svalue = (char*)malloc(len);
    if (result.svalue != NULL) {
        strcpy(result.svalue, loperand.svalue);
        strcat(result.svalue, roperand.svalue);
    } else {
        fprintf(stderr, "Error: Memory allocation failed for string concatenation\n");
        result.type = UNDEFINED_DATA;
    }

    return result;
}

value_info arithmetic(const value_info loperand, const operator_t operation, const value_info roperand) {
    // Result object initialization
    value_info result;
    result.type = UNDEFINED_DATA;
    result.svalue = NULL;
    result.ivalue = 0;
    result.fvalue = 0.0f;
    result.bvalue = 0;

    if (loperand.type == INTEGER && roperand.type == INTEGER) {
        result = handle_integer_arithmetic(loperand, operation.type, roperand);
    } else if ((loperand.type == FLOAT || loperand.type == INTEGER) &&
               (roperand.type == FLOAT || roperand.type == INTEGER)) {
        result = handle_float_arithmetic(loperand, operation.type, roperand);
    } else if (loperand.type == STRING && roperand.type == STRING && operation.type == PLUS) {
        result = handle_string_concatenation(loperand, roperand);
    } else {
        fprintf(stderr, "Error: Unsupported operation or mismatched types\n");
    }

    return result;
}
