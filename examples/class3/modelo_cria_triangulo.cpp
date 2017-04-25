/*
- Rodrigo Contreras
- Computação Gráfica 2017
- Desenhando 3 pontos e um triângulo.
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <sstream>
#include <stdio.h>

// Variáveis para controles de navegação
GLfloat Px1, Px2, Px3, Py1, Py2, Py3;
bool existeTr = false, bP1 = false, bP2 = false, bP3 = false;
float a, b, c;
GLsizei Sx = 500, Sy = 500;
GLdouble xmin = -1, xmax = 1, ymin = -1, ymax = 1;
bool desenhar = false;

// Função que desenha um cubo cujas cores dos vértices
// mostram como é o espaço RGB
void DesenhaTrianguloRGB(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2, GLfloat x3, GLfloat y3)
{

	// Desenha o triângulo
	glColor3f(1.0f, 0.0f, 1.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glEnd();

}

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

	if (existeTr) DesenhaTrianguloRGB(Px1, Py1, Px2, Py2, Px3, Py3);

	if (bP3) DesenhaPonto(Px3, Py3);
	if (bP2) DesenhaPonto(Px2, Py2);
	if (bP1) DesenhaPonto(Px1, Py1);

	// Executa os comandos OpenGL
	glFlush();

}

// Função usada para especificar o volume de visualização
void EspecificaParametrosVisualizacao(void)
{
	//Fundo da cena preto
	glClearColor(1.0f, 1.0f, 1.0f, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(xmin, xmax, ymin, ymax);

}


// Função callback para eventos de botões do mouse
void on_MouseClick(int button, int state, int mouse_x, int mouse_y)
{
	if (state == GLUT_DOWN)
	{
		GLfloat x = (xmax - xmin)*mouse_x / Sx + xmin;
		GLfloat y = ymax - (ymax - ymin)*mouse_y / Sy;

		if (existeTr) {
			existeTr = false;
			bP1 = false;
			bP2 = false;
			bP3 = false;
		}

		if (button == GLUT_LEFT_BUTTON) {

			if (!bP1) {
				Px1 = (GLfloat)x;
				Py1 = (GLfloat)y;
				bP1 = true;
			}
			else {
				if (!bP2) {
					Px2 = (GLfloat)x;
					Py2 = (GLfloat)y;
					bP2 = true;
				}
				else {
					if (!bP3) {
						Px3 = (GLfloat)x;
						Py3 = (GLfloat)y;
						bP3 = true;
					}
				}
			}
		}

		glutPostRedisplay();
	}

	existeTr = bP1 && bP2 && bP3;

	if (existeTr) {

		a = sqrt((Px1 - Px2)*(Px1 - Px2) + (Py1 - Py2)*(Py1 - Py2));
		b = sqrt((Px1 - Px3)*(Px1 - Px3) + (Py1 - Py3)*(Py1 - Py3));
		c = sqrt((Px2 - Px3)*(Px2 - Px3) + (Py2 - Py3)*(Py2 - Py3));
		if ((a + b < c) || (b + c < a) || (a + c < b)) {
			existeTr = false;
			bP1 = false;
			bP2 = false;
			bP3 = false;
		}

		glutPostRedisplay();
	}

}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divisão por zero
	if (h == 0) h = 1;

	// Especifica as dimensões da viewport
	glViewport(0, 0, w, h);

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
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); //GLUT_DOUBLE | GLUT_DEPTH); 

												 // Especifica a posição inicial da janela GLUT
	glutInitWindowPosition(5, 5);

	// Especifica o tamanho inicial em pixels da janela GLUT
	glutInitWindowSize(Sx, Sy);

	// Cria a janela passando como argumento o título da mesma
	glutCreateWindow("Cubo RGB");

	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);

	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a função callback para eventos de botões do mouse	
	glutMouseFunc(on_MouseClick);

	// Chama a função responsável por fazer as inicializações 
	Inicializa();

	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}