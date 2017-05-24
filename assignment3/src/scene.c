#include <stdlib.h>
#include "../includes/scene.h"

/* ------------------------------- GLOBALS ---------------------------------- */

/* ------ INPUT STATUS -----*/
char leftMouseButtonDown = 0;
char rightMouseButtonDown = 0;
char Adown = 0;
char Ddown = 0;
char Wdown = 0;
char Sdown = 0;

/* ------ AUDIOS -----*/
Mix_Chunk *bg = NULL;

/* ------ 3D -----*/
GLfloat aspectRatio;

GLfloat fieldOfView = 90;
GLfloat zNear = 1.0f;
GLfloat zFar = 1000.0f;

GLfloat camera_tX = 0.0f;
GLfloat camera_tY = 0.0f;
GLfloat camera_tZ = 0.0f;
GLfloat camera_rX = 0.0f;
GLfloat camera_rY = 90.0f;
GLfloat camera_rZ = 0.0f;

int lastX = -1;
int lastY = -1;
int depth = 1;

/* ------------------------------- GLOBALS ---------------------------------- */
int loadTextures() {

        // base_texture = loadTexture("./assets/textures/base.png");

        //if (!(/*texturas*/)) {
        //        return EXIT_FAILURE;
        //}

        return 1;
}
/* -------------------------------- INPUT ----------------------------------- */

// ------------ MOUSE EVENT HANDLING ------------ //
// Mouse clicks
void on_mouseClick(int button, int click_state,
        int x, int y)
{
        // Get current mouse status
	if (button == GLUT_RIGHT_BUTTON) {
            rightMouseButtonDown = (click_state == GLUT_DOWN);
    } else if (button == GLUT_LEFT_BUTTON) {
            leftMouseButtonDown = (click_state == GLUT_DOWN);
            lastX = x;
            lastY = y;
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

// Mouse hold
void onMouseMove(int x, int y){
    if(x != lastX)
        camera_rY += lastX - x;
    if(y != lastY)
        camera_rX += lastY - y;
    lastX = x;
    lastY = y;
}
// ------------ MOUSE EVENT HANDLING ------------ //

// ----------- KEYBOARD EVENT HANDLING ---------- //
// Key presses
void keyPress(unsigned char key, int x, int y){
    if(key == 'w' || key == 'W') {
            Wdown = 1;
    } else if(key == 's' || key == 'S') {
            Sdown = 1;
    } else if(key == 'a' || key == 'A') {
            Adown = 1;
    } else if(key == 'd' || key == 'D') {
            Ddown = 1;
    } else if(key == 'p' || key == 'P') {
        if(depth == 0) {
            glEnable(GL_DEPTH_TEST);
            depth = 1;
        }
        else {
            glDisable(GL_DEPTH_TEST);
            depth = 0;
        }
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
        } else if (key == 'w' || key == 'W') {
                Wdown = 0;
        } else if (key == 's' || key == 'S') {
                Sdown = 0;
        }
}

// Key holding
void keyHold() {
        if (Adown) {
                camera_tX -= 10;
        } else if (Ddown) {
                camera_tX += 10;
        } else if (Sdown) {
                camera_tZ += 10;
        } else if (Wdown) {
                camera_tZ -= 10;
        }
}
// ----------- KEYBOARD EVENT HANDLING ---------- //
/* -------------------------------- INPUT ----------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void reshape(GLsizei width, GLsizei height) {
    if(height == 0) height = 1;

    glViewport(0, 0, width, height);

    aspectRatio = width / height;

    updateView();
}
/* -------------------------------- WINDOW ---------------------------------- */

/* -------------------------------- AUDIO ----------------------------------- */
int initAudio() {

        // Audio assets
        char* BG = "./assets/audio/macintosh.wav"; // BGM

        // Initialize SDL
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
                printf("ERROR SDL %s\n", Mix_GetError());
                return -1;
        }

	// Initialize SDL_mixer
	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1) {
                printf("ERROR SDL %s\n", Mix_GetError());
                return -1;
        }

        // Load BGM
        bg = Mix_LoadWAV(BG);
        if (bg == NULL) {
                printf("ERROR bg %s\n", Mix_GetError());
        }

}

void audioCleanup() {
        Mix_FreeChunk(bg);
}
/* -------------------------------- AUDIO ----------------------------------- */

/*-------------------------------- RENDERING ---------------------------------*/

/*--------------------CAMERA--------------------*/
void repositionCamera() {
    glLoadIdentity();
    glTranslatef(-camera_tX, -camera_tY, -camera_tZ);
    glRotatef(-camera_rX, 1, 0, 0);
    glRotatef(-camera_rY, 0, 1, 0);
    glRotatef(-camera_rZ, 0, 0, 1);
}

void updateView(void) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fieldOfView, aspectRatio, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);

    repositionCamera();
}

void drawCube(void) {
    repositionCamera();

    glColor3f(0.0f, 0.0f, 0.0f);
	glLineWidth(1.6f);
	glBegin(GL_LINE_LOOP);	// frontal
		glVertex3f(40.0, -40.0, 40.0);
        glVertex3f(-40.0, -40.0, 40.0);
        glVertex3f(-40.0, 40.0, 40.0);
        glVertex3f(40.0, 40.0, 40.0);
	glEnd();
	glBegin(GL_LINE_LOOP);	//  posterior
		glVertex3f(40.0, 40.0, -40.0);
		glVertex3f(40.0, -40.0, -40.0);
		glVertex3f(-40.0, -40.0, -40.0);
		glVertex3f(-40.0, 40.0, -40.0);
	glEnd();
	glBegin(GL_LINES);	//  laterais
		glVertex3f(-40.0, 40.0, -40.0);
		glVertex3f(-40.0, 40.0, 40.0);
		glVertex3f(-40.0, -40.0, -40.0);
		glVertex3f(-40.0, -40.0, 40.0);
		glVertex3f(40.0, 40.0, -40.0);
		glVertex3f(40.0, 40.0, 40.0);
		glVertex3f(40.0, -40.0, -40.0);
		glVertex3f(40.0, -40.0, 40.0);
	glEnd();

	// Desenha as faces do cubo preenchidas
	glBegin(GL_QUADS);
		// Face frontal
		glColor3f(1.0f, 0.5f, 1.0f); //Pink
        glVertex3f(40.0, 40.0, 40.0);
        glVertex3f(-40.0, 40.0, 40.0);
        glVertex3f(-40.0, -40.0, 40.0);
        glVertex3f(40.0, -40.0, 40.0);
	    // Face posterior
		glColor3f(0.0f, 0.0f, 0.0f); //Black
		glVertex3f(40.0, 40.0, -40.0);
		glVertex3f(40.0, -40.0, -40.0);
		glVertex3f(-40.0, -40.0, -40.0);
		glVertex3f(-40.0, 40.0, -40.0);
	    // Face lateral esquerda
		glColor3f(0.0f, 1.0f, 0.0f); //Verde
		glVertex3f(-40.0, 40.0, 40.0);
		glVertex3f(-40.0, 40.0, -40.0);
		glVertex3f(-40.0, -40.0, -40.0);
		glVertex3f(-40.0, -40.0, 40.0);
	    // Face lateral direita
		glColor3f(1.0f, 0.0f, 0.0f); //Vermelho
		glVertex3f(40.0, 40.0, 40.0);
		glVertex3f(40.0, -40.0, 40.0);
		glVertex3f(40.0, -40.0, -40.0);
		glVertex3f(40.0, 40.0, -40.0);
	    // Face superior
		glColor3f(1.0f, 1.0f, 0.0f); //Amarelo
        glVertex3f(-40.0, 40.0, -40.0);
		glVertex3f(-40.0, 40.0, 40.0);
		glVertex3f(40.0, 40.0, 40.0);
		glVertex3f(40.0, 40.0, -40.0);
	    // Face inferior
		glColor3f(0.0f, 0.0f, 1.0f); //Azul
		glVertex3f(-40.0, -40.0, -40.0);
		glVertex3f(40.0, -40.0, -40.0);
		glVertex3f(40.0, -40.0, 40.0);
		glVertex3f(-40.0, -40.0, 40.0);
	glEnd();
}

/*--------------------SCENE--------------------*/
void drawScene() {
        // Load matrix mode
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
}

void drawLoop() {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 0.51f, 0.7f, 1.0f);

        glMatrixMode(GL_MODELVIEW);

        keyHold();
        drawCube();

        glFlush();
        glutSwapBuffers();
}
/* ----------------------------- SCENE DRAWING ------------------------------ */
