#include "camera.h"

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
	//		  camera->view[0], camera->view[1], camera->view[2],
	//		  camera->up[0],   camera->up[1],   camera->up[2]);
    glRotatef(camera->rot[0], 1, 0, 0);
    glRotatef(camera->rot[1], 0, 1, 0);
    glRotatef(camera->rot[2], 0, 0, 1);
    glTranslatef(-camera->pos[0], -camera->pos[1], -camera->pos[2]);
}

void moveCamera(Camera *camera, GLfloat speed){
    if(camera == NULL) return;
    float xrotRad = (camera->rot[0] / 180 * 3.141592654f);
    float yrotRad = (camera->rot[1] / 180 * 3.141592654f);
    camera->pos[0] += (float)(sin(yrotRad)) * speed;
    camera->pos[2] -= (float)(cos(yrotRad)) * speed;
    //camera->pos[1] -= (float)(sin(xrotRad)) * speed;
}

void strafeCamera(Camera *camera, GLfloat speed){
    if(camera == NULL) return;
    float yrotRad = (camera->rot[1] / 180 * 3.141592654f);
    camera->pos[0] += (float)(cos(yrotRad)) * speed;
    camera->pos[2] += (float)(sin(yrotRad)) * speed;
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
