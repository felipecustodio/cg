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
#include <SDL2/SDL.h>
#include <math.h>
#include "scene.h"
#include "settings.h"

int main(int argc, char* argv[]) {

        if(CONSOLE == 1) printf("\n * W i n d m i l l * \n");
        IF_DEBUG printf("◆ Initializing\n");

        // INIT GLUT
        glutInit(&argc, argv); // Instanciate Glut
        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE); // Defines the buffer display mode
        glEnable(GL_MULTISAMPLE); // Enables antialiasing

        // TEXTURES
        glEnable(GL_BLEND); // Enables color blending
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glEnable(GL_TEXTURE_2D); // Enables 2D texturing

        // AUDIO
        SDL_Init(SDL_INIT_AUDIO); // Initialize SDL
        static Uint32 wav_length; // length of our sample
        static Uint8 *wav_buffer; // buffer containing our audio file
        static SDL_AudioSpec wav_spec; // the specs of our piece of music
        IF_DEBUG printf("◆ LOADING AUDIO\n");
        if(!(SDL_LoadWAV("./assets/stars.wav", &wav_spec, &wav_buffer, &wav_length))) {
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

        // TODO: play audio during rotation
        SDL_PauseAudio(0);

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

        // LOAD TEXTURES
        IF_DEBUG printf("◆ LOADING TEXTURES\n");
        background_texture = loadTexture("./assets/bgmaterial.png");
        if (!background_texture)  {
            printf("✗✗✗ ERROR LOADING TEXTURE\n");
            return EXIT_FAILURE;
        }
        IF_DEBUG printf("◆ SUCCESS LOADING TEXTURES\n");

        // START RENDERING
        glutMainLoop(); // Start operations according to the specifications above

        IF_DEBUG printf("◆ Closing window\n");

        // Shutdown SDL
        SDL_CloseAudio();
	SDL_FreeWAV(wav_buffer);

        return 0;
}
