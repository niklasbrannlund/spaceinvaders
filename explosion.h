/* *************************
   Header file for explosion
   ************************* */

#ifndef explosion_h
#define explosion_h

#include <vector>

struct Explosion {
	std::vector<Bitmap> explosion;
	int explosionTime;
};

void InitializeExplosion(Explosion *explo);
void drawExplosion(Explosion *explo, int x, int y, double time);

#endif