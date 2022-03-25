/*
9. Prepare un programa con una variable de tipo char y otra de tipo unsigned
    char. Inicialice ambas variables con los valores máximos de cada tipo,
    para comprobar el resultado de incrementarlas en una unidad.
    Imprima los valores de cada variable antes y después del incremento.
*/

main()
{
    char a;
    unsigned char unA;

    for (int i = 0; i <= 256; i++)
    {
        a = i;
        unA = i;

        printf("unsigned %d = %c , ", unA, unA);
        printf(" signded %d = %c\n", a, a);
    }

    // rta: los tipos char son indiferentes del signo y su representacion es de 0 a 127 independientemente del signo.
}