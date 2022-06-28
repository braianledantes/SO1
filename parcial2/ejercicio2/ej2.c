#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/stat.h>

const char *filename = "./principe_y_mendigo.txt";
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

    
    
    char palabra[] = "Catalina";
    int inicio = 65512;
    int longitud = sizeof(palabra);

    printf("pid: %d\n", getpid());

    if (sb.st_size >= inicio + longitud)
    {
        for (int i = 0; i < longitud; i++)
        {
            palabra[i] = filebuffer[inicio + 1];
            printf("%c", palabra[i]);
        }
        printf("\n");

        if (palabra == "Catalina")
        {
            printf("Es Catalina\n");
        } else {
            printf("NO es Catalina\n");
        }
    } else {
        printf("el archivo no es tan grande\n");
    }

    sleep(20);

    exit(EXIT_SUCCESS);
}