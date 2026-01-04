#pragma once


#define ERR_MSG_INVALID_ARGUMENT_TYPE "[Semantic Error] Invalid argument type %s for argument #%d on %s, expected %s\n"
#define ERR_MSG_INVALID_FUNCTION_IDENTIFIER "[Semantic Error] Invalid function identifier %d\n"

#define ERR_MSG_IDENTIFIER_NOT_DECLARED "[Semantic Error] Cannot find declaration of identifier '%s', first use in line %d\n"
#define ERR_MSG_INVALID_OPERATION "[Semantic Error] Invalid Operation: %s %s %s\n"
#define ERR_MSG_INVALID_OPERAND_TYPES "[Semantic Error] Invalid operand types for: %s %s %s\n"
#define ERR_MSG_INVALID_OPERAND_TYPE "[Semantic Error] Invalid operand type %s for operation %s\n"

#define ERR_MSG_INVALID_IDENTIFIER_TYPE "[Semantic Error] Invalid identifier type <%s> for operation <%s>"
#define ERR_MSG_IDENTIFIER_ALREADY_DECLARED "[Semantic Error] Identifier already declared: Identifier <%s> was already declared in line <%d>"
#define ERR_MSG_TYPE_MISMATCH "[Semantic Error] Type mismatch: Cannot assign value <%s> with type <%s> to identifier <%s> with type <%s>\n"

#define ERR_MSG_MEMORY_ALLOCATION_FAILED "[Fatal Error] Memory allocation failed\n"
#define ERR_MSG_UNDEFINED_SEQUENCE "[Lexical Error] undefined sequence: %s\n"

// LITERALS
#define LOG_MSG_LITERAL_VALUE "| ◄ Parsed literal <%s>:%s"

// IDENTIFIERS
#define LOG_MSG_IDENTIFIER_RETRIEVED "| ◄ Retrieved identifier %s = <%s>:%s"
#define LOG_MSG_IDENTIFIER_DECLARED "├─── Declared identifier %s:%s"
#define LOG_MSG_IDENTIFIER_ASSIGNED "├─── Assigned identifier %s ← <%s>:%s"

// ARITHMETIC EXPRESSIONS
#define LOG_MSG_ARITHMETIC_EXPRESSION "| ■ Arithmetic Expression → <%s>:%s %s <%s>:%s"
#define LOG_MSG_END_OF_ARITHMETIC_EXPRESSION "│ ╰─ End of Arithmetic Expression: <%s>"

// BOOLEAN EXPRESSIONS
#define LOG_MSG_BOOLEAN_UNARY_EXPRESSION "│ ■ Boolean Expression → %s <%s>:%s"
#define LOG_MSG_BOOLEAN_BINARY_EXPRESSION "│ ■ Boolean Expression → <%s>:%s %s <%s>:%s"
#define LOG_MSG_END_OF_BOOLEAN_EXPRESSION "│ ╰─ End of Boolean Expression: <%s>"

// RELATIONAL EXPRESSIONS
#define LOG_MSG_RELATIONAL_EXPRESSION "| Relational Expression | <%s>:%s %s <%s>:%s"
#define LOG_MSG_END_OF_RELATIONAL_EXPRESSION "│ ╰─ End of Relational Expression: <%s>\n"
// END OF STATEMENTS/PROGRAM
#define LOG_MSG_END_OF_STATEMENT "╰┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉ Line %d: End of statement ┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n"
#define LOG_MSG_END_OF_PROGRAM "╰┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉ Line %d: End of program ┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉┉\n"
