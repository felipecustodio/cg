#include <GL/glut.h>
#include <math.h>

GLfloat angSeg = 0.0f, angMin = 0.0f, angHor = 0.0f, passo = 6.0f;

// Funcao callback chamada para fazer o desenho
void desenha() {

	// Colorir o fundo de branco
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	/////////////////////////////////////

	// Iniciar as transformações 2D
	glMatrixMode(GL_MODELVIEW); // Inicia-se a matriz de transformações da openGL
	glLoadIdentity();
	///////////////////////////////


	// Especifica a cor preta 
	glColor3f(0.0f, 0.0f, 0.0f);

	GLfloat N = 100.0f, a = 100.0f, b = 100.0f, r = 100.0f, LIM = 2.0f*3.14159265f, h = LIM / N, theta;
	glLineWidth(10);
	glBegin(GL_LINE_LOOP);
	for (theta = 0.0f; theta <= LIM; theta += h) {
		glVertex2f(a + r*cos(theta), b + r*sin(theta));
	}
	glEnd();

	// Ponteiro das horas
	glLineWidth(8);
	glBegin(GL_LINES);
	glVertex2f(a, b);
	glVertex2f(a, b + r);
	glEnd();


	glLoadIdentity();
	// Ponteiro dos minutos
	glColor3f(0.0f, 1.0f, 0.0f);
	glLineWidth(4);
	glBegin(GL_LINES);
	glVertex2f(a, b);
	glVertex2f(a, b + r);
	glEnd();


	glLoadIdentity();
	// Ponteiro dos segundos
	glColor3f(1.0f, 0.0f, 0.0f);
	glLineWidth(2);
	glBegin(GL_LINES);
	glVertex2f(a, b);
	glVertex2f(a, b + r);
	glEnd();

	glutSwapBuffers();
	glFlush();
}





// Programa Principal 
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); // Inicia uma instância da glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Define o modo de display do buffer
	glutInitWindowSize(800, 800); // Define o tamanho em pixels da janela
	glutCreateWindow("Transformações 2D em triângulos");
	glutDisplayFunc(desenha); // Estabelece que a função de rendering é a função "desenha(.)"


	glMatrixMode(GL_PROJECTION); // Especificações de observação de cena
	gluOrtho2D(0, 200, 0, 200);	// Observa-se a seção de plano [0,200]x[0,200]


	glutMainLoop();
}
