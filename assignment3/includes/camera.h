#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>
#include <math.h>

typedef struct Camera{
    GLfloat pos[3];
    GLfloat rot[3];
    GLfloat up[3];
} Camera;

Camera *createCamera();
void destroyCamera(Camera *camera);

void repositionCamera(Camera *camera);
void moveCamera(Camera *camera, GLfloat speed);
void strafeCamera(Camera *camera, GLfloat speed);
void rotateCameraX(Camera *camera, GLfloat angle);
void rotateCameraY(Camera *camera, GLfloat angle);
void rotateCameraZ(Camera *camera, GLfloat angle);

#endif
