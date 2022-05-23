#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>

int main () {
    const int SIZE = 894;
    const char *name = "punto1";
    const char *filename = "/usr/share/doc/util-linux/source-code-management.txt";

    int shm_fd;
    void *ptr;

    /* create the shared memory segment */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    ftruncate(shm_fd, SIZE);

    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        printf("Map faild\n");
        return -1;
    }

    int file = open(filename, O_RDONLY);
    read(file, ptr, SIZE);

    return 0;
}