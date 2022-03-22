/*
9. Prepare un programa con una variable de tipo char y otra de tipo unsigned 
    char. Inicialice ambas variables con los valores máximos de cada tipo, 
    para comprobar el resultado de incrementarlas en una unidad. 
    Imprima los valores de cada variable antes y después del incremento.
*/

main() {
    char a = ' ' + 1;
    unsigned char unA = ' ' + 1;

    for(int i = 0; i <= 255; i++) {
        a = i;
        unA = i;

        printf("unsigned %d = %c , ", unA, unA);
        printf(" signded %d = %c\n", a, a);
        
    }

    // rta: los tipos char son indiferentes del signo.
}