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

/* -------------------------------- GLOBALS ----------------------------------- */

// Movement
extern GLfloat playerPosition; // player horizontal speed
extern GLfloat enemySpeed; // enemy horizontal speed
extern GLfloat enemyApproach; // enemy vertical speed (approaching player base)

/* -------------------------------- GLOBALS ----------------------------------- */

/* -------------------------------- PLAYER ----------------------------------- */
typedef struct player {

        // Coordinates
        GLfloat x[4];
        GLfloat y[4];

        // Movement
        GLfloat boundary_left;
        GLfloat boundary_right;

        // Health
        int health;

        // Laser cooldown
        int cooldown;

} PLAYER;

// Create/Destroy
PLAYER* createPlayer();
void drawPlayer(PLAYER* player);
void destroyPlayer(PLAYER* player);

// Movement
char checkBorders(GLfloat x);

/* -------------------------------- PLAYER ----------------------------------- */

/* -------------------------------- ENEMY ----------------------------------- */
typedef struct enemy {

        // Coordinates
        GLfloat x[4];
        GLfloat y[4];

        // Health
        int health;

        // Movement
        GLfloat pos_x;
        GLfloat pos_y;

        // Laser cooldown
        int cooldown;

} ENEMY;

ENEMY* createEnemy(int design);
void destroyEnemy(ENEMY* enemy);
/* -------------------------------- ENEMY ----------------------------------- */

/* -------------------------------- LASER ----------------------------------- */
typedef struct laser {

        // Coordinates
        GLfloat x[4];
        GLfloat y[4];

        // Has it exploded yet?
        int explosion;

} LASER;

LASER* createLaser();
void destroyLaser();

// Action
void shootLaser(LASER** shots, int amount);
/* -------------------------------- LASER ----------------------------------- */

/* -------------------------------- GAME ----------------------------------- */


#endif
