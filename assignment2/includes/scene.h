#ifndef SCENE_H
#define SCENE_H

/*
* Handles scene drawing and animations
*/

#include <GL/glut.h>
#include <SDL/SDL.h>
#include "shapes.h"
#include "transforms.h"
#include "physics.h"
#include "settings.h"
#include "invaders.h"

/* -------------------------------- INPUT ----------------------------------- */
void on_mouseClick(int button, int click_state,
    int x_mouse_position, int y_mouse_position);
void mouseHold();
void keyPress(unsigned char key, int x, int y);
void keyHold();
/* -------------------------------- INPUT ----------------------------------- */

/* ------------------------------- TEXTURES --------------------------------- */
// Textures
GLuint background_texture, player_texture, enemy_texture;
/* ------------------------------- TEXTURES --------------------------------- */

/* -------------------------------- AUDIO ---------------------------------- */
// CODE INSPIRED BY ARMORNICK (github.com/armornick) GIST
// https://gist.github.com/armornick/3447121
void audioCallback(void *userdata, Uint8 *stream, unsigned int len);
// variable declarations
Uint32 wav_length; // length of our sample
Uint8 *wav_buffer; // buffer containing our audio file
SDL_AudioSpec wav_spec; // the specs of our piece of music
Uint8 *audio_pos; // global pointer to the audio buffer to be played
Uint32 audio_len; // remaining length of the sample we have to play
/* -------------------------------- AUDIO ---------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void reshape(int width, int height);
/* -------------------------------- WINDOW ---------------------------------- */

/* ----------------------------- SCENE DRAWING ------------------------------ */
void drawLoop();
/* ----------------------------- SCENE DRAWING ------------------------------ */

#endif
