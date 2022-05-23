#include <xinu.h>

/*
* Un proceso libera el mutex
*/
void mutex_unlock(sid32 sem)
{
    signal(sem);
}