/* **********************
   Header file for player
   ********************** */

#ifndef _player_h
#define _player_h
#include <vector>

/* different states that are used in the game */
enum movement{ left, right, up, freeze, hit, alive };

/* struct for player */
struct Player{
	movement state;
	int x, y, radius, hits, time;
	double ExplosionTime;
	Laser l;
	Bitmap player;
};

void InitializePlayer(Player *p, int hits);
void UpdatePlayer(Player *p);

#endif