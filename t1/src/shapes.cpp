#include "~/cg/t1/includes/shapes.h"

/* ---------------------------------- TEXT ---------------------------------- */
Text *createText(void *font, const char *string){
    Text *newTxt = (Text *) malloc(sizeof(Text));

    newTxt->font = font;
    newTxt->string = string;

    newTxt->x = 0.0;
    newTxt->y = 0.0;

    return newTxt;
}

void drawText(Text *text){
    if(text == NULL || text->font == NULL || text->string == NULL) return;

    int strsize = strlen(text->string);

    glRasterPos2f(text->x, text->y);

    int i = 0;
    for(i = 0; i < strsize; i++){
        glutBitmapCharacter(text->font, text->string[i]);
    }
}

void freeText(Text *text){
    if(text){
        if(text->font)
            free(text->font);
        free(text);
    }
}
/* ---------------------------------- TEXT ---------------------------------- */

/* ------------------------ TRIANGLE ------------------------ */
Triangle *createTriangle(float width, float height){

  Triangle * t;

  t = (Triangle*) malloc (sizeof(Triangle));

  t->width = width;
  t->height = height;

  return t;
}

void drawTriangle(Triangle *tri){

  glColor3f(tri->color[0], tri->color[1], tri->color[2]);

  glBegin(GL_TRIANGLES);
	glVertex2f(tri->x[0], tri->y[0]);
	glVertex2f(tri->x[1], tri->y[1]);
	glVertex2f(tri->x[2], tri->y[2]);
	glEnd();
}

void freeTriangle(Triangle *tri){

  free(tri);

}
/* ------------------------ TRIANGLE ------------------------ */

/* ------------------------ QUADRILATERAL ------------------------ */
Quadrilateral* createQuad(float width, float height){

  Quadrilateral *q;

  q = (Quadrilateral*) malloc (sizeof(Quadrilateral));

  q->width = width;
  q->height = height;

  return q;
}

void drawQuad(Quadrilateral* quad)
{
  glColor3f(quad->color[0], quad->color[1], quad->color[2]);

  glBegin(GL_QUADS);
  glVertex2f(quad->x[0], quad->y[0]);
	glVertex2f(quad->x[1], quad->y[1]);
	glVertex2f(quad->x[2], quad->y[2]);
  glVertex2f(quad->x[3], quad->y[3]);
	glEnd();
}

void freeQuad(Quadrilateral* quad){

  free(quad);

}
/* ------------------------ QUADRILATERAL ------------------------ */

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

    newCirc->x = 0.0;
    newCirc->y = 0.0;

    return newCirc;
}

void drawCircleHollow(Circle *circle){
    float x = 0.0, y = 0.0;

    glLineWidth(circle->thickness);
    glBegin(GL_LINE_LOOP);
        int i = 0;
        for(i = 0; i < 360; i++){
            x = circle->x + (circle->radius * sin(i));
            y = circle->y + (circle->radius * cos(i));
            glVertex2f(x, y);
        }
    glEnd();
}

void drawCircleFilled(Circle *circle){
    float x = 0.0, y = 0.0;

    glBegin(GL_TRIANGLE_FAN);
        int i = 0;
        glVertex2f(circle->x, circle->y);
        for(i = 0; i < 360; i++){
            x = circle->x + (circle->radius * sin(i));
            y = circle->y + (circle->radius * cos(i));
            glVertex2f(x, y);
        }
    glEnd();
}

void freeCircle(Circle *circle){
    if(circle)
        free(circle);
}
/* ---------------------------------- CIRCLE ---------------------------------- */
