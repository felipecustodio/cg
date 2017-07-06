#include "../includes/camera.h"
#include<stdio.h>

GLfloat limitXl = 44.0f;
GLfloat limitXr = -44.0f;
GLfloat limitZu = -27.0f;
GLfloat limitZd = 47.0f;

Camera *createCamera(){
    Camera *camera = (Camera *) malloc(sizeof(Camera));

    camera->pos[0] = 0.0f;
    camera->pos[1] = 10.0f;
    camera->pos[2] = 0.0f;

    camera->rot[0] = 0.0f;
    camera->rot[1] = 0.0f;
    camera->rot[2] = 0.0f;

    camera->up[0] = 0.0f;
    camera->up[1] = 1.0f;
    camera->up[2] = 0.0f;

    return camera;
}

void destroyCamera(Camera *camera){
    if(camera == NULL) return;
    free(camera);
}

void repositionCamera(Camera *camera){
    if(camera == NULL) return;
    glLoadIdentity();
    //gluLookAt(camera->pos[0],  camera->pos[1],  camera->pos[2],
	  //		      camera->view[0], camera->view[1], camera->view[2],
	  //		      camera->up[0],   camera->up[1],   camera->up[2]);
    glRotatef(camera->rot[0], 1, 0, 0); // Rotate x-axis
    glRotatef(camera->rot[1], 0, 1, 0); // Rotate y-axis
    glRotatef(camera->rot[2], 0, 0, 1); // Rotate z-axis
    glTranslatef(-camera->pos[0], -camera->pos[1], -camera->pos[2]);
}

void checkBoundings(Camera *camera){
    if(camera->pos[0] > limitXl)
        camera->pos[0] = limitXl;
    if(camera->pos[0] < limitXr)
        camera->pos[0] = limitXr;
    if(camera->pos[2] > limitZd)
        camera->pos[2] = limitZd;
    if(camera->pos[2] < limitZu)
        camera->pos[2] = limitZu;
}

void moveCamera(Camera *camera, GLfloat speed){
    if(camera == NULL) return;
    float yrotRad = (camera->rot[1] / 180 * 3.141592654f);
    camera->pos[0] += (float)(sin(yrotRad)) * speed;
    camera->pos[2] -= (float)(cos(yrotRad)) * speed;
    checkBoundings(camera);
}

void strafeCamera(Camera *camera, GLfloat speed){
    if(camera == NULL) return;
    float yrotRad = (camera->rot[1] / 180 * 3.141592654f);
    camera->pos[0] += (float)(cos(yrotRad)) * speed;
    camera->pos[2] += (float)(sin(yrotRad)) * speed;
    checkBoundings(camera);
}

void rotateCameraX(Camera *camera, GLfloat angle){
    if(camera == NULL) return;
    camera->rot[0] += angle;
    if(camera->rot[0] > 90)
        camera->rot[0] = 90;
    if(camera->rot[0] < -90)
        camera->rot[0] = -90;
}

void rotateCameraY(Camera *camera, GLfloat angle){
    if(camera == NULL) return;
    camera->rot[1] += angle;
    if(camera->rot[1] >= 360 || camera->rot[1] <= -360)
        camera->rot[1] = 0;
}

void rotateCameraZ(Camera *camera, GLfloat angle){
    if(camera == NULL) return;
    camera->rot[2] += angle;
    if(camera->rot[2] >= 360 || camera->rot[2] <= -360)
        camera->rot[2] = 0;
}
