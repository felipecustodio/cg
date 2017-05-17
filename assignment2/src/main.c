/**
 * SCC0250 - Computação Gráfica
 * Trabalho 2 - Space Invaders
 * Alunos:
 *      Felipe Scrochio Custódio - 9442688
 *      Henrique Loschiavo - 8936972
 *      Lucas Antognoni - 8936951
 *      Gustavo Santiago - 8937416
 **/

#include <GL/glut.h>
#include <SDL/SDL.h>
#include <math.h>

#include "scene.h"
#include "settings.h"
#include "invaders.h"

int main(int argc, char* argv[]) {

        // INITIALIZE GLUT
        glutInit(&argc, argv); // Instanciate Glut
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE); // Defines the buffer display mode
        glEnable(GL_MULTISAMPLE); // Enables antialiasing

        // TEXTURES
        glEnable(GL_BLEND); // Enables color blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // AUDIO
        initAudio(); // load audio files and set callback functions
        // Start BGM
        if(Mix_PlayMusic(music, -1)==-1) {
            printf("Mix_PlayMusic: %s\n", Mix_GetError());
        }

        // WINDOW
        glutInitWindowSize(VIEWPORT_X, VIEWPORT_Y); // Defines the size in pixels of the window
        glutCreateWindow("Invaders Must Die"); // Defines the window title

        // RENDERING
        glutDisplayFunc(drawLoop); // Set rendering function as "drawLoop()"
        glutReshapeFunc(reshape); // Set reshaping function as "reshape()"
        glutIdleFunc(drawLoop); // Set drawLoop to repeat while no events occur

        // EVENT HANDLING
        glutMouseFunc(on_mouseClick); // Handles mouse clicks
        glutKeyboardFunc(keyPress); // Handles keyboard presses
        glutKeyboardUpFunc(keyUp); // Handles keyboard releases

        glMatrixMode(GL_PROJECTION); // Load matrix projection mode
        glViewport(0, 0, VIEWPORT_X, VIEWPORT_Y); // Set viewport size
        gluOrtho2D(-ORTHO_X, ORTHO_X, -ORTHO_Y, ORTHO_Y); // Defines the orthogonal plane

        // LOAD ALL TEXTURES
        loadTextures();

        // SET KEY PRESSES TO NON-REPEAT MODE
        glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

        // START RENDERING
        glutMainLoop(); // Start operations according to the specifications above

        // SHUTDOWN
        audioCleanup();
        Mix_CloseAudio();
        SDL_CloseAudio();

        return 0;
}
