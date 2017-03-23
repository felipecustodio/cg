// PrimeiroPrograma.c - Isabel H. Manssour
// Um programa OpenGL simples que abre uma janela GLUT
// Este cуdigo estб baseado no Simple.c, exemplo
// disponнvel no livro "OpenGL SuperBible",
// 2nd Edition, de Richard S. e Wright Jr.

#include <GL/glut.h>

// Funзгo callback chamada para fazer o desenho
void Desenha(){
        //Define a cor branca para o fundo
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        //Pinta a tela com a cor de fundo
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_QUADS);
        //Define a cor preta
        glColor3f(0.0f, 0.0f, 0.0f);
        glVertex2f(-45.0f, -15.0f);
        glVertex2f(-45.0f, 15.0f);
        //Define a cor branca
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(-15.0f, 15.0f);
        glVertex2f(-15.0f, -15.0f);
        glEnd();

        glFlush();
}

// Programa Principal
int main(int argc, char* argv[])
{
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
        glutCreateWindow("Primeiro Programa");
        glutDisplayFunc(Desenha);
        gluOrtho2D(-50, -10, -20, 20);



        glutMainLoop();
}
