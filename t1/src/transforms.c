#include "transforms.h"

/* ---------------------------------- TRIANGLE ---------------------------------- */
void rotateTriangleCenter(Triangle *tri, float angle){
    if(tri == NULL) return;
    float midX = (tri->xA + tri->xB + tri->xC) / 3;
    float midY = (tri->yA + tri->yB + tri->yC) / 3;

    tri->angle = angle;

    glTranslatef(midX, midY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-midX, -midY, 0.0f);
}
/* ---------------------------------- TRIANGLE ---------------------------------- */
