#include <xinu.h>

sid32 prod_sem, cons_sem;

void produce(void), consume(void);

int32 n=0;

void tp2ej2 (void)
{
	prod_sem = semcreate(1);
	cons_sem = semcreate(0);

	resume (create (consume, 1024, 20, "cons", 0));
	resume (create (produce, 1024, 20, "prod", 0));
}


void produce (void)
{
	int32 i;

	for(i=1; i<=2000; i++)
	{
		wait(prod_sem);
		n++;
		//sleep(2);
		signal(cons_sem);
	}
}

void consume (void)
{
	int32 i;
	for(i=1; i<=2000; i++)
	{
		wait(cons_sem);
		printf("the value of n is %d \n", n);
		//sleep(1);
		signal(prod_sem);
	}

}