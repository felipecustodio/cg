#include "../includes/scene.h"

/* -------------------------------- INPUT ----------------------------------- */

/* ------ INPUT STATUS -----*/
int leftMouseButtonDown = 0;
int rightMouseButtonDown = 0;

void on_mouseClick(int button, int click_state,
        int x_mouse_position, int y_mouse_position)
{
	if (button == GLUT_RIGHT_BUTTON) {
        if (CONSOLE == 1 && DEBUG == 1) printf(">[INPUT]: Right Mouse Button\n");
            rightMouseButtonDown = (click_state == GLUT_DOWN);
            SDL_PauseAudio(0);
            // audioOn = 1;

    } else if (button == GLUT_LEFT_BUTTON) {
        if (CONSOLE == 1 && DEBUG == 1) printf(">[INPUT]: Left Mouse Button\n");
            leftMouseButtonDown = (click_state == GLUT_DOWN);
            SDL_PauseAudio(0);
            // audioOn = 1;
	}
	glutPostRedisplay(); // Forces scene redraw
}

void mouseHold() {
        if (leftMouseButtonDown) {
                accelerateLeft();
        } else if (rightMouseButtonDown) {
                accelerateRight();
        } else {
                SDL_PauseAudio(1);
        }
}

void keyPress(unsigned char key, int x, int y) {
        if (key == '+') {
                airResistance(1);
        } else if (key == '-') {
                airResistance(0);
        } else {
                printf("RECEIVED %c INPUT\n", key);
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
        //glBindTexture(GL_TEXTURE_2D, tex);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        //glBindTexture(GL_TEXTURE_2D, 0);

	return tex;
}
/* ----------------------------- TEXTURES ------------------------------ */

/* -------------------------------- MUSIC ---------------------------------- */
// CODE INSPIRED BY ARMORNICK (github.com/armornick) GIST
// https://gist.github.com/armornick/3447121
void audioCallback(void *userdata, Uint8 *stream, int len) {

	if (audio_len == 0) {
                return;
        }

	len = ( len > audio_len ? audio_len : len );
	// SDL_memcpy (stream, audio_pos, len);
	// simply copy from one buffer into the other
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}
/* -------------------------------- MUSIC ---------------------------------- */

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

        /*--------------------WINDMILL--------------------*/

        // Refresh matrix for new object
        glLoadIdentity();
        Triangle *roof = createTriangle();
                setTriangleCoordinates(roof, -70.0f, 50.0f, 70.0f,50.0f, 0.0f,100.0f);
                setTriangleColor(roof, 1.0f, 0.8f, 0.5f);
                drawTriangleFilled(roof);
        freeTriangle(roof);

        // Refresh matrix for new object
        glLoadIdentity();
        Quadrilateral *building = createQuad();
                setQuadCoordinates(building, -50.0f, 50.0f, 50.0f, 50.0f, 100.0f, -250.0f, -100.0f, -250.0f);
                setQuadColor(building, 0.93f, 0.92f, 0.91f);
                drawQuadFilled(building);
        freeQuad(building);

        // Refresh matrix for new object
        glLoadIdentity();
        Quadrilateral *door = createQuad();
                setQuadCoordinates(door, -25.0f, -180.0f, 25.0f, -180.0f, 25.0f, -250.0f, -25.0f, -250.0f);
                setQuadColor(door, 0.55f, 0.43f, 0.38f);
                drawQuadFilled(door);
        freeQuad(door);

        /*--------------------END--------------------*/

        /*--------------------PADS--------------------*/

        // Refresh matrix for new object
        glLoadIdentity();
        Triangle *pad1 = createTriangle();
                setTriangleCoordinates(pad1, 0.0f, 0.0f, 100.0f, 200.0f, 0.0f, 100.0f);
                setTriangleColor(pad1, 1.0f, 0.87f, 0.51f);
                setTriangleThickness(pad1, 5.0f);
                rotateTriangleVertex(pad1, getCurAngle(), 1);
                drawTriangleFilled(pad1);
        freeTriangle(pad1);

        // Refresh matrix for new object
        glLoadIdentity();
        Triangle *pad2 = createTriangle();
                setTriangleCoordinates(pad2, 0.0f, 0.0f, 200.0f, -100.0f, 100.0f, 0.0f);
                setTriangleColor(pad2, 1.0f, 0.83f, 0.31f);
                setTriangleThickness(pad2, 5.0f);
                rotateTriangleVertex(pad2, getCurAngle(), 1);
                drawTriangleFilled(pad2);
        freeTriangle(pad2);

        // Refresh matrix for new object
        glLoadIdentity();
        Triangle *pad3 = createTriangle();
                setTriangleCoordinates(pad3, 0.0f, 0.0f, -100.0f, -200.0f, 0.0f, -100.0f);
                setTriangleColor(pad3, 1.0f, 0.79f, 0.15f);
                setTriangleThickness(pad3, 5.0f);
                rotateTriangleVertex(pad3, getCurAngle(), 1);
                drawTriangleFilled(pad3);
        freeTriangle(pad3);

        // Refresh matrix for new object
        glLoadIdentity();
        Triangle *pad4 = createTriangle();
                setTriangleCoordinates(pad4, 0.0f, 0.0f, -200.0f, 100.0f, -100.0f, 0.0f);
                setTriangleColor(pad4, 1.0f, 0.70f, 0.0f);
                setTriangleThickness(pad4, 5.0f);
                rotateTriangleVertex(pad4, getCurAngle(), 1);
                drawTriangleFilled(pad4);
        freeTriangle(pad4);

        /*--------------------END--------------------*/

        /*--------------------POLE--------------------*/
        // Refresh matrix for new object
        glLoadIdentity();

        // Joint of windmill pole
        Quadrilateral *pole = createQuad();
                setQuadColor(pole, 0.98f, 0.55f, 0.0f);
                setQuadCoordinates(pole, -10.0f, 10.0f, 10.0f, 10.0f, 10.0f, -10.0f, -10.0f, -10.0f);
                rotateQuadCenter(pole, getCurAngle());
                drawQuadFilled(pole);
        freeQuad(pole);
        /*--------------------END--------------------*/

        /*--------------------TEXT--------------------*/
        // Refresh matrix for new object
        glLoadIdentity();

        glColor3f(1.0f, 1.0f, 1.0f);
        char const* text = "- Diminui resistencia do ar";
        Text* UI = createText(GLUT_BITMAP_9_BY_15, text);
        drawText(UI, -450, 200);
        freeText(UI);

        char const* text2 = "+ Aumenta resistencia do ar";
        Text* UI2 = createText(GLUT_BITMAP_9_BY_15, text2);
        drawText(UI2, -450, 220);
        freeText(UI2);

        char const* text3 = "Trabalho 01 - Windmill";
        Text* UI3 = createText(GLUT_BITMAP_9_BY_15, text3);
        drawText(UI3, -450, 240);
        freeText(UI3);
        /*--------------------END--------------------*/

}

void drawLoop()
{
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);

        // Repaint screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Draw scene
        drawScene();

        // Check mouse event
        mouseHold();

        // Animator
        physicsAnimator();

        // Clear buffer
        glutSwapBuffers();
}
/* ----------------------------- SCENE DRAWING ------------------------------ */
