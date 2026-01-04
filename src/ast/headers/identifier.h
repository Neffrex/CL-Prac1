#pragma once
#include "base.h"

identifier_node* declare(identifier_node*, type_t);
identifier_node* createIdentifierNode(identifier_node* head, identifier* id, type_t type);
identifier assign(identifier*, literal);
identifier getIdentifier(char*);
