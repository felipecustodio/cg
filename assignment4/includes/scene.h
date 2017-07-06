#ifndef SCENE_H
#define SCENE_H

/*
* Handles scene drawing and animations
*/

#define GLEW_STATIC

#include <GL/glew.h>
#include <GL/glut.h>
#include <SDL/SDL.h>
#include "../includes/SDL_mixer/SDL_mixer.h"

#include "glsl.h"
#include "material.h"
#include "obj.h"
#include "shapes.h"
#include "camera.h"
#include "settings.h"

/* -------------------------------- INPUT ----------------------------------- */
void onMouseClick(int button, int click_state,
    int x, int y);
void onMouseDrag();
void onMouseHold();
void onKeyPress(unsigned char key, int x, int y);
void onKeyUp(unsigned char key, int x, int y);
void onMouseMove(int x, int y);
/* -------------------------------- INPUT ----------------------------------- */

/* ------------------------------- TEXTURES --------------------------------- */
// Load all textures to program
int loadTextures();
/* ------------------------------- TEXTURES --------------------------------- */

/* ------------------------------- MODELS --------------------------------- */
int loadModels();
void moveAlex(char key);
void rotateAlex(char key);
/* ------------------------------- MODELS --------------------------------- */

/* -------------------------------- AUDIO ----------------------------------- */
extern Mix_Chunk *bg; // BGM starts playing at main
int initAudio();
void audioCleanup();
/* -------------------------------- AUDIO ----------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void reshape(GLsizei width, GLsizei height);
/* -------------------------------- WINDOW ---------------------------------- */

/* ----------------------------- SCENE DRAWING ------------------------------ */
void updateView(void);
void drawLoop(void);
void initializeScene(void);
/* ----------------------------- SCENE DRAWING ------------------------------ */

#endif
