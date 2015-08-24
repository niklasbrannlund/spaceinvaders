/* *********************
   Header file for laser
   ********************* */

#ifndef laser_h
#define laser_h
#include <vector>
#include "Graphics.hpp"

/* Vector containing bullet information */
struct Vector{
	int x;
	int y;
	int dy;
	Vector(int x, int y, int dy) : x(x), y(y), dy(dy) {}
};

/* Laser struct */
struct Laser {
	std::vector<Vector> bullet;
	bool reload;
	int radius;
	int reload_timer;
	Bitmap laser;
};

void InitializeLaser(Laser *l, char *filename);
void DrawLaser(Laser *l);
void RemoveBullet(Laser *l);
#endif