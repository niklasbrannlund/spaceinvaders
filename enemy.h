
/* *********************
   Header file for enemy
   ********************* */

#ifndef enemy_h
#define enemy_h

/* struct for enemy */
struct Enemy{
	movement state;
	int x, y, radius, time, hits;
	double randPos, ExplosionTime;
	Laser enemyL;
	Bitmap enemy;
};

void InitializeEnemy(Enemy *e, int hits);
void UpdateEnemy(Enemy *e);
#endif 
