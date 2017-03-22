#include <GL/glut.h>

// Funcao callback chamada para fazer o desenho
void desenha() {

        // Colorir o fundo de branco
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        /////////////////////////////////////

        // Iniciar as transforma��es 2D
        glMatrixMode(GL_MODELVIEW); // Inicia-se a matriz de transforma��es da openGL
        glLoadIdentity();
        ///////////////////////////////


        // Especifica a cor preta
        glColor3f(0.0f, 0.0f, 0.0f);

        // Desenha o triangulo
        glBegin(GL_TRIANGLES);
        glVertex2f(30.0f, 30.0f);
        glVertex2f(50.0f, 60.0f);
        glVertex2f(70.0f, 30.0f);
        glEnd();

        glLoadIdentity();

        //Inicia a sequencia de transformacoes
        glTranslatef(100.0f, 0.0f, 0.0f);
        glTranslatef(30.0f, 30.0f, 0.0f);
        glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
        glScalef(2.0f, 2.0f, 0.0f);
        glTranslatef(-30.0f, -30.0f, 0.0f);

        /*
        glTranslatef(50.0f,40.0f,0.0f);
        glRotatef(180.0f,0.0f,0.0f,1.0f);
        glTranslatef(-50.0f,-40.0f,0.0f);
        */


        /*
        glTranslatef(50.0f,40.0f,0.0f);
        glScalef(0.5f,0.5f,0.0f);
        glTranslatef(-50.0f,-40.0f,0.0f);
        */

        // Especifica a cor vermelha
        glColor3f(1.0f, 0.0f, 0.0f);

        // Desenha o mesmo triangulo
        glBegin(GL_TRIANGLES);
        glVertex2f(30.0f, 30.0f);
        glVertex2f(50.0f, 60.0f);
        glVertex2f(70.0f, 30.0f);
        glEnd();

        glFlush();
}


// Programa Principal
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); // Inicia uma inst�ncia da glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Define o modo de display do buffer
	glutInitWindowSize(800, 800); // Define o tamanho em pixels da janela
	glutCreateWindow("Transforma��es 2D em tri�ngulos");
	glutDisplayFunc(desenha); // Estabelece que a fun��o de rendering � a fun��o "desenha(.)"


	glMatrixMode(GL_PROJECTION); // Especifica��es de observa��o de cena
        gluOrtho2D(0, 200, 0, 200);	// Observa-se a se��o de plano [0,200]x[0,200]


	glutMainLoop();
}
