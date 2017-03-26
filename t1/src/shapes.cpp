#include "~/cg/t1/includes/shapes.h"

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
