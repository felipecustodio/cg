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

        // Coordinates
        GLfloat x[3];
        GLfloat y[3];

        // Health
        int health;

        // Laser cooldown
        int cooldown;

} PLAYER;

PLAYER* createPlayer();
void destroyPlayer(PLAYER* player);
/* -------------------------------- PLAYER ----------------------------------- */

/* -------------------------------- ENEMY ----------------------------------- */
typedef struct enemy {

        // Coordinates
        GLfloat x[3];
        GLfloat y[3];

        // Health
        int health;

        // Laser cooldown
        int cooldown;

} ENEMY;

ENEMY* createEnemy();
void destroyEnemy(ENEMY* enemy);
/* -------------------------------- ENEMY ----------------------------------- */




#endif
