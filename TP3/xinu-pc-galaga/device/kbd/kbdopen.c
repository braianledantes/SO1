/* kbdopen.c  -  kbdopen */
#include <xinu.h>

/*------------------------------------------------------------------------
 * kbdopen  -  Open the ps/2 keyboard device
 *------------------------------------------------------------------------
 */
struct kbd_data kbd;

devcall	kbdopen (
	 struct	dentry	*devptr,	/* Entry in device switch table	*/
	 char	*name,			/* Unused for a kbd */
	 char	*mode			/* Unused for a kbd */
	)
{
	wait(kbd.mutex);
	kbd.pid = getpid();
}
