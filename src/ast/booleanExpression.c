#include "headers/booleanExpression.h"

literal booleanExpressionToLiteral(bool value) 
{ return createBooleanLiteral(value); }

bool booleanExpressionIdentifier(identifier* id)
{ literal result = getIdentifierValue(id);
  if(isNullLiteral(&result))
  { log_message(LOG_ERROR, ERR_MSG_IDENTIFIER_NOT_DECLARED, id->name, id->lineno); }
  return result.bvalue;
}

bool booleanExpression(bool loperand, op_type op, bool roperand)
{ 
#ifdef LOG
  log_message(LOG_INFO, LOG_MSG_BOOLEAN_EXPRESSION,
    type2str(E_BOOLEAN), op2str(op), type2str(E_BOOLEAN),
    loperand? "true":"false", op2str(op), roperand?"true":"false");
#endif
  
  switch(op)
  {
    case E_OR:    return loperand || roperand;
    case E_AND:   return loperand && roperand;
    case E_NOT:   return !roperand;
    default:
        log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION, type2str(E_BOOLEAN), op2str(op), type2str(E_BOOLEAN));
        return false;
  }
}

bool booleanExpressionOr(bool loperand, bool roperand) 
{ return booleanExpression(loperand, E_OR, roperand); }

bool booleanExpressionAnd(bool loperand, bool roperand) 
{ return booleanExpression(loperand, E_AND, roperand); }

bool booleanExpressionNot(bool operand)
{ return booleanExpression(booleanExpressionFalse(), E_NOT, operand); }

bool booleanExpressionTrue() 
{ return true; }

bool booleanExpressionFalse() 
{ return false; }


bool relationalExpression(literal* loperand, op_type op, literal* roperand) 
{

#ifdef LOG
  char lvalue[STR_MAX_LENGTH];
  val2str(lvalue, sizeof(lvalue), mode, loperand);
  char rvalue[STR_MAX_LENGTH];
  val2str(rvalue, sizeof(rvalue), mode, roperand);
  log_message(LOG_INFO, LOG_MSG_RELATIONAL_EXPRESSION,
    type2str(loperand->type), op2str(op), type2str(roperand->type),
    lvalue, op2str(op), rvalue);
#endif

  bool result = false;
  if(isNumber(loperand) && isNumber(roperand)) 
  {
    double lvalue = isInteger(loperand)? (double)loperand->ivalue : (double)loperand->fvalue;
    double rvalue = isInteger(roperand)? (double)roperand->ivalue : (double)roperand->fvalue;
    switch (op)
    {
      case E_EQUALS:          result = lvalue == rvalue; break;
      case E_GREATER_THAN:    result = lvalue >  rvalue; break;
      case E_GREATER_EQUALS:  result = lvalue >= rvalue; break;
      case E_LOWER_THAN:      result = lvalue <  rvalue; break;
      case E_LOWER_EQUALS:    result = lvalue <= rvalue; break;
      case E_NOT_EQUALS:      result = lvalue != rvalue; break;
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
#ifdef LOG
  log_message(LOG_INFO, "***** End of Relational Expression: %s *****", result? "true": "false");
#endif
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

