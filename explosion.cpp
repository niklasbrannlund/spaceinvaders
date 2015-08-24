/* *************************
   Source code for explosion
   ************************* */

#include "game.h"
#include "explosion.h"
#include <ctime>

/* char array containing filenames for the explosion bitmaps */
char *explosionFiles[] = { "images/explosion/explosion5.bmp",
						   "images/explosion/explosion4.bmp",
						   "images/explosion/explosion3.bmp",
						   "images/explosion/explosion2.bmp",
						   "images/explosion/explosion1.bmp", };


/* Funtion that initializes the explosion */
void InitializeExplosion(Explosion *explo){
	for (int i = 0; i < 5; i++) {
		Bitmap b;
		LoadBitmapFromFile(explosionFiles[i], b);
		explo->explosion.push_back(b);
	}
	explo->explosionTime = 0;
}

/* Draw the sequence of explosion bitmaps 
   Each bitmap gets 0.2 seconds each */
void drawExplosion(Explosion *explo, int x, int y, double time) {

	int timediff = difftime(GetTickCount64(), time);
	if (timediff < 200)
		DrawBitmap(explo->explosion[0], x, y);
	else if (timediff > 200 && timediff < 400)
		DrawBitmap(explo->explosion[1], x, y);
	else if (timediff > 400 && timediff < 600)
		DrawBitmap(explo->explosion[2], x, y);
	else if (timediff > 600 && timediff < 800)
		DrawBitmap(explo->explosion[3], x, y);
	else if (timediff > 800 && timediff < 1000)
		DrawBitmap(explo->explosion[4], x, y);
}