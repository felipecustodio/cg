/*
* Criação de sombras planares.
* Referência do Código Original: OpenGL Super Bible
* Shadow.cpp ( página 339 )
*/
#include <windows.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdio.h>
// Variaveis para controle de giro de visao
float g_fSpinX_L = 0.0f;
float g_fSpinY_L = -10.0f;
// Controle do Giro do Objeto
float g_fSpinX_R = 0.0f;
float g_fSpinY_R = 0.0f;
// Matriz da sombra
float g_shadowMatrix[16];
// Posição da fonte de luz no espaço
float g_lightPosition[] = { 2.0f, 6.0f, 0.0f, 1.0f };
// Controla o objeto a ser desenhado
int objeto = 1;
/*
Variáveis para desenho da
superfície de projeção da sombra
*/
struct Vertex
{
	float nx, ny, nz;
	float x, y, z;
};
Vertex g_floorQuad[] =
{
	{ 0.0f, 1.0f, 0.0f, -5.0f, 0.0f, -5.0f },
	{ 0.0f, 1.0f, 0.0f, -5.0f, 0.0f, 5.0f },
	{ 0.0f, 1.0f, 0.0f, 5.0f, 0.0f, 5.0f },
	{ 0.0f, 1.0f, 0.0f, 5.0f, 0.0f, -5.0f },
};
void init(void)
{
	// glClearColor( 0.35f, 0.53f, 0.7f, 1.0f );
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, 640 / 480.0f, 0.1f, 100.0f);
	
	float luzAmbiente[] = { 0.0f, 0.2f, 0.0f, 1.0f };
	float luzDifusa[] = { 0.0, 1.0, 0.0, 1.0 };
	float luzEspecular[] = { 0.0, 1.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa);
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular);
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
}
/*
Esta função é responsável pela construção
da matriz de sombra.
*/
void ConstroiMatrizSombra(float Matriz[16], float PosicaoLuz[4], float Plano[4])
{
	float Ponto;
	// Calcula o ponto prodizido entre o plano e a posição da luz
	Ponto = Plano[0] * PosicaoLuz[0] +
		    Plano[1] * PosicaoLuz[1] +
		    Plano[2] * PosicaoLuz[2] +
		    Plano[3] * PosicaoLuz[3];
	// Primeira Coluna da Matriz
	Matriz[0] = Ponto - PosicaoLuz[0] * Plano[0];
	Matriz[4] = 0.0f - PosicaoLuz[0] * Plano[1];
	Matriz[8] = 0.0f - PosicaoLuz[0] * Plano[2];
	Matriz[12] = 0.0f - PosicaoLuz[0] * Plano[3];
	// Segunda Coluna da Matriz
	Matriz[1] = 0.0f - PosicaoLuz[1] * Plano[0];
	Matriz[5] = Ponto - PosicaoLuz[1] * Plano[1];
	Matriz[9] = 0.0f - PosicaoLuz[1] * Plano[2];
	Matriz[13] = 0.0f - PosicaoLuz[1] * Plano[3];
	// Terceira Coluna da Matriz
	Matriz[2] = 0.0f - PosicaoLuz[2] * Plano[0];
	Matriz[6] = 0.0f - PosicaoLuz[2] * Plano[1];
	Matriz[10] = Ponto - PosicaoLuz[2] * Plano[2];
	Matriz[14] = 0.0f - PosicaoLuz[2] * Plano[3];
	// Quarta Coluna da Matriz
	Matriz[3] = 0.0f - PosicaoLuz[3] * Plano[0];
	Matriz[7] = 0.0f - PosicaoLuz[3] * Plano[1];
	Matriz[11] = 0.0f - PosicaoLuz[3] * Plano[2];
	Matriz[15] = Ponto - PosicaoLuz[3] * Plano[3];
}
/*
Esta função é responsável por encontrar a
equacao do plano com base em tres pontos
*/
void EncontraPlano(GLfloat plano[4], GLfloat v0[3], GLfloat v1[3], GLfloat v2[3])
{
	GLfloat vec0[3], vec1[3];
	// Necessicta de 2 vetores para encontrar a interseção
	vec0[0] = v1[0] - v0[0];
	vec0[1] = v1[1] - v0[1];
	vec0[2] = v1[2] - v0[2];
	vec1[0] = v2[0] - v0[0];
	vec1[1] = v2[1] - v0[1];
	vec1[2] = v2[2] - v0[2];
	// Encontra o produto de interseção para adquirir A, B, e C da equacao do plano
	plano[0] = vec0[1] * vec1[2] - vec0[2] * vec1[1];
	plano[1] = -(vec0[0] * vec1[2] - vec0[2] * vec1[0]);
	plano[2] = vec0[0] * vec1[1] - vec0[1] * vec1[0];
	plano[3] = -(plano[0] * v0[0] + plano[1] * v0[1] + plano[2] * v0[2]);
}
/*
Efetua o desenho da superfície de projeção
da sombra
*/
void Superficie()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glInterleavedArrays(GL_N3F_V3F, 0, g_floorQuad);
	glDrawArrays(GL_QUADS, 0, 4);
}
/*
Função responsável pelo desenho do objeto.
*/
void DesenhaObjeto(void)
{
	switch (objeto) {
	case 1:
		glRotatef(90, 1.0f, 0.0, 0.0);
		glutSolidTorus(0.4, 0.8, 30, 35);
		break;
	case 2:
		glutSolidTeapot(1.0);
		break;
	}
}
/*
Função responsável pelo desenho dos objetos
bem como projeção da sombra.
*/
void display(void)
{
	//
	// Define o plano da superficie planar que terá a sombra projetada.
	//
	GLfloat PlanoSombra[4];
	GLfloat v0[3], v1[3], v2[3];
	// Para definir o plano que contém a superfíces são necessários
	// 3 vértices
	v0[0] = g_floorQuad[0].x;
	v0[1] = g_floorQuad[0].y;
	v0[2] = g_floorQuad[0].z;
	v1[0] = g_floorQuad[1].x;
	v1[1] = g_floorQuad[1].y;
	v1[2] = g_floorQuad[1].z;
	v2[0] = g_floorQuad[2].x;
	v2[1] = g_floorQuad[2].y;
	v2[2] = g_floorQuad[2].z;
	EncontraPlano(PlanoSombra, v0, v1, v2);
	
	//
	// Constroi a matriz de sombra utilizando a posicao da luz corrente e o plano.
	//
	ConstroiMatrizSombra(g_shadowMatrix, g_lightPosition, PlanoSombra);
	//
	//
	//


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f, -2.0f, -15.0f);
	glRotatef(-g_fSpinY_L, 1.0f, 0.0f, 0.0f);
	glRotatef(-g_fSpinX_L, 0.0f, 1.0f, 0.0f);
	//
	// Desenha superfície
	//
	Superficie();



	


	//
	// Cria a sombra para o objeto utilizando a matriz de sombra
	//
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_LIGHTING);
	// Define a cor que a sombra terá
	glColor3f(0.2f, 0.2f, 0.2f);
	glPushMatrix();
	{
		glMultMatrixf((GLfloat *)g_shadowMatrix);
		// Posição e orientação do objeto
		// necessita ter as mesmas transformações
		// utilizadas para a criação do objeto em si
		glTranslatef(0.0f, 2.5f, 0.0f);
		glRotatef(-g_fSpinY_R, 1.0f, 0.0f, 0.0f);
		glRotatef(-g_fSpinX_R, 0.0f, 1.0f, 0.0f);
		switch (objeto) {
		case 1:
			glRotatef(90, 1.0f, 0.0, 0.0);
			glutSolidTorus(0.4, 0.8, 30, 35);
			break;
		case 2:
			glutSolidTeapot(1.0);
			break;
		case 3:
			glRotatef(90, 1.0f, 0.0, 0.0);
			glutWireTorus(0.4, 0.8, 30, 35);
			break;
		case 4:
			glutWireTeapot(1.0);
			break;
		}
	}
	glPopMatrix();
	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);


	//
	// Cria um objeto.
	//
	glEnable(GL_LIGHTING);
	glPushMatrix();
	{
		// Orientação e posição do objeto.
		glTranslatef(0.0f, 2.5f, 0.0f);
		glRotatef(-g_fSpinY_R, 1.0f, 0.0f, 0.0f);
		glRotatef(-g_fSpinX_R, 0.0f, 1.0f, 0.0f);
		glColor3f(1, 0, 0);
		switch (objeto) {
		case 1:
			glRotatef(90, 1.0f, 0.0, 0.0);
			glutSolidTorus(0.4, 0.8, 30, 35);
			break;
		case 2:
			glutSolidTeapot(1.0);
			break;
		case 3:
			glRotatef(90, 1.0f, 0.0, 0.0);
			glutWireTorus(0.4, 0.8, 30, 35);
			break;
		case 4:
			glutWireTeapot(1.0);
			break;
		}
	}
	glPopMatrix();


	//
	// Cria uma pequena esfera na posição da luz.
	//
	glDisable(GL_LIGHTING);
	glPushMatrix();
	{
		glLightfv(GL_LIGHT0, GL_POSITION, g_lightPosition);
		// Esfera representando a luz
		glTranslatef(g_lightPosition[0], g_lightPosition[1], g_lightPosition[2]);
		glColor3f(1.0f, 1.0f, 0.5f);
		glutSolidSphere(0.1, 8, 8);
	}
	glPopMatrix();
	

	glutSwapBuffers();
}
/*
Função responsável pelo desenho da tela
Nesta função são determinados o tipo de Projeção
o modelo de Matrizes e
a posição da câmera
Quando a tela é redimensionada os valores
da visão perspectiva são recalculados com base no novo tamanho da tela
assim como o Viewport
*/
void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (GLfloat)w / (GLfloat)h, 0.1, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
/* Função responsável pelo controle de teclado
quando pressionada a tecla ESC
o programa é terminado.
*/
void keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(1);
		break;
	}
}
/* Função responsável pelo controle das
teclas especiais através do GLUT
as setas mudam o posicionamento da luz na cena
*/
void Special_keyboard(int key, int x, int y)
{
	switch (key) {
	case GLUT_KEY_LEFT:
		g_lightPosition[0] -= 0.1f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		g_lightPosition[1] += 0.1f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_DOWN:
		g_lightPosition[1] -= 0.1f;
		glutPostRedisplay();
		break;
	case GLUT_KEY_RIGHT:
		g_lightPosition[0] += 0.1f;
		glutPostRedisplay();
		break;
	}
}
/*
As duas funcoes que seguem controlam os eventos do mouse
o efeito esperado é a movimentacao de toda a cena e a movimentacao
somente do objeto. Estes efeitos sao obtivos respectivamente atraves
do pressionamento dos botoes esquerdo ou direito e a movimentacao do mouse
na tela.
*/
typedef struct PONTO
{
	int x;
	int y;
} PONTO_T;
static PONTO_T ptLastMousePosit_L;
static PONTO_T ptCurrentMousePosit_L;
static int bMousing_L;
static PONTO_T ptLastMousePosit_R;
static PONTO_T ptCurrentMousePosit_R;
static int bMousing_R;
void mouse(int button, int state, int x, int y)
{
	switch (button) {
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN)
		{
			ptLastMousePosit_L.x = ptCurrentMousePosit_L.x = x;
			ptLastMousePosit_L.y = ptCurrentMousePosit_L.y = y;
			bMousing_L = 1;
		}
		else
			bMousing_L = 0;
		glutPostRedisplay();
		break;
	case GLUT_MIDDLE_BUTTON:
		if (state == GLUT_DOWN)
		{
			objeto = objeto + 1; if (objeto > 4)
				objeto = 1;
			glutPostRedisplay();
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN)
		{
			ptLastMousePosit_R.x = ptCurrentMousePosit_R.x = x;
			ptLastMousePosit_R.y = ptCurrentMousePosit_R.y = y;
			bMousing_R = 1;
		}
		else
			bMousing_R = 0;
		glutPostRedisplay();
		break;
	default:
		break;
	}
}
/*
Obtem a posicao atual da movimentacao do mouse se algum botao esta pressionado.
*/
void motion_mouse(int x, int y)
{
	ptCurrentMousePosit_L.x = x;
	ptCurrentMousePosit_L.y = y;
	ptCurrentMousePosit_R.x = x;
	ptCurrentMousePosit_R.y = y;
	if (bMousing_L)
	{
		g_fSpinX_L -= (ptCurrentMousePosit_L.x - ptLastMousePosit_L.x);
		g_fSpinY_L -= (ptCurrentMousePosit_L.y - ptLastMousePosit_L.y);
	}
	if (bMousing_R)
	{
		g_fSpinX_R -= (ptCurrentMousePosit_R.x - ptLastMousePosit_R.x);
		g_fSpinY_R -= (ptCurrentMousePosit_R.y - ptLastMousePosit_R.y);
	}
	ptLastMousePosit_L.x = ptCurrentMousePosit_L.x;
	ptLastMousePosit_L.y = ptCurrentMousePosit_L.y;
	ptLastMousePosit_R.x = ptCurrentMousePosit_R.x;
	ptLastMousePosit_R.y = ptCurrentMousePosit_R.y;
	glutPostRedisplay();
}
/*
Função principal do programa.
*/
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Exemplo 12 - Sombras Planares");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	/*
	Funcao de Callback que controla o
	pressionamento de teclas especiais
	F1..F12, END, DELETE,SETAS etc..
	*/
	glutSpecialFunc(Special_keyboard);
	glutMouseFunc(mouse);/*
Funcao de Callback que controla
a posição atual do ponteiro do mouse
se algum dos botoes (esquerdo, direito, centro)
esta pressionado.
*/
	glutMotionFunc(motion_mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
