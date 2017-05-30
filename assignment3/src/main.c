/**
 * SCC0250 - Computação Gráfica
 * Trabalho 3 - Macintosh Plus
 * Alunos:
 *      Felipe Scrochio Custódio - 9442688
 *      Henrique Loschiavo - 8936972
 *      Lucas Antognoni - 8936951
 *      Gustavo Santiago - 8937416
 **/

#include <GL/glut.h>
#include <SDL/SDL.h>
#include <time.h>

#include "../includes/scene.h"
#include "../includes/settings.h"

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

        // Start BGM on loop
        // Mix_PlayChannel(-1, bg, -1);

        // WINDOW
        glutInitWindowSize(VIEWPORT_X, VIEWPORT_Y); // Defines the size in pixels of the window
        glutInitWindowPosition(5,5); // Defines the initial window position on screen
        glutCreateWindow("コンピューターグラフィックス"); // Defines the window title

        // RENDERING
        glutDisplayFunc(drawLoop); // Set rendering function as "drawLoop()"
        glutReshapeFunc(reshape); // Set reshaping function as "reshape()"
        glutIdleFunc(drawLoop); // Set drawLoop to repeat while no events occur
        glEnable(GL_DEPTH_TEST); // Enable depth buffer by default
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST); // Enable perspective correction
        glShadeModel(GL_SMOOTH); // Enable smooth shading

        // EVENT HANDLING
        glutMouseFunc(onMouseClick); // Handles mouse clicks
        glutPassiveMotionFunc(onMouseMove); // Handles mouse motion
        glutKeyboardFunc(onKeyPress); // Handles keyboard presses
        glutKeyboardUpFunc(onKeyUp); // Handles keyboard releases

        glMatrixMode(GL_PROJECTION); // Load matrix projection mode
        glViewport(0, 0, VIEWPORT_X, VIEWPORT_Y); // Set viewport size

        // LOAD ALL TEXTURES
        loadTextures();

        // LOAD MODELS
        loadModels();

        // SET KEY PRESSES TO NON-REPEAT MODE
        glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);

        // SET SEED FOR RANDOM NUMBERS
        srand(time(NULL));

        // START RENDERING LOOP
        initializeScene(); // Scene and variable initialization
        glutWarpPointer(VIEWPORT_X/2, VIEWPORT_Y/2); // Centralize mouse pointer
        glutSetCursor(GLUT_CURSOR_NONE); // Hide mouse cursor
        glutMainLoop(); // Start operations according to the specifications above

        // SHUTDOWN
        audioCleanup();
        Mix_CloseAudio();
        SDL_CloseAudio();

        return 0;
}
