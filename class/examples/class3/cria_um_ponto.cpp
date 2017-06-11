/*
- Rodrigo Contreras
- Computação Gráfica 2017
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>


// Variáveis para controles de navegação
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

// Função callback de redesenho da janela de visualização
void Desenha(void)
{
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	if (desenhar) DesenhaPonto(Px, Py);

	// Executa os comandos OpenGL
	glFlush();
}

// Função callback para eventos de botões do mouse
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

// Função responsável por inicializar parâmetros e variáveis
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
	// Define do modo de operação da GLUT
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	// Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(100, 100);
	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(Sx, Sy);
	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Criador de pontos");
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);
	// Função responsável por atualizar a tela EM DETERMINADO MOMENTO
	//glutReshapeFunc(on_ReshapeWindow);
	// Registra a função callback para eventos de botões do mouse	
	glutMouseFunc(on_MouseClick);
	// Chama a função responsável por fazer as inicializações 
	Inicializa();
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}