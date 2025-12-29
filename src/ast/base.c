#include "headers/base.h"

literal createIntegerLiteral(int ivalue)
{
  literal result;
  result.type = TYPE_INTEGER;
  result.ivalue = ivalue;
  return result;
}

literal createFloatLiteral(float fvalue)
{
  literal result;
  result.type = TYPE_FLOAT;
  result.fvalue = fvalue;
  return result;
}

literal createStringLiteral(char* svalue, int len)
{
  literal result;
  result.type = TYPE_STRING;
  result.svalue = strndup(svalue, len);
  return result;
}

literal createBooleanLiteral(bool bvalue)
{
  literal result;
  result.type = TYPE_BOOLEAN;
  result.bvalue = bvalue;
  return result;
}

