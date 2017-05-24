#ifndef SCENE_H
#define SCENE_H

/*
* Handles scene drawing and animations
*/

#include <GL/glut.h>
#include <SDL/SDL.h>
#include "../includes/SDL_mixer/SDL_mixer.h"

#include "shapes.h"
#include "transforms.h"
#include "settings.h"

/* -------------------------------- INPUT ----------------------------------- */
void on_mouseClick(int button, int click_state,
    int x_mouse_position, int y_mouse_position);
void mouseHold();
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keyHold();
/* -------------------------------- INPUT ----------------------------------- */

/* ------------------------------- TEXTURES --------------------------------- */
// Textures
// GLuint texture;

// Load all textures to program
int loadTextures();
/* ------------------------------- TEXTURES --------------------------------- */

/* -------------------------------- AUDIO ----------------------------------- */
extern Mix_Chunk *bg; // BGM starts playing at main
int initAudio();
void audioCleanup();
/* -------------------------------- AUDIO ----------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void reshape(int width, int height);
/* -------------------------------- WINDOW ---------------------------------- */

/* ----------------------------- SCENE DRAWING ------------------------------ */
void drawLoop();
/* ----------------------------- SCENE DRAWING ------------------------------ */

#endif
