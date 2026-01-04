#ifndef LOG_H
#define LOG_H

#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

extern void yyerror(const char* msg);

typedef enum {
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR,
    LOG_DEBUG
} LogLevel;

void init_log(const char *filename);
void close_log(void);
void log_message(LogLevel level, const char *format, ...);
void halt(const char *format, ...);

#endif

