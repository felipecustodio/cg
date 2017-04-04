#include "../includes/physics.h"

/* -------------------------------- VARIABLES ------------------------------- */
float curAngle = 0.0f; // Current Angle
float curVeloc = 0.0f; // Current Velocity

float rotAccel = 1.0f; // Rotation Acceleration
float airResis = 0.2f; // Air Resistance

float velLimit = 5.0f; // Velocity Limit

float getCurAngle() {
    return curAngle;
}
/* -------------------------------- VARIABLES ------------------------------- */

/* -------------------------------- ANIMATIONS ------------------------------ */
void physicsAnimator() {
    // Physics Animator //
    // Air resistance
    if(curVeloc >= airResis)
        curVeloc = curVeloc - airResis;
    else if(curVeloc <= -airResis)
        curVeloc = curVeloc + airResis;
    else if(curVeloc > -airResis && curVeloc < airResis)
        curVeloc = 0; //curVeloc = -curVeloc;

    // Max velocity
    if(curVeloc > velLimit)
        curVeloc = velLimit;
    else if(curVeloc < -velLimit)
        curVeloc = -velLimit;

    curAngle = curAngle + curVeloc;

    // Avoid overflow
    if (curAngle > 360) {
            curAngle = 0;
    } else if (curAngle < 0) {
            curAngle = 360;
    }

    if(CONSOLE == 1 && DEBUG == 1)
        printf("\n>[ANIM]: Angle: %f, Velocity: %f\n", curAngle, curVeloc);
}
/* -------------------------------- ANIMATIONS ------------------------------ */

/* --------------------------------- MOTIONS -------------------------------- */
void accelerateLeft() {
    curVeloc = curVeloc + rotAccel;
    curAngle = curAngle + curVeloc;
}

void accelerateRight() {
    curVeloc = curVeloc - rotAccel;
    curAngle = curAngle + curVeloc;
}
/* --------------------------------- MOTIONS -------------------------------- */
