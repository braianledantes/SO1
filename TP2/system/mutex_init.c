#include <xinu.h>

/*
* Crea un mutex con semaforos
*/
sid32 mutex_init(void)
{
    return semcreate(1);
}