#include <xinu.h>
void    sndA(void), sndB(void);
/*------------------------------------------------------------------------
 * main  --  example of creating processes in Xinu
 *------------------------------------------------------------------------
 */
void    ejer5(void)
{
    int idp1 = create(sndA, 1024, 20, "process 1", 0);
    int idp2 = create(sndB, 1024, 20, "process 2", 0);
    resume( idp1 );
    resume( idp2 );
    sleep(10);
    int pid = getpid();
    kill(idp1);
    kill(idp2);
    printf("pid %i \n", pid);
}
/*------------------------------------------------------------------------
 * sndA  --  repeatedly emit 'A' on the console without terminating
 *------------------------------------------------------------------------
 */
void    sndA(void)
{
    while( 1 ) {
        //sleep(1);
        putc(CONSOLE, 'A');
    }
}
/*------------------------------------------------------------------------
 * sndB  --  repeatedly emit 'B' on the console without terminating
 *------------------------------------------------------------------------
 */
void    sndB(void)
{
    while( 1 ) {
        //sleep(1);
        putc(CONSOLE, 'B');
    }
}
