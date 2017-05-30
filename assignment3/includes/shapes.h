#ifndef SHAPES_H
#define SHAPES_H

#include <stdlib.h>
#include <GL/glut.h>
#include "../includes/SOIL/SOIL.h"
#include <math.h>
#include <string.h>

/* -------------------------------- TEXTURES -------------------------------- */
GLuint loadTexture(const char *filename);
/* -------------------------------- TEXTURES -------------------------------- */

/* ---------------------------------- TEXT ---------------------------------- */
typedef struct Text {
        //Font, String
        void *font;
        const char *string;

        //Coordinates
        float x, y, z;
} Text;

Text *createText(void *font, const char *string);
void drawText(Text *text, int x, int y);
void freeText(Text *text);
/* ---------------------------------- TEXT ---------------------------------- */

/* ---------------------------------- PLANE --------------------------------- */
typedef struct Plane {
        // Size
        float thickness;

        // Color
        float color[3];

        // Texture
        GLuint texture;

        // Coordinates
        float x[4];
        float y[4];
        float z[4];
} Plane;

Plane* createPlane();
void setPlaneColor(Plane *plane, float r, float g, float b);
void setPlaneCoordinates(Plane *plane, float x1, float y1, float z1,
                                    float x2, float y2, float z2,
                                    float x3, float y3, float z3,
                                    float x4, float y4, float z4);
void setPlaneThickness(Plane *plane, float thickness);
void setPlaneTexture(Plane *plane, GLuint texture);
void drawPlaneHollow(Plane *plane);
void drawPlaneFilled(Plane *plane);
void drawPlaneTextured(Plane *plane);
void freePlane(Plane *plane);
/* ---------------------------------- PLANE --------------------------------- */

/* ---------------------------------- CUBE ---------------------------------- */
typedef struct Cube {
        // Size
        float thickness;

        // Color
        float color[3];

        // Texture
        GLuint texture;

        // Coordinates
        float x, y, z;
        float sizeX, sizeY, sizeZ;
} Cube;

Cube *createCube();
void setCubeColor(Cube *cube, float r, float g, float b);
void setCubeCoordinates(Cube *cube, float x, float y, float z);
void setCubeSize(Cube *cube, float x, float y, float z);
void setCubeThickness(Cube *cube, float thickness);
void setCubeTexture(Cube *cube, GLuint texture);
void drawCubeHollow(Cube *cube);
void drawCubeFilled(Cube *cube);
void drawCubeTextured(Cube *cube);
void freeCube(Cube *cube);
/* ---------------------------------- CUBE ---------------------------------- */

#endif
