#include <xinu.h>

void buscar (int, int);

int n;
sid32 mutex, sumatoria;

recuperatorio() {
	n = 0;
	int p;
	int cantProcesos = 10;
	int inicio = 0;
	int fin = 99;
	mutex_create2();
	sumatoria = semcreate(0);

	for (p=0; p<cantProcesos; p++) {
		resume(create(buscar, 1024, 20, "primos", 2, inicio, fin));
		inicio = fin + 1;
		fin = inicio + 99;
	}

	for (p=0; p<cantProcesos; p++) {
		wait(sumatoria);
	}

	printf("La suma de los nros primos menores a 1000 es = %d \n", n);
}

void buscar(int ini, int fin) {
    int i,j;
	pid32 pid = getpid();

	for (i=ini; i<=fin; i++) {

		/* verificamos si i es primo */

		for (j=i-1; j>1; j--) {
			if ((i % j) == 0) break;
		}

		/* si j es distinto de 1 entonces i no es primo */
		if (j == 1) {
			mutex_lock2();
			printf("%d es primo porque es solo divisible por 1 y por %d\n", i, i);
			n = n + i;
			mutex_unlock2();
		}
	}

	signal(sumatoria);
}

void mutex_create2() {
	mutex = semcreate(1);
}

void mutex_lock2() {
	wait(mutex);
}

void mutex_unlock2() {
	signal(mutex);
}