//******************************************************************************
//
// Aula de Computação Gráfica ICMC - USP (29/09/2016)
//
// Programa a ser concluído em aula.
//
// Objetivo: Desenhar um jatinho (como o do jogo "Space Invader") controlável 
//via teclado. Sendo que o mesmo possua dois mísseis disparáveis.
//
// Rodrigo C. Contreras
// 
//******************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>

// Declaração de variáveis globais
GLfloat missel1_y = 0, missel2_y = 0;
GLfloat aviao_x = 0, missel1_tx = 0, missel2_tx = 0;

bool missel1_moving = false, missel2_moving = false;

int msec_missel1 = 0, msec_missel2 = 0;


void move_missel1(int passo){
	
	missel1_y += (1.0*passo)/100;
	glutPostRedisplay();
	
	glutTimerFunc(10, move_missel1, passo);
}
void move_missel2(int passo){
	
	missel2_y += (1.0*passo)/100;
	glutPostRedisplay();
	
	glutTimerFunc(10, move_missel2, passo);
}

// Função para desenhar a base do objeto           
void DesenhaAviao(){
	
	glColor3f(1.0f,0.0f,1.0f);
	glLineWidth(2);
	glBegin(GL_TRIANGLES);
		glVertex2f(-1.0f,-1.0f);
		glVertex2f(1.0f,-1.0f);
		glVertex2f(0.0f,0.0f);		
	glEnd();
	
	glBegin(GL_QUADS);
		glVertex2f(0.2f,-0.2f);
		glVertex2f(0.2f,0.5f);
		glVertex2f(-0.2f,0.5f);
		glVertex2f(-0.2f,-0.2f);
	glEnd();
}

void DesenhaMisseis(){
	
	glColor3f(1.0f,0.0f,0.0f);
	glLineWidth(2);
	glBegin(GL_POLYGON);
		glVertex2f(-1.0f,-1.0f);
		glVertex2f(-1.0f,-0.7f);
		glVertex2f(-0.9f,-0.6f);
		glVertex2f(-0.8f,-0.7f);
		glVertex2f(-0.8f,-1.0f);
	glEnd();
}
           
// Função callback de redesenho da janela de visualização
void Desenha(void)
{	
	// Muda para o sistema de coordenadas do modelo
	glMatrixMode(GL_MODELVIEW);
	// Inicializa a matriz de transformação corrente
	glLoadIdentity();
     
	// Limpa a janela de visualização com a cor  
	// de fundo definida previamente
	glClear(GL_COLOR_BUFFER_BIT);
	
	
	
	
	
	
	glTranslatef(aviao_x,0.0f,0.0f);
	glTranslatef(0.0f,-0.7f,0.0f);	
	glScalef(0.3f,0.3f,0.0f);
	glPushMatrix(); 
	
	if(missel2_moving){			
		glTranslatef(-aviao_x,0.0f,0.0f);	
		glTranslatef(missel2_tx,0.0f,0.0f);
	}
	
	//Míssel 2;
	glTranslatef(0.0f,missel2_y,0.0f);	
	glTranslatef(1.8f,0.0f,0.0f);
	DesenhaMisseis();
	
	glPopMatrix(); // Carrega a identidade = Limpa a matrix de transformações.
	glPushMatrix();
	
	if(missel1_moving){
		glTranslatef(-aviao_x,0.0f,0.0f);	
		glTranslatef(missel1_tx,0.0f,0.0f);
	}
	//Míssel 1.
	glTranslatef(0.0f,missel1_y,0.0f);
	DesenhaMisseis();
	
	glPopMatrix(); //Pro jatinho nao sair junto com o missel 1.
	// Desenha o jatinho.
	DesenhaAviao();
	
	
	
	
	
	
	// Executa os comandos OpenGL 
	glFlush();
}

// Função callback chamada quando o tamanho da janela é alterado 
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
	GLsizei largura, altura;
                   
	// Evita a divisao por zero
	if(h == 0) h = 1;

	// Atualiza as variáveis
	largura = w;
	altura = h;
                                              
	// Especifica as dimensões da Viewport
	glViewport(0, 0, largura, altura);

	// Inicializa o sistema de coordenadas
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Estabelece a janela de seleção (esquerda, direita, inferior, 
	// superior) mantendo a proporção com a janela de visualização
	if (largura <= altura) 
	{ 
		gluOrtho2D (-1.0f, 1.0f, -1.0f*altura/largura, 1.0f*altura/largura);
		//win = 1.0f;
	}              
	else 
	{ 
		gluOrtho2D (-1.0f*largura/altura, 1.0f*largura/altura, -1.0f, 1.0f);
	//	win = 1.0f*largura/altura;           
	}             
}

// Função callback chamada para gerenciar eventos de teclas especiais(F1,PgDn,...)
void TeclasEspeciais(int key, int x, int y)
{
	// Move a base
	if(key == GLUT_KEY_LEFT)
	{
		aviao_x-=0.05;
		if ( aviao_x < -1.5f )
			aviao_x = -1.5f; 
	}
	if(key == GLUT_KEY_RIGHT)
	{
		aviao_x+=0.05;
		if ( aviao_x > 1.5f )
			aviao_x = 1.5f; 
	}
	if(key == GLUT_KEY_UP){
		missel1_moving = true;
		missel1_tx = aviao_x;
		glutTimerFunc(10, move_missel1, 1);
	}     
	if(key == GLUT_KEY_DOWN){
		missel2_moving = true;
		missel2_tx = aviao_x;
		glutTimerFunc(10, move_missel2, 1);
	}
    
                                                
	glutPostRedisplay();
}

// Função callback chamada para gerenciar eventos de teclas
void Teclado(unsigned char key, int x, int y)
{
	if (key == 27)
		exit(0);
}
           
// Função responsável por inicializar parâmetros e variáveis
void Inicializa (void)
{   
	// Define a cor de fundo da janela de visualização como branca
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	gluOrtho2D (-1.0f, 1.0f, -1.0f, 1.0f);
	glViewport(0, 0, 500, 500);   
}



// Programa Principal 
int main(int argc, char* argv[])
{
	glutInit(&argc, argv); // Inicia uma instância da glut
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  
	glutInitWindowPosition(5,5);     
	glutInitWindowSize(500,500);  
	glutCreateWindow("Desenho de um protótipo de jatinho do Space Invaders!"); 
 
	// Registra a função callback de redesenho da janela de visualização
	glutDisplayFunc(Desenha);  
	
	// Registra a função callback de redimensionamento da janela de visualização
	glutReshapeFunc(AlteraTamanhoJanela);    

	// Registra a função callback para tratamento das teclas especiais
	glutSpecialFunc(TeclasEspeciais);

	// Registra a função callback para tratamento das teclas ASCII
	glutKeyboardFunc (Teclado);

	// Chama a função responsável por fazer as inicializações 
	Inicializa(); 
	
	glutTimerFunc(0, move_missel1, 0); // Timer para mover o missel 1
	glutTimerFunc(0, move_missel2, 0); // ..........................2
 
	// Inicia o processamento e aguarda interações do usuário
	glutMainLoop();

	return 0;
}
