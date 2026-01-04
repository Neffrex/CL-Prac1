#include "headers/booleanExpression.h"

// ╭───────────────────────────╮ //
// │ BOOLEAN CONVERSION        │ //
// ╰───────────────────────────╯ //

literal booleanExpressionToLiteral(bool value) 
{ return createBooleanLiteral(value); }


// ╭──────────────────╮ //
// │ BOOLEAN LITERALS │ //
// ╰──────────────────╯ //

bool booleanExpressionTrue() 
{ return true; }

bool booleanExpressionFalse() 
{ return false; }


// ╭───────────────────────────╮ //
// │ UNARY BOOLEAN EXPRESSIONS │ //
// ╰───────────────────────────╯ //


void logBooleanExpressionUnaryEntry(op_type op, bool operand) 
{ log_message(LOG_INFO, LOG_MSG_BOOLEAN_UNARY_EXPRESSION, op2str(op), bool2str(operand), S_BOOLEAN); }

void logBooleanExpressionUnaryExit(bool result) 
{ log_message(LOG_INFO, LOG_MSG_END_OF_BOOLEAN_EXPRESSION, bool2str(result)); }

bool booleanExpressionUnary(op_type op, bool operand) 
{ 
  logBooleanExpressionUnaryEntry(op, operand);

  bool result = false;
  switch(op)
  {
    case OP_NOT: result = !operand; break;
    default:    halt(ERR_MSG_INVALID_OPERATION, type2str(TYPE_BOOLEAN), op2str(op), type2str(TYPE_BOOLEAN));
  }

  logBooleanExpressionUnaryExit(result);
  return result;
}

bool booleanExpressionNot(bool operand)
{ return booleanExpressionUnary(OP_NOT, operand); }


// ╭────────────────────────────╮ //
// │ BINARY BOOLEAN EXPRESSIONS │ //
// ╰────────────────────────────╯ //

void logBooleanBinaryExpressionEntry(bool loperand, op_type op, bool roperand)
{ log_message(LOG_INFO, LOG_MSG_BOOLEAN_BINARY_EXPRESSION, bool2str(loperand), S_BOOLEAN, op2str(op), bool2str(roperand), S_BOOLEAN); }

void logBooleanBinaryExpressionExit(bool result)
{ log_message(LOG_INFO, LOG_MSG_END_OF_BOOLEAN_EXPRESSION, bool2str(result)); }

bool booleanBinaryExpression(bool loperand, op_type op, bool roperand)
{ 
  logBooleanBinaryExpressionEntry(loperand, op, roperand);

  bool result = false;
  switch(op)
  {
    case OP_OR:    result = loperand || roperand; break;
    case OP_AND:   result = loperand && roperand; break;
    default: halt(ERR_MSG_INVALID_OPERATION, type2str(TYPE_BOOLEAN), op2str(op), type2str(TYPE_BOOLEAN));
  }

  logBooleanBinaryExpressionExit(result);
  return result;
}

bool booleanExpressionOr(bool loperand, bool roperand) 
{ return booleanBinaryExpression(loperand, OP_OR, roperand); }

bool booleanExpressionAnd(bool loperand, bool roperand) 
{ return booleanBinaryExpression(loperand, OP_AND, roperand); }


// ╭─────────────────────────────╮ //
// │ RELATIONAL EXPRESSIONS      │ //
// ╰─────────────────────────────╯ //

void logRelationalExpressionEntry(literal* loperand, op_type op, literal* roperand)
{
  char* lvalue = literal2str(loperand);
  char* rvalue = literal2str(roperand);
  log_message(LOG_INFO, LOG_MSG_RELATIONAL_EXPRESSION, lvalue, type2str(loperand->type), op2str(op), rvalue, type2str(roperand->type));
  free(lvalue); free(rvalue);
}

void logRelationalExpressionExit(bool result)
{
  log_message(LOG_INFO, LOG_MSG_END_OF_RELATIONAL_EXPRESSION, bool2str(result));
}

bool relationalExpression(literal* loperand, op_type op, literal* roperand) 
{
  logRelationalExpressionEntry(loperand, op, roperand);

  bool result = false;
  if(!isNumber(loperand) || !isNumber(roperand))
  { halt(ERR_MSG_INVALID_OPERAND_TYPES, type2str(loperand->type), op2str(op), type2str(roperand->type)); }
  
  double lvalue = isInteger(loperand) ? (double) loperand->ivalue : (double)loperand->fvalue;
  double rvalue = isInteger(roperand) ? (double) roperand->ivalue : (double)roperand->fvalue;
  switch (op)
  {
    case OP_EQUALS:          result = lvalue == rvalue; break;
    case OP_GREATER_THAN:    result = lvalue >  rvalue; break;
    case OP_GREATER_EQUALS:  result = lvalue >= rvalue; break;
    case OP_LOWER_THAN:      result = lvalue <  rvalue; break;
    case OP_LOWER_EQUALS:    result = lvalue <= rvalue; break;
    case OP_NOT_EQUALS:      result = lvalue != rvalue; break;
    default: halt(ERR_MSG_INVALID_OPERATION, type2str(loperand->type), op2str(op), type2str(roperand->type));
  }

  logRelationalExpressionExit(result);
  return result;
}

bool relationalExpressionEquals(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, OP_EQUALS, roperand); }

bool relationalExpressionGreaterThan(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, OP_GREATER_THAN, roperand); }

bool relationalExpressionGreaterEquals(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, OP_GREATER_EQUALS, roperand); }

bool relationalExpressionLowerThan(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, OP_LOWER_THAN, roperand); }

bool relationalExpressionLowerEquals(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, OP_LOWER_EQUALS, roperand); }

bool relationalExpressionNotEquals(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, OP_NOT_EQUALS, roperand); }