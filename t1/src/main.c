/**
 * SCC0250 - Computação Gráfica
 * Trabalho 1 - Windmill
 * Alunos:
 *      Felipe Scrochio Custódio - 9442688
 *      Henrique Loschiavo -
 *      Lucas Antognoni -
 *      Gustavo Santiago - 8937416
 **/

#include <GL/glut.h>
#include <math.h>
#include "scene.h"
#include "settings.h"

int main(int argc, char* argv[]) {
    if(CONSOLE == 1) printf("\n * W i n d m i l l * \n");
    if(CONSOLE == 1 && DEBUG == 1) printf(">Initializing window...");

    glutInit(&argc, argv); // Instanciate Glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE); // Defines the buffer display mode
    glEnable(GL_MULTISAMPLE); // Enables antialiasing
    glutInitWindowSize(VIEWPORT_X, VIEWPORT_Y); // Defines the size in pixels of the window
    glutCreateWindow("Windmill"); // Defines the window title

    glutDisplayFunc(drawLoop); // Set rendering function as "drawLoop()"
    glutReshapeFunc(reshape); // Set reshaping function as "reshape()"
	glutIdleFunc(drawLoop); // Set draw to repeat while no events occur

    glutMouseFunc(on_mouseClick); // Handles mouse clicks

    glMatrixMode(GL_PROJECTION); // Load matrix mode
    glViewport(0, 0, VIEWPORT_X, VIEWPORT_Y); // Set viewport size
    gluOrtho2D(-ORTHO_X, ORTHO_X, -ORTHO_Y, ORTHO_Y); // Defines the orthogonal plane to build the scene in

    if(CONSOLE == 1 && DEBUG == 1) printf(">Starting loop...");

    glutMainLoop(); // Start operations according to the specifications above

    if(CONSOLE == 1 && DEBUG == 1) printf(">Closing window...");

    return 0;
}
