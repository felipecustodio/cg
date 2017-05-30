#include "../includes/shapes.h"

/* ----------------------------- TEXTURES ------------------------------ */
GLuint loadTexture(const char *filename) {

        // Load texture with RGBA
        // Transparency enabled
        GLuint tex = SOIL_load_OGL_texture(filename,
        SOIL_LOAD_RGBA,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);

        if (!tex) {
                return EXIT_FAILURE;
        }

        // Texture parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}
/* ----------------------------- TEXTURES ------------------------------ */

/* ---------------------------------- TEXT ---------------------------------- */
Text *createText(void *font, const char *string) {
    Text *newTxt = (Text *) malloc(sizeof(Text));

    newTxt->font = font;
    newTxt->string = string;

    newTxt->x = 0.0;
    newTxt->y = 0.0;
    newTxt->z = 0.0;

    return newTxt;
}

void drawText(Text *text, int x, int y) {
    if(text == NULL || text->font == NULL || text->string == NULL) return;

    text->x = x;
    text->y = y;

    int strsize = strlen(text->string);

    glRasterPos3f(text->x, text->y, text->z);

    int i = 0;
    for(i = 0; i < strsize; i++) {
        glutBitmapCharacter(text->font, text->string[i]);
    }
}

void freeText(Text *text) {
    if(text) {
        free(text);
        text = NULL;
    }
}
/* ---------------------------------- TEXT ---------------------------------- */

/* ---------------------------------- PLANE --------------------------------- */
// 0-------1
// |   .   |
// |       |
// 3-------2
// Plane Coordinates
Plane* createPlane(){
    Plane *plane = (Plane *) malloc(sizeof(Plane));

    plane->thickness = 1.0f;

    plane->color[0] = 1.0;
    plane->color[1] = 1.0;
    plane->color[2] = 1.0;

    plane->texture = 0;

    plane->x[0] = 0.0;
    plane->y[0] = 0.0;
    plane->z[0] = 0.0;

    plane->x[1] = 0.0;
    plane->y[1] = 0.0;
    plane->z[1] = 0.0;

    plane->x[2] = 0.0;
    plane->y[2] = 0.0;
    plane->z[2] = 0.0;

    plane->x[3] = 0.0;
    plane->y[3] = 0.0;
    plane->z[3] = 0.0;

    return plane;
}

void setPlaneCoordinates(Plane *plane, float x1, float y1, float z1,
                                             float x2, float y2, float z2,
                                             float x3, float y3, float z3,
                                             float x4, float y4, float z4) {
    if (plane == NULL) return;

    plane->x[0] = x1;
    plane->y[0] = y1;
    plane->z[0] = z1;

    plane->x[1] = x2;
    plane->y[1] = y2;
    plane->z[1] = z2;

    plane->x[2] = x3;
    plane->y[2] = y3;
    plane->z[2] = z3;

    plane->x[3] = x4;
    plane->y[3] = y4;
    plane->z[3] = z4;
}

void setPlaneThickness(Plane *plane, float thickness){
    if (plane == NULL) return;

    plane->thickness = thickness;
}

void setPlaneColor(Plane *plane, float r, float g, float b){
    if (plane == NULL) return;

    plane->color[0] = r;
    plane->color[1] = g;
    plane->color[2] = b;
}

void setPlaneTexture(Plane *plane, GLuint texture){
    if (plane == NULL) return;

    plane->texture = texture;
}

void drawPlaneHollow(Plane* plane) {
    if (plane == NULL) return;

    glColor3f(plane->color[0], plane->color[1], plane->color[2]);

    glLineWidth(plane->thickness);

    glBegin(GL_LINE_LOOP);
        glVertex3f(plane->x[0], plane->y[0], plane->z[0]);
        glVertex3f(plane->x[1], plane->y[1], plane->z[1]);
        glVertex3f(plane->x[2], plane->y[2], plane->z[2]);
        glVertex3f(plane->x[3], plane->y[3], plane->z[3]);
    glEnd();
}

void drawPlaneFilled(Plane* plane) {
    if (plane == NULL) return;

    glColor3f(plane->color[0], plane->color[1], plane->color[2]);

    glBegin(GL_QUADS);
        glVertex3f(plane->x[0], plane->y[0], plane->z[0]);
        glVertex3f(plane->x[1], plane->y[1], plane->z[1]);
        glVertex3f(plane->x[2], plane->y[2], plane->z[2]);
        glVertex3f(plane->x[3], plane->y[3], plane->z[3]);
    glEnd();
}

void drawPlaneTextured(Plane *plane){
    if (plane == NULL) return;

    glBindTexture(GL_TEXTURE_2D, plane->texture);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor3f(plane->color[0], plane->color[1], plane->color[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glVertex3f(plane->x[0], plane->y[0], plane->z[0]);
        glTexCoord2f(0, 1);
        glVertex3f(plane->x[1], plane->y[1], plane->z[1]);
        glTexCoord2f(1, 1);
        glVertex3f(plane->x[2], plane->y[2], plane->z[2]);
        glTexCoord2f(1, 0);
        glVertex3f(plane->x[3], plane->y[3], plane->z[3]);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);
}

void freePlane(Plane *plane) {
    if(plane){
        free(plane);
        plane = NULL;
    }
}
/* ---------------------------------- PLANE --------------------------------- */

/* ---------------------------------- CUBE ---------------------------------- */
Cube *createCube(){
    Cube *cube = (Cube *) malloc(sizeof(Cube));

    cube->thickness = 1.0f;

    cube->color[0] = 1.0;
    cube->color[1] = 1.0;
    cube->color[2] = 1.0;

    cube->texture = 0;

    cube->x = 0.0;
    cube->y = 0.0;
    cube->z = 0.0;

    cube->sizeX = 0.0;
    cube->sizeY = 0.0;
    cube->sizeZ = 0.0;

    return cube;
}

void setCubeColor(Cube *cube, float r, float g, float b){
    if (cube == NULL) return;

    cube->color[0] = r;
    cube->color[1] = g;
    cube->color[2] = b;
}

void setCubeCoordinates(Cube *cube, float x, float y, float z){
    if (cube == NULL) return;

    cube->x = x;
    cube->y = y;
    cube->z = z;
}

void setCubeThickness(Cube *cube, float thickness){
    if (cube == NULL) return;

    cube->thickness = thickness;
}

void setCubeSize(Cube *cube, float x, float y, float z){
    if (cube == NULL) return;

    cube->sizeX = x;
    cube->sizeY = y;
    cube->sizeZ = z;
}

void setCubeTexture(Cube *cube, GLuint texture){
    cube->texture = texture;
}

void drawCubeHollow(Cube *cube){
    if (cube == NULL) return;

    Plane *plane = createPlane();
        setPlaneColor(plane, cube->color[0], cube->color[1], cube->color[2]);
        setPlaneThickness(plane, cube->thickness);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z);
        drawPlaneHollow(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneHollow(plane);
        setPlaneCoordinates(plane, (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneHollow(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneHollow(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneHollow(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneHollow(plane);
    freePlane(plane);
}

void drawCubeFilled(Cube *cube){
    if (cube == NULL) return;

    Plane *plane = createPlane();
        setPlaneColor(plane, cube->color[0], cube->color[1], cube->color[2]);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z);
        drawPlaneFilled(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneFilled(plane);
        setPlaneCoordinates(plane, (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneFilled(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneFilled(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneFilled(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneFilled(plane);
    freePlane(plane);
}

void drawCubeTextured(Cube *cube){
    if (cube == NULL) return;

    Plane *plane = createPlane();
        setPlaneColor(plane, cube->color[0], cube->color[1], cube->color[2]);
        setPlaneTexture(plane, cube->texture);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z);
        drawPlaneTextured(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneTextured(plane);
        setPlaneCoordinates(plane, (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneTextured(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneTextured(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, (cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneTextured(plane);
        setPlaneCoordinates(plane, -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, (cube->sizeZ/2) + cube->z,
                                (cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z,
                                -(cube->sizeX/2) + cube->x, -(cube->sizeY/2) + cube->y, -(cube->sizeZ/2) + cube->z);
        drawPlaneTextured(plane);
    freePlane(plane);
}

void freeCube(Cube *cube){
    if(cube){
        free(cube);
        cube = NULL;
    }
}
/* ---------------------------------- CUBE ---------------------------------- */
