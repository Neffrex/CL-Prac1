#pragma once


#define ERR_MSG_INVALID_ARGUMENT_TYPE "syntax error, invalid argument type %s for argument #%d on %s, expected %s\n"
#define ERR_MSG_INVALID_FUNCTION_IDENTIFIER "syntax error, invalid function identifier %d\n"

#define ERR_MSG_IDENTIFIER_NOT_DECLARED "syntax error, cannot find declaration of identifier '%s', first use in line %d\n"
#define ERR_MSG_UNSUPPORTED_OPERATION "syntax error, unsupported operation or mismatched types %s %s %s:\n\t'%s' %s '%s'\n"
#define ERR_MSG_INVALID_OPERAND_TYPES "syntax error, invalid operand types for: %s %s %s\n"
#define ERR_MSG_INVALID_OPERAND_TYPE "syntax error, invalid operand type %s for operation %s\n"

#define LOG_MSG_ASSIGN "Assigned %s value to identifier %s := %s"
#define LOG_MSG_GET_IDENTIFIER "Retrieved %s value of identifier %s <- %s"
#define LOG_MSG_ARITHMETIC_EXPRESSION "Arithmetic Expression %s %s %s: '%s' %s '%s'"
#define LOG_MSG_BOOLEAN_UNARY_EXPRESSION "Boolean Unary Expression %s %s: %s '%s'"
#define LOG_MSG_BOOLEAN_BINARY_EXPRESSION "Boolean Expression %s %s %s: '%s' %s '%s'"
#define LOG_MSG_RELATIONAL_EXPRESSION "Relational Expression %s %s %s: '%s' %s '%s'"


#define LOG_MSG_END_OF_BOOLEAN_EXPRESSION "----- End of Boolean Expression: %s -----\n"
#define LOG_MSG_END_OF_RELATIONAL_EXPRESSION "----- End of Relational Expression: %s -----\n"
#define LOG_MSG_END_OF_STATEMENT "--------------- End of statement ---------------\n"
#define LOG_MSG_END_OF_PROGRAM "\n---------------------------------------------\n*************** End of program ***************\n----------------------------------------------\n"
