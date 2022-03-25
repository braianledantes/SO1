/*
8. Averigüe los tamaños de todos los tipos básicos en su sistema aplicando
    el operador sizeof().
*/
/*
Los tipos básicos son:
-char (un elemento del tamaño de un byte)
-int (un número entero con signo)
-long (un entero largo)
-float (un número en punto flotante)
-double (un número en punto flotante, doble precisión)
*/
main()
{
    char a = 'a';           // 1 byte
    int b = 1;              // 4 bytes
    long c = 111111111;     // 8 bytes
    float d = 1.1;          // 4 bytes
    double e = 3.14;       // 8 bytes

    printf("char ocupa %d B\n", sizeof(a));
    printf("int ocupa %d B\n", sizeof(b));
    printf("long ocupa %d B\n", sizeof(c));
    printf("float ocupa %d B\n", sizeof(d));
    printf("double ocupa %d B\n", sizeof(e));
}