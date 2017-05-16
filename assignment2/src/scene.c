#include "../includes/invaders.h"
#include "../includes/scene.h"

/* -------------------------------- GLOBALS ----------------------------------- */

// You, the player!
PLAYER* player;

// Shots fired
LASER** shots;
int ammount = 0;

// User Interface
char* UI_reset = "Press R to reset game";
char* UI_shoot = "Press spacebar to shoot";
char* UI_move = "Press A/D to move left/right";

/* -------------------------------- GLOBALS ----------------------------------- */

/* -------------------------------- INPUT ----------------------------------- */

/* ------ INPUT STATUS -----*/
char leftMouseButtonDown = 0;
char rightMouseButtonDown = 0;
char Adown = 0;
char Ddown = 0;

// MOUSE EVENT HANDLING
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

// MOUSE STATUS
void mouseHold() {
        if (leftMouseButtonDown) {
                // left mouse event
        } else if (rightMouseButtonDown) {
                // right mouse event
        }
}

// KEYBOARD EVENT HANDLING
void keyPress(unsigned char key, int x, int y) {
    IF_DEBUG printf("E\n");
    if (key == 'a' || key == 'A') {
        IF_DEBUG printf("pressdA\n");
        Adown = 1;
    } else if (key == 'd' || key == 'D') {
        IF_DEBUG printf("pressdD\n");
        Ddown = 1;
    } else if (key == ' ') {
        // SHOOT LASER WHEN SPACEBAR PRESSED
        shootLaser(shots, ammount);
    } else if (key == 'R') {
        // reset game
    }
    IF_DEBUG printf("ADOWN: %d\n", Adown);
    IF_DEBUG printf("DDOWN: %d\n", Ddown);
    keyHold();
    Adown = 0;
    Ddown = 0;
}

void keyHold() {
    IF_DEBUG printf("A\n");
    if (Adown) {
        // move/accelerate player left
        IF_DEBUG printf("B\n");
        movePlayer(player, 0);
    } else if (Ddown) {
        // move/accelerate player right
        IF_DEBUG printf("C\n");
        movePlayer(player, 1);
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
        if (player == NULL)
        {
            player = createPlayer();
        }
        glTranslatef(0.0f, -228, 0.0f);
        drawPlayer(player);

        /*--------------------END--------------------*/
}

void drawHUD(){
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

        // Draw HUD
        drawHUD();

        // Clear buffer
        glutSwapBuffers();
}
/* ----------------------------- SCENE DRAWING ------------------------------ */
