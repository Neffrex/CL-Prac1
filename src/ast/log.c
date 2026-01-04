#include "headers/log.h"

static FILE *log_file = NULL;
extern void yyerror(const char*);

void init_log(const char *filename) {
    log_file = fopen(filename, "w");
    if (!log_file) {
        fprintf(stderr, "ERROR: No se pudo abrir el archivo de log: %s\n", filename);
        exit(EXIT_FAILURE);
    }
}

void close_log() {
    if (log_file) {
        fclose(log_file);
        log_file = NULL;
    }
}

void log_message(LogLevel level, const char *format, ...) {
    if (!log_file) return;
    va_list args;
    va_start(args, format);

    const char *prefix;
    switch (level) {
        case LOG_INFO:    prefix = "INFO"; break;
        case LOG_WARNING: prefix = "WARNING"; break;
        case LOG_ERROR:   prefix = "ERROR"; break;
        case LOG_DEBUG:   prefix = "DEBUG"; break;
        default:          prefix = "LOG"; break;
    }

    fprintf(log_file, "[%s] ", prefix);
    vfprintf(log_file, format, args);
    va_end(args);

    fprintf(log_file, "\n");
    fflush(log_file);
}

void halt(const char *format, ...) {
    if (!log_file) return;
    va_list args;
    va_start(args, format);
    
    char err_msg[256];
    vsprintf(err_msg, format, args);
    yyerror(err_msg);

    va_end(args);
}