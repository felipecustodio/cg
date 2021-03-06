#ifndef SCENE_H
#define SCENE_H

/*
* Handles scene drawing and animations
*/

#include <GL/glut.h>
#include "../includes/SOIL/SOIL.h"
#include <SDL2/SDL.h>
#include "shapes.h"
#include "transforms.h"
#include "physics.h"
#include "settings.h"

/* -------------------------------- INPUT ----------------------------------- */
void on_mouseClick(int button, int click_state,
    int x_mouse_position, int y_mouse_position);
void mouseHold();
void keyPress(unsigned char key, int x, int y);
/* -------------------------------- INPUT ----------------------------------- */

/* -------------------------------- TEXTURES ---------------------------------- */
GLuint background_texture, cloud_texture, goku_texture;
GLuint loadTexture(const char *filename);
/* -------------------------------- TEXTURES ---------------------------------- */

/* -------------------------------- MUSIC ---------------------------------- */
// CODE INSPIRED BY ARMORNICK (github.com/armornick) GIST
// https://gist.github.com/armornick/3447121
void audioCallback(void *userdata, Uint8 *stream, int len);
// variable declarations
Uint32 wav_length; // length of our sample
Uint8 *wav_buffer; // buffer containing our audio file
SDL_AudioSpec wav_spec; // the specs of our piece of music
Uint8 *audio_pos; // global pointer to the audio buffer to be played
Uint32 audio_len; // remaining length of the sample we have to play
/* -------------------------------- MUSIC ---------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void reshape(int width, int height);
/* -------------------------------- WINDOW ---------------------------------- */

/* ----------------------------- SCENE DRAWING ------------------------------ */
void drawLoop();
/* ----------------------------- SCENE DRAWING ------------------------------ */

#endif
