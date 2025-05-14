#pragma once
#include "base.h"

literal arithmeticExpression(literal*, op_type, literal*);
literal arithmeticExpressionIdentifier(identifier*);
literal arithmeticExpressionConcat(literal*, literal*);
literal arithmeticExpressionPlus(literal*, literal*);
literal arithmeticExpressionMinus(literal*, literal*);
literal arithmeticExpressionTimes(literal*, literal*);
literal arithmeticExpressionDivide(literal*, literal*);
literal arithmeticExpressionMod(literal*, literal*);
literal arithmeticExpressionPow(literal*, literal*);
literal arithmeticExpressionNegate(literal*);

literal arithmeticExpressionFunction(funct_id funct_id, ...);
literal arithmeticExpressionTrigonometry(funct_id funct_id, literal* value);
literal arithmeticExpressionLen(literal* string);
literal arithmeticExpressionSubstr(literal* string, literal* start, literal* len);
