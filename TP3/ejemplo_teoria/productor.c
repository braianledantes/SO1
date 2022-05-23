#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main () {
    const int SIZE = 4096;
    const char *name = "OS";
    const char *mess0 = "Studing ";
    const char *mess1 = "Operating Systems" ;

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

    sprintf(ptr, "%s", mess0);
    ptr += strlen(mess0);
    sprintf(ptr, "%s", mess1);

    return 0;
}