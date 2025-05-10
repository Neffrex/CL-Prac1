# Nombre del ejecutable
TARGET = compiler

SOURCES := $(wildcard *.c)

# Archivos de origen
LEX_FILE = calc.l
BISON_FILE = calc.y

# Archivos generados por Bison y Flex
BISON_C = calc.tab.c
BISON_H = calc.tab.h
LEX_C = lex.yy.c
COMPILER_C = compiler.c
COMPILER_H = compiler.h
SYMTAB = symtab.o
SYMTAB_C = symtab.c
SYMTAB_H = symtab.h
LOG_C = log.c
LOG_H = log.h

# Compilador y opciones de compilación
CC = gcc
CFLAGS = -Wall -lm -lfl -g

# Archivo de entrada para pruebas
INPUT_FILE = ../input.txt
ERROR_FILE = ../error.txt

# Regla principal
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(SOURCES) $(BISON_C) $(LEX_C)
	$(CC) -o $(TARGET) $(SOURCES) $(BISON_C) $(LEX_C) $(CFLAGS)

# Regla para generar el archivo .c y .h de Bison
$(BISON_C) $(BISON_H): $(BISON_FILE)
	bison -d -Wcounterexamples $(BISON_FILE)

# Regla para generar el archivo .c de Flex
$(LEX_C): $(LEX_FILE) $(BISON_H)
	flex $(LEX_FILE)

# Regla para ejecutar el programa con el archivo de entrada
run: $(TARGET)
	./$(TARGET) < $(INPUT_FILE) 2>$(ERROR_FILE)

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET) $(BISON_C) $(BISON_H) $(LEX_C)

