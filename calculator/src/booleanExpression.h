#pragma once
#include "base.h"

literal booleanExpressionToLiteral(bool);
bool booleanExpressionIdentifier(identifier*);
bool booleanExpressionOr(bool, bool);
bool booleanExpressionAnd(bool, bool);
bool booleanExpressionNot(bool);
bool booleanExpressionTrue(void);
bool booleanExpressionFalse(void);

bool relationalExpression(literal*, op_type, literal*);
bool relationalExpressionEquals(literal*, literal*);
bool relationalExpressionGreaterThan(literal*, literal*);
bool relationalExpressionGreaterEquals(literal*, literal*);
bool relationalExpressionLowerThan(literal*, literal*);
bool relationalExpressionLowerEquals(literal*, literal*);
bool relationalExpressionNotEquals(literal*, literal*);
