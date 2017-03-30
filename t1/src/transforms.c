#include "transforms.h"

/* -------------------------------- TRIANGLE -------------------------------- */
void rotateTriangleCenter(Triangle *tri, float angle) {
    if(tri == NULL) return;
    float midX = (tri->x[0] + tri->x[1] + tri->x[2]) / 3;
    float midY = (tri->y[0] + tri->y[1] + tri->y[2]) / 3;

    glTranslatef(midX, midY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-midX, -midY, 0.0f);
}
/* -------------------------------- TRIANGLE -------------------------------- */
