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
    int x, int y);
void mouseHold();
void onMouseMove(int x, int y);
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
void reshape(GLsizei width, GLsizei height);
/* -------------------------------- WINDOW ---------------------------------- */

/* ----------------------------- SCENE DRAWING ------------------------------ */
void repositionCamera(void);
void updateView(void);

void drawCube(void);

void drawLoop();
/* ----------------------------- SCENE DRAWING ------------------------------ */

#endif
