/* ********************
   Source code for game 
   ******************** */


#include <ctime>
#include <string>
#include "game.h"

/* Initializes the game and all its components */
void InitializeGame(Game *g, HWND hwnd) {
	g->hwnd = hwnd;
	InitializePlayer(&g->p, 0);
	InitializeEnemy(&g->e, 0);
	InitializeBackground(&g->b);
	InitializeExplosion(&g->explo);
	g->score = new char[19 + 1]; // strlen(Player: x  Enemy: y)
	g->winner = false;
	RemoveBullet(&g->p.l);
	RemoveBullet(&g->e.enemyL);
	srand(time(NULL));
}

/* Makes relevant update depending on which key player has pressed */
void UpdateInput(Game *g) {
	if (g->p.state != hit) {
		if (GetAsyncKeyState(VK_LEFT))
			g->p.state = left;
		if (GetAsyncKeyState(VK_RIGHT))
			g->p.state = right;
		if (GetAsyncKeyState(VK_SPACE)) {
			if (!g->p.l.reload) {
				g->p.l.reload = true;
				g->p.l.reload_timer = time(0);
				g->p.l.bullet.push_back(Vector(g->p.x, g->p.y - 10, -5));
			}
		}
		if (GetAsyncKeyState(VK_RETURN))
			InitializeGame(g, g->hwnd);
	}
}

/* Check for collision,
   The int player variable is to see if it is the enemy or the player that fired the shot */
bool CircleCollision(int x, int y, Player *p, Enemy *e, int player) {

	/* did the the player fire the shot? */
	if (player) {
		/* yes */
		float dx = float(x - e->x);
		float dy = float(y - e->y);
		int dist = (int)sqrt(dx*dx + dy*dy);

		// overlap?
		if (dist < p->l.radius + e->radius)
			return true;
		else
			return false;
	}
	else {
		/* it was the enemy that fired the shot */
		float dx = float(x - p->x);
		float dy = float(y - p->y);
		int dist = (int)sqrt(dx*dx + dy*dy);

		// overlap?
		if (dist < e->enemyL.radius + p->radius)
			return true;
		else
			return false;
	}
}

/* updates the players and the enemys shots that have been fired */
void UpdateShots(Player *p, Enemy *e) {
	
	/* player laser */ 
	/* Assign vector to bullets beeing shot */
	std::vector<Vector>::iterator shot = p->l.bullet.begin();
	while (shot != p->l.bullet.end()) {
		/* Look for collision with players bullet and enemy ship*/
		if (e->state != hit && CircleCollision(shot->x, shot->y, p, e, 1)) {
			/* we got a hit */
			shot = p->l.bullet.erase(shot);
			/* increase point to player */
			p->hits++;
			e->state = hit;
			PlaySound(TEXT("sounds/explosion.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC);
			/* initializes explosion time */
			e->ExplosionTime = GetTickCount64();
		}
		/* if bullet is outside game area, erase it */
		else if (shot->y > 400) {
			shot = p->l.bullet.erase(shot);
		}
		/* bullet has neither hit enemy nor gone outside game area. just update position */
		else {
			shot->y += shot->dy;
			shot++;
		}
	}
	/* see if enough time has passed so that player is done reloading and can shoot again. */
	if (p->state != hit && difftime(time(0), p->l.reload_timer) > 0.5) 
		p->l.reload = false;

	/* enemy laser */
	/* Assign vector to bullets beeing shot */
	std::vector<Vector>::iterator enemyShot = e->enemyL.bullet.begin();
	while (enemyShot != e->enemyL.bullet.end()) {
		/* look for collision */
		if (p->state != hit && CircleCollision(enemyShot->x, enemyShot->y, p, e, 0)) {
			/* we have a hit */
			enemyShot = e->enemyL.bullet.erase(enemyShot);
			/* increase enemy point */
			e->hits++;
			p->state = hit;
			/* initialize a timer for revival */
			p->time = time(0);
			/* initialize a explosion timer */
			p->ExplosionTime = GetTickCount64();
			PlaySound(TEXT("sounds/explosion.wav"), NULL, SND_FILENAME | SND_NOSTOP | SND_ASYNC);
		}
		/* if bullet is outside game area, erase it */
		else if (enemyShot->y > 400) {
			enemyShot = e->enemyL.bullet.erase(enemyShot);
		}
		/* bullet has neither hit enemy nor gone outside game area. just update position */
		else {
			enemyShot->y -= enemyShot->dy;
			enemyShot++;
		}
	}
	/* check if enemy is done reloading */
	if (e->state != hit && difftime(time(0), e->enemyL.reload_timer) > (rand() % 3)) {
		e->enemyL.bullet.push_back(Vector(e->x, e->y + 10, -5));
		e->enemyL.reload_timer = time(0);
	}
}
/* Updates the player, enemy and laser */
void UpdateLogic(Game *g) {
	UpdatePlayer(&g->p);
	UpdateEnemy(&g->e);
	UpdateShots(&g->p, &g->e);
}

/* check if a player has hit the limit*/
void checkForWinner(Game *g) {
	if (g->e.hits == 3 || g->p.hits == 3)
		g->winner = true;

}

/* Displays all the main components of the game */
void RenderGame(Game *g) {
	sprintf(g->score, "Player: %d  Enemy: %d", g->p.hits, g->e.hits);
	BeginGraphics();
	DrawBackground(&g->b);
	DrawString(g->score, 0, 0);
	
	/* draw player*/
	switch (g->p.state) {
		case hit:
			drawExplosion(&g->explo, g->p.x, g->p.y, g->p.ExplosionTime);
			break;
		default: 
			DrawBitmap(g->p.player, g->p.x, g->p.y);
			break;
	}
	
	/* draw enemy */
	switch (g->e.state) {
		case hit: 
			drawExplosion(&g->explo, g->e.x, g->e.y, g->e.ExplosionTime);
			break;
		case alive: 
			DrawBitmap(g->e.enemy, g->e.x, g->e.y);
			break;
	}
	
	/* draw player laser */
	DrawLaser(&g->p.l);
	/* draw enemy laser */
	DrawLaser(&g->e.enemyL);
	/* check if anyone has reached the limit */
	checkForWinner(g);

	EndGraphics();
}

/* main game update function */
void UpdateGame(Game *g) {
	/* see if someone has reached the limit */
	if (!g->winner) {
		/* no, keep on updating */
		UpdateInput(g);
		UpdateLogic(g);
		RenderGame(g);
	}

	/* we have a winner */
	else {
		if (g->p.hits == 3) {
			/* Player is the winner, display cheering words */
			if (MessageBox(g->hwnd, "You won! Would you like to play again?", "Congratulations!", MB_YESNO) == IDYES) {
				/* free all memory */
				ShutDownGame(g);
				/* reinitialize */
				InitializeGame(g, g->hwnd);
			}
			else
				SendMessage(g->hwnd, WM_CLOSE, NULL, NULL);
		}
		else if (g->e.hits == 3) {
			/* Enemy won, display sad words */
			if (MessageBox(g->hwnd, "You lost! Would you like to play again?", "Too bad!", MB_YESNO) == IDYES) {
				/* free all memory */
				ShutDownGame(g);
				/* reinitialize */
				InitializeGame(g, g->hwnd);
			}
			else
				SendMessage(g->hwnd, WM_CLOSE, NULL, NULL);
		}
	}
}

/* free all the memory */
void ShutDownGame(Game *g) {
	FreeBitmap(g->b.bkground);
	FreeBitmap(g->p.player);
	FreeBitmap(g->p.l.laser);
	FreeBitmap(g->e.enemyL.laser);
	FreeBitmap(g->e.enemy);
	for (int i = 0; i < 5; i++) {
		FreeBitmap(g->explo.explosion[i]);
	}
	delete[] g->score;
}

