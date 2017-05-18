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
#include "physics.h"
#include "settings.h"
#include "invaders.h"

/* -------------------------------- INPUT ----------------------------------- */
void on_mouseClick(int button, int click_state,
    int x_mouse_position, int y_mouse_position);
void mouseHold();
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keyHold();
/* -------------------------------- INPUT ----------------------------------- */

/* ------------------------------- TEXTURES --------------------------------- */
// HUD
GLuint hudL, hudM, hudR;

// Textures
GLuint background_texture, parallax1_texture, parallax2_texture, player_texture,
alien_1_1, alien_1_2, alien_2_1, alien_2_2,
alien_3_1, alien_3_2, base_texture;

// Load all textures to program
int loadTextures();

/* ------------------------------- TEXTURES --------------------------------- */

/* -------------------------------- AUDIO ----------------------------------- */
extern Mix_Music *music; // BGM needs to be played by main.c
int initAudio();
/* -------------------------------- AUDIO ----------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void reshape(int width, int height);
/* -------------------------------- WINDOW ---------------------------------- */

/* ----------------------------- SCENE DRAWING ------------------------------ */
void drawLoop();
/* ----------------------------- SCENE DRAWING ------------------------------ */

#endif
