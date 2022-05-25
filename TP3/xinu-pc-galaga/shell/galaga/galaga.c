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

#define BUTTON_A	0x24
#define BUTTON_B	0x25 
#define BUTTON_SELECT	0x03
#define BUTTON_START	0x2c
#define BUTTON_RIGHT	0x1f
#define BUTTON_LEFT	0x1e	
#define BUTTON_UP	'w'
#define BUTTON_DOWN 	's'	
#define BUTTON_R	'1'
#define BUTTON_L	'2'
#define KEY_DOWN_NOW(key)  (tecla_actual == key)

//variable definitions
#define playerspeed 2
#define enemyspeed 1
#define fastXSpeed 3
#define fastYSpeed 2


void setPixel(int x, int y, u16 color);
void drawRect(int x, int y, int width, int height, u16 color);
void drawHollowRect(int x, int y, int width, int height, u16 color);
void drawImage3(int x, int y, int width, int height, const u16* image);
void delay_galaga();
void waitForVBlank();

//helpers
void initialize();
void drawEnemies();
void endGame();
int collision(u16 enemyX, u16 enemyY, u16 enemyWidth, u16 enemyHeight, u16 playerX, u16 playerY);

//objects
struct Players {
	volatile u16 playerX;
	volatile u16 playerY;
};
struct Enemy {
	volatile u16 enemyX;
	volatile u16 enemyY;
};
struct FastEnemy {
	volatile u16 fastX;
	volatile u16 fastY;
};

int shoots[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int curr_shot = 0;
#define N_SHOOTS 10

pid32 pid_proceso1, pid_proceso2, pid_proceso3, pid_proceso4, pid_proceso5;
sid32 terminar;

struct Enemy easyEnemies[9];
struct Enemy hardEnemies[9];
struct Players player;
struct FastEnemy fast;

void teclado(void), jugador(void), colisionador(void), navesYDisparos(void);

// proceso 1
void teclado(void)
{
	while (1)
	{
		// player movement input
		if (KEY_DOWN_NOW(BUTTON_LEFT))
		{
			send(pid_proceso2, BUTTON_LEFT);
		}
		if (KEY_DOWN_NOW(BUTTON_RIGHT))
		{
			send(pid_proceso2, BUTTON_RIGHT);
		}
		if (KEY_DOWN_NOW(BUTTON_UP))
		{
			send(pid_proceso2, BUTTON_UP);
		}
		if (KEY_DOWN_NOW(BUTTON_DOWN))
		{
			send(pid_proceso2, BUTTON_DOWN);
		}
		if (KEY_DOWN_NOW(BUTTON_A))
		{
			send(pid_proceso2, BUTTON_A);
		}
	}
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
				shoots[curr_shot] = 136 * 240 + player.playerX + 9; /* 24 widht player */
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

	while (1)
	{
		
	}

}

// proceso 4
void navesYDisparos(void)
{
	umsg32 msg;
	while (1)
	{
		
	}
}

int galaga(void) {
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

	// REG_DISPCNT = MODE3 | BG2_ENABLE;
	// initalize title screen
	print_text_on_vga(10, 20, "GALAGA ");
	drawImage3(0, 0, 240, 160, titlescreen);

	while (1)
	{
		if (KEY_DOWN_NOW(BUTTON_START))
		{
			break;
		}
	}
	// start black screen for drawing
	for (int i = 0; i < 240; i++)
	{
		for (int j = 0; j < 160; j++)
		{
			setPixel(i, j, BLACK);
		}
	}

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
	terminar = semcreate(0);

	wait(terminar);
	return 0;
}


int collision(u16 enemyX, u16 enemyY, u16 enemyWidth, u16 enemyHeight, u16 playerX, u16 playerY) {
	//check if bottom right corner of enemy is within player
	if (((enemyX + enemyWidth) > playerX) && ( (enemyY + enemyHeight) 
		> playerY ) &&  ((enemyX + enemyWidth) < (playerX + 24)) 
		&& ((enemyY + enemyWidth) < (playerY + 24))) {
		return 1;
	} 
	//check bottom left corner of enemy
	if ( (enemyX < (playerX + 24)) 
		&& (enemyX > playerX)
		&& ((enemyY + enemyHeight) > playerY)
		&& ((enemyY + enemyHeight) < (playerY + 24))
		) {
		return 1;
	}
	//check top left corner
	if ( (enemyX < (playerX + 24)) 
		&& (enemyX > playerX)
		&& (enemyY > playerY)
		&& (enemyY < (playerY + 24))
		) {
		return 1;
	}	
	//check top right corner
	if ( ((enemyX + enemyWidth) < (playerX + 24)) 
		&& ((enemyX + enemyWidth) > playerX)
		&& (enemyY > playerY)
		&& (enemyY < (playerY + 24))
		) {
		return 1;
	}	
	return 0;
}

void endGame() {
	receive();
	//start Game Over State
	drawImage3(0, 0, 240, 160, gameover);
	drawHollowRect(0, 0, 240, 160, WHITE);
	while(1) {
		if (KEY_DOWN_NOW(BUTTON_SELECT)) {
			galaga();
		}
		if (KEY_DOWN_NOW(BUTTON_START))	{
			galaga();
		}
	}
	signal(terminar);
}
