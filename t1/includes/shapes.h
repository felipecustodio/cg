#ifndef SHAPES_H
#define SHAPES_H

#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>

/* ---------------------------------- TEXT ---------------------------------- */
typedef struct Text {
    //Font, String
    void *font;
    const char *string;

    //Coordinates
    float x, y;
} Text;

Text *createText(void *font, const char *string);
void drawText(Text *text, int x, int y);
void freeText(Text *text);
/* ---------------------------------- TEXT ---------------------------------- */

/* -------------------------------- TRIANGLE -------------------------------- */
typedef struct Triangle {
    //Size
    float thickness;

    //Color
    float color[3];

    //Coordinates
    float x[3];
    float y[3];

} Triangle;

Triangle *createTriangle();
void setTriangleCoordinates(Triangle *tri, float x1, float y1, float x2, float y2, float x3, float y3);
void setTriangleThickness(Triangle *tri, float thickness);
void setTriangleColor(Triangle *tri, float r, float g, float b);
void drawTriangleHollow(Triangle *tri);
void drawTriangleFilled(Triangle *tri);
void freeTriangle(Triangle *tri);

/* -------------------------------- TRIANGLE -------------------------------- */

/* ------------------------------ QUADRILATERAL ----------------------------- */
typedef struct Quadrilateral {
    // Size
    float thickness;

    // Color
    float color[3];

    // Coordinates
    float x[4];
    float y[4];
} Quadrilateral;

Quadrilateral* createQuad();
void setQuadColor(Quadrilateral *quad, float r, float g, float b);
void setQuadCoordinates(Quadrilateral *quad, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
void setQuadThickness(Quadrilateral *quad, float thickness);
void drawQuadHollow(Quadrilateral* quad);
void drawQuadFilled(Quadrilateral* quad);
void freeQuad(Quadrilateral* quad);
/* ------------------------------ QUADRILATERAL ----------------------------- */

/* --------------------------------- CIRCLE --------------------------------- */
typedef struct Circle {
    // Size
    float thickness, radius;

    // Color
    float color[3];

    // Coordinates
    float center[2];
} Circle;

Circle *createCircle(float radius, float thickness);
void setCircleCoordinates(Circle *circle, float x, float y);
void setCircleColor(Circle *circle, float r, float g, float b);
void drawCircleHollow(Circle *circle);
void drawCircleFilled(Circle *circle);
void freeCircle(Circle *circle);
/* --------------------------------- CIRCLE --------------------------------- */

#endif
