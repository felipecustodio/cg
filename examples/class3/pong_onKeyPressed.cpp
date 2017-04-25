/* programa TELEJOGO */
/* Prof. Marco Antonio G. de Carvalho, UNICAMP-2006 */
/* Adaptado por Renato Rodrigues Oliveira da Silva, ICMC-USP-2009 */
/* Readaptado por Rodrigo C Contreras, ICMC-USP-2017 */
/* EXEMPLO DE ANIMACAO */

#include <stdlib.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>
#include <cmath>

#define DIREITA 1
#define ESQUERDA 0
#define CIMA 1
#define BAIXO 0

GLint movebolax = 0, movebolay = 0;
GLfloat raquetePy = 215, raqueteIAPy = 250, deltay = 10;
GLint direcaox = DIREITA, direcaoy = CIMA;
GLsizei largura = 600, altura = 400;
GLdouble ortholeft = 0, orthoright = 600, orthobot = 0, orthotop = 400;
int contTicks = 0, r = RAND_MAX / 2;



void iniciaParametrosVisualizacao(void) {
	//Fundo da cena verde mesa de ping-pong
	glClearColor(0.0, 0.6, 0.2, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(ortholeft, orthoright, orthobot, orthotop);
}

void display(void) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);
	glLineWidth(15.0);

	//Desenha a borda da cena
	glBegin(GL_LINE_LOOP);
	glVertex2i(2, 2);  glVertex2i(599, 2);
	glVertex2i(599, 399); glVertex2i(2, 399);
	glEnd();

	//Desenha as raquetes

	// Raquete da IA
	glBegin(GL_LINES);
	glVertex2f(100.0f, raqueteIAPy - 25);
	glVertex2f(100.0f, raqueteIAPy + 25);
	glEnd();

	// Raquete do usuário
	glBegin(GL_LINES);
	glVertex2f(500.0f, raquetePy - 25);
	glVertex2f(500.0f, raquetePy + 25);
	glEnd();

	glPointSize(15.0);
	//Desenha a bola
	glBegin(GL_POINTS);
	glVertex2i(movebolax + 200, movebolay + 210);
	glEnd();

	//glutSwapBuffers();
	glFlush();
}

// Função callback chamada para gerenciar eventos de teclas normais (ESC)
void on_KeyPressed(unsigned char tecla, int x, int y)
{
	if (tecla == 27) // ESC ?
		exit(0);

	if (tecla == 'w' || tecla == 'W') {
		raquetePy += deltay;
		glutPostRedisplay();
	}
	if (tecla == 's' || tecla == 'S') {
		raquetePy -= deltay;
		glutPostRedisplay();
	}
}

// Função callback para tratar eventos de teclas especiais
void on_SpecialKeyPressed(int tecla, int x, int y)
{
	switch (tecla)
	{
	case GLUT_KEY_UP:	raquetePy += deltay;
		break;
	case GLUT_KEY_DOWN:	raquetePy -= deltay;
		break;
	}

	glutPostRedisplay();
}

void on_TickTackBola(int passo)
{
	//Se estiver se movendo para a direita...
	if (direcaox == DIREITA) {
		movebolax += passo;
		// Se alcancou a raquete do usuário e este defendeu, muda de direcao, senão acabou o jogo.
		if (movebolax == 290) {
			float dist = abs(raquetePy - (movebolay + 210));
			if (dist <= 25)
				direcaox = ESQUERDA;
			else {
				// Desliga este timer, não deixando a bolinha andar mais.
				passo = 0;
				// Telona vermelha = PERDEU!!!
				glClearColor(1.0, 0.0, 0.0, 0.0);
				glClear(GL_COLOR_BUFFER_BIT);

				// Não deixe mais o usuário movimentar a raquete.
				glutPassiveMotionFunc(NULL);
			}
		}
	}
	else { // A bolinha foi pro campo da IA
		movebolax -= passo;
		if (movebolax == -90) {
			float dist = abs(raqueteIAPy - (movebolay + 210));
			if (dist <= 25)
				direcaox = DIREITA;
			else {
				// Desliga este timer, não deixando a bolinha andar mais.
				passo = 0;
				// Telona azul = GANHOU!!!
				glClearColor(0.0, 0.0, 1.0, 0.0);
				glClear(GL_COLOR_BUFFER_BIT);

				// Não deixe mais o usuário movimentar a raquete.
				glutPassiveMotionFunc(NULL);
			}
		}
	}

	//Se estiver se movendo para a direita
	if (direcaoy == CIMA) { // Bolinha subindo.
		movebolay += passo;
		// Se alcancou a borda de cima, muda de direcao
		if (movebolay == 180) direcaoy = BAIXO;
	}
	else { // Bolinha Descendo
		movebolay -= passo;
		// Se alcançou a borda de baixo, pode começar a subir
		if (movebolay == -200) direcaoy = CIMA;
	}

	//Forca o GLUT a pintar a cena novamente
	glutPostRedisplay();
	//Aciona novamente o timer
	glutTimerFunc(10, on_TickTackBola, passo);

}


void raqueteIA(int passo)
{
	if (contTicks == 10) {
		r = rand();
		contTicks = 0;
	}
	else {
		contTicks++;
	}
	//Se estiver se movendo para a direita
	if (direcaoy == CIMA) { // Bolinha subindo.
		if ((1.0*r) / RAND_MAX <= 0.99) raqueteIAPy += passo;
		else {
			raqueteIAPy -= passo;
		}
	}
	else {
		if ((1.0*r) / RAND_MAX <= 0.99) raqueteIAPy -= passo;
		else {
			raqueteIAPy += passo;
		}
	}

	//Aciona novamente o timer
	glutTimerFunc(10, raqueteIA, passo);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(largura, altura);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("PONG");

	iniciaParametrosVisualizacao();
	glutDisplayFunc(display);
	glutTimerFunc(10, on_TickTackBola, 1);
	glutTimerFunc(10, raqueteIA, 1);
	glutKeyboardFunc(on_KeyPressed);
	glutSpecialFunc(on_SpecialKeyPressed);
	glutMainLoop();
	return 0;
}