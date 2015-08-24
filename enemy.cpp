/* *********************
   Source code for enemy
   ********************* */

#include <ctime>
#include <Windows.h>
#include "laser.h"
#include "Graphics.hpp"
#include "player.h"
#include "enemy.h"


/* Function that initializes the enemy */
void InitializeEnemy(Enemy *e, int hits) {
	e->state = alive;
	e->x = rand() % 370;
	e->y = 20;
	e->radius = 8;
	e->ExplosionTime = 0;
	e->randPos = rand() % 370;
	e->time = 0;
	e->hits = hits;
	InitializeLaser(&e->enemyL, "images/greenlaser.bmp");
	if (!LoadBitmapFromFile("images/enemyship.bmp", e->enemy))
		PostQuitMessage(0);
}

/* updates the enemys position and if hit, it initializes the enemy after 2 seconds*/
void UpdateEnemy(Enemy *e) {
	switch (e->state){
	case alive:
		if (e->x < e->randPos) {
			e->x += 2;
			if (e->x > e->randPos)
				/* generate a new random position */
				e->randPos = rand() % 370;
		}
		else {
			e->x -= 2;
			if (e->x < e->randPos)
				/* generate a new random position */
				e->randPos = rand() % 370;
		}
		break;
	case hit:
		if (difftime(GetTickCount64(), e->ExplosionTime) > 2000)
			/* two seconds have passed, initialize enemy */
			InitializeEnemy(e, e->hits);
		break;
	}
}
