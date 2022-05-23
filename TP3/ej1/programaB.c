#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>

int main () {
    const int SIZE = 894;
    const char *name = "punto1";

    int shm_fd;
    void *ptr;
    int i;

    shm_fd = shm_open(name, O_RDONLY, 0666);
    if (shm_fd == -1)
    {
        printf("shared memory failed\n");
    }
    

    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        printf("Map faild\n");
        return -1;
    }

    printf("%s", (char *) ptr);

    if (shm_unlink(name) == -1)
    {
        printf("Error removing %s\n", name);
        exit(-1);
    }
    

    return 0;
}