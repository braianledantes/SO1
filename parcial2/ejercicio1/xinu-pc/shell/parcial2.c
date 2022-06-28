#include <xinu.h>

#define BUTTON_ESCAPE 0x1 // tecla escape

void proceso1(void), proceso2(void);
pid32 pidp1, pidp2;
sid32 terminar;

parcial2() {
    terminar = semcreate(0);
    
    pidp1 = create(proceso1, 1024, 20, "teclado", 0);
    pidp2 = create(proceso2, 1024, 20, "pantalla", 0);
    printf("parcial2\n");

    resume(pidp1);
    resume(pidp2);

    wait(terminar);
    send(pidp1, 10);
}


void proceso1() {
    int tecla;

    open(KEYBOARD, 0, 0);
	while (recvclr() == OK)
	{
        read(KEYBOARD, &tecla, 1);
        send(pidp2, tecla);
    }
    close(KEYBOARD);
}

void proceso2() {
    int scancode = receive();
    char t[80];

    while (scancode != BUTTON_ESCAPE)
    {
        sprintf(t, "tecla presionada: 0x%x ", scancode);
        print_text_on_vga(10, 340, t); 
        scancode = receive();
    }
    
    sleep(5);
    printf("\n");

    signal(terminar);
}