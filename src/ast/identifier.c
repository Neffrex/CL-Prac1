#include "headers/identifier.h"



identifier_node* declare(identifier_node* id_node, type_t type) 
{	
  for(identifier_node* current = id_node; current != NULL; current = current->next)
  {
    if(sym_lookup(current->id.name, &current->id) == SYMTAB_NOT_FOUND)
    {	
      current->id.type = type;
      sym_enter(current->id.name, &current->id);
      log_message(LOG_INFO, LOG_MSG_IDENTIFIER_DECLARED, current->id.name, type2str(current->id.type));
    } else 
    {	
      // Identifier already declared
      halt(ERR_MSG_IDENTIFIER_ALREADY_DECLARED, current->id.name, current->id.lineno);
    }
  }
  return id_node;
}

identifier_node* createIdentifierNode(identifier_node* head, identifier* id, type_t type)
{
  identifier_node* new_node = (identifier_node*) malloc (sizeof(identifier_node));
  new_node->id.name = strdup(id->name);
  new_node->id.type = type;
  new_node->id.lineno = id->lineno;
  new_node->next = head;
  return new_node;
}

identifier assign(identifier* id, literal value)
{
  char *svalue = literal2str(&value);
  log_message(LOG_INFO, LOG_MSG_IDENTIFIER_ASSIGNED, type2str(value.type), id->name, svalue);

	//TODO: Check if id->type == value.type
  id->value = value;
  sym_enter(id->name, id);
  return *id;
}

identifier getIdentifier(char* name)
{
  identifier* id = (identifier*) malloc(sizeof(identifier));
  if(sym_lookup(name, id) != SYMTAB_NOT_FOUND)
  { 
    char *svalue = literal2str(&id->value);
    log_message(LOG_INFO, LOG_MSG_IDENTIFIER_RETRIEVED, type2str(id->type), id->name, svalue);
    free(svalue);
  } 
  identifier result = *id;
  free(id);
  return result;
}