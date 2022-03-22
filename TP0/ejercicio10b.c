/*
10.b ¿Qué resultado puede esperarse del siguiente fragmento de código?

    int a, b, c, d;
    a = 1;
    b = 2;
    c = a / b;
    d = a / c;
*/
main() {
    int a, b, c, d;
    a = 1;
    b = 2;
    c = a / b;
    d = a / c;

    printf("a = %i\n", a);
    printf("b = %i\n", b);
    printf("c = %i\n", c);
    printf("d = %i\n", d);

    /* $ ./ejercicio10b
        Floating point exception+
    */

    // rta: c y d deberian ser como mínimo de tipo flotante
    // sino el programa muestra una excepcion.
}