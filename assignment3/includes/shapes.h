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
        GLfloat x[4];
        GLfloat y[4];
        GLfloat z[4];
} Plane;

Plane* createPlane();
void setPlaneColor(Plane *plane, float r, float g, float b);
void setPlaneCoordinates(Plane *plane, GLfloat x1, GLfloat y1, GLfloat z1,
                                    GLfloat x2, GLfloat y2, GLfloat z2,
                                    GLfloat x3, GLfloat y3, GLfloat z3,
                                    GLfloat x4, GLfloat y4, GLfloat z4);
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
        GLfloat x, y, z;
        GLfloat sizeX, sizeY, sizeZ;
} Cube;

Cube *createCube();
void setCubeColor(Cube *cube, float r, float g, float b);
void setCubeCoordinates(Cube *cube, GLfloat x, GLfloat y, GLfloat z);
void setCubeSize(Cube *cube, GLfloat x, GLfloat y, GLfloat z);
void setCubeThickness(Cube *cube, float thickness);
void setCubeTexture(Cube *cube, GLuint texture);
void drawCubeHollow(Cube *cube);
void drawCubeFilled(Cube *cube);
void drawCubeTextured(Cube *cube);
void freeCube(Cube *cube);
/* ---------------------------------- CUBE ---------------------------------- */

#endif
