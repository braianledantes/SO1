/* programa usamem.c */

#include <stdio.h>
#include <stdlib.h>
#define N 240000
#define BSIZE 4096
#define SMALL 4

char *pp;

main()
{
    int i, j, k;
    // printf("pid: %d\n", getpid());
    // printf("main: 0x%llx, i: 0x%llx, j: 0x%llx\n", &main, &i, &j);

    pp = malloc(N * BSIZE);
    if (pp == NULL)
    {
        printf("Error al reservar memoria.\n");
        exit(1);
    }

    /* RECORREMOS y modificamos todo el segmento solicitado */
    for (k = 0; k < BSIZE / SMALL; k++)
    {
        for (i = 0; i < N; i++)
        {
            for (j = 0; j < SMALL; j++)
            {
                *(pp + i * BSIZE + (SMALL * k + j)) = 2; // pp[i][SMALL*k+j] = 2;
            }
        }
    }

    /* RECORREMOS y VERIFICAMOS QUE HEMOS MODIFICADO todo el segmento solicitado */
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < BSIZE; j++)
        {
            if (*(pp + i * BSIZE + j) != 2)
            { // if (pp[i][j] != 2)
                printf("ERROR! \n");
                exit(1);
            }
        }
    }

    printf("OK \n");
}