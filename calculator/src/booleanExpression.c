#include "booleanExpression.h"

literal booleanExpressionToLiteral(bool value) 
{ return createBooleanLiteral(value); }

bool booleanExpressionIdentifier(identifier* id)
{ return getIdentifierValue(id).bvalue; }

bool booleanExpressionOr(bool loperand, bool roperand) 
{ return loperand || roperand; }

bool booleanExpressionAnd(bool loperand, bool roperand) 
{ return loperand && roperand; }

bool booleanExpressionNot(bool operand)
{ return !operand; }

bool booleanExpressionTrue() 
{ return true; }

bool booleanExpressionFalse() 
{ return false; }


bool relationalExpression(literal* loperand, op_type op, literal* roperand) 
{
  bool result = false;
  if(isNumber(loperand) && isNumber(roperand)) 
  {
    double lvalue = isInteger(loperand)? (double)loperand->ivalue : (double)loperand->fvalue;
    double rvalue = isInteger(roperand)? (double)roperand->ivalue : (double)roperand->fvalue;
    switch (op)
    {
      case E_EQUALS:          result = lvalue == rvalue;
      case E_GREATER_THAN:    result = lvalue >  rvalue;
      case E_GREATER_EQUALS:  result = lvalue >= rvalue;
      case E_LOWER_THAN:      result = lvalue <  rvalue;
      case E_LOWER_EQUALS:    result = lvalue <= rvalue;
      case E_NOT_EQUALS:      result = lvalue != rvalue;
      default: 
        log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION,
          type2str(loperand->type), op2str(op), type2str(roperand->type));
    }
  }
  else
  {
    log_message(LOG_ERROR, ERR_MSG_INVALID_OPERAND_TYPES,
      type2str(loperand->type), op2str(op), type2str(loperand->type));
  }
  return result;
}

bool relationalExpressionEquals(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, E_EQUALS, roperand); }

bool relationalExpressionGreaterThan(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, E_GREATER_THAN, roperand); }

bool relationalExpressionGreaterEquals(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, E_GREATER_EQUALS, roperand); }

bool relationalExpressionLowerThan(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, E_LOWER_THAN, roperand); }

bool relationalExpressionLowerEquals(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, E_LOWER_EQUALS, roperand); }

bool relationalExpressionNotEquals(literal* loperand, literal* roperand)
{ return relationalExpression(loperand, E_NOT_EQUALS, roperand); }

