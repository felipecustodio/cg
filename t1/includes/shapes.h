#ifndef SHAPES_H
#define SHAPES_H

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

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

    //Color
    float color[3];

    //Coordinates
    float x[3];
    float y[3];

} Triangle;

Triangle *createTriangle(float width, float height);
void setTriangleColor(Triangle *tri, float r, float g, float b);
void drawTriangle(Triangle *tri);
void freeTriangle(Triangle *tri);

/* ------------------------ TRIANGLE ------------------------ */

/* ------------------------ QUADRILATERAL ------------------------ */
typedef struct Quadrilateral {
    //Size
    float width, height, thickness;

    //Color
    float color[3];

    //Coordinates
    float x[4];
    float y[4];
} Quadrilateral;

Quadrilateral* createQuad(float c_x, float c_y, float width, float height, float thickness);
void setQuadColor(Quadrilateral *quad, float r, float g, float b);
void drawQuadHollow(Quadrilateral* quad);
void drawQuadFilled(Quadrilateral* quad);
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
void setCircleColor(Circle *circle, float r, float g, float b);
void drawCircleHollow(Circle *circle);
void drawCircleFilled(Circle *circle);
void freeCircle(Circle *circle);
/* ------------------------ CIRCLE ------------------------ */

#endif
