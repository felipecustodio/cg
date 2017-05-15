#include "../includes/scene.h"

/* -------------------------------- INPUT ----------------------------------- */

/* ------ INPUT STATUS -----*/
int leftMouseButtonDown = 0;
int rightMouseButtonDown = 0;

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
        if (key == 'A') {
                //movePlayer(0);
        } else if (key == 'D') {
                //movePlayer(1);
        } else if (key == ' ') {
                // shoot missile
        } else if (key == 'R') {
                // reset game
        }
}

/* -------------------------------- INPUT ----------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void reshape(int width, int height){
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
    //gluPerspective(45, ratio, -1, 1);
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
void drawScene(){
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
        PLAYER* player = createPlayer();

        Quadrilateral *playerSprite = createQuad();
            setQuadCoordinates(playerSprite, -100, -100, -100, 100, 100, 100, 100, -100);
            setQuadTexture(playerSprite, player_texture);
            drawQuadTextured(playerSprite);
        freeQuad(playerSprite);
        /*--------------------END--------------------*/
}

void drawLoop()
{
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glColor3f(1.0f, 1.0f, 1.0f);

        // Repaint screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw scene
        drawScene();

        // Clear buffer
        glutSwapBuffers();
}
/* ----------------------------- SCENE DRAWING ------------------------------ */
