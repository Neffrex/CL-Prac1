#include "headers/identifier.h"

/**
 * Declares the type of an identifier
 * @return The identifer with its type declared
 * @throw IDENTIFIER_ if the given identifier is found in the symbol table
 */
identifier declare(identifier* id, type_t type) 
{	
	if(sym_lookup(id->name, id) == SYMTAB_NOT_FOUND)
	{	
		id->type = type;
		sym_enter(id->name, id);
		log_message(LOG_INFO, LOG_MSG_IDENTIFIER_DECLARED, id->name, type);
	} else 
	{	
		// Identifier already declared
		log_message(LOG_ERROR, ERR_MSG_IDENTIFIER_ALREADY_DECLARED, id->name, id->lineno);
	}
}

identifier assign(identifier* id, literal value)
{
  char svalue[STR_MAX_LENGTH];
  literal2str(svalue, sizeof(svalue), &value);
  log_message(LOG_INFO, LOG_MSG_IDENTIFIER_ASSIGNED, type2str(value.type), id->name, svalue);

	//TODO: Check if id->type == value.type
  id->value = value;
  sym_enter(id->name, id);
  return *id;
}

literal getIdentifierValue(identifier* id)
{
  literal result;
  if(sym_lookup(id->name, &result) != SYMTAB_NOT_FOUND)
  { char svalue[STR_MAX_LENGTH];
    literal2str(svalue, sizeof(svalue), &result);
    log_message(LOG_INFO, LOG_MSG_IDENTIFIER_RETRIEVED, type2str(result.type), id->name, svalue);
  } 
  return result;
}   

// { log_message(LOG_ERROR, ERR_MSG_IDENTIFIER_NOT_DECLARED, id->name, id->lineno); }
