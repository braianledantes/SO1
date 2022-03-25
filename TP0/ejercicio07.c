/*
7. Cuáles de entre estas declaraciones contienen errores?

    integer a;
    short i,j,k;
    long float (h);
    double long d3;
    unsigned float n;
    char 2j;
    int MY;
    float ancho, alto, long;
    bool i;
*/

main() {
    integer a; // mal, integer no es un tipo de dato definido
    short i,j,k; // bien, queda int como predeterminado
    long float (h);  // error, por sintaxis los paréntesis no van.
    double long d3;  // error, el modificador del tipo debe estar antes del tipo.
    unsigned float n;  // bien, no sé porqué el compilador dá error.
    char 2j;   // error, nombre de variable incorrecta.
    int MY;    // correcto.
    float ancho, alto, long;  // error, long es una palabra reservada para tipo de dato.
    bool i; // error, no existe tal tipo de dato.
}

// LO SIGUIENTE ES LO QUE MUESTRA EL COMPILADOR DE C:
/*
ejercicio07.c: In function ‘main’:
ejercicio07.c:16:5: error: unknown type name ‘integer’
   16 |     integer a;
      |     ^~~~~~~
ejercicio07.c:18:10: error: both ‘long’ and ‘float’ in declaration specifiers
   18 |     long float (h);
      |          ^~~~~
ejercicio07.c:20:14: error: both ‘unsigned’ and ‘float’ in declaration specifiers
   20 |     unsigned float n;
      |              ^~~~~
ejercicio07.c:21:10: error: expected identifier or ‘(’ before numeric constant
   21 |     char 2j;
      |          ^~
ejercicio07.c:23:24: error: expected identifier or ‘(’ before ‘long’
   23 |     float ancho, alto, long;
      |                        ^~~~
ejercicio07.c:24:5: error: unknown type name ‘bool’
   24 |     bool i;
      |     ^~~~
ejercicio07.c:24:10: error: conflicting types for ‘i’
   24 |     bool i;
      |          ^
ejercicio07.c:17:11: note: previous declaration of ‘i’ was here
   17 |     short i,j,k;
      |           ^
*/