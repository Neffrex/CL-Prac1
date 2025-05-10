#pragma once

#define ERR_MSG_IDENTIFIER_NOT_DECLARED "syntax error, cannot find declaration of identifier '%s', first use in line %d\n"
#define ERR_MSG_UNSUPPORTED_OPERATION "syntax error, unsupported operation or mismatched types %s %s %s:\n\t'%s' %s '%s'\n"
#define ERR_MSG_INVALID_OPERAND_TYPES "syntax error, invalid operand types for: %s %s %s\n"
#define ERR_MSG_INVALID_OPERAND_TYPE "syntax error, invalid operand type %s for operation %s\n"

#define LOG_MSG_ASSIGN "Assigned value '%s' to identifier '%s'\n"
#define LOG_MSG_GET_IDENTIFIER "Retrieved value '%s' of identifier '%s'\n"
