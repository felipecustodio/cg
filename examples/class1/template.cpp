#include <GL/glut.h>

void draw(void)
{
        /* Primitives */
        glBegin(GL_LINES);
        glVertex2f(0, -150);
        glVertex2f(400, 150);
        glEnd();

        glFlush();
}

int main(int argc, char* argv[])
{
        glutInit(&argc, argv); // Instanciate Glut
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Defines the buffer display mode
        glutInitWindowSize(400, 300); // Defines the size in pixels of the window
        glutCreateWindow("Exemplo OpenGL"); // Defines the window title
        glutDisplayFunc(draw); // Set rendering function as "draw(.)"

        gluOrtho2D(0, 400, -150, 150); // Defines the orthogonal plane to build the scene in

        glutMainLoop(); // Start operations according to the specifications above
}
