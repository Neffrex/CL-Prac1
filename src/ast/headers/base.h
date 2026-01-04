#pragma once
#include <stdbool.h>
#include <math.h>
#include "log.h"
#include "types.h"
#include "../../symtab/symtab.h"
#include "messages.h"
#include "identifier.h"

literal createEmptyLiteral();
literal createIntegerLiteral(int);
literal createFloatLiteral(float);
literal createStringLiteral(char*, int);
literal createBooleanLiteral(bool);

