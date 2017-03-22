////// Rand /////////////////////////////
#include "cstdlib"     /* srand, rand */
#include "ctime"
#include <stdio.h>
////////////////////////////////////////

#include<GL/glut.h>


/////////////////////////////////////////

GLfloat R=0.0f, G=0.0f, B=0.0f;
////////////////////////////////////////

GLfloat sorteia_cor() {

	return (rand()*1.0f) / (RAND_MAX*1.0f);
}


void desenha(void) {
	/* Colorir o fundo da cena de branco */
	glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glColor3f(R, G, B);
	glBegin(GL_QUADS);
		glVertex2f(100.0f, -100.0f);
		glVertex2f(100.0f, 100.0f);
		glVertex2f(300.0f, 100.0f);
		glVertex2f(300.0f, -100.0f);
	glEnd();


	glFlush();

}

////////////// Eventos /////////////////////
void on_mouseClick(int botao_clicado, int estado_do_click, int x_mouse_position, int y_mouse_position) {

	if (estado_do_click == GLUT_DOWN) {
		if (botao_clicado == GLUT_RIGHT_BUTTON) {
			R = 0.0f;
			G = 0.0f;
			B = 0.0f;
		} else if (botao_clicado == GLUT_LEFT_BUTTON) {
			R = sorteia_cor();
			G = sorteia_cor();
			B = sorteia_cor();
		}
	}

	glutPostRedisplay(); // For�a a glut redesenhar a cena ap�s a atualiza��o.
}
///////////////////////////////////////////

int main(int argc, char* argv[])
{

	srand(time(NULL));

	glutInit(&argc, argv); // Inicia uma inst�ncia da glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Define o modo de display do buffer
	glutInitWindowSize(400, 300); // Define o tamanho em pixels da janela
	glutCreateWindow("Exemplo OpenGL"); // Define o t�tulo da janela
	glutDisplayFunc(desenha); // Estabelece que a fun��o de rendering � a fun��o "desenha(.)"


	glutMouseFunc(on_mouseClick); // Evento de click do mouse


	gluOrtho2D(0, 400, -150, 150); // Define o plano ortogonal em que a cena ser� constru�da

	glutMainLoop(); // Inicia as opera��es conforme as especifica��es anteriores
}
