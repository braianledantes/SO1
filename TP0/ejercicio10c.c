/*
10.c ¿Cuál es el resultado del siguiente fragmento de código? Anticipe su
    respuesta en base a lo dicho en esta unidad y luego confírmela mediante
    un programa.

    muestra el valor bien
    printf("%d\n", 20/3);

    muestra el valor bien
    printf("%f\n", 20/3);

    idem
    printf("%f\n", 20/3.);

    idem
    printf("%d\n", 10%3);

    idem
    printf("%d\n", 3.1416);

    idem
    printf("%f\n", (double)20/3);

    idem
    printf("%f\n", (int)3.1416);

    idem
    printf("%d\n", (int)3.1416);
*/

main()
{
    printf("d  20/3 = %d \n", 20 / 3);
    printf("f  20/3 = %f\n", 20 / 3);
    printf("f  20/3 = %f\n", 20 / 3.);
    printf("d  12mod3 = %d\n", 10 % 3);
    printf("d  3.1416 =  %d\n", 3.1416);
    printf("fd (double) 20/3 =  %f\n", (double)20 / 3);
    printf("fi (int) 3.1416 = %f \n", (int)3.1416);
    printf("di (int) 3.1416 =  %d\n", (int)3.1416);
}
