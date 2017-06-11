/*
- Rodrigo Contreras
- Computa��o Gr�fica 2017
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


// Vari�veis para controles de navega��o
GLfloat Px, Py;
GLsizei Sx = 500, Sy = 500;
GLdouble xmin = -1, xmax = 1, ymin = -1, ymax = 1;
bool desenhar = false;


void DesenhaPonto(GLfloat x, GLfloat y) {

	glColor3f(1.0f, 0.0f, 0.0f);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(x, y);
	glEnd();

}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	if (desenhar) DesenhaPonto(Px, Py);

	// Executa os comandos OpenGL
	glFlush();
}

// Fun��o callback para eventos de bot�es do mouse
void on_MouseClick(int button, int state, int mouse_x, int mouse_y)
{
	if (state == GLUT_DOWN)
	{

		if (button == GLUT_LEFT_BUTTON) {

			Px = (GLfloat)mouse_x;
			Py = (GLfloat)mouse_y;


			desenhar = true;
		}

		glutPostRedisplay();
	}

}

// Fun��o respons�vel por inicializar par�metros e vari�veis
void Inicializa(void)
{
	//Fundo da cena preto
	glClearColor(1.0f, 1.0f, 1.0f, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xmin, xmax, ymin, ymax);
	glViewport(0, 0, Sx, Sy);
}

// Programa Principal 
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	// Define do modo de opera��o da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Especifica a posi��o inicial da janela GLUT
	glutInitWindowPosition(100, 100);
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(Sx, Sy);
	// Cria a janela passando como argumento o t�tulo da mesma
	glutCreateWindow("Criador de pontos");
	// Registra a fun��o callback de redesenho da janela de visualiza��o
	glutDisplayFunc(Desenha);
	// Fun��o respons�vel por atualizar a tela EM DETERMINADO MOMENTO
	//glutReshapeFunc(on_ReshapeWindow);
	// Registra a fun��o callback para eventos de bot�es do mouse	
	glutMouseFunc(on_MouseClick);
	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();
	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}