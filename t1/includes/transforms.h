#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "shapes.h"
#include <stdlib.h>
#include <GL/glut.h>

/* ------------------------ TRIANGLE ------------------------ */
void translateTriangle(Triangle *tri, float x, float y);
void scaleTriangle(Triangle *tri, float x, float y);
void rotateTriangleCenter(Triangle *tri, float angle);
/* ------------------------ TRIANGLE ------------------------ */

#endif
