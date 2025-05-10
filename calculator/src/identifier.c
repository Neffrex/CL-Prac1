#include "identifier.h"

identifier assign(identifier* id, literal value)
{
  char svalue[STR_MAX_LENGTH];
  val2str(svalue, sizeof(svalue), E_DEC, &value);
  log_message(LOG_INFO, LOG_MSG_ASSIGN, svalue, id->name);
  sym_enter(id->name, &value);
  id->value = value;
  return *id;
}

literal getIdentifierValue(identifier* id)
{
  literal result;
  if(sym_lookup(id->name, &result) == SYMTAB_NOT_FOUND)
  { log_message(LOG_ERROR, ERR_MSG_IDENTIFIER_NOT_DECLARED, id->name, id->lineno); }
  else
  { char buffer[STR_MAX_LENGTH];
    val2str(buffer, sizeof(buffer), E_DEC, &result);
    log_message(LOG_INFO, LOG_MSG_GET_IDENTIFIER, id->name, buffer);
  } 
  return result;
}
