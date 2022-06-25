#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>

const char *filename = "/usr/share/doc/libsdl1.2-dev/docs.html";
char *filebuffer;

int main(int argc, char *argv[])
{
    int c;

    // abrimos el archivo
    int fd = open(filename, O_RDONLY);
    // si no lo pudo abrir termina el programa
    if (fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (read(fd, &c, 1) != 0)
    {
        printf("%c", c);
    }

    close(fd);

    exit(EXIT_SUCCESS);
}