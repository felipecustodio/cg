#include <stdlib.h>
#include "../includes/invaders.h"
#include "../includes/scene.h"

/* ------------------------------- GLOBALS ---------------------------------- */
/* ------ THE PLAYER -----*/
PLAYER* player;

/* ------ ENEMIES -----*/
ENEMY** enemies;

/* ------ LASERS -----*/

// Lasers that exist
LASER** shots_player;
LASER** shots_enemy;

// Amount of lasers on screen
int shots_player_count = 0;
int shots_enemy_count = 0;

/* ------ UI -----*/
const char* UI_reset = "Press R to reset game";
const char* UI_shoot = "Press spacebar to shoot";
const char* UI_move = "Press A/D to move left/right";
const char* UI_exit = "Press E to exit";
int wave = 1;

/* ------ INPUT STATUS -----*/
char leftMouseButtonDown = 0;
char rightMouseButtonDown = 0;
char Adown = 0;
char Ddown = 0;
/* ------------------------------- GLOBALS ---------------------------------- */

int loadTextures() {
        // HUD
        hudL = loadTexture("./assets/hudL.png");
        hudM = loadTexture("./assets/hudM.png");
        hudR = loadTexture("./assets/hudR.png");

        // Background
        background_texture = loadTexture("./assets/bg.png");

        // Parallax
        parallax1_texture = loadTexture("./assets/parallax1.png");
        parallax2_texture = loadTexture("./assets/parallax2.png");

        // Player sprite
        player_texture = loadTexture("./assets/ship.png");

        // Enemy sprites
        alien_1_1 = loadTexture("./assets/alien_1_1.png");
        alien_1_2 = loadTexture("./assets/alien_1_2.png");
        alien_2_1 = loadTexture("./assets/alien_2_1.png");
        alien_2_2 = loadTexture("./assets/alien_2_2.png");
        alien_3_1 = loadTexture("./assets/alien_3_1.png");
        alien_3_2 = loadTexture("./assets/alien_3_2.png");

        if (!(hudL || hudM || hudR || background_texture
                || player_texture ||alien_1_1 ||
                alien_1_2 || alien_2_1 ||
                alien_2_2 || alien_3_1 ||
                alien_3_2)) {
                return EXIT_FAILURE;
        }

        return 1;
}
/* -------------------------------- INPUT ----------------------------------- */

// ------------ MOUSE EVENT HANDLING ------------ //
// Mouse clicks
void on_mouseClick(int button, int click_state,
        int x_mouse_position, int y_mouse_position)
{
        // Get current mouse status
	if (button == GLUT_RIGHT_BUTTON) {
            rightMouseButtonDown = (click_state == GLUT_DOWN);
    } else if (button == GLUT_LEFT_BUTTON) {
            leftMouseButtonDown = (click_state == GLUT_DOWN);
	}
	glutPostRedisplay(); // Forces scene redraw
}

// Mouse status
void mouseHold() {
        if (leftMouseButtonDown) {
                // left mouse event
        } else if (rightMouseButtonDown) {
                // right mouse event
        }
}
// ------------ MOUSE EVENT HANDLING ------------ //

// ----------- KEYBOARD EVENT HANDLING ---------- //
// Key presses
void keyPress(unsigned char key, int x, int y) {
        IF_DEBUG printf("E\n");
        if (key == 'a' || key == 'A') {
                Adown = 1;
        } else if (key == 'd' || key == 'D') {
                Ddown = 1;
        } else if (key == ' ') {
                // PEW! PEW!
                if(shots_player == NULL) {
                    shots_player = (LASER **) malloc(sizeof(LASER *));
                }
                else{
                    shots_player = (LASER **) realloc(shots_player, sizeof(LASER *) * (shots_player_count + 1));
                }
                shootLaser(shots_player, &shots_player_count, playerPosition);
        } else if (key == 'r' || key == 'R') {
                // reset game
        } else if (key == 'e' || key == 'E') {
                exit(0);
        }
}

// Key releases
void keyUp(unsigned char key, int x, int y) {
        if (key == 'a' || key == 'A') {
                Adown = 0;
        } else if (key == 'd' || key == 'D') {
                Ddown = 0;
        }
}

// Key holding
void keyHold() {
        // A - Move left
        // D - Move right
        if (Adown) {
                // check for collision with window
                if((checkBorders(player->boundary_left - playerSpeed))) {
                        // move left
                        player->boundary_left -= playerSpeed;
                        player->boundary_right -= playerSpeed;
                        playerPosition -= playerSpeed;
                }
        } else if (Ddown) {
                // check for collision with window
                if((checkBorders(player->boundary_right + playerSpeed))) {
                        // move right
                        player->boundary_right += playerSpeed;
                        player->boundary_left += playerSpeed;
                        playerPosition += playerSpeed;
                }
        }
}
// ----------- KEYBOARD EVENT HANDLING ---------- //
/* -------------------------------- INPUT ----------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void reshape(int width, int height) {
    // Screen can't be smaller than 0
    if(height == 0)
        height = 1;

    float ratio = width * 1.0/height;

    // Changes matrix mode to projection
    glMatrixMode(GL_PROJECTION);

    // Reset Matrix
    glLoadIdentity();

    // Viewport correction
    glViewport(0, 0, width, height);

    // Perspective and projection correction
    gluOrtho2D(-ORTHO_X * ratio, ORTHO_X * ratio, -ORTHO_Y, ORTHO_Y);

    // Switches matrix mode back to modelview
    glMatrixMode(GL_MODELVIEW);
}
/* -------------------------------- WINDOW ---------------------------------- */


/* -------------------------------- AUDIO ----------------------------------- */
int initAudio() {
        SDL_Init(SDL_INIT_AUDIO); // Initialize SDL
        IF_DEBUG printf("◆ LOADING AUDIO\n");
        if(!(SDL_LoadWAV("./assets/resonance.wav", &wav_spec, &wav_buffer, &wav_length))) {
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
        return 1;
}

// Audio callback
void audioCallback(void *userdata, Uint8 *stream, unsigned int len) {
	if (audio_len == 0) {
                IF_DEBUG printf("LOOPING AUDIO\n");
                audio_pos = wav_buffer; // copy sound buffer
                audio_len = wav_length; // copy file length
                return;
        }

	len = ( len > audio_len ? audio_len : len );
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME); // mix from one buffer into another

        // Move audio
	audio_pos += len;
	audio_len -= len;
}
/* -------------------------------- AUDIO ----------------------------------- */

/* ----------------------------- SCENE DRAWING ------------------------------ */
void drawScene() {
        // Load matrix mode
        glMatrixMode(GL_MODELVIEW);

        /*--------------------BACKGROUND--------------------*/
        // Refresh matrix for new object
        glLoadIdentity();

        Quadrilateral *bgSprite = createQuad();
            setQuadCoordinates(bgSprite, -VIEWPORT_X, -VIEWPORT_Y,
                                -VIEWPORT_X, VIEWPORT_Y,
                                VIEWPORT_X, VIEWPORT_Y,
                                VIEWPORT_X, -VIEWPORT_Y);
            setQuadTexture(bgSprite, background_texture);
            drawQuadTextured(bgSprite);
        freeQuad(bgSprite);

        // Refresh matrix for new object
        glLoadIdentity();

        int parallaxfactor = playerPosition / 12;

        glTranslatef(parallaxfactor, 0.0f, 0.0f);

        Quadrilateral *parallax1Sprite = createQuad();
            setQuadCoordinates(parallax1Sprite, -VIEWPORT_X - 100, -VIEWPORT_Y - 100,
                                -VIEWPORT_X - 100, VIEWPORT_Y + 100,
                                VIEWPORT_X + 100, VIEWPORT_Y + 100,
                                VIEWPORT_X + 100, -VIEWPORT_Y - 100);
            setQuadTexture(parallax1Sprite, parallax1_texture);
            drawQuadTextured(parallax1Sprite);
        freeQuad(parallax1Sprite);

        // Refresh matrix for new object
        glLoadIdentity();

        parallaxfactor = playerPosition / 6;

        glTranslatef(parallaxfactor, 0.0f, 0.0f);

        Quadrilateral *parallax2Sprite = createQuad();
            setQuadCoordinates(parallax2Sprite, -VIEWPORT_X - 200, -VIEWPORT_Y - 200,
                                -VIEWPORT_X - 200, VIEWPORT_Y + 200,
                                VIEWPORT_X + 200, VIEWPORT_Y + 200,
                                VIEWPORT_X + 200, -VIEWPORT_Y - 200);
            setQuadTexture(parallax2Sprite, parallax2_texture);
            drawQuadTextured(parallax2Sprite);
        freeQuad(parallax2Sprite);
        /*--------------------END--------------------*/

        // matrix for player
        glLoadIdentity();

        /*--------------------PLAYER--------------------*/
        if (player == NULL) {
            player = createPlayer();
        }
        drawPlayer(player);

        /*--------------------END--------------------*/

        /*--------------------PLAYER SHOTS--------------------*/
        // Refresh matrix for new object
        glLoadIdentity();

        // LASER MATRIX CHECKING

        // Laser screen collision check
        int i = 0, j = 0;
        for(i = 0; i < shots_player_count; i++) {
            // Check Top boundary
            // 340
            if(shots_player[i]->position - 200 >= 340){
                destroyLaser(shots_player[i]);
                for(j = i + 1; j < shots_player_count; j++) {
                    shots_player[j - 1] = shots_player[j];
                }
                shots_player_count = shots_player_count - 1;
                shots_player = (LASER **) realloc(shots_player, sizeof(LASER *) * shots_player_count);
            }
        }

        // Laser Movement
        i = 0;
        for(i = 0; i < shots_player_count; i++) {
            if (shots_player[i]) {
                drawLaser(shots_player[i]);
                shots_player[i]->position += laserSpeed;
            }
        }
        /*--------------------END--------------------*/
}

void drawHUD() {
    // -------------- LEFT FRAME -------------- //
    // Refresh matrix for new object
    glLoadIdentity();
    glTranslatef(-(VIEWPORT_X/2) - 112, VIEWPORT_Y/2, 0.0f);

    Quadrilateral *hudL_sprite = createQuad();
        setQuadCoordinates(hudL_sprite, 0, 0, 0, 64, 288, 64, 288, 0);
        setQuadTexture(hudL_sprite , hudL);
        drawQuadTextured(hudL_sprite);
    freeQuad(hudL_sprite);

    char const* hudL_text = "SHIPS";
    Text* hudL = createText(GLUT_BITMAP_9_BY_15, hudL_text);
        drawText(hudL, 10, 20);
    freeText(hudL);

    char hudL_cnt_text[2];
    sprintf(hudL_cnt_text, "%d", player->health);
    Text* hudL_cnt = createText(GLUT_BITMAP_HELVETICA_18, hudL_cnt_text);
        drawText(hudL_cnt, 190, 20);
    freeText(hudL_cnt);
    // -------------- LEFT FRAME -------------- //

    // -------------- MID FRAME -------------- //
    // Refresh matrix for new object
    glLoadIdentity();
    glTranslatef(-88, VIEWPORT_Y/2, 0.0f);

    Quadrilateral *hudM_sprite = createQuad();
        setQuadCoordinates(hudM_sprite, 0, 0, 0, 64, 188, 64, 188, 0);
        setQuadTexture(hudM_sprite , hudM);
        drawQuadTextured(hudM_sprite);
    freeQuad(hudM_sprite);

    char const* hudM_text = "WAVE";
    Text* hudM = createText(GLUT_BITMAP_9_BY_15, hudM_text);
        drawText(hudM, VIEWPORT_X/4 - 130, 45);
    freeText(hudM);

    char hudM_cnt_text[2];
    sprintf(hudM_cnt_text, "%d", wave);
    Text* hudM_cnt = createText(GLUT_BITMAP_HELVETICA_18, hudM_cnt_text);
        drawText(hudM_cnt, VIEWPORT_X/4 - 115, 20);
    freeText(hudM_cnt);
    // -------------- MID FRAME -------------- //

    // -------------- RIGHT FRAME -------------- //
    // Refresh matrix for new object
    glLoadIdentity();
    glTranslatef(VIEWPORT_X/2 - 178, VIEWPORT_Y/2, 0.0f);

    Quadrilateral *hudR_sprite = createQuad();
        setQuadCoordinates(hudR_sprite, 0, 0, 0, 64, 288, 64, 288, 0);
        setQuadTexture(hudR_sprite , hudR);
        drawQuadTextured(hudR_sprite);
    freeQuad(hudR_sprite);

    char const* hudR_text = "SCORE";
    Text* hudR = createText(GLUT_BITMAP_9_BY_15, hudR_text);
        drawText(hudR, VIEWPORT_X/2 - 188, 20);
    freeText(hudR);

    char hudR_cnt_text[2];
    sprintf(hudR_cnt_text, "%d", player->score);
    Text* hudR_cnt = createText(GLUT_BITMAP_HELVETICA_18, hudR_cnt_text);
        drawText(hudR_cnt, VIEWPORT_X/2 - 317, 20);
    freeText(hudR_cnt);
    // -------------- RIGHT FRAME -------------- //
}

void drawLoop() {
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glColor3f(1.0f, 1.0f, 1.0f);

        // Repaint screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Check collisions

        // Draw scene
        drawScene();

        glColor3f(1.0f, 1.0f, 1.0f);

        // Draw HUD
        drawHUD();

        // Check for key presses
        keyHold();

        // Clear buffer
        glutSwapBuffers();
}
/* ----------------------------- SCENE DRAWING ------------------------------ */
