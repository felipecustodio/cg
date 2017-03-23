#ifndef SHAPES_H
#define SHAPES_H

#include <stdlib.h>
#include <GL\glut.h>
#include <math.h>

/* ------------------------ TRIANGLE ------------------------ */
typedef struct Triangle{
    float width, height;
    float angle;

    float xA, xB, xC;
    float yA, yB, yC;
} Triangle;

Triangle *createTriangle(float width, float height);
void drawTriangle(Triangle *tri);
void freeTriangle(Triangle *tri);

/* ------------------------ TRIANGLE ------------------------ */

/* ------------------------ CIRCLE ------------------------ */
typedef struct Circle{
    float thickness, radius;

    float centerX, centerY;
} Circle;

Circle *createCircle(float radius, float thickness);
void drawCircleHollow(Circle *circle);
void drawCircleFilled(Circle *circle);
void freeCircle(Circle *circle);
/* ------------------------ CIRCLE ------------------------ */

#endif
