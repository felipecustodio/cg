#include <stdlib.h>
#include "../includes/scene.h"

/* ------------------------------- GLOBALS ---------------------------------- */

/* ------ INPUT STATUS -----*/
char leftMouseButtonDown = 0;
char rightMouseButtonDown = 0;
int wDown = 0;
int sDown = 0;
int aDown = 0;
int dDown = 0;
int cDown = 0;

/* ------ AUDIOS -----*/
Mix_Chunk *bg = NULL;

/* ------ TEXTURES -----*/
GLuint checker, miami, playstation, title;

/* ------ 3D -----*/
GLfloat aspectRatio;

GLfloat fieldOfView = 90;
GLfloat zNear = 1.0f;
GLfloat zFar = 10000.0f;

GLfloat moveSpeed = 0.6f;
GLfloat lookSpeed = 0.1f;
GLfloat gforce = 0.98f;

Camera *cam;

/* ------ MECHANICS ------ */
int midX = 0, midY = 0;
float initialY = 0;
float jumpBuff = 0;
int crouchBuff = 0;

/* ------------------------------- GLOBALS ---------------------------------- */
int loadTextures() {

        checker = loadTexture("./assets/textures/checker.png");
        miami = loadTexture("./assets/textures/miami.png");
        playstation = loadTexture("./assets/textures/playstation.png");
        title = loadTexture("./assets/textures/title.png");

        if (!(checker && miami && playstation && title)) {
                printf("ERROR LOADING TEXTURES\n");
        }

        return 1;
}
/* ------------------------------- GLOBALS ---------------------------------- */

/* ------------------------------ MECHANICS --------------------------------- */
void gravityCamera(){
    if(jumpBuff != 0){
        jumpBuff -= gforce;
        if(jumpBuff > 0)
            cam->pos[1] -= gforce;
        else{
            cam->pos[1] = initialY;
            jumpBuff = 0;
        }
    }
}

void crouch(int state){
    if(jumpBuff == 0){
        if(crouchBuff == 0 && state == 1){
            cam->pos[1] -= 5.0;
            crouchBuff = 1;
        }
        else if(crouchBuff == 1 && state == 0){
            cam->pos[1] += 5.0;
            crouchBuff = 0;
        }
    }
}

void jump(){
    if(jumpBuff == 0){
        initialY = cam->pos[1];
        cam->pos[1] += 15;
        jumpBuff = 15;
    }
}
/* ------------------------------ MECHANICS --------------------------------- */

/* -------------------------------- INPUT ----------------------------------- */
// Mouse clicks
void onMouseClick(int button, int click_state, int x, int y){
}

// Mouse status
void onMouseHold() {
        if (leftMouseButtonDown) {
                // left mouse event
        } else if (rightMouseButtonDown) {
                // right mouse event
        }
}

void onKeyPress(unsigned char key, int x, int y){
    if(key == 27){ // ESC
        exit(0);
    }
    if(key == 'w' || key == 'W'){
        wDown = 1;
    }
    if(key == 's' || key == 'S'){
        sDown = 1;
    }
    if(key == 'a' || key == 'A'){
        aDown = 1;
    }
    if(key == 'd' || key == 'D'){
        dDown = 1;
    }
    if(key == 'c' || key == 'C'){
        cDown = 1;
    }
    if(key == ' '){
        jump();
    }
}

void onKeyUp(unsigned char key, int x, int y){
    if(key == 'w' || key == 'W'){
        wDown = 0;
    }
    if(key == 's' || key == 'S'){
        sDown = 0;
    }
    if(key == 'a' || key == 'A'){
        aDown = 0;
    }
    if(key == 'd' || key == 'D'){
        dDown = 0;
    }
    if(key == 'c' || key == 'C'){
        cDown = 0;
        crouch(0);
    }
}

void onKeyHold(){
    if(wDown == 1){
        moveCamera(cam, moveSpeed);
    }
    if(sDown == 1){
        moveCamera(cam, -moveSpeed);
    }
    if(aDown == 1){
        strafeCamera(cam, -moveSpeed);
    }
    if(dDown == 1){
        strafeCamera(cam, moveSpeed);
    }
    if(cDown == 1){
        crouch(1);
    }
}

void onMouseMove(int x, int y){
    if(x == midX && y == midY) return;
    float diffX = x - midX;
    float diffY = y - midY;
    rotateCameraX(cam, diffY * lookSpeed);
    rotateCameraY(cam, diffX * lookSpeed);
    glutWarpPointer(midX, midY);
}
/* -------------------------------- INPUT ----------------------------------- */

/* -------------------------------- WINDOW ---------------------------------- */
void updateView(void){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(fieldOfView, aspectRatio, zNear, zFar);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(GLsizei width, GLsizei height){
    if(height == 0) height = 1;

    glViewport(0, 0, width, height);

    midX = width/2;
    midY = height/2;

    aspectRatio = width / height;

    updateView();
}
/* -------------------------------- WINDOW ---------------------------------- */

/* -------------------------------- AUDIO ----------------------------------- */
// Load audio files and start SDL mixer
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
void drawCube(void) {
    repositionCamera(cam);

    glColor3f(1.0f, 1.0f, 1.0f);
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
		glColor3f(1.0, 0.31, 0.97); // Pink
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
		glColor3f(0.0f, 0.0f, 0.0f); //Black
		glVertex3f(-40.0, 40.0, 40.0);
		glVertex3f(-40.0, 40.0, -40.0);
		glVertex3f(-40.0, -40.0, -40.0);
		glVertex3f(-40.0, -40.0, 40.0);
	    // Face lateral direita
		glColor3f(0.0f, 0.0f, 0.0f); //Black
		glVertex3f(40.0, 40.0, 40.0);
		glVertex3f(40.0, -40.0, 40.0);
		glVertex3f(40.0, -40.0, -40.0);
		glVertex3f(40.0, 40.0, -40.0);
	    // Face superior
		glColor3f(0.0f, 0.0f, 0.0f); //Black
                glVertex3f(-40.0, 40.0, -40.0);
		glVertex3f(-40.0, 40.0, 40.0);
		glVertex3f(40.0, 40.0, 40.0);
		glVertex3f(40.0, 40.0, -40.0);
	    // Face inferior
		glColor3f(0.0f, 0.0f, 0.0f); //Black
		glVertex3f(-40.0, -40.0, -40.0);
		glVertex3f(40.0, -40.0, -40.0);
		glVertex3f(40.0, -40.0, 40.0);
		glVertex3f(-40.0, -40.0, 40.0);
	glEnd();
}

void drawGrid(void){
    repositionCamera(cam);

    float i = -500;
	while(i <= 500){
		glBegin(GL_LINES);
			glColor3ub(150, 190, 150);
			glVertex3f(-500, 0, i);
			glVertex3f(500, 0, i);
			glVertex3f(i, 0,-500);
			glVertex3f(i, 0, 500);
		glEnd();
        i += 5;
	}
}

/*--------------------SCENE--------------------*/
void drawScene() {
        // Load matrix mode
        glMatrixMode(GL_MODELVIEW);
        drawCube();
        drawGrid();
}

void drawLoop(void) {
        // Paint background
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glClearColor(1.0f, 0.71f, 0.89f, 1.0f);
        glClearDepth(1.0f);

        drawScene();

        gravityCamera();
        onKeyHold();

        glFlush();
        glutSwapBuffers();
}

void initializeScene(void){
    cam = createCamera();
    initialY = cam->pos[1];
    midX = VIEWPORT_X/2;
    midY = VIEWPORT_Y/2;
}
/* ----------------------------- SCENE DRAWING ------------------------------ */
