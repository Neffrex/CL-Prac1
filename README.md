# Práctica 1 – Calculadora con Flex & Bison  
**Compiladores (CL) – GEI 2025/26**

## Descripción general

Este proyecto implementa el **front-end de un compilador** para un lenguaje de tipo calculadora, utilizando **Flex** para el análisis léxico y **Bison** para el análisis sintáctico.  
El sistema actúa como un **intérprete**: analiza, valida semánticamente y evalúa expresiones y asignaciones de un lenguaje tipado sencillo.

La práctica cubre los siguientes conceptos:
- Análisis léxico
- Análisis sintáctico
- Tabla de símbolos
- Comprobación de tipos
- Evaluación de expresiones
- Manejo de errores léxicos, sintácticos y semánticos

## Funcionalidades implementadas

### Tipos soportados
- `int`
- `float`
- `string`
- `bool`

Las variables **deben declararse antes de su uso** y su tipo queda registrado en la tabla de símbolos.

### Literales
- Enteros: `123`
- Reales: `3.14`, `1e-3`
- Strings: `"Hola mundo"`
- Booleanos: `true`, `false`

### Comentarios
- `//` comentario de una línea
- `#` comentario de una línea
- `/* ... */` comentario multilínea

### Expresiones aritméticas
- Operadores: `+ - * / % **`
- Operadores unarios: `+ -`
- Paréntesis
- Promoción automática `int → float`
- Concatenación de strings con `+`

**Precedencia implementada mediante la gramática**, no con directivas de Bison.

### Expresiones booleanas
- Relacionales: `> >= < <= = <>`
- Lógicos: `not`, `and`, `or`
- Precedencia: `not` > `and` > `or`
- No se implementa cortocircuito (evaluación completa)

### Asignaciones
- Sintaxis:  
```
identificador := expresión
```
- Se comprueba compatibilidad de tipos
- Se registra el valor en la tabla de símbolos


### Funciones predefinidas
- `sin(x)`
- `cos(x)`
- `tan(x)`
- `LEN(string)`
- `SUBSTR(string; inicio; longitud)`
- Constantes: `PI`, `E`

### Salida del programa
- Cada expresión o asignación produce una salida en `stdout`
- El formato indica **tipo y valor**
- El log del parser se guarda por separado



## Descripción de los componentes principales

### `src/lexer/`
- `calc.l`: Analizador léxico (Flex)
- Reconoce tokens, literales, comentarios y palabras clave


### `src/parser/`
- `calc.y`: Gramática Bison
- Define la precedencia de operadores
- Construye y evalúa expresiones
- Integra comprobaciones semánticas


### `src/symtab/`
- Implementación de la **tabla de símbolos**

### `src/ast/`
- Implementación de nodos semánticos y evaluación
- Separación entre:
  - Expresiones aritméticas
  - Expresiones booleanas
  - Identificadores
  - Tipos
- Sistema de logging interno

### `Makefile`
- `make` : compila el proyecto
- `make clean` : limpia archivos generados
- `make debug` : ejecuta con `gdb`


## Cómo compilar y ejecutar

### Requisitos
- `flex`
- `bison`
- `gcc`
- Sistema Linux

Instalación automática:
```
sudo ./install.sh
```

O manualmente usando el archivo requirements.

### Compilación
```
make
```

### Ejecución
```
make run
```

Se ejecuta el codigo proveniente del fichero `input.txt`.

En caso de querer utilizar otro fichero se puede llamar al make de la siguiente manera:
```
make run INPUT_FILE=<input_file>
```
donde `<input_file>` es el nombre del fichero de entrada que se quiere utilizar.

En `example_output.txt` se ha dejado el resultado de la ejecución con el fichero `input.txt` por defecto  

### Limpieza
```
make clean
```

## Manejo de errores

El sistema detecta y reporta:
* Errores léxicos
* Errores sintácticos
* Errores semánticos (tipos, variables no declaradas)

Los mensajes incluyen información contextual cuando es posible.

## Limitaciones y funcionalidades no implementadas

Las siguientes limitaciones son conocidas:
* Los struct no están implementados
* Las expresiones aritméticas no aceptan expresiones booleanas
* No se implementa evaluación con cortocircuito en booleanos
* No hay arrays ni listas
* No se permite conversión explícita de tipos