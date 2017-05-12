#ifndef INVADERS_H
#define INVADERS_H

/*
* Game functions
*/

#include <GL/glut.h>
#include "../includes/SOIL/SOIL.h"
#include <SDL/SDL.h>
#include "shapes.h"
#include "transforms.h"
#include "physics.h"
#include "settings.h"

/* -------------------------------- PLAYER ----------------------------------- */
typedef struct player {

        // Shape

        // Coordinates
        GLfloat x[3];
        GLfloat y[3];

        // Movement
        GLfloat pos_x;
        GLfloat pos_y;

        // Health
        int health;

        // Laser cooldown
        int cooldown;

} PLAYER;

// Create/Destroy
PLAYER* createPlayer();
void destroyPlayer(PLAYER* player);

// Movement
char checkBorders(GLfloat x);
void movePlayer(char direction);

/* -------------------------------- PLAYER ----------------------------------- */

/* -------------------------------- ENEMY ----------------------------------- */
typedef struct enemy {

        // Coordinates
        GLfloat x[3];
        GLfloat y[3];

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

/* -------------------------------- MISSILE ----------------------------------- */
typedef struct missile {

        // Coordinates
        GLfloat x[3];
        GLfloat y[3];

        // Has it exploded yet?
        int explosion;

} MISSILE;

MISSILE* createMissile();
void destroyMissile();
/* -------------------------------- MISSILE ----------------------------------- */

/* -------------------------------- GAME ----------------------------------- */


#endif
