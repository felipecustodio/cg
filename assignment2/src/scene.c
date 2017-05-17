#include <stdlib.h>
#include "../includes/invaders.h"
#include "../includes/scene.h"

/* -------------------------------- GLOBALS ----------------------------------- */

/* ------ THE PLAYER -----*/
PLAYER* player;
int playerSpeed = 7.0f;
int playerShootSpeed = 10.0f;

/* ------ ENEMIES -----*/
ENEMY** enemies;

/* ------ LASERS -----*/
LASER** shots_player;
LASER** shots_enemy;

int shots_player_count = 0;
int shots_enemy_count = 0;

/* ------ UI -----*/
char* UI_reset = "Press R to reset game";
char* UI_shoot = "Press spacebar to shoot";
char* UI_move = "Press A/D to move left/right";
char* UI_exit = "Press E to exit";

/* ------ INPUT STATUS -----*/
char leftMouseButtonDown = 0;
char rightMouseButtonDown = 0;
char Adown = 0;
char Ddown = 0;

/* -------------------------------- GLOBALS ----------------------------------- */
int loadTextures() {
        // HUD
        hudL = loadTexture("./assets/hudL.png");
        hudM = loadTexture("./assets/hudM.png");
        hudR = loadTexture("./assets/hudR.png");

        // Background
        background_texture = loadTexture("./assets/bg.png");

        // Player sprite
        player_texture = loadTexture("./assets/ship.png");

        // Enemy sprites
        enemy_texture_1_1 = loadTexture("./assets/alien_1_1.png");
        enemy_texture_1_2 = loadTexture("./assets/alien_1_2.png");
        enemy_texture_2_1 = loadTexture("./assets/alien_2_1.png");
        enemy_texture_2_2 = loadTexture("./assets/alien_2_2.png");
        enemy_texture_3_1 = loadTexture("./assets/alien_3_1.png");
        enemy_texture_3_2 = loadTexture("./assets/alien_3_2.png");

        if (!(hudL || hudM || hudR || background_texture
                || player_texture ||enemy_texture_1_1 ||
                enemy_texture_1_2 || enemy_texture_2_1 ||
                enemy_texture_2_2 || enemy_texture_3_1 ||
                enemy_texture_3_2)) {
                printf("✗✗✗ ERROR LOADING TEXTURE\n");
                return EXIT_FAILURE;
        }

        IF_DEBUG printf("◆ SUCCESS LOADING TEXTURES\n");
        return 1;
}

/* -------------------------------- INPUT ----------------------------------- */
// MOUSE EVENT HANDLING

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

// KEYBOARD EVENT HANDLING

// Key presses
void keyPress(unsigned char key, int x, int y) {
        IF_DEBUG printf("E\n");
        if (key == 'a' || key == 'A') {
                Adown = 1;
        } else if (key == 'd' || key == 'D') {
                Ddown = 1;
        } else if (key == ' ') {
                // PEW! PEW!
                if(shots_player == NULL){
                    shots_player = (LASER **) malloc(sizeof(LASER *));
                }
                shootLaser(shots_player, &shots_player_count, player->x[0]);
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
                        player->x[0] -= playerSpeed;
                        player->x[1] -= playerSpeed;
                        player->x[2] -= playerSpeed;
                        player->x[3] -= playerSpeed;
                        IF_DEBUG printf("PLAYER BOUNDARIES: %f %f\n", player->boundary_left, player->boundary_right);
                }
        } else if (Ddown) {
                // check for collision with window
                if((checkBorders(player->boundary_right + playerSpeed))) {
                        // move right
                        player->boundary_right += playerSpeed;
                        player->boundary_left += playerSpeed;
                        player->x[0] += playerSpeed;
                        player->x[1] += playerSpeed;
                        player->x[2] += playerSpeed;
                        player->x[3] += playerSpeed;
                        IF_DEBUG printf("PLAYER BOUNDARIES: %f %f\n", player->boundary_left, player->boundary_right);
                }
        }
}
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

/* -------------------------------- AUDIO ---------------------------------- */
// CODE INSPIRED BY ARMORNICK (github.com/armornick) GIST
// https://gist.github.com/armornick/3447121
void audioCallback(void *userdata, Uint8 *stream, unsigned int len) {
	if (audio_len == 0) {
                IF_DEBUG printf("LOOPING AUDIO\n");
                audio_pos = wav_buffer; // copy sound buffer
                audio_len = wav_length; // copy file length
                return;
        }

	len = ( len > audio_len ? audio_len : len );
	// SDL_memcpy (stream, audio_pos, len);
	// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME); // mix from one buffer into another

        // Move audio
	audio_pos += len;
	audio_len -= len;
}
/* -------------------------------- AUDIO ---------------------------------- */

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
        /*--------------------END--------------------*/

        /*--------------------PLAYER--------------------*/
        if (player == NULL) {
            player = createPlayer();
        }
        drawPlayer(player);

        /*--------------------END--------------------*/

        /*--------------------PLAYER SHOTS--------------------*/
        // Refresh matrix for new object
        glLoadIdentity();

        int i = 0;
        for(i = 0; i < shots_player_count; i++){
            if(shots_player[i]){
                drawLaser(shots_player[i]);
                shots_player[i]->y[0] += playerShootSpeed;
                shots_player[i]->y[1] += playerShootSpeed;
                shots_player[i]->y[2] += playerShootSpeed;
                shots_player[i]->y[3] += playerShootSpeed;
            }
        }
        /*--------------------END--------------------*/
}

void drawHUD() {

    // Refresh matrix for new object
    glLoadIdentity();
    glTranslatef(-(VIEWPORT_X/2) - 112, VIEWPORT_Y/2, 0.0f);

    Quadrilateral *hudL_sprite = createQuad();
        setQuadCoordinates(hudL_sprite, 0, 0, 0, 64, 288, 64, 288, 0);
        setQuadTexture(hudL_sprite , hudL);
        drawQuadTextured(hudL_sprite);
    freeQuad(hudL_sprite);

    // Refresh matrix for new object
    glLoadIdentity();
    glTranslatef(-88, VIEWPORT_Y/2, 0.0f);

    Quadrilateral *hudM_sprite = createQuad();
        setQuadCoordinates(hudM_sprite, 0, 0, 0, 64, 188, 64, 188, 0);
        setQuadTexture(hudM_sprite , hudM);
        drawQuadTextured(hudM_sprite);
    freeQuad(hudM_sprite);

    // Refresh matrix for new object
    glLoadIdentity();
    glTranslatef(VIEWPORT_X/2 - 178, VIEWPORT_Y/2, 0.0f);

    Quadrilateral *hudR_sprite = createQuad();
        setQuadCoordinates(hudR_sprite, 0, 0, 0, 64, 288, 64, 288, 0);
        setQuadTexture(hudR_sprite , hudR);
        drawQuadTextured(hudR_sprite);
    freeQuad(hudR_sprite);
}

void drawLoop() {
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glColor3f(1.0f, 1.0f, 1.0f);

        // Repaint screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
