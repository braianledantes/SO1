#include <stdio.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <string.h>

/* programa A (productor) */
int main () {
    const int SIZE = 894;
    const char *name = "punto1";
    const char *filename = "/usr/share/doc/util-linux/col.txt";

    int shm_fd;
    void *ptr;

    /* create the shared memory segment */
    shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);

    /* configure the size of the shared memory segment */
    ftruncate(shm_fd, SIZE);

    /* now map the shared memory segment in the address space of the process */
    ptr = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED)
    {
        printf("Map faild\n");
        return -1;
    }

    /* Now write to the shared memory region. */
    int file = open(filename, O_RDONLY);
    read(file, ptr, SIZE);

    
    return 0;
}