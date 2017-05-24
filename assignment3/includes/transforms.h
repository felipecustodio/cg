#ifndef TRANSFORMS_H
#define TRANSFORMS_H

/*
* Handles movements of the shapes in shapes.h
*/

#include "shapes.h"
#include <stdlib.h>
#include <GL/glut.h>

/* -------------------------------- TRIANGLE -------------------------------- */
void rotateTriangleCenter(Triangle *tri, float angle);
void rotateTriangleVertex(Triangle *tri, float angle, int vertex);
/* -------------------------------- TRIANGLE -------------------------------- */

/* ------------------------------ QUADRILATERAL ----------------------------- */
void rotateQuadCenter(Quadrilateral *quad, float angle);
void rotateQuadVertex(Quadrilateral *quad, float angle, int vertex);
/* ------------------------------ QUADRILATERAL ----------------------------- */

#endif
