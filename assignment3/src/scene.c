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
GLfloat jumpSpeed = 2.0f;
GLfloat gforce = 0.98f;

Camera *cam;

Obj *alexander;
Obj *pyramid;

/* ------ MECHANICS ------ */
int midX = 0, midY = 0;
float bobX = 0.05, bobY = 0.15;
float bobXbuff = 0, bobYbuff = 0;
float jumpBuff = 0, jumpSet = 0;
int crouchBuff = 0;
float pyramidRot = 0;

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
int loadModels() {
        alexander = loadObj("./assets/models/alexander/alexander.obj");
        setObjTexture(alexander, loadTexture("./assets/models/alexander/OCM.png"));

        pyramid = loadObj("./assets/models/pyramid.obj");
        setObjTexture(pyramid, loadTexture("./assets/models/AO.png"));

        return 1;
}

/* ------------------------------ MECHANICS --------------------------------- */
void gravityCamera(){
    if(jumpSet >= 1){
        jumpSet += jumpSpeed;
        cam->pos[1] += jumpSpeed;
        if(jumpSet >= jumpBuff)
            jumpSet = 0;
    }
    if(jumpBuff != 0 && jumpSet == 0){
        jumpBuff -= gforce;
        if(jumpBuff > 0)
            cam->pos[1] -= gforce;
        else{
            cam->pos[1] -= jumpBuff;
            jumpBuff = 0;
        }
    }
}

void bobCamera(){
    if(jumpBuff == 0 && (wDown || aDown || sDown || dDown)){
        if(bobXbuff <= -1 || bobXbuff >= 1)
            bobX = -bobX;
        cam->pos[0] += bobX;
        bobXbuff += bobX;

        if(bobYbuff <= -1.5 || bobYbuff >= 0)
            bobY = -bobY;
        cam->pos[1] += bobY;
        bobYbuff += bobY;
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
        jumpBuff = 15;
        jumpSet = 1;
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

    aspectRatio = (GLfloat) width / (GLfloat) height;

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
void drawSkybox(void) {
    repositionCamera(cam);

    glColor3f(1.0f, 1.0f, 1.0f);
	glLineWidth(1.6f);
	glBegin(GL_LINE_LOOP);	// frontal
		glVertex3f(500.0, -500.0, 500.0);
        glVertex3f(-500.0, -500.0, 500.0);
        glVertex3f(-500.0, 500.0, 500.0);
        glVertex3f(500.0, 500.0, 500.0);
	glEnd();
	glBegin(GL_LINE_LOOP);	//  posterior
		glVertex3f(500.0, 500.0, -500.0);
		glVertex3f(500.0, -500.0, -500.0);
		glVertex3f(-500.0, -500.0, -500.0);
		glVertex3f(-500.0, 500.0, -500.0);
	glEnd();
	glBegin(GL_LINES);	//  laterais
		glVertex3f(-500.0, 500.0, -500.0);
		glVertex3f(-500.0, 500.0, 500.0);
		glVertex3f(-500.0, -500.0, -500.0);
		glVertex3f(-500.0, -500.0, 500.0);
		glVertex3f(500.0, 500.0, -500.0);
		glVertex3f(500.0, 500.0, 500.0);
		glVertex3f(500.0, -500.0, -500.0);
		glVertex3f(500.0, -500.0, 500.0);
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

void drawPyramid(){
    repositionCamera(cam);

    glTranslatef(0.0f, 0.0f, 15.0f);
    glRotatef(pyramidRot, 0, 1, 0);

    pyramidRot += 0.5;
    if(pyramidRot >= 360)
        pyramidRot = 0;

    drawObjTextured(pyramid);

    glColor3f(1.0f, 0.0f, 0.0f);
    drawObjWireframe(pyramid);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawObjVertices(pyramid);
    glColor3f(1.0f, 1.0f, 1.0f);
}

void drawAlex(){
    repositionCamera(cam);

    glTranslatef(50.0f, 0.0f, 0.0f);
    glRotatef(-90, 0, 1, 0);
    glScalef(1.5f, 1.5f, 1.5f);

    drawObjTextured(alexander);

    /*glColor3f(0.0f, 0.0f, 1.0f);
    drawObjWireframe(alexander);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawObjVertices(alexander);
    glColor3f(1.0f, 1.0f, 1.0f);*/
}

/*--------------------SCENE--------------------*/
void drawScene() {
    // Load matrix mode
    glMatrixMode(GL_MODELVIEW);

    drawSkybox();
    drawPyramid();
    drawAlex();
    drawGrid();

    Cube *cube = createCube();
        setCubeCoordinates(cube, 0.0f, 20.0f, 20.0f);
        setCubeSize(cube, 30.0f, 30.0f, 10.0f);
        setCubeColor(cube, 1.0f, 1.0f, 1.0f);
        setCubeTexture(cube, checker);
        glTranslatef(0.0f, 0.0f, 30.0f);
        drawCubeTextured(cube);
    freeCube(cube);
}

void drawLoop(void) {
    // Paint background
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 0.71f, 0.89f, 1.0f);
    glClearDepth(1.0f);

    drawScene();

    gravityCamera();
    bobCamera();
    onKeyHold();

    glFlush();
    glutSwapBuffers();
}

void initializeScene(void){
    cam = createCamera();
    midX = VIEWPORT_X/2;
    midY = VIEWPORT_Y/2;
}
/* ----------------------------- SCENE DRAWING ------------------------------ */
