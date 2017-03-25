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

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
	{
		h = 1;
	}

	float ratio = 1.0* w / h;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(45,ratio,1,600);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void rotate_around() {

	GLfloat temp_x, temp_y;
	// Recalculate 1st vertex
	x_1 = x_1 - c_x;
	y_1 = y_1 - c_y;
	temp_x = x_1;
	temp_y = y_1;
	x_1 = temp_x * cos(0.00174533) - temp_y * sin(0.00174533);
	y_1 = temp_y * cos(0.00174533) + temp_x * sin(0.00174533);
	x_1 += c_x;
	y_1 += c_y;

}

GLfloat x_1 = 100;
GLfloat y_1 = 0;
GLfloat x_2 = 150;
GLfloat y_2 = 50;

void draw(void)
{
	GLfloat temp_x, temp_y;
        GLfloat c_x, c_y;
        c_x = 200;
        c_y = 0;

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

	// Blade
	glBegin(GL_TRIANGLES);
            glColor3f(0.0f, 0.88f, 0.95f);
            glVertex2f(c_x, c_y);
            glColor3f(0.96f, 0.38f, 0.56f);
            glVertex2f(x_1, y_1);
            glVertex2f(x_2, y_2);
        glEnd();

	// Recalculate 1st vertex
        x_1 = x_1 - c_x;
        y_1 = y_1 - c_y;
        temp_x = x_1;
        temp_y = y_1;
        x_1 = temp_x * cos(0.00174533) - temp_y * sin(0.00174533);
        y_1 = temp_y * cos(0.00174533) + temp_x * sin(0.00174533);
        x_1 += c_x;
        y_1 += c_y;

	// Recalculate 2nd vertex
	x_2 = x_2 - c_x;
        y_2 = y_2 - c_y;
        temp_x = x_2;
        temp_y = y_2;
        x_2 = temp_x * cos(0.00174533) - temp_y * sin(0.00174533);
        y_2 = temp_y * cos(0.00174533) + temp_x * sin(0.00174533);
        x_2 += c_x;
        y_2 += c_y;

        glBegin(GL_POINTS);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex2f(x_1, y_1);
        glEnd();

	glBegin(GL_POINTS);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex2f(x_2, y_2);
        glEnd();

        glFlush();
}

void on_mouseClick(int button, int click_state, int x_mouse_position, int y_mouse_position)
{

	if (click_state == GLUT_DOWN) {
		if (button == GLUT_RIGHT_BUTTON) {
                        // Rotate clockwise
		} else if (button == GLUT_LEFT_BUTTON) {
                        // Rotate counter clockwise
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
        // glutReshapeFunc(changeSize);
        glutIdleFunc(draw);

        glutMouseFunc(on_mouseClick); // Handles mouse clicks

        gluOrtho2D(0, 400, -150, 150); // Defines the orthogonal plane to build the scene in

        glutMainLoop(); // Start operations according to the specifications above
}
