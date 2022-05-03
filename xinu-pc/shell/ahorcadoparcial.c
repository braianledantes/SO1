#include <xinu.h>

int N = 8; /* cantidad de letras */
char secreta[] = "casandra";
char ui[] = "________";

int vidas = 5;
int restante = 8;
char c;

sid32 mutex, entrada, computar;

void p1(void), p2(void), p3(void), p4(void);
pid32 pid_p1, pid_p2, pid_p3, pid_p4;

void ahorcadoparcial()
{
	entrada = semcreate(1);
	computar = semcreate(0);
	mutex = semcreate(1);

	pid_p1 = create(p1, 1024, 20, "p1", 0);
	pid_p2 = create(p2, 1024, 20, "p2", 0);
	pid_p3 = create(p3, 1024, 20, "p3", 0);
	pid_p4 = create(p4, 1024, 20, "p4", 0);

	/* Decirle al sistema que el modo input es RAW */
	control(0, TC_MODER, 0, 0);

	resume(pid_p1);
	resume(pid_p2);
	resume(pid_p3);
	resume(pid_p4);
}

void p1()
{
	while (1)
	{
		wait(entrada);
		c = getchar();
		signal(computar);
	}
}

void p2()
{
	int i, j;

	while (1)
	{
		wait(computar);
		wait(mutex);
		/* controlar si es una letra en la palabra */
		j = 0;
		for (i = 0; i < N; i++)
		{
			if (ui[i] == '_' && secreta[i] == c)
			{
				ui[i] = c;
				j++;
			}
		}

		restante = restante - j;
		if (j == 0)
			vidas--;

		signal(mutex);
		signal(entrada);
	}
}

/*
 * Muesta al usuario el estado del juego
 */
void p3()
{
	while (1)
	{
		wait(mutex);
		printf("\r                                                          ");
		printf("\r %s  . Vidas=%d . Ingrese una letra (0 para salir): ", ui, vidas);
		signal(mutex);
		sleepms(1000);
	}
}

/*
 *
 */
void p4()
{
	while (1)
	{
		if (vidas == 0)
		{
			printf("\r\n PERDISTE \r\n");
			break;
		}
		else if (restante == 0)
		{
			printf("\r\n GANASTE \r\n");
			break;
		}
	}

	kill(pid_p1);
	kill(pid_p2);
	kill(pid_p3);
}
