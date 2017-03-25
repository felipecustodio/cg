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


/** Globals **/
/** TODO remove this **/
GLfloat c_x = 200;
GLfloat c_y = 0;
GLfloat x_1 = 100;
GLfloat y_1 = 0;
GLfloat x_2 = 150;
GLfloat y_2 = 50;

/* Draw loop */
void draw(void)
{
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);

        // Repaint screen
        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(10.0); // Define dot size

        // Center dot
        glBegin(GL_POINTS);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(c_x, c_y);
        glEnd();

	// Post
	glBegin(GL_QUADS);
		glColor3f(1.0, 0.59, 0.26);
		glVertex2f(c_x - 10, c_y - 100);
		glVertex2f(c_x - 10, c_y);
		glColor3f(0.3, 0.17, 0.0);
		glVertex2f(c_x + 10, c_y);
		glVertex2f(c_x + 10, c_y - 100);
	glEnd();

	// Blades
	glBegin(GL_TRIANGLES);
	    glColor3f(0.0f, 0.88f, 0.95f);
	    glVertex2f(c_x, c_y);
	    glColor3f(0.96f, 0.38f, 0.56f);
	    glVertex2f(x_1, y_1);
	    glVertex2f(x_2, y_2);
	glEnd();

	glBegin(GL_TRIANGLES);
	    glColor3f(0.0f, 0.88f, 0.95f);
	    glVertex2f(c_x, c_y);
	    glColor3f(0.96f, 0.38f, 0.56f);
	    glVertex2f(x_1 + 20, y_1);
	    glVertex2f(x_2 + 20, y_2);
	glEnd();

	glBegin(GL_TRIANGLES);
	    glColor3f(0.0f, 0.88f, 0.95f);
	    glVertex2f(c_x, c_y);
	    glColor3f(0.96f, 0.38f, 0.56f);
	    glVertex2f(x_1 + 50, y_1);
	    glVertex2f(x_2 + 20, y_2);
	glEnd();

        glFlush();
}

void on_mouseClick(int button, int click_state, int x_mouse_position, int y_mouse_position)
{
	GLfloat temp_x, temp_y;
	if (click_state == GLUT_DOWN) {
		if (button == GLUT_RIGHT_BUTTON) {

			// Recalculate 1st vertex
		        x_1 = x_1 - c_x;
		        y_1 = y_1 - c_y;
		        temp_x = x_1;
		        temp_y = y_1;
		        x_1 = temp_x * cos(0.5) + temp_y * sin(0.5);
		        y_1 = temp_y * cos(0.5) - temp_x * sin(0.5);
		        x_1 += c_x;
		        y_1 += c_y;

			// Recalculate 2nd vertex
			x_2 = x_2 - c_x;
		        y_2 = y_2 - c_y;
		        temp_x = x_2;
		        temp_y = y_2;
		        x_2 = temp_x * cos(0.5) + temp_y * sin(0.5);
		        y_2 = temp_y * cos(0.5) - temp_x * sin(0.5);
		        x_2 += c_x;
		        y_2 += c_y;

		} else if (button == GLUT_LEFT_BUTTON) {

			// Recalculate 1st vertex
		        x_1 = x_1 - c_x;
		        y_1 = y_1 - c_y;
		        temp_x = x_1;
		        temp_y = y_1;
		        x_1 = temp_x * cos(0.5) - temp_y * sin(0.5);
		        y_1 = temp_y * cos(0.5) + temp_x * sin(0.5);
		        x_1 += c_x;
		        y_1 += c_y;

			// Recalculate 2nd vertex
			x_2 = x_2 - c_x;
		        y_2 = y_2 - c_y;
		        temp_x = x_2;
		        temp_y = y_2;
		        x_2 = temp_x * cos(0.5) - temp_y * sin(0.5);
		        y_2 = temp_y * cos(0.5) + temp_x * sin(0.5);
		        x_2 += c_x;
		        y_2 += c_y;
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

        glutDisplayFunc(draw); // Set rendering function as "draw()"

	glutIdleFunc(draw); // Set draw to repeat while no events occur

        glutMouseFunc(on_mouseClick); // Handles mouse clicks

        gluOrtho2D(0, 400, -150, 150); // Defines the orthogonal plane to build the scene in

        glutMainLoop(); // Start operations according to the specifications above
}
