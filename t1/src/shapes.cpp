#include "~/cg/t1/includes/shapes.h"

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
