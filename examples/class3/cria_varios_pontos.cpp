/*
- Rodrigo Contreras
- Computa��o Gr�fica 2017
- Desenhando quantos pontos forem necess�rio com o aux�lio da "<vector>".
*/

#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <vector>


// Vari�veis para controles de navega��o
GLfloat R = 0.0f, G = 0.0f, B = 0.0f;
GLsizei Sx = 500, Sy = 500;
GLdouble xmin = -1, xmax = 1, ymin = -1, ymax = 1;
struct Ponto {
	GLfloat x;
	GLfloat y;

	GLfloat R;
	GLfloat G;
	GLfloat B;
};
std::vector<Ponto> pontos;
int contPontos = 0, i;


void DesenhaPonto(Ponto P) {

	glColor3f(P.R, P.G, P.B);
	glPointSize(5.0);
	glBegin(GL_POINTS);
	glVertex2f(P.x, P.y);
	glEnd();

}

// Fun��o callback de redesenho da janela de visualiza��o
void Desenha(void)
{
	// Limpa a janela de visualiza��o com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);

	if (contPontos)
		for (i = 0; i < contPontos; i++)
			DesenhaPonto(pontos[i]);


	// Executa os comandos OpenGL
	glFlush();
}

// Fun��o callback para eventos de bot�es do mouse
void on_MouseClick(int button, int state, int mouse_x, int mouse_y)
{
	if (state == GLUT_DOWN)
	{

		switch (button) {
		case GLUT_LEFT_BUTTON:	  R = 1.0f;
			G = 0.0f;
			B = 0.0f;
			break;
		case GLUT_MIDDLE_BUTTON:  R = 0.0f;
			G = 1.0f;
			B = 0.0f;
			break;
		case GLUT_RIGHT_BUTTON:	  R = 0.0f;
			G = 0.0f;
			B = 1.0f;
			break;
		}


		float x = xmin + (mouse_x *(xmax - xmin)) / Sx;
		float y = ymax - (mouse_y * (ymax - ymin)) / Sy;
		
		pontos.push_back(Ponto());
		pontos[contPontos].x = (GLfloat)x;
		pontos[contPontos].y = (GLfloat)y;

		pontos[contPontos].R = R;
		pontos[contPontos].G = G;
		pontos[contPontos].B = B;

		contPontos++;


		glutPostRedisplay();
	}

}

// Fun��o callback chamada quando o tamanho da janela � alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	// Para previnir uma divis�o por zero
	if (h == 0) h = 1;

	// Especifica as dimens�es da viewport
	Sx = w;
	Sy = h;
	glViewport(0, 0, Sx, Sy);

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
	glutReshapeFunc(AlteraTamanhoJanela);

	// Registra a fun��o callback para eventos de bot�es do mouse	
	glutMouseFunc(on_MouseClick);

	// Chama a fun��o respons�vel por fazer as inicializa��es 
	Inicializa();

	// Inicia o processamento e aguarda intera��es do usu�rio
	glutMainLoop();

	return 0;
}