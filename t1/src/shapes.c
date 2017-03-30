#include "shapes.h"

/* ---------------------------------- TEXT ---------------------------------- */
Text *createText(void *font, const char *string) {
    Text *newTxt = (Text *) malloc(sizeof(Text));

    newTxt->font = font;
    newTxt->string = string;

    newTxt->x = 0.0;
    newTxt->y = 0.0;

    return newTxt;
}

void drawText(Text *text) {
    if(text == NULL || text->font == NULL || text->string == NULL) return;

    int strsize = strlen(text->string);

    glRasterPos2f(text->x, text->y);

    int i = 0;
    for(i = 0; i < strsize; i++) {
        glutBitmapCharacter(text->font, text->string[i]);
    }
}

void freeText(Text *text) {
    if(text) {
        if(text->font)
            free(text->font);
            text->font = NULL;
        free(text);
        text = NULL;
    }
}
/* ---------------------------------- TEXT ---------------------------------- */

/* -------------------------------- TRIANGLE -------------------------------- */
// TODO: passar como parâmetro tipo de triângulo
// TODO: passar coordenada inicial
Triangle *createTriangle(float width, float height) {
    Triangle *newTri = (Triangle *) malloc(sizeof(Triangle));

    newTri->width = width;
    newTri->height = height;

    newTri->x[0] = 0.0;
    newTri->y[0] = 0.0;

    newTri->x[1] = width;
    newTri->y[1] = 0.0;

    newTri->x[2] = width/2;
    newTri->y[2] = height;

    return newTri;
}

void drawTriangle(Triangle *tri) {
    if(tri == NULL) return;

    glColor3f(tri->color[0], tri->color[1], tri->color[2]);

    glBegin(GL_TRIANGLES);
        glVertex2f(tri->x[0], tri->y[0]);
        glVertex2f(tri->x[1], tri->y[1]);
        glVertex2f(tri->x[2], tri->y[2]);
    glEnd();
}

void freeTriangle(Triangle *tri){
    if (tri) {
            free(tri);
            tri = NULL;
    }
}
/* -------------------------------- TRIANGLE -------------------------------- */

/* ----------------------------- QUADRILATERAL ------------------------------ */
// TODO: mudar 0 para coordenada inicial
Quadrilateral* createQuad(float width, float height) {
    Quadrilateral* quad = (Quadrilateral *) malloc(sizeof(Quadrilateral));

    quad->width = width;
    quad->height = height;

    quad->x[0] = 0;
    quad->x[1] = 0;
    quad->x[2] = 0 + width;
    quad->x[3] = 0 + width;

    quad->y[0] = 0;
    quad->y[1] = 0 + height;
    quad->y[2] = 0 + height;
    quad->y[3] = 0;

    return quad;
}

// TODO: draw quad filled and hollow
void drawQuad(Quadrilateral* quad) {
    if (quad == NULL) return;

    glColor3f(quad->color[0], quad->color[1], quad->color[2]);

    glBegin(GL_QUADS);
        glVertex2f(quad->x[0], quad->y[0]);
        glVertex2f(quad->x[1], quad->y[1]);
        glVertex2f(quad->x[2], quad->y[2]);
        glVertex2f(quad->x[3], quad->y[3]);
    glEnd();
}
void freeQuad(Quadrilateral* quad) {
    if(quad){
            free(quad);
            quad = NULL;
    }
}
/* ----------------------------- QUADRILATERAL ------------------------------ */

/* --------------------------------- CIRCLE --------------------------------- */
//TODO: passar coordenadas iniciais como parâmetro
Circle *createCircle(float radius, float thickness) {
    Circle *newCirc = (Circle *) malloc(sizeof(Circle));

    if(radius > 0.0)
        newCirc->radius = radius;
    else
        newCirc->radius = 1.0;

    if(thickness > 0.0)
        newCirc->thickness = thickness;
    else
        newCirc->thickness = 1.0;

    newCirc->center[0] = 0.0;
    newCirc->center[1] = 0.0;

    return newCirc;
}

void drawCircleHollow(Circle *circle) {
    float x = 0.0, y = 0.0;

    glLineWidth(circle->thickness);
    glBegin(GL_LINE_LOOP);
        int i = 0;
        for(i = 0; i < 360; i++) {
            x = circle->center[0] + (circle->radius * sin(i));
            y = circle->center[1] + (circle->radius * cos(i));
            glVertex2f(x, y);
        }
    glEnd();
}

void drawCircleFilled(Circle *circle){
    float x = 0.0, y = 0.0;

    glBegin(GL_TRIANGLE_FAN);
        int i = 0;
        glVertex2f(circle->centerX, circle->centerY);
        for(i = 0; i < 360; i++) {
            x = circle->center[0] + (circle->radius * sin(i));
            y = circle->center[1] + (circle->radius * cos(i));
            glVertex2f(x, y);
        }
    glEnd();
}

void freeCircle(Circle *circle){
    if(circle){
        free(circle);
        circle = NULL;
    }
}
/* --------------------------------- CIRCLE --------------------------------- */
