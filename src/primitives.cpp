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

  //Define a cor preta
  glColor3f(0.0f, 0.0f, 0.0f);

  //Desenha uma linha
  glBegin(GL_LINES);
     glVertex2f(10.0f, -10.0f);
     glVertex2f(10.0f, 10.0f);
  glEnd();

  glTranslatef(50,-5,0);
  glRotatef(45,0,0,1);
  glTranslatef(-50,5,0);  //Desenha um triangulo
  glBegin(GL_TRIANGLES);
     glVertex2f(30.0f, -10.0f);
     glVertex2f(50.0f, 10.0f);
     glVertex2f(70.0f, -10.0f);
  glEnd();

  //Desenha um retangulo
  glBegin(GL_QUADS);
      glVertex2f(90.0f, -10.0f);
      glVertex2f(90.0f, 10.0f);
      glVertex2f(130.0f, 10.0f);
      glVertex2f(130.0f, -10.0f);
  glEnd();

  glFlush();
}

// Programa Principal
int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1000, 200);
    glutCreateWindow("Primeiro Programa");
    //Define a janela de selecao: esquerda, direita, baixo, cima
    gluOrtho2D(0, 400, 20, -20);

    glutDisplayFunc(Desenha);




    glutMainLoop();
}
