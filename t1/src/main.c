/**
 * SCC0250 - Computação Gráfica
 * Trabalho 1 - Windmill
 * Alunos:
 *      Felipe Scrochio Custódio - 9442688
 *      Henrique Loschiavo -
 *      Lucas Antognoni -
 *      Gustavo Santiago - 8937416
 **/

#include <GL/glut.h>
#include <math.h>
#include "shapes.h"
#include "transforms.h"

/* Draw loop */
void draw(void)
{
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);

        // Repaint screen
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_POINTS);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(0, 0);
        glEnd();


        glPointSize(10.0); // Define dot size

        glFlush();
}

void on_mouseClick(int button, int click_state, int x_mouse_position, int y_mouse_position)
{
	if (click_state == GLUT_DOWN) {
		if (button == GLUT_RIGHT_BUTTON) {

		} else if (button == GLUT_LEFT_BUTTON) {

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

        // TODO: reshape function

        glutDisplayFunc(draw); // Set rendering function as "draw()"

	glutIdleFunc(draw); // Set draw to repeat while no events occur

        glutMouseFunc(on_mouseClick); // Handles mouse clicks

        gluOrtho2D(-400, 400, -300, 300); // Defines the orthogonal plane to build the scene in

        glutMainLoop(); // Start operations according to the specifications above
}
