#include <GL\glut.h>
#include <math.h>

#include "shapes.h"
#include "transforms.h"

#define BG_COL 0.5f, 0.0f, 0.75f, 1.0f
#define OBJ_COL1 0.37f, 0.88f, 0.95f
#define OBJ_COL2 0.96f, 0.38f, 0.56f

float curAngle = 0.0;

void draw(){
    // Colorir o fundo de branco
    glClearColor(BG_COL);
    glClear(GL_COLOR_BUFFER_BIT);
    /////////////////////////////////////

    // Iniciar as transformaçoes 2D
    glMatrixMode(GL_MODELVIEW);
    ///////////////////////////////

    /* -----------------TRI-01------------------ */
    glLoadIdentity();

    glColor3f(OBJ_COL1);
    Triangle *tri1 = createTriangle(10.0, 10.0);
        glTranslatef(6.0f, 6.0f, 0.0f);
        rotateTriangleCenter(tri1, -curAngle);
        drawTriangle(tri1);
    freeTriangle(tri1);
    /* -----------------TRI-01------------------ */

    /* -----------------TRI-02------------------ */
    glLoadIdentity();

    glColor3f(OBJ_COL2);
    Triangle *tri2 = createTriangle(10.0, 10.0);
        glTranslatef(22.0f, 6.0f, 0.0f);
        rotateTriangleCenter(tri2, curAngle);
        drawTriangle(tri2);
    freeTriangle(tri2);
    /* -----------------TRI-02------------------ */
    curAngle = curAngle + 0.05f;

    /* -----------------CIR-01------------------ */
    glLoadIdentity();

    glColor3f(OBJ_COL1);
    Circle *cir1 = createCircle(5.0, 1.0);
        glTranslatef(18.0f, 18.0f, 0.0f);
        drawCircleHollow(cir1);
    freeCircle(cir1);
    /* -----------------CIR-01------------------ */

    /* -----------------CIR-02------------------ */
    glLoadIdentity();

    glColor3f(OBJ_COL2);
    Circle *cir2 = createCircle(5.0, 5.0);
        glTranslatef(22.0f, 18.0f, 0.0f);
        drawCircleFilled(cir2);
    freeCircle(cir2);
    /* -----------------CIR-02------------------ */

    glFlush();
}

int main(int argc, char *argv[]){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 460);
    glutCreateWindow("a e s t h e t i c s");
    glutDisplayFunc(draw);

    glutIdleFunc(draw);

    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 50, 0, 36);

    glutMainLoop();
}
