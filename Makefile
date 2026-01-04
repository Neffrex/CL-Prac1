# Final compilacion target
TARGET = src/build/calculator

# Source Files
AST_C = $(wildcard src/ast/*.c)
LEXER_SOURCE = src/lexer/calc.l
LEXER_C = src/lexer/lex.yy.c
PARSER_SOURCE = src/parser/calc.y
PARSER_FILE = src/parser/calc.tab
PARSER_C = src/parser/calc.tab.c
PARSER_H = src/parser/calc.tab.h
SYMTAB_C = src/symtab/symtab.c
SYMTAB_H = src/symtab/symtab.h

CC = gcc
CFLAGS = -Wall -lm -lfl -g

# Archivo de entrada y salida
INPUT_FILE = input.txt

# Regla principal
all: $(TARGET)

# Regla para compilar el ejecutable
$(TARGET): $(AST_C) $(LEXER_C) $(PARSER_C) $(SYMTAB_C)
	$(CC) -o $(TARGET) $(AST_C) $(LEXER_C) $(PARSER_C) $(SYMTAB_C) $(CFLAGS)

# Regla para generar el archivo .c y .h de Bison
$(PARSER_C) $(PARSER_H): $(PARSER_SOURCE)
	bison -d -Wcounterexamples $(PARSER_SOURCE)
	mv $(notdir $(PARSER_C)) $(PARSER_C)
	mv $(notdir $(PARSER_H)) $(PARSER_H)

# Regla para generar el archivo .c de Flex
$(LEXER_C): $(LEXER_SOURCE) $(PARSER_H)
	flex $(LEXER_SOURCE)
	mv $(notdir $(LEXER_C)) $(LEXER_C)

# Regla para ejecutar el programa con el archivo de entrada
run: $(TARGET)
	./$(TARGET) < $(INPUT_FILE)

debug: ${TARGET}
	gdb ./$(TARGET)

# Regla para limpiar archivos generados
clean:
	rm -f $(TARGET) $(PARSER_C) $(PARSER_H) $(LEXER_C)

