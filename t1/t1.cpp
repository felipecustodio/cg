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

// Passar por parâmetro
// GLfloat, R, G, B
void triangle(void)
{
        glBegin(GL_TRIANGLES);
            glColor3f(0.0f, 0.88f, 0.95f);
            glVertex2f(100, -50);
            glColor3f(0.96f, 0.38f, 0.56f);
            glVertex2f(200, 100);
            glVertex2f(300, -50);
        glEnd();
}

// Passar por parâmetro
// GLfloat, R, G, B
void quad(void)
{
        glBegin(GL_QUADS);
                glColor3f(0.0f, 0.88f, 0.95f);
                glVertex2f(100, -50);
                glVertex2f(200, 100);
                glColor3f(0.96f, 0.38f, 0.56f);
                glVertex2f(300, -50);
                glVertex2f(400, 100);
        glEnd();
}

void rotation_test(void)
{

        GLfloat x, y;
        x = 100.0f;
        y = 0.0f;

        GLfloat temp_x, temp_y;
        temp_x = x;
        temp_y = y;

        GLfloat c_x, c_y;
        c_x = 200.0f;
        c_y = 0.0f;

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

        for (int i = 0; i < 10000; i++) {

                // x′=xcosθ−ysinθ
                // y′=ycosθ+xsinθ
                // Adicionar (x, y) em (x', y')
                x = x - c_x;
                y = y - c_y;
                temp_x = x;
                temp_y = y;
                x = temp_x * cos(0.52) - temp_y * sin(0.52);
                y = temp_y * cos(0.52) + temp_x * sin(0.52);
                x += c_x;
                y += c_y;

                glBegin(GL_POINTS);
                        glColor3f(0.0f, 0.0f, 1.0f);
                        glVertex2f(x, y);
                glEnd();

        }

}

void draw(void)
{
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        // Paint background
        glClear(GL_COLOR_BUFFER_BIT);

        glPointSize(10.0);

        rotation_test();

        glFlush();
}

void on_mouseClick(int button, int click_state, int x_mouse_position, int y_mouse_position)
{

        // Rotação em volta de um ponto
        // (x', y') em volta de (0, 0)
        // x′=xcosθ−ysinθ
        // y′=ycosθ+xsinθ
        // Adicionar (x, y) em (x', y')

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
        glutDisplayFunc(draw); // Set rendering function as "draw()"

        // glutMouseFunc(on_mouseClick); // Handles mouse clicks

        gluOrtho2D(0, 400, -150, 150); // Defines the orthogonal plane to build the scene in

        glutMainLoop(); // Start operations according to the specifications above
}
