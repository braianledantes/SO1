#include <xinu.h>

void procesoA(void), procesoB(void), procesoC(void);

void tp2ej1(void)
{
    int prioPla = getprio(getpid()); // prioridad del planificador

    printf("proceso del planificador con prioridad = %d\n", prioPla);

    pid32 pid_a = create(procesoA, 1024, 20, "proceso_a", 0);
    pid32 pid_b = create(procesoB, 1024, 20, "proceso_b", 0);
    pid32 pid_c = create(procesoC, 1024, 20, "proceso_c", 0);

    resume(pid_a);
    resume(pid_b);
    resume(pid_c);

    high_level_sheduler(pid_a, 120, pid_b, 60, pid_c, 20);
}

void high_level_sheduler(int pid_a, int ms_a,
                         int pid_b, int ms_b,
                         int pid_c, int ms_c)
{
    /* Obtener el PID del planificador del proceso actual */
    int pid_pla = getpid();
    /* Obtener la prioridad del planificador (proceso con la mas alta prioridad) */
    uint32 prio_pla = getprio(pid_pla);

    uint32 prio_process;

    while (1)
    {
        printf("turno al proceso a.\n");
        /* obtener la prioridad del proceso a */
        prio_process = getprio(pid_a);
        /* cambiar la prioridad del proceso a, a un valor igual a la
           prioridad del planificar menos 1 */
        chprio(pid_a, prio_pla - 1);
        /* liberar la CPU por ms_a ms (ponerse a dormir), por lo que
           Xinu asignará la CPU al proceso a*/
        sleepms(ms_a);
        /* devolverle al proceso a su prioridad original*/
        chprio(pid_a, prio_process);

        /* planificar aquí el proceso b */
        printf("turno al proceso b.\n");
        prio_process = getprio(pid_b);
        chprio(pid_b, prio_pla - 1);
        sleepms(ms_b);
        chprio(pid_b, prio_process);

        /* planificar aquí el proceso c */
        printf("turno al proceso c.\n");
        prio_process = getprio(pid_c);
        chprio(pid_c, prio_pla - 1);
        sleepms(ms_c);
        chprio(pid_c, prio_process);
    }
}

void procesoA(void)
{
    int a = 0;
    while (1)
    {
        a++;
        sleepms(10);
        printf("a = %d\n", a);
    }
}

void procesoB(void)
{
    int b = 0;
    while (1)
    {
        b++;
        sleepms(10);
        printf("b = %d\n", b);
    }
}

void procesoC(void)
{
    int c = 0;
    while (1)
    {
        c++;
        sleepms(10);
        printf("c = %d\n", c);
    }
}