/*
Utilice el ejemplo de la clase para crear un programa en Linux,
que le pida al sistema operativo crear un nuevo proceso hijo.
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

void main()
{
    /* fork a child process */
    int pid = fork();

    if (pid < 0)
    { /* error occurred */
        printf(stderr, "Fork Field\n");
        return 1;
    }
    else if (pid == 0)
    { /* child process */
        printf("Proceso hijo %d\n", pid);
    }
    else
    { /* parent process */
        printf("Proceso padre. Mi hijo es el pid = %d\n", pid);
        wait(NULL);
        printf("Child Complete\n");
    }

    return 0;
}