#ifndef PHYSICS_H
#define PHYSICS_H

#include <stdio.h>
#include "scene.h"
#include "settings.h"

/* -------------------------------- VARIABLES ------------------------------- */
float getCurAngle();
/* -------------------------------- VARIABLES ------------------------------- */

/* -------------------------------- ANIMATIONS ------------------------------ */
void physicsAnimator();
/* -------------------------------- ANIMATIONS ------------------------------ */

/* --------------------------------- MOTIONS -------------------------------- */
void accelerateLeft();
void accelerateRight();
void airResistance(char key);
/* --------------------------------- MOTIONS -------------------------------- */

#endif
