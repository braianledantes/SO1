#include <xinu.h>

unsigned char kbdgetc(
    struct	dentry	*devptr		/* no lo usamos :(	*/
)
{
    if (getpid() == kbd.pid)
    {
        wait(kbd.sem_buffer);
        unsigned char c = kbd.buffer[kbd.head];
        kbd.head = (kbd.head + 1) % KEYBORD_BUFFER_LENGTH;
        return c;
    }
    else
    {
        return SYSERR;
    }
    
}