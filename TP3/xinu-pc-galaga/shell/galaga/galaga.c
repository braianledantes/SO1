#include <xinu.h>

#include "titlescreen.h"
#include "playerImage.h"
#include "enemy.h"
#include "boss.h"
#include "gameover.h"
#include "shoot.h"

extern unsigned char tecla_actual;
typedef unsigned short u16;
#define RGB(r, g, b) (r | (g << 5) | (b << 10))
// #define REG_DISPCNT *(u16 *)0x4000000
#define extern videoBuffer
#define MODE3 3
#define BG2_ENABLE (1 << 10)
#define WHITE RGB(31, 31, 31)
#define BLACK RGB(0, 0, 0)

/*
#define BUTTON_A		(1<<0)
#define BUTTON_B		(1<<1)
#define BUTTON_SELECT	(1<<2)
#define BUTTON_START	(1<<3)
#define BUTTON_RIGHT	(1<<4)
#define BUTTON_LEFT		(1<<5)
#define BUTTON_UP		(1<<6)
#define BUTTON_DOWN		(1<<7)
#define BUTTON_R		(1<<8)
#define BUTTON_L		(1<<9)
#define KEY_DOWN_NOW(key)  (~(BUTTONS) & key)
*/
//#define BUTTONS *(volatile unsigned int *)0x4000130

#define BUTTON_A 0x39	  // espace
#define BUTTON_B 0x21	  // f
#define BUTTON_SELECT 0x1 // escape
#define BUTTON_START 0x1c // enter
#define BUTTON_RIGHT 0x4d // right arrow
#define BUTTON_LEFT 0x4b  // left arrow
#define BUTTON_UP 0x48	  // up arrow
#define BUTTON_DOWN 0x50  // down arrow
#define BUTTON_R 0x10	  // q
#define BUTTON_L 0x12	  // e
//#define KEY_DOWN_NOW(key) (tecla_actual == key)

// variable definitions
#define playerspeed 2
#define enemyspeed 1
#define fastXSpeed 3
#define fastYSpeed 2

#define CONTINUAR 1
#define FINALIZAR -1

void setPixel(int x, int y, u16 color);
void drawRect(int x, int y, int width, int height, u16 color);
void drawHollowRect(int x, int y, int width, int height, u16 color);
void drawImage3(int x, int y, int width, int height, const u16 *image);
void delay_galaga();
void waitForVBlank();

// helpers
void initialize();
void drawEnemies();
void endGame();
int collision(u16 enemyX, u16 enemyY, u16 enemyWidth, u16 enemyHeight, u16 playerX, u16 playerY);

// objects
struct Players
{
	volatile u16 playerX;
	volatile u16 playerY;
};
struct Enemy
{
	volatile u16 enemyX;
	volatile u16 enemyY;
};
struct FastEnemy
{
	volatile u16 fastX;
	volatile u16 fastY;
};

int shoots[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int curr_shot = 0;
#define N_SHOOTS 10

pid32 pid_proceso1, pid_proceso2, pid_proceso3, pid_proceso4, pid_proceso5, pid_galaga;
int continuar;		 // para reiniciar o finalizar el juego
sid32 sem_continuar; // indica al proceso galaga si tiene que reiniciar o finalizar el juego

struct Enemy easyEnemies[9];
struct Enemy hardEnemies[9];
struct Players player;
struct FastEnemy fast;

void teclado(void), jugador(void), colisionador(void), navesYDisparos(void);
char tecla_presionada;

// proceso 1
void teclado(void)
{
	open(KEYBOARD, 0, 0);
	while (recvclr() == OK)
	{
		// tecla_presionada = getc(KEYBOARD);
		read(KEYBOARD, &tecla_presionada, 1);

		// player movement input
		if (tecla_presionada == BUTTON_LEFT)
		{
			send(pid_proceso2, BUTTON_LEFT);
		}
		if (tecla_presionada == BUTTON_RIGHT)
		{
			send(pid_proceso2, BUTTON_RIGHT);
		}
		if (tecla_presionada == BUTTON_UP)
		{
			send(pid_proceso2, BUTTON_UP);
		}
		if (tecla_presionada == BUTTON_DOWN)
		{
			send(pid_proceso2, BUTTON_DOWN);
		}
		// player shots
		if (tecla_presionada == BUTTON_A)
		{
			send(pid_proceso2, BUTTON_A);
		}
		// go back to title screen if select button is pressed
		if (tecla_presionada == BUTTON_SELECT)
		{
			send(pid_proceso5, BUTTON_SELECT);
		}
	}
	close(KEYBOARD);
}

// proceso 2
void jugador(void)
{
	umsg32 msg;
	while (1)
	{
		// draw player
		drawImage3(player.playerX, player.playerY, 24, 24, playerImage);
		drawHollowRect(player.playerX - 1, player.playerY - 1, 26, 26, BLACK);
		drawHollowRect(player.playerX - 2, player.playerY - 2, 28, 28, BLACK);

		msg = recvclr();

		// player movement input
		if (msg == BUTTON_LEFT && (player.playerX > 0))
		{
			player.playerX -= playerspeed;
		}
		if (msg == BUTTON_RIGHT && (player.playerX <= 216))
		{
			player.playerX += playerspeed;
		}
		if (msg == BUTTON_UP && (player.playerY > 25))
		{
			player.playerY -= playerspeed;
		}
		if (msg == BUTTON_DOWN && (player.playerY <= 136))
		{
			player.playerY += playerspeed;
		}

		// agrega disparos al arreglo de disparos
		if (msg == BUTTON_A)
		{
			if (shoots[curr_shot] == 0)
			{
				shoots[curr_shot] = (136 - (136 - player.playerY)) * 240 + player.playerX + 9; /* 24 widht player */
				curr_shot++;
				if (curr_shot >= N_SHOOTS)
					curr_shot = 0;
			};
		}
		waitForVBlank();
		sleepms(50);
	}
}

// proceso 3
void colisionador(void)
{
	umsg32 msg;
	while (1)
	{
		// colision con enemigos faciles
		for (int a = 0; a < 9; a++)
		{
			if (collision(easyEnemies[a].enemyX, easyEnemies[a].enemyY, 20, 20, player.playerX, player.playerY))
			{
				send(pid_proceso5, 1);
			}
		}
		// colision de naves enemigas con disparos
		for (int i = 0; i < N_SHOOTS; i++)
		{
			// check hits of shoots
			for (int j = 0; j < 9; j++)
			{
				if (j != 0)
				{
					if (collision(easyEnemies[j].enemyX, easyEnemies[j].enemyY, 15, 15, shoots[i] % 240, shoots[i] / 240))
					{
						msg = (j << 4) | i;
						send(pid_proceso4, msg);
					}
				}
			}
		}
		// colision con enemnigos dificiles
		for (int a = 0; a < 9; a++)
		{
			if (collision(hardEnemies[a].enemyX, hardEnemies[a].enemyY, 20, 20, player.playerX, player.playerY))
			{
				send(pid_proceso5, 1);
			}
		}
		// colision con enemigo facil
		if (collision(fast.fastX, fast.fastY, 15, 15, player.playerX, player.playerY))
		{
			send(pid_proceso5, 1);
		}
	}
}

// proceso 4
void navesYDisparos(void)
{
	umsg32 msg;
	int i, j;
	while (1)
	{
		msg = recvclr();
		if (msg != OK)
		{
			// desdibuja el enemigo eliminado
			j = msg >> 4;
			i = msg ^ (j << 4);

			drawRect(easyEnemies[j].enemyX, easyEnemies[j].enemyY, 20, 20, BLACK);
			drawRect((shoots[i] % 240), (shoots[i] / 240) + 4, 5, 5, BLACK);
			easyEnemies[j].enemyY = 0;
			shoots[i] = 0;
		}

		// draw shots
		for (int i = 0; i < N_SHOOTS; i++)
		{
			if (shoots[i] != 0)
			{
				drawRect((shoots[i] % 240), (shoots[i] / 240) + 4, 5, 5, BLACK);
				drawImage3((shoots[i] % 240), (shoots[i] / 240), 5, 5, shoot);
				shoots[i] = shoots[i] - 240 * 4;
				if (shoots[i] <= 0)
					shoots[i] = 0;
			}
		}

		// draw easy enemies with downward movement
		for (int a = 0; a < 9; a++)
		{
			easyEnemies[a].enemyY += enemyspeed;
			drawImage3(easyEnemies[a].enemyX, easyEnemies[a].enemyY, 20, 20, enemy);
			if (easyEnemies[a].enemyY >= 160)
			{
				easyEnemies[a].enemyY = 0;
			}
		}
		// draw hard enemies
		for (int a = 0; a < 9; a++)
		{
			hardEnemies[a].enemyY += enemyspeed;
			drawImage3(hardEnemies[a].enemyX, hardEnemies[a].enemyY, 20, 20, enemy);
			if (hardEnemies[a].enemyY >= 228)
			{
				hardEnemies[a].enemyY = 0;
			}
			if ((hardEnemies[a].enemyY >= 200) && (easyEnemies[a].enemyY <= 45))
			{
				hardEnemies[a].enemyY = 160;
			}
			// space enemies apart
			if ((hardEnemies[a].enemyY >= 200) && (easyEnemies[a].enemyY <= 45))
			{
				hardEnemies[a].enemyY = 160;
			}
			if ((easyEnemies[a].enemyY >= 120) && (hardEnemies[a].enemyY >= 170))
			{
				hardEnemies[a].enemyY = 160;
			}
		}
		// draw fast enemy
		drawImage3(fast.fastX, fast.fastY, 15, 15, boss);
		drawHollowRect(fast.fastX - 1, fast.fastY - 1, 17, 17, BLACK);
		drawHollowRect(fast.fastX - 2, fast.fastY - 2, 19, 19, BLACK);
		if (fast.fastX >= 240)
		{
			fast.fastX = 0;
		}
		if (fast.fastY >= 200)
		{
			fast.fastY = player.playerY - 20;
		}

		waitForVBlank();
		sleepms(50);
	}
}

int galaga(void)
{
	pid_galaga = getpid();
	sem_continuar = semcreate(0);

	// REG_DISPCNT = MODE3 | BG2_ENABLE;
	// initalize title screen
	print_text_on_vga(10, 20, "GALAGA ");
	drawImage3(0, 0, 240, 160, titlescreen);

	do
	{
		// easy enemy wave set setup
		for (int a = 0; a < 9; a++)
		{
			easyEnemies[a].enemyX = (28 * a);
			easyEnemies[a].enemyY = 0;
		}
		easyEnemies[1].enemyX = 240;
		easyEnemies[4].enemyX = 240;
		easyEnemies[8].enemyX = 240;
		// difficult enemies setup
		for (int a = 0; a < 9; a++)
		{
			hardEnemies[a].enemyX = (28 * a);
			hardEnemies[a].enemyY = 160;
		}
		hardEnemies[3].enemyX = 240;
		hardEnemies[6].enemyX = 240;
		// player setup
		player.playerX = 120;
		player.playerY = 136;
		// fast enemy "boss" setup
		fast.fastX = 0;
		fast.fastY = 30;
		for (int i = 0; i < N_SHOOTS; i++)
		{
			shoots[i] = 0;
		}

		open(KEYBOARD, 0, 0);
		while (1)
		{
			read(KEYBOARD, &tecla_presionada, 1);
			if (tecla_presionada == BUTTON_START)
			{
				break;
			}
		}
		close(KEYBOARD);

		// start black screen for drawing
		drawBlackScreen();

		// Iniciar los procesos
		pid_proceso1 = create(teclado, 1024, 20, "teclado", 0);
		pid_proceso2 = create(jugador, 1024, 20, "jugador", 0);
		pid_proceso3 = create(colisionador, 1024, 20, "colisionador", 0);
		pid_proceso4 = create(navesYDisparos, 1024, 20, "navesYDisparos", 0);
		pid_proceso5 = create(endGame, 1024, 20, "endGame", 0);
		resume(pid_proceso1);
		resume(pid_proceso2);
		resume(pid_proceso3);
		resume(pid_proceso4);
		resume(pid_proceso5);

		wait(sem_continuar);
	} while (continuar == CONTINUAR);

	return 0;
}

int collision(u16 enemyX, u16 enemyY, u16 enemyWidth, u16 enemyHeight, u16 playerX, u16 playerY)
{
	// check if bottom right corner of enemy is within player
	if (((enemyX + enemyWidth) > playerX) && ((enemyY + enemyHeight) > playerY) && ((enemyX + enemyWidth) < (playerX + 24)) && ((enemyY + enemyWidth) < (playerY + 24)))
	{
		return 1;
	}
	// check bottom left corner of enemy
	if ((enemyX < (playerX + 24)) && (enemyX > playerX) && ((enemyY + enemyHeight) > playerY) && ((enemyY + enemyHeight) < (playerY + 24)))
	{
		return 1;
	}
	// check top left corner
	if ((enemyX < (playerX + 24)) && (enemyX > playerX) && (enemyY > playerY) && (enemyY < (playerY + 24)))
	{
		return 1;
	}
	// check top right corner
	if (((enemyX + enemyWidth) < (playerX + 24)) && ((enemyX + enemyWidth) > playerX) && (enemyY > playerY) && (enemyY < (playerY + 24)))
	{
		return 1;
	}
	return 0;
}

// proceso 5
void endGame()
{
	receive();

	send(pid_proceso1, 10); // le dice al teclado que termine
	kill(pid_proceso2);
	kill(pid_proceso3);
	kill(pid_proceso4);

	// start Game Over State
	drawImage3(0, 0, 240, 160, gameover);
	drawHollowRect(0, 0, 240, 160, WHITE);

	waitForVBlank();
	sleepms(1000);

	open(KEYBOARD, 0, 0);
	while (1)
	{
		read(KEYBOARD, &tecla_presionada, 1);
		// enter presionado
		if (tecla_presionada == BUTTON_START)
		{
			send(pid_galaga, CONTINUAR);
			continuar = CONTINUAR;
			signal(sem_continuar);
			break;
		}
		// escape precionado
		if (tecla_presionada == BUTTON_SELECT)
		{
			drawBlackScreen();
			continuar = FINALIZAR;
			signal(sem_continuar);
			break;
		}
	}
	close(KEYBOARD);
}

void drawBlackScreen(void)
{
	for (int i = 0; i < 240; i++)
	{
		for (int j = 0; j < 160; j++)
		{
			setPixel(i, j, BLACK);
		}
	}
}