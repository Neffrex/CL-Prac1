# TODO:
· Al dividir por cero imprime un numero (erroneo) cuando no deberia imprimir nada
· Cambiar los fprintf(stderr, ...) por yyerror() cuando sea necesario
· Hacer el log (Es un requisito funcional)

# Requisitos funcionales
Literales y comentarios:
[+] Literales enteros
[+] Literales reales
[+] Cadenas de caracteres, limitadas por comillas dobles y de una sola linea.
[+] Booleanos
[+] Comentarios simples con `//` y `#`
[+] Comentarios multilinea comenzados con `/*` y terminados en `*/`

Identificadores y expresiones:
[+] Tipos de identificadores:
  [+] entero
  [+] real
  [+] cadena
  [+] booleano
[-] Expresiones aritmeticas formadas por:
  [-] enteros
  [-] literales
  [-] reales
  [-] cadenas de caracteres
  [-] identificadores (no booleanos)
  [-] parentesis
  [-] operador de concatenacion de cadenas: `+`
  [-] operadores aritmeticos unarios (`+`,`-`)
  [-] operadores aritmeticos binarios (`+`,`-`,`*`,`/`,`%`,`**`)

[-] Niveles de precedencia de los operadores aritmeticos:
- Binarios
  01. `**`
  02. `*`,`/`,`%`
  03. `+`,`-`
- Unarios
  03. `-`

[-] Expresiones booleanas (`>`,`>=`,`<`,`<=`,`=`,`<>`) sobre expresiones aritmeticas
[-] Expresiones booleanas (`not`,`and`,`or`) sobre expresiones booleanas
[-] Niveles de precedencia de los operadores booleanos:
  01. `not`
  02. `and`
  03. `or`

Sentencias
[-] Pueden ser: (todas ocupan una sola linea)
  [-] expresiones aritmeticas
  [-] expresiones booleanas
  [-] asignaciones (identificador := expresion aritmetica/booleana)
[-] En una asignacion el tipo del identificador es igual al del resultado de la expresion
[-] Si se operan expresiones aritmeticas del mismo tipo el resultado es del mismo tipo
[-] Si se opera un real con un entero el resultado es un real
[-] Si se opera un entero con una cadena el resultado es una cadena
[-] Hace falta inicializar los identificadores antes de utilizarlos (para conocer el tipo)

Funcionalidades
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
