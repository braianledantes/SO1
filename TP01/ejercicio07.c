/*
Utilice el ejemplo de la clase para crear un programa en Linux,
que le pida al sistema operativo crear un nuevo proceso hijo.
*/

#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
    /* fork a child process */
    int pid = fork();

    if (pid < 0) /* error occurred */
    {
        printf(stderr, "Fork Field\n");
        return 1;
    }
    else if (pid == 0) /* child process */
    {
        execlp("/bin/ls", "ls", NULL);
    }
    else /* parent process */
    {
        wait(NULL);
        printf("Child Complete\n");
    }

    return 0;
}