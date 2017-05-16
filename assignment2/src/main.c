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

        IF_DEBUG printf("◆ Initializing\n");

        // INITIALIZE GLUT
        glutInit(&argc, argv); // Instanciate Glut
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE); // Defines the buffer display mode
        glEnable(GL_MULTISAMPLE); // Enables antialiasing

        // TEXTURES
        glEnable(GL_BLEND); // Enables color blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // AUDIO
        SDL_Init(SDL_INIT_AUDIO); // Initialize SDL
        IF_DEBUG printf("◆ LOADING AUDIO\n");
        if(!(SDL_LoadWAV("./assets/omen.wav", &wav_spec, &wav_buffer, &wav_length))) {
            IF_DEBUG printf("✗✗✗ ERROR LOADING AUDIO\n");
            return EXIT_FAILURE;
        }
        IF_DEBUG printf("◆ AUDIO LOADED\n");
        // set the callback function
        wav_spec.callback = audioCallback;
        wav_spec.userdata = NULL;
        // set our global static variables
        audio_pos = wav_buffer; // copy sound buffer
        audio_len = wav_length; // copy file length
        // open audio device
        SDL_OpenAudio(&wav_spec, NULL);

        // WINDOW
        glutInitWindowSize(VIEWPORT_X, VIEWPORT_Y); // Defines the size in pixels of the window
        glutCreateWindow("Invaders Must Die XL"); // Defines the window title

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

        // LOAD TEXTURES
        IF_DEBUG printf("◆ LOADING TEXTURES\n");

        hudL = loadTexture("./assets/hudL.png");
        if (!hudL)  {
            printf("✗✗✗ ERROR LOADING TEXTURE\n");
            return EXIT_FAILURE;
        }

        hudM = loadTexture("./assets/hudM.png");
        if (!hudM)  {
            printf("✗✗✗ ERROR LOADING TEXTURE\n");
            return EXIT_FAILURE;
        }

        hudR = loadTexture("./assets/hudR.png");
        if (!hudR)  {
            printf("✗✗✗ ERROR LOADING TEXTURE\n");
            return EXIT_FAILURE;
        }

        background_texture = loadTexture("./assets/bg.png");
        if (!background_texture)  {
            printf("✗✗✗ ERROR LOADING TEXTURE\n");
            return EXIT_FAILURE;
        }

        player_texture = loadTexture("./assets/ship.png");
        if (!player_texture)  {
            printf("✗✗✗ ERROR LOADING TEXTURE\n");
            return EXIT_FAILURE;
        }
        IF_DEBUG printf("◆ SUCCESS LOADING TEXTURES\n");

        // START BG MUSIC
        SDL_PauseAudio(0);

        // START RENDERING
        glutMainLoop(); // Start operations according to the specifications above

        IF_DEBUG printf("◆ Closing window\n");

        // Shutdown SDL
        SDL_CloseAudio();
        SDL_FreeWAV(wav_buffer);

        return 0;
}
