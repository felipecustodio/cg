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

#define ORTHO_X 300
#define ORTHO_Y 300

/* Reshaping function */
void reshape(int width, int height){
    // Screen can't be smaller than 0
    if(height == 0)
        height = 1;

    float ratio = width * 1.0/height;

    // Changes matrix mode to projection
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
	glLoadIdentity();

    // Viewport correction
    glViewport(0, 0, width, height);

    // Perspective and projection correction
    //gluPerspective(45, ratio, -1, 1);
    gluOrtho2D(-ORTHO_X * ratio, ORTHO_X * ratio, -ORTHO_Y, ORTHO_Y);

    // Switches matrix mode back to modelview
    glMatrixMode(GL_MODELVIEW);
}


/* Draw loop */
void draw(void)
{
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);

        // Repaint screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Set matrix mode to MODELVIEW
        glMatrixMode(GL_MODELVIEW);

        // Reset Matrix
    	glLoadIdentity();

        glBegin(GL_POINTS);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(0, 0);
        glEnd();


        glPointSize(10.0); // Define dot size

        glutSwapBuffers();
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
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Defines the buffer display mode
        glutInitWindowSize(800, 600); // Defines the size in pixels of the window
        glutCreateWindow("Windmill"); // Defines the window title

        glutDisplayFunc(draw); // Set rendering function as "draw()"
        glutReshapeFunc(reshape); // Set reshaping function as "reshape()"
        glutIdleFunc(draw); // Set draw to repeat while no events occur
        glutMouseFunc(on_mouseClick); // Handles mouse clicks

        glMatrixMode(GL_PROJECTION);
        gluOrtho2D(-ORTHO_X, ORTHO_X, -ORTHO_Y, ORTHO_Y); // Defines the orthogonal plane to build the scene in

        glutMainLoop(); // Start operations according to the specifications above
}
