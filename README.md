# Flex & Bison Simple Calculator

## What can this proyect do?
This tool serves as an interpret of a simple typed language

# Get started

## Requirements
To start using this tool you will need to first install the package requirements

You can do so by running the installation script located in the root directory of this proyect
```
sudo install.sh
```

Or installing the packages listed in the `requirements` file manually

## Using the tool
Once you have installed the requirement packages you can now run the `MakeFile` by doing one of the following commands:

Running the tool with the default file

Running the tool with an input file. You must change `foo` to the path of the desired file to use 
```
make run INPUT_FILE=foo
```

```
make clean
```

# TODO:
· Al dividir por cero imprime un numero (erroneo) cuando no deberia imprimir nada
· Cambiar los fprintf(stderr, ...) por yyerror() cuando sea necesario
· Hacer el log (Es un requisito funcional)

# Requisitos funcionales

## Literales

[+] Literales enteros

[+] Literales reales

[+] Cadenas de caracteres, limitadas por comillas dobles y de una sola linea.

[+] Booleanos

## Comentarios

[+] Comentarios simples con `//` y `#`

[+] Comentarios multilinea comenzados con `/*` y terminados en `*/`

## Tipos de identificadores:

  [+] entero

  [+] real

  [+] cadena

  [+] booleano

## Expresiones aritmeticas formadas por

  [-] enteros

  [-] literales

  [-] reales

  [-] cadenas de caracteres

  [-] identificadores (no booleanos)

  [-] parentesis

  [-] operador de concatenacion de cadenas: `+`

  [-] operadores aritmeticos unarios (`+`,`-`)

  [-] operadores aritmeticos binarios (`+`,`-`,`*`,`/`,`%`m `**`)

## Niveles de precedencia de los operadores aritmeticos:

  [-] `_**_` > `_*_`,`_/_`,`_%_` > `_+_`,`_-_`,`-_`

	
## Expresiones booleanas

[-] Expresiones booleanas (`>`,`>=`,`<`,`<=`,`=`,`<>`) sobre expresiones aritmeticas

[-] Expresiones booleanas (`not`,`and`,`or`) sobre expresiones booleanas

### Niveles de precedencia de los operadores booleanos:

  [-] `not` > `and` > `or`

## Sentencias

[-] Pueden ser: (todas ocupan una sola linea)
  [-] expresiones aritmeticas
  [-] expresiones booleanas
  [-] asignaciones (identificador := expresion aritmetica/booleana)
[-] En una asignacion el tipo del identificador es igual al del resultado de la expresion
[-] Si se operan expresiones aritmeticas del mismo tipo el resultado es del mismo tipo
[-] Si se opera un real con un entero el resultado es un real
[-] Si se opera un entero con una cadena el resultado es una cadena
[-] Hace falta inicializar los identificadores antes de utilizarlos (para conocer el tipo)

## Funcionalidades
[-] funciones trigonometricas:
  [-] sin
  [-] cos
  [-] tan
[-] funcion de longitud de cadena: LEN
[-] funcion de extraccion de cadena: SUBSTR(cadena; inicio; longitud)
[+] Constantes: 
  [+] PI
  [+] E
[-] Representacion en diversos modos:
  [-] octal
  [-] binario
  [-] hexadecimal
  [-] decimal (por defecto)
[]

[-] Funciones matematicas
[-] Variables
[-] Operadores unarios
