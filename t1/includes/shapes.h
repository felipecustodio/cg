#ifndef SHAPES_H
#define SHAPES_H

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

/* ------------------------ TEXT ------------------------ */
typedef struct Text{
    //Font, String
    void *font;
    const char *string;

    //Coordinates
    float x, y;
} Text;

Text *createText(void *font, const char *string);
void drawText(Text *text);
void freeText(Text *text);
/* ------------------------ TEXT ------------------------ */

/* ------------------------ TRIANGLE ------------------------ */
typedef struct Triangle {
    //Size
    float width, height;

    //Rotation angle(?)
    float angle;

    //Color
    float color[3];

    //Coordinates
    float x[3];
    float y[3];

} Triangle;

Triangle *createTriangle(float width, float height);
void drawTriangle(Triangle *tri);
void freeTriangle(Triangle *tri);

/* ------------------------ TRIANGLE ------------------------ */

/* ------------------------ QUADRILATERAL ------------------------ */
typedef struct Quadrilateral {
    //Size
    float width, height;

    //Color
    float color[3];

    //Coordinates
    float x[4];
    float y[4];
} Quadrilateral;

Quadrilateral* createQuad(float width, float height);
void drawQuad(Quadrilateral* quad);
void freeQuad(Quadrilateral* quad);
/* ------------------------ QUADRILATERAL ------------------------ */

/* ------------------------ CIRCLE ------------------------ */
typedef struct Circle {
    //Size
    float thickness, radius;

    //Color
    float color[3];

    //Coordinates
    float center[2];
} Circle;

Circle *createCircle(float radius, float thickness);
void drawCircleHollow(Circle *circle);
void drawCircleFilled(Circle *circle);
void freeCircle(Circle *circle);
/* ------------------------ CIRCLE ------------------------ */

#endif
