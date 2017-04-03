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

void rotateTriangleVertex(Triangle *tri, float angle, int vertex){
    if(tri == NULL) return;

    switch(vertex){
        case 1:
            glTranslatef(tri->x[0], tri->y[0], 0.0f);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            glTranslatef(-tri->x[0], -tri->y[0], 0.0f);
            break;
        case 2:
            glTranslatef(tri->x[1], tri->y[1], 0.0f);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            glTranslatef(-tri->x[1], -tri->y[1], 0.0f);
            break;
        case 3:
            glTranslatef(tri->x[2], tri->y[2], 0.0f);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            glTranslatef(-tri->x[2], -tri->y[2], 0.0f);
            break;
        default:
            break;
    }
}
/* -------------------------------- TRIANGLE -------------------------------- */
