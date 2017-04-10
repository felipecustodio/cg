#include "../includes/physics.h"

/* -------------------------------- VARIABLES ------------------------------- */
float curAngle = 0.0f; // Current Angle
float curVeloc = 0.0f; // Current Velocity

float rotAccel = 1.0f; // Rotation Acceleration
float airResis = 0.2f; // Air Resistance

float velLimit = 5.0f; // Velocity Limit
float airResisLimit = 2.0f; // Air Resistance increase limit

float getCurAngle() {
    return curAngle;
}
/* -------------------------------- VARIABLES ------------------------------- */

/* -------------------------------- ANIMATIONS ------------------------------ */
void checkMaxVelocity() {
    // Max velocity
    if(curVeloc > velLimit)
        curVeloc = velLimit;
    else if(curVeloc < -velLimit)
        curVeloc = -velLimit;
}
void physicsAnimator() {
    // Physics Animator //
    // Air resistance
    if(curVeloc >= airResis)
        curVeloc = curVeloc - airResis;
    else if(curVeloc <= -airResis)
        curVeloc = curVeloc + airResis;
    else if(curVeloc > -airResis && curVeloc < airResis)
        curVeloc = 0; // curVeloc = -curVeloc;

    checkMaxVelocity();

    curAngle = curAngle + curVeloc;

    // Avoid overflow
    if (curAngle > 360) {
            curAngle = 0;
    } else if (curAngle < 0) {
            curAngle = 360;
    }

    if (curVeloc == 0) {
            SDL_PauseAudio(1);
    } else {
            SDL_PauseAudio(0);
    }

    IF_DEBUG printf("\n>[ANIM]: Angle: %f, Velocity: %f\n", curAngle, curVeloc);
}
/* -------------------------------- ANIMATIONS ------------------------------ */

/* --------------------------------- MOTIONS -------------------------------- */
void accelerateLeft() {
        curVeloc = curVeloc + rotAccel;
        checkMaxVelocity();
        curAngle = curAngle + curVeloc;
}

void accelerateRight() {
        curVeloc = curVeloc - rotAccel;
        checkMaxVelocity();
        curAngle = curAngle + curVeloc;
}

void airResistance(char key) {
        IF_DEBUG printf("Change air resistance\n");
        if (key) {
                if (airResis + 0.1 < airResisLimit) airResis += 0.1;
        } else {
                if (airResis - 0.1 >= 0) airResis -= 0.1;
        }
        IF_DEBUG printf("AIR RESISTANCE = %lf\n", airResis);
}

/* --------------------------------- MOTIONS -------------------------------- */
