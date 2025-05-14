#include "headers/base.h"

literal createEmptyLiteral()
{
  literal result;
  result.type = E_NULL_TYPE;
  result.ivalue = 0;
  result.fvalue = 0.0;
  result.svalue = NULL;
  result.bvalue = false;
  return result;
}

literal createIntegerLiteral(int ivalue)
{
  literal result;
  result.type = E_INTEGER;
  result.ivalue = ivalue;
  return result;
}

literal createFloatLiteral(float fvalue)
{
  literal result;
  result.type = E_FLOAT;
  result.fvalue = fvalue;
  return result;
}

literal createStringLiteral(char* svalue, int len)
{
  literal result;
  result.type = E_STRING;
  result.svalue = strndup(svalue, len);
  return result;
}

literal createBooleanLiteral(bool bvalue)
{
  literal result;
  result.type = E_BOOLEAN;
  result.bvalue = bvalue;
  return result;
}

