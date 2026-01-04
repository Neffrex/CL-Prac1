#include "headers/booleanExpression.h"

/**
 * Converts a boolean value to a literal.
 */
literal booleanExpressionToLiteral(bool value) 
{ return createBooleanLiteral(value); }

/**
 * Performs a boolean operation on two boolean operands.
 */
bool booleanExpression(bool loperand, op_type op, bool roperand)
{ 
  log_message(LOG_INFO, LOG_MSG_BOOLEAN_BINARY_EXPRESSION, S_BOOLEAN, op2str(op), S_BOOLEAN, bool2str(loperand), op2str(op), bool2str(roperand));
  
  bool result = false;
  switch(op)
  {
    case OP_OR:    result = loperand || roperand; break;
    case OP_AND:   result = loperand && roperand; break;
    default: 
    {
      log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION, 
        type2str(TYPE_BOOLEAN), op2str(op), type2str(TYPE_BOOLEAN)
      );
    }
  }

  log_message(LOG_INFO, LOG_MSG_END_OF_BOOLEAN_EXPRESSION, bool2str(result));
  return result;
}

/**
 * Performs a unary boolean operation on a boolean operand.
 */
bool booleanExpressionUnary(op_type op, bool operand) 
{ 
  log_message(LOG_INFO, LOG_MSG_BOOLEAN_UNARY_EXPRESSION, op2str(op), S_BOOLEAN, op2str(op), bool2str(operand));

  bool result = false;
  switch(op)
  {
    case OP_NOT: result = !operand; break;
    default:    log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION, type2str(TYPE_BOOLEAN), op2str(op), type2str(TYPE_BOOLEAN));
  }

  log_message(LOG_INFO, LOG_MSG_END_OF_BOOLEAN_EXPRESSION, bool2str(result));
  return result;
}

/**
 * Performs a boolean OR operation.
 */
bool booleanExpressionOr(bool loperand, bool roperand) 
{ return booleanExpression(loperand, OP_OR, roperand); }

/**
 * Performs a boolean AND operation.
 */
bool booleanExpressionAnd(bool loperand, bool roperand) 
{ return booleanExpression(loperand, OP_AND, roperand); }

/**
 * Performs a boolean NOT operation.
 */
bool booleanExpressionNot(bool operand)
{ return booleanExpressionUnary(OP_NOT, operand); }

/**
 * Returns a boolean TRUE literal.
 */
bool booleanExpressionTrue() 
{ return true; }

/**
 * Returns a boolean FALSE literal.
 */
bool booleanExpressionFalse() 
{ return false; }

/**
 * Performs a relational operation on two literals.
 */
bool relationalExpression(literal* loperand, op_type op, literal* roperand) 
{
  char* lsvalue = literal2str(loperand);
  char* rsvalue = literal2str(roperand);
  log_message(LOG_INFO, LOG_MSG_RELATIONAL_EXPRESSION, type2str(loperand->type), op2str(op), type2str(roperand->type), lsvalue, op2str(op), rsvalue);
  free(lsvalue); free(rsvalue);

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
    default: log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION, type2str(loperand->type), op2str(op), type2str(roperand->type));
  }

  log_message(LOG_INFO, LOG_MSG_END_OF_RELATIONAL_EXPRESSION, result? S_TRUE : S_FALSE);
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