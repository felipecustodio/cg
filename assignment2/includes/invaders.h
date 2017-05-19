#ifndef INVADERS_H
#define INVADERS_H

/*
* Game functions
*/

#include <GL/glut.h>
#include "./SOIL/SOIL.h"
#include <SDL/SDL.h>
#include <time.h>
#include "shapes.h"
#include "transforms.h"
#include "physics.h"
#include "settings.h"

/* ------------------------------- GLOBALS ---------------------------------- */
// Textures
extern GLuint laserblur;

// Game mechanics
extern int shots_player_count;
extern int shots_enemy_count;
extern int enemies_left;
extern int level;
extern int paused;
extern int gameover;
extern int victory;

// Movement
extern GLfloat playerPosition; // player position (x)
extern GLfloat playerSpeed; // player speed
extern GLfloat laserSpeed; // laser speed
extern GLfloat enemyPositionX; // enemy position (x)
extern GLfloat enemyPositionY; // enemy position (y)
extern GLfloat enemySpeed; // enemy horizontal speed
/* ------------------------------- GLOBALS ---------------------------------- */

/* ------------------------------- PLAYER ----------------------------------- */
typedef struct player {

        // Coordinates
        GLfloat x[4];
        GLfloat y[4];

        // Movement
        GLfloat boundary_left;
        GLfloat boundary_right;

        // Health
        int health;

        // Score
        int score;

        // Powerup
        int powerup;

        // Laser cooldown
        int cooldown;

} PLAYER;

extern PLAYER* player;

// Create/Destroy
PLAYER* createPlayer();
void drawPlayer(PLAYER* player);
void destroyPlayer(PLAYER* player);

// Movement
char checkBorders(GLfloat x);
/* ------------------------------- PLAYER ----------------------------------- */

/* ------------------------------- ENEMY ------------------------------------ */
typedef struct enemy {

        // Coordinates
        GLfloat x[4];
        GLfloat y[4];

        // Health
        int health;

        // Type
        int shape;

        // Movement
        GLfloat pos_x;
        GLfloat pos_y;

        // Animation
        int frame;
        GLfloat current_time;

        // Boundaries
        GLfloat boundaryL; // left
        GLfloat boundaryR; // right
        GLfloat boundaryD; // down
        GLfloat boundaryU; // up

        // Laser cooldown
        int cooldown;

} ENEMY;

extern ENEMY** enemies; // 25 enemies (5x5)

ENEMY** createEnemyMatrix();
void destroyEnemyMatrix(ENEMY** enemies);
void createEnemy(ENEMY* enemy, int xindex, int yindex);
void moveEnemies(ENEMY** enemies);
void drawEnemy(ENEMY* enemy);
void destroyEnemy(ENEMY* enemy);

/* ------------------------------- ENEMY ------------------------------------ */

/* ------------------------------- LASER ------------------------------------ */
typedef struct laser {

        // Coordinates
        GLfloat x[4];
        GLfloat y[4];

        // Movement
        int position;

        // Boundary
        GLfloat boundaryU; // up
        GLfloat boundaryD; // down

        // Has it exploded yet?
        int explosion;

        // Color
        char color;

} LASER;

extern LASER** shots_player;
extern LASER** shots_enemy;

// Create/Destroy
LASER* createLaser(int x, int y, int color);
void destroyLaser(LASER *laser);

// Action
void shootLaser_Player(LASER** shots, int *amount, int x);
void shootLaser_Enemy(LASER** shots, int *amount, int x, int y);
void drawLaser(LASER* laser);
/* ------------------------------- LASER ------------------------------------ */

/* ----------------------------- ANIMATIONS --------------------------------- */
int switchTexture();
/* ----------------------------- ANIMATIONS --------------------------------- */

/* -------------------------------- GAME ------------------------------------ */
void saveGame();
void resetGame();
/* -------------------------------- GAME ------------------------------------ */

#endif
