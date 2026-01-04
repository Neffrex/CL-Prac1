#pragma once
#include "base.h"

// ╭───────────────────────────╮ //
// │ BOOLEAN CONVERSION        │ //
// ╰───────────────────────────╯ //

literal booleanExpressionToLiteral(bool);

// ╭──────────────────╮ //
// │ BOOLEAN LITERALS │ //
// ╰──────────────────╯ //

bool booleanExpressionTrue(void);
bool booleanExpressionFalse(void);

// ╭───────────────────────────╮ //
// │ UNARY BOOLEAN EXPRESSIONS │ //
// ╰───────────────────────────╯ //

void logBooleanExpressionUnaryEntry(op_type, bool);
void logBooleanExpressionUnaryExit(bool);
bool booleanExpressionUnary(op_type op, bool operand);
bool booleanExpressionOr(bool, bool);

// ╭────────────────────────────╮ //
// │ BINARY BOOLEAN EXPRESSIONS │ //
// ╰────────────────────────────╯ //

void logBooleanBinaryExpressionEntry(bool, op_type, bool);
void logBooleanBinaryExpressionExit(bool);
bool booleanBinaryExpression(bool, op_type, bool);
bool booleanExpressionAnd(bool, bool);
bool booleanExpressionNot(bool);


// ╭─────────────────────────────╮ //
// │ RELATIONAL EXPRESSIONS      │ //
// ╰─────────────────────────────╯ //

bool relationalExpression(literal*, op_type, literal*);
bool relationalExpressionEquals(literal*, literal*);
bool relationalExpressionGreaterThan(literal*, literal*);
bool relationalExpressionGreaterEquals(literal*, literal*);
bool relationalExpressionLowerThan(literal*, literal*);
bool relationalExpressionLowerEquals(literal*, literal*);
bool relationalExpressionNotEquals(literal*, literal*);
