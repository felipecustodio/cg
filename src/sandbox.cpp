#include <GL/glut.h>

void draw(void)
{
        /* Primitives */

        // Line
        glBegin(GL_LINES);
                glVertex2f(0, -150);
                glVertex2f(400, 150);
        glEnd();

        // Triangle
        glBegin(GL_TRIANGLES);
                glVertex2f(100, -50);
                glVertex2f(200, 100);
                glVertex2f(300, -50);
        glEnd();

        // Quad
        glBegin(GL_QUADS);
                glVertex2f(100, -50);
                glVertex2f(100, 50);
                glVertex2f(200, 50);
                glVertex2f(200, -50);
        glEnd();

        glFlush();
}

int main(int argc, char* argv[])
{
        glutInit(&argc, argv); // Instanciate Glut
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Defines the buffer display mode
        glutInitWindowSize(800, 600); // Defines the size in pixels of the window
        glutCreateWindow("Sandbox"); // Defines the window title
        glutDisplayFunc(draw); // Set rendering function as "draw(.)"

        gluOrtho2D(0, 400, -150, 150); // Defines the orthogonal plane to build the scene in

        glutMainLoop(); // Start operations according to the specifications above
}
