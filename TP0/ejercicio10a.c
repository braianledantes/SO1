/*
10.a ¿Qué hace falta corregir para que la variable r contenga la división
    exacta de a y b?

    int a, b;
    float r;
    a = 5;
    b = 2;
    r = a / b;
*/
main()
{
    int a, b;
    float r;
    a = 5;
    b = 2;
    r = (float)a / (float)b;

    printf("r = a / b\n");
    printf("%f = %i / %i\n", r, a, b);

    // rta: haria falta castear ambos valores, a y b.
}