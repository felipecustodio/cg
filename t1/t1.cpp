/**
 * SCC0250 - Computação Gráfica
 * Trabalho 1 - Catavento
 * Alunos:
 *      Felipe Scrochio Custódio - 9442688
 *      Henrique Loschiavo -
 *      Lucas Antognoni -
 *      Gustavo Santiago -
 **/

#include <GL/glut.h>

void draw(void)
{

        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        // Paint background
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

void on_mouseClick(int button, int click_state, int x_mouse_position, int y_mouse_position)
{
	if (click_state == GLUT_DOWN) {
		if (button == GLUT_RIGHT_BUTTON) {
			// Rotate blades clockwise
		} else if (button == GLUT_LEFT_BUTTON) {
                        // Rotate blades counter clockwise
		}
	}

	glutPostRedisplay(); // Forces scene redraw
}

int main(int argc, char* argv[])
{
        glutInit(&argc, argv); // Instanciate Glut
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Defines the buffer display mode
        glutInitWindowSize(800, 600); // Defines the size in pixels of the window
        glutCreateWindow("Windmill"); // Defines the window title
        glutDisplayFunc(draw); // Set rendering function as "draw(.)"

        glutMouseFunc(on_mouseClick); // Handles mouse clicks

        gluOrtho2D(0, 400, -150, 150); // Defines the orthogonal plane to build the scene in

        glutMainLoop(); // Start operations according to the specifications above
}
