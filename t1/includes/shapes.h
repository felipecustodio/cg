#ifndef SHAPES_H
#define SHAPES_H

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/* ------------------------ TRIANGLE ------------------------ */
typedef struct Triangle {
    float width, height;
    float angle;

    //Salvar a cor para cada triângulo ao invés de uma macro?
    float color[3];

    // Melhor 2 vetores do que 6 variáveis?
    float x[3];
    float y[3];

} Triangle;

Triangle *createTriangle(float width, float height);
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
