/* **********************
   Source code for player
   ********************** */

#include "game.h"
#include <ctime>
#include "laser.h"
#include "player.h"

/* Function that initializes the player. 
   Values like position and states etc are initialized. */
void InitializePlayer(Player *p, int points) {
	p->state = alive;
	p->x = rand() % 370;
	p->y = 320;	
	p->hits = points;
	p->ExplosionTime = 0;
	p->radius = 8;
	p->time = 0;
	InitializeLaser(&p->l, "images/yellowlaser.bmp");
	if (!LoadBitmapFromFile("images/playership.bmp", p->player))
		PostQuitMessage(0);
}

/* Updates the players position depending on which key that has been pressed. 
   Initializes the player if it has been hit. */
void UpdatePlayer(Player *p) {
	switch (p->state) {
	case left:
		p->x -= 2;
		if (p->x < 0)
			p->x = 0;
		p->state = freeze; // left button is released
		break;
	case right:
		p->x += 2;
		if (p->x > 370)
			p->x = 370;
		p->state = freeze; // right button is released 
		break;
	case hit:
		if (difftime(GetTickCount64(), p->ExplosionTime) > 2000)
			InitializePlayer(p, p->hits);
		break;
	}
}
