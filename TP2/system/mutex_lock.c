#include <xinu.h>

/**
 * un proceso solicita un mutex
 */
void mutex_lock(sid32 sem)
{
    wait(sem);
}