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

/* ------------------------------ QUADRILATERAL ----------------------------- */
void rotateQuadCenter(Quadrilateral *quad, float angle) {
    if(quad == NULL) return;
    float midX = (quad->x[0] + quad->x[1] + quad->x[2] + quad->x[3]) / 4;
    float midY = (quad->y[0] + quad->y[1] + quad->y[2] + quad->y[3]) / 4;

    glTranslatef(midX, midY, 0.0f);
    glRotatef(angle, 0.0f, 0.0f, 1.0f);
    glTranslatef(-midX, -midY, 0.0f);
}

void rotateQuadVertex(Quadrilateral *quad, float angle, int vertex){
    if(quad == NULL) return;

    switch(vertex){
        case 1:
            glTranslatef(quad->x[0], quad->y[0], 0.0f);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            glTranslatef(-quad->x[0], -quad->y[0], 0.0f);
            break;
        case 2:
            glTranslatef(quad->x[1], quad->y[1], 0.0f);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            glTranslatef(-quad->x[1], -quad->y[1], 0.0f);
            break;
        case 3:
            glTranslatef(quad->x[2], quad->y[2], 0.0f);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            glTranslatef(-quad->x[2], -quad->y[2], 0.0f);
            break;
        case 4:
            glTranslatef(quad->x[3], quad->y[3], 0.0f);
            glRotatef(angle, 0.0f, 0.0f, 1.0f);
            glTranslatef(-quad->x[3], -quad->y[3], 0.0f);
            break;
        default:
            break;
    }
}
/* ------------------------------ QUADRILATERAL ----------------------------- */
