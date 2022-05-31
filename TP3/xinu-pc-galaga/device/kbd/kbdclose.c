/* kbdclose.c  -  kbdclose */

#include <xinu.h>

struct kbd_data kbd;

/*------------------------------------------------------------------------
 * kbdclose  -  Close the keyboard device
 *------------------------------------------------------------------------
 */
devcall	kbdclose (
	  struct dentry	*devptr		/* Entry in device switch table	*/
	)
{
	if (getpid() == kbd.pid)
	{
		kbd.pid = NONE_PROCESS;
		signal(kbd.mutex);
	}
	else 
	{
		return SYSERR;
	}
	
}
