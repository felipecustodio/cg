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
    if(CONSOLE == 1 && DEBUG == 1) printf("> Initializing\n");

    glutInit(&argc, argv); // Instanciate Glut
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE); // Defines the buffer display mode
    glEnable(GL_MULTISAMPLE); // Enables antialiasing

    // TEXTURES
    glEnable(GL_BLEND); // Enables color blending
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_TEXTURE_2D); // Enables 2D texturing

    // WINDOW
    glutInitWindowSize(VIEWPORT_X, VIEWPORT_Y); // Defines the size in pixels of the window
    glutCreateWindow("Windmill"); // Defines the window title

    // RENDERING
    glutDisplayFunc(drawLoop); // Set rendering function as "drawLoop()"
    glutReshapeFunc(reshape); // Set reshaping function as "reshape()"
    glutIdleFunc(drawLoop); // Set draw to repeat while no events occur

    // EVENTS
    glutMouseFunc(on_mouseClick); // Handles mouse clicks
    glutKeyboardFunc(keyPress); // Handles keyboard presses

    glMatrixMode(GL_PROJECTION); // Load matrix mode
    glViewport(0, 0, VIEWPORT_X, VIEWPORT_Y); // Set viewport size
    gluOrtho2D(-ORTHO_X, ORTHO_X, -ORTHO_Y, ORTHO_Y); // Defines the orthogonal plane to build the scene in

    if(CONSOLE == 1 && DEBUG == 1)

    // LOAD TEXTURES
    if(CONSOLE == 1 && DEBUG == 1) printf("◆ LOADING TEXTURES\n");
    background_texture = loadTexture("./assets/background.jpg");
    if (!background_texture)  {
            printf("✗✗✗ ERROR LOADING TEXTURE\n");
            return EXIT_FAILURE;
    }
    if(CONSOLE == 1 && DEBUG == 1) printf("◆ SUCCESS LOADING TEXTURES\n");

    // START RENDERING
    glutMainLoop(); // Start operations according to the specifications above

    if(CONSOLE == 1 && DEBUG == 1) printf("> Closing window\n");

    return 0;
}
