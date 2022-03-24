/*
12. Usando printf() y getchar(), desarrolle un video juego del ahorcado.
    Utilice el código ahorcado.c como base.
*/

#include <stdio.h>
#include <stdlib.h> /* para las funciones system y exit */

const int MAX_LENGHT = 80;
char palabra[80];
int tamanioPalabra = 0;

char palabraAhorcado[80];
int cantFallos = 0;

int MAX_FALLOS = 6;

int main()
{
    solicitarPalabra();
    jugar();
}

void solicitarPalabra()
{
    char c;

    system("/bin/stty raw");
    int i = 0;
    while (i < MAX_LENGHT - 1)
    {
        printf("\r                                                                           ");
        printf("\rIngrese la palabra del ahorcado: %s", palabra);
        c = getchar();

        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        { // si la letra es valida
            palabra[i] = c;
            i++;
        }
        else if (c == 127)
        { // si se borro
            i--;
            if (i < 0)
                i = 0;
            palabra[i] = 0;
        }
        else if (c == 13)
        { // si se ingresa ENTER termina
            tamanioPalabra = i;
            palabra[i] = 0;
            break;
        }
    }

    system("/bin/stty sane erase ^H");

    // copia la palabra en el "pizarron"
    for (int i = 0; i < tamanioPalabra; i++)
    {
        if (i == tamanioPalabra)
            palabraAhorcado[i] = 0;
        else
            palabraAhorcado[i] = '_';
    }
}

/**
 * Verifica si la letra está en la palabra
 * @return int 1 ó 0
 */
int letraAcertada(char c)
{
    int r = 0;
    int i = 0;
    while (r == 0 && i < tamanioPalabra)
    {
        if (palabra[i] == c)
        {
            r = 1;
        }
        else
        {
            i++;
        }
    }
    return r;
}

void insertarLetra(char c)
{
    for (int i = 0; i < tamanioPalabra; i++)
    {
        if (palabra[i] == c)
        {
            palabraAhorcado[i] = c;
        }
    }
}

int verificarPalabra()
{
    int finalizo = 1;
    int i = 0;

    do
    {
        if (palabra[i] != palabraAhorcado[i])
        {
            finalizo = 0;
            break;
        }

        i++;

    } while (i < tamanioPalabra);

    return finalizo;
}

void jugar()
{
    int c;

    /* Decirle al sistema que el modo input es RAW */
    system("/bin/stty raw");

    do
    {
        printf("\rPalabra: %s fallos: %i/%i  ingrese una letra (0 para salir): ", palabraAhorcado, cantFallos, MAX_FALLOS);

        c = getchar();
        if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        {
            if (letraAcertada(c))
                insertarLetra(c);
            else
                cantFallos++;
        }

        if (c == '0')
            cantFallos = MAX_FALLOS;

    } while (verificarPalabra() == 0 && cantFallos < MAX_FALLOS);

    printf("\rPalabra: %s fallos: %i/%i  ingrese una letra (0 para salir): ", palabraAhorcado, cantFallos, MAX_FALLOS);

    system("/bin/stty sane erase ^H");
    printf("\n");
}
