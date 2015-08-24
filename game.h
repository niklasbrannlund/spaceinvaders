/* ************************
   Header file for the game
   ************************ */

#include <Windows.h>
#include <vector>
#include "Graphics.hpp"
#include "laser.h"
#include "player.h"
#include "enemy.h"
#include "explosion.h"
#include "background.h"

/* Struct for the game. It contains all parts of the game;
	¤ Background
	¤ Player
	¤ Enemy
	¤ Explosion
	¤ Scoreboard					
	**************************************************	*/

struct Game {
	HWND hwnd;
	Background b;
	Player p;
	Enemy e;
	Explosion explo;
	char *score;
	bool winner;
};

void InitializeGame(Game *game, HWND hwnd);
void UpdateInput(Game *g);
bool CircleCollision(int x, int y, Player *p, Enemy *e, int player);
void UpdateShots(Player *p, Enemy *e);
void UpdateLogic(Game *g);
void CheckForWinner(Game *g);
void RenderGame(Game *g);
void UpdateGame(Game *game);
void ShutDownGame(Game *game);