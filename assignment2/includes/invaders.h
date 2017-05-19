#ifndef INVADERS_H
#define INVADERS_H

/*
* Game functions
*/

#include <GL/glut.h>
#include "./SOIL/SOIL.h"
#include <SDL/SDL.h>
#include "shapes.h"
#include "transforms.h"
#include "physics.h"
#include "settings.h"

/* ------------------------------- GLOBALS ---------------------------------- */
// Movement
extern GLfloat playerPosition; // player horizontal speed
extern GLfloat playerSpeed; // player speed
extern GLfloat laserSpeed; // laser speed
extern GLfloat enemyPositionX; // enemy position (x)
extern GLfloat enemyPositionY; // enemy position (y)
extern GLfloat enemySpeed; // enemy horizontal speed
extern GLfloat enemySpeed; // enemy horizontal speed
extern GLfloat enemyApproach; // enemy vertical speed (approaching player base)
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

        // Laser cooldown
        int cooldown;

} PLAYER;

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

        // Laser cooldown
        int cooldown;

} ENEMY;

ENEMY** createEnemyMatrix();
void destroyEnemyMatrix(ENEMY** enemies);
void createEnemy(ENEMY* enemy, int xindex, int yindex);
void drawEnemy(ENEMY* enemy);
void destroyEnemy(ENEMY* enemy);
/* ------------------------------- ENEMY ------------------------------------ */

/* ------------------------------- LASER ------------------------------------ */
typedef struct laser {

        // Coordinates
        GLfloat x[4];
        GLfloat y[4];

        // Position to translate
        int position;

        // Has it exploded yet?
        int explosion;

        // Color
        char color;

} LASER;

LASER* createLaser(int x, int y, int color);
void destroyLaser(LASER *laser);

// Action
void shootLaser_Player(LASER** shots, int *amount, int x);
void shootLaser_Enemy(LASER** shots, int *amount, int x, int y);
void drawLaser(LASER* laser);
/* ------------------------------- LASER ------------------------------------ */

/* -------------------------------- ANIMATIONS ----------------------------------- */
int switchTexture();
/* ----------------------------- ANIMATIONS --------------------------------- */

/* -------------------------------- GAME ------------------------------------ */
void saveGame();
void resetGame();
/* -------------------------------- GAME ------------------------------------ */

#endif
