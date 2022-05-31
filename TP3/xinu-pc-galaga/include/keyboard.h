
#define inportb(p)      inb(p)
#define outportb(p,v)   outb(p,v)

#define KEYBOARD_DATAREG 0x60  // :Data Register(Read\Write)
#define KEYBOARD_CMDREG 0x64   // :Command Register(Read\Write)
#define KEYBORD_BUFFER_LENGTH 10
#define NONE_PROCESS 0

extern unsigned char kblayout [128];  // { ... } Fill your layout yourself 

struct kbd_data
{
    pid32 pid;
    unsigned char buffer[KEYBORD_BUFFER_LENGTH];
    sid32 mutex;
    sid32 sem_buffer;
    sid32 mutex_buffer;
    int head;
    int tail; // cola
}; 

extern struct kbd_data kbd;

