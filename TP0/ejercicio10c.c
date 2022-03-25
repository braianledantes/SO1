/*
10.c ¿Cuál es el resultado del siguiente fragmento de código? Anticipe su
    respuesta en base a lo dicho en esta unidad y luego confírmela mediante
    un programa.

    
    printf("%d\n", 20/3);
    Predicción: imprime solo la parte entera (6), debería ser casteado.
    Resultado: 6
    
    printf("%f\n", 20/3);
    Predicción: idem que el anterior
    Resultado: 0.000000
    
    printf("%f\n", 20/3.);
    Predicción: 6.66666.. ya qye 3. lo toma como un flotante
    Resultado: 6.666667
    
    printf("%d\n", 10%3);
    Predicción: el módulo devuelve el resto de la división que es 1.
    Resultado: 1
    
    printf("%d\n", 3.1416);
    Predicción: 3.1416
    Resultado: 445403808. Seguamente porque %d interpreta el binario como un entero.
    
    printf("%f\n", (double)20/3);
    Predicción: 6.666667
    Resultado: 6.666667
    
    printf("%f\n", (int)3.1416);
    Predicción: o toma la parte entera (3) o interpreta su valor binario.
    Resultado: 6.666667
    
    printf("%d\n", (int)3.1416);
    Predicción: idem que el anterior.
    Resultado: 3
*/

main()
{
    printf("d  20/3 = %d \n", 20 / 3);
    printf("f  20/3 = %f\n", 20 / 3);
    printf("f  20/3 = %f\n", 20 / 3.);
    printf("d  10mod3 = %d\n", 10 % 3);
    printf("d  3.1416 =  %d\n", 3.1416);
    printf("fd (double) 20/3 =  %f\n", (double)20 / 3);
    printf("fi (int) 3.1416 = %f \n", (int)3.1416);
    printf("di (int) 3.1416 =  %d\n", (int)3.1416);
}
