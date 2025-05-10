#include "arithmeticExpression.h"

literal arithmeticExpression(literal* loperand, op_type op, literal* roperand)
{
#ifdef LOG
  char lvalue[STR_MAX_LENGTH];
  val2str(lvalue, sizeof(lvalue), E_DEC, loperand);
  char rvalue[STR_MAX_LENGTH];
  val2str(rvalue, sizeof(rvalue), E_DEC, roperand);

  log_message(LOG_INFO, LOG_MSG_ARITHMETIC_EXPRESSION,
    type2str(loperand->type), op2str(op), type2str(roperand->type),
    lvalue, op2str(op), rvalue);
#endif

  literal result = createEmptyLiteral();

  if(isInteger(loperand) && isInteger(roperand))
  { // Integer Arithmetic
    result.type = E_INTEGER;
    switch(op)
    {
      case E_PLUS:    result.ivalue = loperand->ivalue + roperand->ivalue; break;
      case E_MINUS:   result.ivalue = loperand->ivalue - roperand->ivalue; break;
      case E_TIMES:   result.ivalue = loperand->ivalue * roperand->ivalue; break;
      case E_DIVIDE:  result.ivalue = loperand->ivalue / roperand->ivalue; break;
      case E_MOD:     result.ivalue = loperand->ivalue % roperand->ivalue; break;
      case E_POW:     result.ivalue = (int)(pow(loperand->ivalue, roperand->ivalue)+0.5); break;
      default:
        log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION,
          type2str(loperand->type), op2str(op), type2str(roperand->type));
    }
  }
  else if(isNumber(loperand) && isNumber(roperand))
  { // Float Arthmetic
    result.type = E_FLOAT;
    double lvalue = isInteger(loperand)? (double)loperand->ivalue: (double)loperand->fvalue;
    double rvalue = isInteger(roperand)? (double)roperand->ivalue: (double)roperand->fvalue;
    double resultD;
    switch(op)
    {
      case E_PLUS:    resultD = lvalue + rvalue; break;
      case E_MINUS:   resultD = lvalue - rvalue; break;
      case E_TIMES:   resultD = lvalue * rvalue; break;
      case E_DIVIDE:  resultD = lvalue / rvalue; break;
      case E_POW:     resultD = pow(lvalue, rvalue); break;
      case E_MOD:     /* Operation not allowed */
      default:
        log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION,
          type2str(loperand->type), op2str(op), type2str(roperand->type));
    }
    result.fvalue = (float)resultD;
  }
  else if(isString(loperand) || isString(roperand))
  { // String Arithmetic
    if(op == E_PLUS)
    { result = arithmeticExpressionConcat(loperand, roperand); }
    else
    { log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION,
        type2str(loperand->type), op2str(op), type2str(roperand->type));
    }
  }
  else
  { // TYPE ERROR
    log_message(LOG_ERROR, ERR_MSG_INVALID_OPERAND_TYPES,
      type2str(loperand->type), op2str(op), type2str(roperand->type));
  }
  return result;
}

literal arithmeticExpressionIdentifier(identifier* id)
{ literal result = getIdentifierValue(id);
  if(isNullLiteral(&result))
  { log_message(LOG_ERROR, ERR_MSG_IDENTIFIER_NOT_DECLARED, id->name, id->lineno); }
  return result; 
}

literal arithmeticExpressionConcat(literal* loperand, literal* roperand)
{
  literal result = createEmptyLiteral();
  result.type = E_STRING;

  char lvalue[STR_MAX_LENGTH];
  val2str(lvalue, sizeof(lvalue), mode, loperand);
  char rvalue[STR_MAX_LENGTH];
  val2str(rvalue, sizeof(rvalue), mode, roperand);

  size_t len = strlen(lvalue) + strlen(rvalue) + 1;
  result.svalue = malloc(len);
  if(result.svalue != NULL)
  {
    strcpy(result.svalue, lvalue);
    strcat(result.svalue, rvalue);
  }
  
  return result;
}

literal arithmeticExpressionPlus(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, E_PLUS, roperand); }

literal arithmeticExpressionMinus(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, E_MINUS, roperand); }

literal arithmeticExpressionTimes(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, E_TIMES, roperand); }

literal arithmeticExpressionDivide(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, E_DIVIDE, roperand); }

literal arithmeticExpressionMod(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, E_MOD, roperand); }

literal arithmeticExpressionPow(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, E_POW, roperand); }

literal arithmeticExpressionNegate(literal* operand)
{ 
  literal result;
  if(isInteger(operand))
  { result = createIntegerLiteral(-operand->ivalue); }
  else if(isFloat(operand))
  { result = createFloatLiteral(-operand->fvalue); }
  else
  { // TYPE ERROR
    log_message(LOG_ERROR, ERR_MSG_INVALID_OPERAND_TYPE,
      op2str(E_NEGATE), type2str(operand->type));
  }
  return result;
}

literal arithmeticExpressionSin(literal* operand)
{
  float fvalue = isInteger(operand)? (float)operand->ivalue: operand->fvalue;
  return createFloatLiteral(sin(fvalue));
}

literal arithmeticExpressionCos(literal* operand)
{
  float fvalue = isInteger(operand)? (float)operand->ivalue: operand->fvalue;
  return createFloatLiteral(cos(fvalue));
}

literal arithmeticExpressionTan(literal* operand)
{
  float fvalue = isInteger(operand)? (float)operand->ivalue: operand->fvalue;
  return createFloatLiteral(tan(fvalue));
}
