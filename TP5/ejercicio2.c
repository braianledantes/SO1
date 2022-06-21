#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>

const char *filename = "/usr/share/doc/libsdl1.2-dev/docs.html";
char *filebuffer;

int main(int argc, char *argv[]) {
    struct stat sb;

    // abrimos el archivo
    int fd = open(filename, O_RDONLY);
    // si no lo pudo abrir termina el programa
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    // si no pudo pedir la info del archivo termina el programa
    if (fstat(fd, &sb) == -1) {
        perror("stat");
        exit(EXIT_FAILURE);
    }

    // solicitamos memoria del tamanio del archivo
    filebuffer = malloc(sb.st_size);

    // guardamos el contenido del archivo en memoria
    read(fd, filebuffer, sb.st_size);
    // cerramos el archivo
    close(fd);

    // recorremos el contenido de forma inversa
    for (int i = sb.st_size - 1; i >= 0; i--)
    {
        printf("%c", filebuffer[i]);
    }
    

    exit(EXIT_SUCCESS);
}