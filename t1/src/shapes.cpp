#include "shapes.h"

/* ---------------------------------- TRIANGLE ---------------------------------- */
Triangle *createTriangle(float width, float height){
    Triangle *newTri = (Triangle *) malloc(sizeof(Triangle));

    newTri->width = width;
    newTri->height = height;
    newTri->angle = 0.0;

    newTri->xA = 0.0;
    newTri->yA = 0.0;

    newTri->xB = width;
    newTri->yB = 0.0;

    newTri->xC = width/2;
    newTri->yC = height;

    return newTri;
}

void drawTriangle(Triangle *tri){
    if(tri == NULL) return;

    float midX = (tri->xA + tri->width) / 2;

    tri->xA = tri->xA;
    tri->xB = tri->xA + tri->width;
    tri->xC = midX;
    tri->yA = tri->yA;
    tri->yB = tri->yA;
    tri->yC = tri->height;

    glBegin(GL_TRIANGLES);
        glVertex2f(tri->xA, tri->yA);
        glVertex2f(tri->xB, tri->yB);
        glVertex2f(tri->xC, tri->yC);
    glEnd();
}


void freeTriangle(Triangle *tri){
    if(tri)
        free(tri);
}
/* ---------------------------------- TRIANGLE ---------------------------------- */

/* ---------------------------------- CIRCLE ---------------------------------- */
Circle *createCircle(float radius, float thickness){
    Circle *newCirc = (Circle *) malloc(sizeof(Circle));

    if(radius > 0.0)
        newCirc->radius = radius;
    else
        newCirc->radius = 1.0;

    if(thickness > 0.0)
        newCirc->thickness = thickness;
    else
        newCirc->thickness = 1.0;

    newCirc->centerX = 0.0;
    newCirc->centerY = 0.0;

    return newCirc;
}

void drawCircleHollow(Circle *circle){
    float x = 0.0, y = 0.0;

    glLineWidth(circle->thickness);
    glBegin(GL_LINE_LOOP);
        int i = 0;
        for(i = 0; i < 360; i++){
            x = circle->centerX + (circle->radius * sin(i));
            y = circle->centerY + (circle->radius * cos(i));
            glVertex2f(x, y);
        }
    glEnd();
}

void drawCircleFilled(Circle *circle){
    float x = 0.0, y = 0.0;

    glBegin(GL_TRIANGLE_FAN);
        int i = 0;
        glVertex2f(circle->centerX, circle->centerY);
        for(i = 0; i < 360; i++){
            x = circle->centerX + (circle->radius * sin(i));
            y = circle->centerY + (circle->radius * cos(i));
            glVertex2f(x, y);
        }
    glEnd();
}

void freeCircle(Circle *circle){
    if(circle)
        free(circle);
}
/* ---------------------------------- CIRCLE ---------------------------------- */
