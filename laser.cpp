/* *********************
   Source code for laser
   ********************* */

#include <ctime>
#include <Windows.h>
#include "laser.h"

/* Initializes the laser */
void InitializeLaser(Laser *l, char *filename) {
	l->reload = false;
	l->radius = 4;
	l->reload_timer = 0;
	if (!LoadBitmapFromFile(filename, l->laser))
		PostQuitMessage(0);
}

/* Draws the laser */
void DrawLaser(Laser *l) {
	std::vector<Vector>::iterator shot = l->bullet.begin();
	while (shot != l->bullet.end()) {
		if ((shot->y > 0) && (shot->y < 400))
			DrawBitmap(l->laser, shot->x, shot->y);
		shot++;
	}
}

/* removes ongoing bullets from screen.
   The purpose of this function is to remove bullets from screen
   if the player chosed to restart the game */
void RemoveBullet(Laser *l) {
	std::vector<Vector>::iterator shot = l->bullet.begin();
	while (shot != l->bullet.end())
		shot = l->bullet.erase(shot);
}