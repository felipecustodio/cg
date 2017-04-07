#include "../includes/shapes.h"

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
        if(text->font != NULL) {
            free(text->font);
            text->font = NULL;
        }
        free(text);
        text = NULL;
    }
}
/* ---------------------------------- TEXT ---------------------------------- */

/* -------------------------------- TRIANGLE -------------------------------- */

Triangle *createTriangle() {

    Triangle *tri = (Triangle *) malloc(sizeof(Triangle));

    tri->thickness = 1.0f;

    tri->color[0] = 0.0;
    tri->color[1] = 0.0;
    tri->color[2] = 0.0;

    tri->x[0] = 0.0;
    tri->y[0] = 0.0;

    tri->x[1] = 0.0;
    tri->y[1] = 0.0;

    tri->x[2] = 0.0;
    tri->y[2] = 0.0;

    return tri;
}

void setTriangleCoordinates(Triangle *tri, float x1, float y1, float x2,
                                           float y2, float x3, float y3) {
    if (tri == NULL) return;

    tri->x[0] = x1;
    tri->y[0] = y1;

    tri->x[1] = x2;
    tri->y[1] = y2;

    tri->x[2] = x3;
    tri->y[2] = y3;
}

void setTriangleThickness(Triangle *tri, float thickness){
    if (tri == NULL) return;

    tri->thickness = thickness;
}

void setTriangleColor(Triangle *tri, float r, float g, float b){
    if (tri == NULL) return;

    tri->color[0] = r;
    tri->color[1] = g;
    tri->color[2] = b;
}

void drawTriangleHollow(Triangle *tri) {
    if(tri == NULL) return;

    glColor3f(tri->color[0], tri->color[1], tri->color[2]);

    glLineWidth(tri->thickness);

    glBegin(GL_LINE_LOOP);
        glVertex2f(tri->x[0], tri->y[0]);
        glVertex2f(tri->x[1], tri->y[1]);
        glVertex2f(tri->x[2], tri->y[2]);
    glEnd();
}

void drawTriangleFilled(Triangle *tri) {
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
// 0-------1
// |   .   |
// |       |
// 3-------2
// Quad Coordinates
Quadrilateral* createQuad() {
    Quadrilateral* quad = (Quadrilateral *) malloc(sizeof(Quadrilateral));

    quad->thickness = 1.0f;

    quad->x[0] = 0.0;
    quad->y[0] = 0.0;

    quad->x[1] = 0.0;
    quad->y[1] = 0.0;

    quad->x[2] = 0.0;
    quad->y[2] = 0.0;

    quad->x[3] = 0.0;
    quad->y[3] = 0.0;

    return quad;
}

void setQuadCoordinates(Quadrilateral *quad, float x1, float y1, float x2, float y2,
                                             float x3, float y3, float x4, float y4) {
    if (quad == NULL) return;

    quad->x[0] = x1;
    quad->y[0] = y1;

    quad->x[1] = x2;
    quad->y[1] = y2;

    quad->x[2] = x3;
    quad->y[2] = y3;

    quad->x[3] = x4;
    quad->y[3] = y4;
}

void setQuadThickness(Quadrilateral *quad, float thickness){
    if (quad == NULL) return;

    quad->thickness = thickness;
}

void setQuadColor(Quadrilateral *quad, float r, float g, float b){
    if (quad == NULL) return;

    quad->color[0] = r;
    quad->color[1] = g;
    quad->color[2] = b;
}

void drawQuadHollow(Quadrilateral* quad) {
    if (quad == NULL) return;

    glColor3f(quad->color[0], quad->color[1], quad->color[2]);

    glLineWidth(quad->thickness);

    glBegin(GL_LINE_LOOP);
        glVertex2f(quad->x[0], quad->y[0]);
        glVertex2f(quad->x[1], quad->y[1]);
        glVertex2f(quad->x[2], quad->y[2]);
        glVertex2f(quad->x[3], quad->y[3]);
    glEnd();
}

void drawQuadFilled(Quadrilateral* quad) {
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
Circle *createCircle(float radius, float thickness) {
    Circle *circle = (Circle *) malloc(sizeof(Circle));

    if(radius > 0.0)
        circle->radius = radius;
    else
        circle->radius = 1.0;

    if(thickness > 0.0)
        circle->thickness = thickness;
    else
        circle->thickness = 1.0;

    circle->center[0] = 0.0;
    circle->center[1] = 0.0;

    return circle;
}

void setCircleCoordinates(Circle *circle, float x, float y){
    if (circle == NULL) return;

    circle->center[0] = x;
    circle->center[1] = y;
}

void setCircleColor(Circle *circle, float r, float g, float b){
    if (circle == NULL) return;

    circle->color[0] = r;
    circle->color[1] = g;
    circle->color[2] = b;
}

void drawCircleHollow(Circle *circle) {
    float x = 0.0, y = 0.0;

    glColor3f(circle->color[0], circle->color[1], circle->color[2]);

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

    glColor3f(circle->color[0], circle->color[1], circle->color[2]);

    glBegin(GL_TRIANGLE_FAN);
        int i = 0;
        glVertex2f(circle->center[0], circle->center[1]);
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
