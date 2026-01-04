#include "headers/arithmeticExpression.h"

void logArithmeticExpressionEntry(literal* loperand, op_type op, literal* roperand) 
{
  char* lvalue = literal2str(loperand);
  char* rvalue = literal2str(roperand);

  log_message(LOG_INFO, LOG_MSG_ARITHMETIC_EXPRESSION, type2str(loperand->type), op2str(op), type2str(roperand->type), lvalue, op2str(op), rvalue);
  free(lvalue); free(rvalue);  
}

void logArithmeticExpressionExit(literal* loperand, op_type op, literal* roperand, literal result) 
{
  char* lvalue = literal2str(loperand);
  char* rvalue = literal2str(roperand);
  char* resvalue = literal2str(&result);

  log_message(LOG_INFO, LOG_MSG_ARITHMETIC_EXPRESSION_RESULT, type2str(loperand->type), op2str(op), type2str(roperand->type), lvalue, op2str(op), rvalue, type2str(result.type), resvalue);
  free(lvalue); free(rvalue); free(resvalue); 
}

literal arithmeticExpression(literal* loperand, op_type op, literal* roperand)
{
  literal result = createEmptyLiteral();
  logArithmeticExpressionEntry(loperand, op, roperand);

  result = handleIntegerArithmetic(loperand, op, roperand);
  if(!isNullLiteral(&result)) {
    logArithmeticExpressionExit(loperand, op, roperand, result);
    return result;
  }

  result = handleFloatArithmetic(loperand, op, roperand);
  if(!isNullLiteral(&result)) {
    logArithmeticExpressionExit(loperand, op, roperand, result);
    return result;
  }

  result = handleStringArithmetic(loperand, op, roperand);
  if(!isNullLiteral(&result)) {
    logArithmeticExpressionExit(loperand, op, roperand, result);
    return result;
  }

  halt(ERR_MSG_UNSUPPORTED_OPERATION, type2str(loperand->type), op2str(op), type2str(roperand->type));
  return result;
}

literal handleFloatArithmetic(literal* loperand, op_type op, literal* roperand)
{
	literal result = createEmptyLiteral();
  if(isNumber(loperand) && isNumber(roperand))
  { 
		double lvalue = isInteger(loperand)? (double)loperand->ivalue: (double)loperand->fvalue;
		double rvalue = isInteger(roperand)? (double)roperand->ivalue: (double)roperand->fvalue;
		result.type = TYPE_FLOAT;

		switch(op)
		{
			case OP_PLUS:    result.fvalue = (float)(lvalue + rvalue); break;
			case OP_MINUS:   result.fvalue = (float)(lvalue - rvalue); break;
			case OP_TIMES:   result.fvalue = (float)(lvalue * rvalue); break;
			case OP_DIVIDE:  result.fvalue = (float)(lvalue / rvalue); break;
			case OP_POW:     result.fvalue = (float)(pow(lvalue, rvalue)); break;
			default:
				log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION, type2str(loperand->type), op2str(op), type2str(roperand->type));
		}
	}
  return result;
}

literal handleIntegerArithmetic(literal* loperand, op_type op, literal* roperand)
{
  literal result = createEmptyLiteral();
	if(isInteger(loperand) && isInteger(roperand))
  {
		result.type = TYPE_INTEGER;
		switch(op)
		{
			case OP_PLUS:    result.ivalue = loperand->ivalue + roperand->ivalue; break;
			case OP_MINUS:   result.ivalue = loperand->ivalue - roperand->ivalue; break;
			case OP_TIMES:   result.ivalue = loperand->ivalue * roperand->ivalue; break;
			case OP_DIVIDE:  result.ivalue = loperand->ivalue / roperand->ivalue; break;
			case OP_MOD:     result.ivalue = loperand->ivalue % roperand->ivalue; break;
			case OP_POW:     result.ivalue = (int)(pow(loperand->ivalue, roperand->ivalue)+0.5); break;
			default:
				log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION, type2str(loperand->type), op2str(op), type2str(roperand->type));
		}
	}

  return result;
}

literal handleStringArithmetic(literal* loperand, op_type op, literal* roperand)
{
	literal result = createEmptyLiteral();

  if(op != OP_PLUS)
  { log_message(LOG_ERROR, ERR_MSG_UNSUPPORTED_OPERATION, type2str(loperand->type), op2str(op), type2str(roperand->type)); }
	else if(isString(loperand) || isString(roperand)) 
	{ result = handleStringConcat(loperand, roperand); }

  return result;
}

literal handleStringConcat(literal* loperand, literal* roperand)
{
  literal result;

  char *lvalue = literal2str(loperand);
  char *rvalue = literal2str(roperand);

  size_t len = strlen(lvalue) + strlen(rvalue) + 1;
	result.type = TYPE_STRING;
  result.svalue = malloc(len);
  if(result.svalue == NULL)
  { halt(ERR_MSG_MEMORY_ALLOCATION_FAILED); }

  strncpy(result.svalue, lvalue, strlen(lvalue) + 1);
  strncat(result.svalue, rvalue, strlen(rvalue) + 1);
  free(lvalue); free(rvalue);

  return result;
}

literal arithmeticExpressionPlus(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, OP_PLUS, roperand); }

literal arithmeticExpressionMinus(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, OP_MINUS, roperand); }

literal arithmeticExpressionTimes(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, OP_TIMES, roperand); }

literal arithmeticExpressionDivide(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, OP_DIVIDE, roperand); }

literal arithmeticExpressionMod(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, OP_MOD, roperand); }

literal arithmeticExpressionPow(literal* loperand, literal* roperand)
{ return arithmeticExpression(loperand, OP_POW, roperand); }

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
      op2str(OP_NEGATE), type2str(operand->type));
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
    case FUNC_SIN:
    case FUNC_COS:
    case FUNC_TAN:
      literal *arg1trig = va_arg(args, literal*);
      result = arithmeticExpressionTrigonometry(funct_id, arg1trig);
      break;
    case FUNC_LEN:
      literal *arg1len = va_arg(args, literal*);
      result = arithmeticExpressionLen(arg1len);
      break;
    case FUNC_SUBSTR:
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
    case FUNC_SIN: return createFloatLiteral(sin(fvalue));
    case FUNC_COS: return createFloatLiteral(cos(fvalue));
    case FUNC_TAN: return createFloatLiteral(tan(fvalue));
    default: log_message(LOG_ERROR, ERR_MSG_INVALID_FUNCTION_IDENTIFIER, funct_id);
  }
  return createEmptyLiteral();
}

literal arithmeticExpressionLen(literal* string)
{
  literal result = createEmptyLiteral();
  
  if(!isString(string))
  { log_message(LOG_ERROR, ERR_MSG_INVALID_ARGUMENT_TYPE, type2str(string->type), 1, "len"); }
  else 
  { result = createIntegerLiteral(strlen(string->svalue)); }

  return result;
}

literal arithmeticExpressionSubstr(literal* string, literal* start, literal* len)
{  
  if(!isString(string))
  { log_message(LOG_ERROR, ERR_MSG_INVALID_ARGUMENT_TYPE, type2str(string->type), 1, "substr", type2str(TYPE_STRING)); }
  else if(!isInteger(start))
  { log_message(LOG_ERROR, ERR_MSG_INVALID_ARGUMENT_TYPE, type2str(start->type), 2, "substr", type2str(TYPE_INTEGER)); }
  else if(!isInteger(len))
  { log_message(LOG_ERROR, ERR_MSG_INVALID_ARGUMENT_TYPE, type2str(len->type), 3, "substr", type2str(TYPE_INTEGER)); }
  return createStringLiteral(strndup(string->svalue + start->ivalue, len->ivalue), len->ivalue);
}
