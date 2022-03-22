/*4. Explique la difercia en la salida de las siguientes instrucciones:

   char a = 'M';
   printf ("a = %i \n", a);
   printf ("La letra %c \n", a);

   ¿Cuál es el valor numérico de a?
*/

main() {
    char a = 'M';
    printf("a = %i \n", a);
    printf("La letra %c \n", a);
}

// La diferencia es la interpretación que le dá el compilador
// al valor que está almacenado en la variable a.
// El valor numérico de a es 77.