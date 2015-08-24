/* **************************
   Source code for background
   ************************** */

#include "game.h"
#include "background.h"

/* Initializes the background bitmap */
void InitializeBackground(Background *b) {
	b->x = 0;
	b->y = 0;
	if (!LoadBitmapFromFile("images/background.bmp", b->bkground))
		PostQuitMessage(0);
}

/* Function that draws the background */
void DrawBackground(Background *b) {
	DrawBitmap(b->bkground, b->x, b->y);
}