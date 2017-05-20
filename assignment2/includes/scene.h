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
#include "invaders.h"

/* -------------------------------- INPUT ----------------------------------- */
void on_mouseClick(int button, int click_state,
    int x_mouse_position, int y_mouse_position);
void mouseHold();
void keyPress(unsigned char key, int x, int y);
void keyUp(unsigned char key, int x, int y);
void keyHold();
/* -------------------------------- INPUT ----------------------------------- */
void cooldown(int value);

/* ------------------------------- TEXTURES --------------------------------- */
// HUD
GLuint hudL, hudM, hudR, hudShips, hudWave, hudScore;

// Textures
GLuint background_texture, parallax1_texture, parallax2_texture, player_texture,
alien_1_1, alien_1_2, alien_2_1, alien_2_2, alien_3_1, alien_3_2,
expsprite, base_texture, pause, game_over, victory_screen, laserblur,
logo, press_start;

// Load all textures to program
int loadTextures();
/* ------------------------------- TEXTURES --------------------------------- */

/* -------------------------------- AUDIO ----------------------------------- */
extern Mix_Chunk *bg; // BGM starts playing at main
extern Mix_Chunk *blaster; // Enemy blaster played at invaders
int initAudio();
void audioCleanup();
/* -------------------------------- AUDIO ----------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void reshape(int width, int height);
/* -------------------------------- WINDOW ---------------------------------- */

/* ----------------------------- SCENE DRAWING ------------------------------ */
void drawLoop();
void checkCollisions();
void destroyDesallocLaser(int i);
/* ----------------------------- SCENE DRAWING ------------------------------ */

#endif
