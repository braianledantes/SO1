#include <xinu.h>

void produce(void), consume(void);

int32 n=0;

void tp2ej2 (void)
{
	resume (create (consume, 1024, 20, "cons", 0));
	resume (create (produce, 1024, 20, "prod", 0));
}


void produce (void)
{
	int32 i;

	for(i=1; i<=2000; i++)
		n++;

}

void consume (void)
{
	int32 i;
	for(i=1; i<=2000; i++)
		printf("the value of n is %d \n", n);

}