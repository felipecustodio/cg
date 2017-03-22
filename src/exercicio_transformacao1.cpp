#include <GL/glut.h>

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

	// Desenha o triangulo
	glBegin(GL_TRIANGLES);
	glVertex2f(5.0f, 2.0f);
	glVertex2f(11.0f, 2.0f);
	glVertex2f(8.0f, 6.0f);
	glEnd();

	glLoadIdentity();
	//Inicia a sequencia de transformacoes

	glTranslatef(8.0f/3.0f, 4.0f, 0.0f);
	glRotatef(90.0f,0.0f,0.0f,1.0f);

	glTranslatef(-8, (-10.0f / 3.0f), 0.0f);

	// Especifica a cor vermelha
	glColor3f(1.0f, 0.0f, 0.0f);

	// Desenha o triangulo
	glBegin(GL_TRIANGLES);
	glVertex2f(5.0f, 2.0f);
	glVertex2f(11.0f, 2.0f);
	glVertex2f(8.0f, 6.0f);
	glEnd();




	glFlush();
}


// Programa Principal 
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); // Inicia uma instância da glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Define o modo de display do buffer
	glutInitWindowSize(800, 800); // Define o tamanho em pixels da janela
	glutCreateWindow("Transformações 2D em triângulos");
	glutDisplayFunc(desenha); // Estabelece que a função de rendering é a função "desenha(.)"


	glMatrixMode(GL_PROJECTION); // Especificações de observação de cena
	gluOrtho2D(0, 20, 0, 20);	// Observa-se a seção de plano [0,200]x[0,200]


	glutMainLoop();
}

