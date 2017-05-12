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
                movePlayer(0);
        } else if (key == 'D') {
                movePlayer(1);
        } else if (key == ' ') {
                // shoot missile
        } else if (key == 'R') {
                // reset game
        }
}

/* -------------------------------- INPUT ----------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void reshape(int width, int height)
{
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

/* ----------------------------- TEXTURES ------------------------------ */
GLuint loadTexture(const char *filename)
{
        GLuint tex = SOIL_load_OGL_texture(filename,
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y);
        if (!tex) {
                printf("ERROR ON TEXTURE LOADING\n");
        return 0;
        }

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}
/* ----------------------------- TEXTURES ------------------------------ */

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
void drawScene()
{
        // Load matrix mode
        glMatrixMode(GL_MODELVIEW);

        /*--------------------BACKGROUND--------------------*/
        // Refresh matrix for new object
        glLoadIdentity();

        // Bind texture to quad
        glBindTexture(GL_TEXTURE_2D, background_texture);
        int bgX = VIEWPORT_X;
        int bgY = VIEWPORT_Y;
        // Start texturing
        glEnable(GL_TEXTURE_2D);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);
                glVertex2f(-bgX, -bgY);
            glTexCoord2f(0, 1);
                glVertex2f(-bgX, bgY);
            glTexCoord2f(1, 1);
                glVertex2f(bgX, bgY);
            glTexCoord2f(1, 0);
                glVertex2f(bgX, -bgY);
    	glEnd();
        glDisable(GL_TEXTURE_2D);

        /*--------------------END--------------------*/

        /*--------------------PLAYER--------------------*/
        PLAYER* player = createPlayer();


        // Transparency tests

        glBegin(GL_QUADS);
                glColor3f(1.0f, 1.0f, 1.0f);
                glVertex2f(-100, -100);
                glVertex2f(-100, 100);
                glVertex2f(100, 100);
                glVertex2f(100, -100);
    	glEnd();
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
