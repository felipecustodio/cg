// "Copyright 2017 Ed"
#include <GL/glut.h>

void canvas(void) {
    glClearColor(0.5f, 0.0f, 0.75f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.88f, 0.95f);
        glVertex2f(100, -50);
        glColor3f(0.96f, 0.38f, 0.56f);
        glVertex2f(200, 100);
        glVertex2f(300, -50);
    glEnd();

    glFlush();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);  // GLUT initialization
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // Window buffer type
    glutInitWindowSize(640, 480);  // Window size
    glutCreateWindow("a e s t h e t i c s");  // Window startup

    glutDisplayFunc(canvas);
    gluOrtho2D(0, 400, -150, 150);

    glutMainLoop();  // GLUT Loop

    return 0;
}
