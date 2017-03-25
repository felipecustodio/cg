#ifndef SHAPES_H
#define SHAPES_H

#include <stdlib.h>
#include <GL\glut.h>
#include <math.h>

/* ------------------------ TRIANGLE ------------------------ */
typedef struct Triangle {
    float width, height;
    float angle;

    float xA, xB, xC;
    float yA, yB, yC;
} Triangle;

Triangle *createTriangle(float width, float height);
// TODO: draw triangle hollow and filled
void drawTriangle(Triangle *tri);
void freeTriangle(Triangle *tri);

/* ------------------------ TRIANGLE ------------------------ */

/* ------------------------ QUADRILATERAL ------------------------ */
typedef struct Quadrilateral {

        // Size
        float width, height;

        // Coordinates
        float xA, xB, xC;
        float yA, yB, yC;

} Quadrilateral;

Quadrilateral* createQuad(float width, float height);
// TODO: draw quad filled and hollow
void drawQuad(Quadrilateral* quad);
void freeQuad(Quadrilateral* quad);
/* ------------------------ QUADRILATERAL ------------------------ */

/* ------------------------ CIRCLE ------------------------ */
typedef struct Circle {
    float thickness, radius;

    float centerX, centerY;
} Circle;

Circle *createCircle(float radius, float thickness);
void drawCircleHollow(Circle *circle);
void drawCircleFilled(Circle *circle);
void freeCircle(Circle *circle);
/* ------------------------ CIRCLE ------------------------ */

#endif
