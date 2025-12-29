#include "headers/arithmeticExpression.h"

literal arithmeticExpression(literal* loperand, op_type op, literal* roperand)
{
#ifdef LOG
  char lvalue[STR_MAX_LENGTH];
  literal2str(lvalue, sizeof(lvalue), loperand);
  char rvalue[STR_MAX_LENGTH];
  literal2str(rvalue, sizeof(rvalue), roperand);

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
    char* svalue = isString(loperand)? loperand->svalue : roperand->svalue;
    switch(op)
    {
      case E_PLUS:    result = arithmeticExpressionConcat(loperand, roperand); break;
      case E_LEN:     result = createIntegerLiteral(strlen(svalue)); break;
      default:
        log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION,
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
{ 
	if(id->type == E_NULL_TYPE)
  { log_message(LOG_ERROR, ERR_MSG_IDENTIFIER_NOT_DECLARED, id->name, id->lineno); }
	else if(id->type != E_INTEGER || id->type != E_FLOAT)
	{ log_message(LOG_ERROR, ERR_MSG_INVALID_IDENTIFIER_TYPE, id->type, id->lineno); }
  return getIdentifierValue(id);
}

literal arithmeticExpressionConcat(literal* loperand, literal* roperand)
{
  literal result = createEmptyLiteral();
  result.type = E_STRING;

  char lvalue[STR_MAX_LENGTH];
  literal2str(lvalue, sizeof(lvalue), loperand);
  char rvalue[STR_MAX_LENGTH];
  literal2str(rvalue, sizeof(rvalue), roperand);

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


literal arithmeticExpressionFunction(funct_id funct_id, ...)
{
  va_list args;
  va_start(args, funct_id);

  literal result;
  switch(funct_id)
  {
    case E_SIN:
    case E_COS:
    case E_TAN:
      literal *arg1trig = va_arg(args, literal*);
      result = arithmeticExpressionTrigonometry(funct_id, arg1trig);
      break;
    case E_LEN:
      literal *arg1len = va_arg(args, literal*);
      result = arithmeticExpressionLen(arg1len);
      break;
    case E_SUBSTR:
      literal *arg1substr = va_arg(args, literal*);
      literal *arg2substr = va_arg(args, literal*);
      literal *arg3substr = va_arg(args, literal*);
      result = arithmeticExpressionSubstr(arg1substr, arg2substr, arg3substr);
      break;
    default: log_message(LOG_ERROR, ERR_MSG_INVALID_FUNCTION_IDENTIFIER, funct_id);
  }

  va_end(args);
  return result;
}

literal arithmeticExpressionTrigonometry(funct_id funct_id, literal* operand)
{
  float fvalue = isInteger(operand)? (float)operand->ivalue: operand->fvalue;
  switch(funct_id)
  {
    case E_SIN: return createFloatLiteral(sin(fvalue));
    case E_COS: return createFloatLiteral(cos(fvalue));
    case E_TAN: return createFloatLiteral(tan(fvalue));
    default: log_message(LOG_ERROR, ERR_MSG_INVALID_FUNCTION_IDENTIFIER, funct_id);
  }
  return createEmptyLiteral();
}

literal arithmeticExpressionLen(literal* string)
{
  literal result = createEmptyLiteral();
  
  if(!isString(string))
  { log_message(LOG_ERROR, ERR_MSG_INVALID_ARGUMENT_TYPE, type2str(string->type), 1, "substr"); }
  else 
  { result = createIntegerLiteral(strlen(string->svalue)); }

  return result;
}

literal arithmeticExpressionSubstr(literal* string, literal* start, literal* len)
{  
  if(!isString(string))
  { log_message(LOG_ERROR, ERR_MSG_INVALID_ARGUMENT_TYPE, type2str(string->type), 1, "substr", type2str(E_STRING)); }
  else if(!isInteger(start))
  { log_message(LOG_ERROR, ERR_MSG_INVALID_ARGUMENT_TYPE, type2str(start->type), 2, "substr", type2str(E_INTEGER)); }
  else if(!isInteger(len))
  { log_message(LOG_ERROR, ERR_MSG_INVALID_ARGUMENT_TYPE, type2str(len->type), 3, "substr", type2str(E_INTEGER)); }

  return createStringLiteral(strndup(string->svalue + start->ivalue, len->ivalue), len->ivalue);
}
