/* source: https://forum.osdev.org/viewtopic.php?t=10247 */

/* kbdhandler.c - kbdhandler */

#include <xinu.h>

struct kbd_data kbd;

unsigned char tecla_actual;

unsigned char get_scancode()
{
    unsigned char inputdata;
    inputdata = inportb(KEYBOARD_DATAREG);
    return inputdata;
}


/*------------------------------------------------------------------------
 *  kbdhandler  -  Handle an interrupt for the keyboard device
 *------------------------------------------------------------------------
 */
void kbdhandler(void)
{
	char t[80];
	unsigned char scancode; 
	unsigned int shift_key = 0;
	int i = 10;

	scancode = get_scancode();
	tecla_actual = scancode;
	sprintf(t, "kbd: 0x%x     ", scancode);
	print_text_on_vga(10, 300, t);

	if(scancode == 0x2A) {
		shift_key = 1;//Shift key is pressed
	} else if(scancode & 0xAA) {
		shift_key = 0;//Shift Key is not pressed
	} else {          
		if (scancode & 0x80) {
			int shiftaltctrl = 1;//Put anything to see what special keys were pressed
		} else {  
		}     
	}

	if (kbd.head != (kbd.tail + 1) % KEYBORD_BUFFER_LENGTH)
	{
		kbd.buffer[kbd.tail] = scancode;
		
		kbd.tail = (kbd.tail + 1) % KEYBORD_BUFFER_LENGTH;
		signal(kbd.sem_buffer);
	}
	
}

