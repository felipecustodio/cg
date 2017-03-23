/**
 * SCC0250 - Computação Gráfica
 * Trabalho 1 - Windmill
 * Alunos:
 *      Felipe Scrochio Custódio - 9442688
 *      Henrique Loschiavo -
 *      Lucas Antognoni -
 *      Gustavo Santiago -
 **/

#include <GL/glut.h>
#include <math.h>


void rotation(GLfloat x, GLfloat y, GLfloat c_x, GLfloat c_y)
{

        x = x - c_x;
        y = y - c_y;
        GLfloat temp_x = x;
        GLfloat temp_y = y;
        x = temp_x * cos(0.52) - temp_y * sin(0.52);
        y = temp_y * cos(0.52) + temp_x * sin(0.52);
        x += c_x;
        y += c_y;

}

void draw(void)
{
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        
        // Paint background
        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(10.0); // Define dot size

        // Center dot
        glBegin(GL_POINTS);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(200, 0);
        glEnd();

        // Dot that will rotate
        glBegin(GL_POINTS);
                glColor3f(0.0f, 0.0f, 1.0f);
                glVertex2f(100, 0);
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

        glutMouseFunc(on_mouseClick); // Handles mouse clicks

        gluOrtho2D(0, 400, -150, 150); // Defines the orthogonal plane to build the scene in

        glutMainLoop(); // Start operations according to the specifications above
}
