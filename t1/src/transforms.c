#include "transforms.h"

/* -------------------------------- TRIANGLE -------------------------------- */
void translateTriangle(Triangle *tri, float x, float y){
    if(tri == NULL) return;

    glTranslatef(x, y, 0.0f);
}

void scaleTriangle(Triangle *tri, float x, float y){
    if(tri == NULL) return;

    glScalef(x, y, 0.0f);
}

void rotateTriangleCenter(Triangle *tri, float angle){
    if(tri == NULL) return;
    float midX = (tri->x[0] + tri->x[1] + tri->x[2]) / 3;
    float midY = (tri->y[0] + tri->y[1] + tri->y[2]) / 3;

    tri->angle = angle;

    glTranslatef(midX, midY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-midX, -midY, 0.0f);
}
/* -------------------------------- TRIANGLE -------------------------------- */
