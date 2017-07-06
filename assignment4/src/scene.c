#include <stdlib.h>
#include <math.h>
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

int iDown = 0;
int kDown = 0;
int jDown = 0;
int lDown = 0;
int oDown = 0;
int uDown = 0;

/* ------ AUDIOS -----*/
Mix_Chunk *bg = NULL;

/* ------ TEXTURES -----*/
GLuint flrtex, skyline, macplus, marble;

/* ------ SHADERS ------ */
Shader *screenShader;

/* ------ MODELS ------ */
Obj *alexander;
Obj *pyramid;
Obj *skybox;
Obj *edgeNoG;
Obj *edge;
Obj *scaffold;

/* ------ MATERIALS ------ */
Material *defaultmat;

/* ------ 3D -----*/
GLfloat aspectRatio;

GLfloat fieldOfView = 90;
GLfloat zNear = 1.0f;
GLfloat zFar = 10000.0f;

GLfloat moveSpeed = 0.6f;
GLfloat lookSpeed = 0.1f;
GLfloat jumpSpeed = 2.0f;
GLfloat gforce = 0.98f;

/* ---- CAMERA & VIEWPORT ---- */
Camera *cam;
GLuint VIEWPORT_CURX = 0, VIEWPORT_CURY = 0;

/* ------ FRAMEBUFFER ------ */
GLuint fbo;
GLuint fboDepth;
GLuint fboTexture;

/* ----- ALEX ----- */
GLfloat alex_x = -6.0f;
GLfloat alex_y = 8.0f;
GLfloat alex_z = -12.75f;

GLfloat alex_rot = 25;
GLfloat alex_rotX = 0;
GLfloat alex_rotY = 1;
GLfloat alex_rotZ = 0;

/* ------ MECHANICS ------ */
int midX = 0, midY = 0;
float diffX = 0, diffY = 0;
float bobX = 0.05, bobY = 0.15;
float bobXbuff = 0, bobYbuff = 0;
float jumpBuff = 0, jumpSet = 0;
int crouchBuff = 0;

/* ------------------------------- GLOBALS ---------------------------------- */
int loadTextures() {
        flrtex = loadTexture("./assets/textures/flrtex.png");
        marble = loadTexture("./assets/textures/marble.png");

        if (!(flrtex && marble)) {
            printf("ERROR LOADING TEXTURES\n");
        }

        return 1;
}
/* ------------------------------- GLOBALS ---------------------------------- */
int loadModels() {
        alexander = loadObj("./assets/models/alexander/alexander.obj");
        setObjTexture(alexander, loadTexture("./assets/models/alexander/CLM.png"));

        pyramid = loadObj("./assets/models/pyramid.obj");
        setObjTexture(pyramid, loadTexture("./assets/models/AO.png"));

        skybox = loadObj("./assets/models/skybox/skybox.obj");
        setObjTexture(skybox, loadTexture("./assets/models/skybox/CLM.png"));

        edgeNoG = loadObj("./assets/models/rooftop/edgeNoG.obj");
        setObjTexture(edgeNoG, loadTexture("./assets/models/rooftop/edgeCLM.png"));

        edge = loadObj("./assets/models/rooftop/edge.obj");
        setObjTexture(edge, loadTexture("./assets/models/rooftop/edgeCLM.png"));

        scaffold = loadObj("./assets/models/rooftop/scaffold.obj");
        setObjTexture(scaffold, loadTexture("./assets/models/rooftop/edgeCLM.png"));

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

void moveAlex(char key) {
    if (key == 'l'){
        // alex_x += moveSpeed; // fallback
        alex_x = (alex_x + cos(cam->rot[1] / 180 * 3.141592654f)/2);
        alex_z = (alex_z + sin(cam->rot[1] / 180 * 3.141592654f)/2);
    }
    if (key == 'j'){
        // alex_x -= moveSpeed; // fallback
        alex_x = (alex_x - cos(cam->rot[1] / 180 * 3.141592654f)/2);
        alex_z = (alex_z - sin(cam->rot[1] / 180 * 3.141592654f)/2);
    }
    if (key == 'i'){
        // alex_z -= moveSpeed; // fallback
        alex_x = (alex_x + sin(cam->rot[1] / 180 * 3.141592654f)/2);
        alex_z = (alex_z - cos(cam->rot[1] / 180 * 3.141592654f)/2);
    }
    if (key == 'k'){
        // alex_z += moveSpeed; // fallback
        alex_x = (alex_x - sin(cam->rot[1] / 180 * 3.141592654f)/2);
        alex_z = (alex_z + cos(cam->rot[1] / 180 * 3.141592654f)/2);
    }
}

void rotateAlex(char key){
    if (key == 'L'){
        alex_rotY += 1;
    }
    if (key == 'J'){
        alex_rotY -= 1;
    }
    if (key == 'I'){
        alex_rotX += 1;
    }
    if (key == 'K'){
        alex_rotX -= 1;
    }
    if (key == 'O'){
        alex_rotZ += 1;
    }
    if (key == 'U'){
        alex_rotZ -= 1;
    }
}
/* ------------------------------ MECHANICS --------------------------------- */

/* -------------------------------- INPUT ----------------------------------- */
// Mouse clicks
void onMouseClick(int button, int click_state, int x, int y) {

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
    if(key == 'i'){
      iDown = 1;
    }
    if(key == 'I'){
      iDown = 2;
    }
    if(key == 'k'){
      kDown = 1;
    }
    if(key == 'K'){
      kDown = 2;
    }
    if(key == 'j'){
      jDown = 1;
    }
    if(key == 'J'){
      jDown = 2;
    }
    if(key == 'l'){
      lDown = 1;
    }
    if(key == 'L'){
      lDown = 2;
    }
    if(key == 'O'){
      oDown = 2;
    }
    if(key == 'U'){
      uDown = 2;
    }
    if(key == 'c' || key == 'C'){
        cDown = 1;
    }
    if(key == ' '){
        jump();
    }
    if (key == 'r' || key == 'R') {
        // reset Alex model
        alex_x = -6.0f;
        alex_y = 8.0f;
        alex_z = -12.75f;

        alex_rot = 25;
        alex_rotX = 0;
        alex_rotY = 1;
        alex_rotZ = 0;
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
    if(key == 'i' || key == 'I'){
        iDown = 0;
    }
    if(key == 'k' || key == 'K'){
        kDown = 0;
    }
    if(key == 'j' || key == 'J'){
        jDown = 0;
    }
    if(key == 'l' || key == 'L'){
        lDown = 0;
    }
    if(key == 'O'){
        oDown = 0;
    }
    if(key == 'U'){
        uDown = 0;
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
    if(iDown == 1){
        moveAlex('i');
    }
    if(kDown == 1){
        moveAlex('k');
    }
    if(jDown == 1){
        moveAlex('j');
    }
    if(lDown == 1){
        moveAlex('l');
    }
    if(iDown == 2){
        rotateAlex('I');
    }
    if(kDown == 2){
        rotateAlex('K');
    }
    if(jDown == 2){
        rotateAlex('J');
    }
    if(lDown == 2){
        rotateAlex('L');
    }
    if(uDown == 2){
        rotateAlex('O');
    }
    if(oDown == 2){
        rotateAlex('U');
    }
    if(cDown == 1){
        crouch(1);
    }
}

void onMouseDrag(int x, int y) {
    if(x == midX && y == midY) return;
    // change alex_rot
    float diffX = x - midX;
    float diffY = y - midY;

    alex_rotX += diffY * lookSpeed;
    alex_rotY += diffX * lookSpeed;

    if (diffX > midX) {
        alex_rot -= lookSpeed;
    } else {
        alex_rot += lookSpeed;
    }

    glutWarpPointer(midX, midY);
}

void onMouseMove(int x, int y) {
    if(x == midX && y == midY) return;
    float diffX = x - midX;
    float diffY = y - midY;
    rotateCameraX(cam, diffY * lookSpeed);
    rotateCameraY(cam, diffX * lookSpeed);
    glutWarpPointer(midX, midY);
}

/* -------------------------------- INPUT ----------------------------------- */

/* ------------------------- FRAMEBUFFER & SHADERS -------------------------- */
void initFrameBufferDepthBuffer(){
    glGenRenderbuffersEXT(1, &fboDepth);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, fboDepth);
    glRenderbufferStorageEXT(GL_RENDERBUFFER_EXT, GL_DEPTH_COMPONENT, VIEWPORT_CURX, VIEWPORT_CURY);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, fboDepth);
    glBindRenderbufferEXT(GL_RENDERBUFFER_EXT, 0);
}

void initFrameBufferTexture(){
    glGenTextures(1, &fboTexture);
    glBindTexture(GL_TEXTURE_2D, fboTexture);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, VIEWPORT_CURX, VIEWPORT_CURY, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void initFrameBuffer(){
    initFrameBufferDepthBuffer();
    initFrameBufferTexture();

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2DEXT(GL_FRAMEBUFFER_EXT, GL_COLOR_ATTACHMENT0_EXT, GL_TEXTURE_2D, fboTexture, 0);
    glFramebufferRenderbufferEXT(GL_FRAMEBUFFER_EXT, GL_DEPTH_ATTACHMENT_EXT, GL_RENDERBUFFER_EXT, fboDepth);

    if(glCheckFramebufferStatusEXT(GL_FRAMEBUFFER_EXT) == GL_FRAMEBUFFER_COMPLETE)
        IF_DEBUG printf("Successfully initialized framebuffer, resolution: %d x %d\n\n", VIEWPORT_CURX, VIEWPORT_CURY);
    else{
        printf("Error generating framebuffer :(\n\n");
        exit(0);
    }

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void initShaders(void){
    screenShader = createShader("./assets/shaders/vcr.vert", "./assets/shaders/vcr.frag");
}
/* ------------------------- FRAMEBUFFER & SHADERS -------------------------- */

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
    /*bg = Mix_LoadWAV(BG);
    if (bg == NULL) {
        printf("ERROR bg %s\n", Mix_GetError());
    }*/
}

void audioCleanup() {
        Mix_FreeChunk(bg);
}
/* -------------------------------- AUDIO ----------------------------------- */

/*-------------------------------- RENDERING ---------------------------------*/
void drawSkybox(void) {
    repositionCamera(cam);

    glDisable(GL_LIGHTING);
    glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
    glScalef(10.0f, 10.0f, 10.0f);
    drawObjTextured(skybox);
    glEnable(GL_LIGHTING);
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

void drawFloor(void){
    repositionCamera(cam);

    Material *floormat = createMaterial();
    setMaterialDiffuse(floormat, 1.0, 1.0, 1.0, 1.0);
    setMaterialSpecular(floormat, 1.0, 1.0, 1.0, 1.0);
    setMaterialShininess(floormat, 90);
    useMaterial(floormat);
    freeMaterial(floormat);

    glTranslatef(0.0f, 0.0f, 70.0f);

    glBindTexture(GL_TEXTURE_2D, flrtex);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBegin(GL_QUADS);
        glTexCoord2f(0, 0);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-50.0f, 0.0f, -100.0f);

        glTexCoord2f(0, 1);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(-50.0f, 0.0f, 0.0f);

        glTexCoord2f(1, 1);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(50.0f, 0.0f, 0.0f);

        glTexCoord2f(1, 0);
        glNormal3f(0.0f, 1.0f, 0.0f);
        glVertex3f(50.0f, 0.0f, -100.0f);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_BLEND);

    useMaterial(defaultmat);
}

void drawEdges(){
    repositionCamera(cam);

    glTranslatef(0.0f, 0.0f, 50.0f);
    glScalef(10.0f, 10.0f, 10.0f);
    glPushMatrix();

    drawObjTextured(edgeNoG);

    glTranslatef(2.0f, 0.0f, 0.0f);
    drawObjTextured(edgeNoG);
    glTranslatef(2.0f, 0.0f, 0.0f);
    drawObjTextured(edgeNoG);

    glTranslatef(-6.0f, 0.0f, 0.0f);
    drawObjTextured(edgeNoG);
    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawObjTextured(edgeNoG);

    glPopMatrix();
    glPushMatrix();

    glTranslatef(3.0f, 0.0f, -7.0f);
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    drawObjTextured(edge);

    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawObjTextured(edge);
    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawObjTextured(edge);
    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawObjTextured(edge);

    glPopMatrix();

    glTranslatef(-3.0f, 0.0f, -1.0f);
    glRotatef(-90.0f, 0.0f, 1.0f, 0.0f);
    drawObjTextured(edge);

    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawObjTextured(edge);
    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawObjTextured(edge);
    glTranslatef(-2.0f, 0.0f, 0.0f);
    drawObjTextured(edge);
}

void drawRooftop(){
    repositionCamera(cam);
    glPushMatrix();
    glTranslatef(0.0f, 0.0f, 42.0f);
    glScalef(6.5f, 10.0f, 7.5f);
    drawObjTextured(scaffold);
    glPopMatrix();
}

void drawAlex(){
    repositionCamera(cam);

    // Statue base
    Cube *cube = createCube();
        setCubeCoordinates(cube, 0.0f, 0.0f, 0.0f);
        setCubeSize(cube, 8.5f, 5.0f, 8.5f);
        setCubeTexture(cube, marble);
        glRotatef(-30, 0, 1, 0);
        glTranslatef(-12.5f, 2.25f, -7.75f);
        drawCubeTextured(cube);
    freeCube(cube);

    repositionCamera(cam);

    // Movement
    glTranslatef(alex_x, alex_y, alex_z);
    //printf("ROT ANGLE: %f\tX: %f\tY: %f\tZ: %fz\n", alex_rot, alex_rx, alex_ry, alex_rz);
    glRotatef(alex_rotX, 1.0f, 0.0f, 0.0f);
    glRotatef(alex_rotY, 0.0f, 1.0f, 0.0f);
    glRotatef(alex_rotZ, 0.0f, 0.0f, 1.0f);
    glScalef(-0.6f, 0.6f, 0.6f);

    // Rendering
    drawObjTextured(alexander);
}

/*--------------------SCENE--------------------*/
void drawScene() {
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, fbo); // Bind our frame buffer for rendering
    glPushAttrib(GL_VIEWPORT_BIT | GL_ENABLE_BIT); // Push our glEnable and glViewport states
    glViewport(0, 0, VIEWPORT_CURX, VIEWPORT_CURY);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);

    // Load matrix mode
    glMatrixMode(GL_MODELVIEW);

    drawSkybox();
    drawFloor();

    drawAlex();

    drawRooftop();
    drawEdges();

    glPopAttrib(); // Restore our glEnable and glViewport states
    glBindFramebufferEXT(GL_FRAMEBUFFER_EXT, 0); // Unbind our texture
}

void setTime(){
    GLint shadertime = glGetUniformLocation(screenShader->program, "time");
    if(shadertime != -1){
        //printf("%f\n", (float) glutGet(GLUT_ELAPSED_TIME) / 1000);
        glUniform1f(shadertime, (float) glutGet(GLUT_ELAPSED_TIME) / 1000);
    }
}

void drawScreen(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClearDepth(1.0f);

    glEnable(GL_TEXTURE_2D); // Enable texturing so we can bind our frame buffer texture
    glEnable(GL_DEPTH_TEST); // Enable depth testing
    glDisable(GL_LIGHTING); // Disable lighting for a while

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glLoadIdentity();

    useShader(screenShader);
    setTime();

    glTranslatef(0.0f, 0.0f, -1.0f);
    glBindTexture(GL_TEXTURE_2D, fboTexture); // Bind our frame buffer texture
    glBegin(GL_QUADS);
        glTexCoord2f(0.0f, 0.0f);
        glVertex3f(-1.0f * aspectRatio, -1.0f, 0.0f); // The bottom left corner

        glTexCoord2f(0.0f, 1.0f);
        glVertex3f(-1.0f * aspectRatio, 1.0f, 0.0f); // The top left corner

        glTexCoord2f(1.0f, 1.0f);
        glVertex3f(1.0f * aspectRatio, 1.0f, 0.0f); // The top right corner

        glTexCoord2f(1.0f, 0.0f);
        glVertex3f(1.0f * aspectRatio, -1.0f, 0.0f); // The bottom right corner
    glEnd();

    glUseProgram(0);
    glDisable(GL_BLEND);
    glBindTexture(GL_TEXTURE_2D, 0); // Unbind any textures

    glEnable(GL_LIGHTING); // Re-enable scene lighting
}

void drawLoop(void) {
    drawScene();
    drawScreen();

    // Camera movement
    gravityCamera();
    bobCamera();

    // Keyboard handling
    onKeyHold();

    //glFlush();

    glutSwapBuffers();
}

void initLight(void){
    glMatrixMode(GL_MODELVIEW);
    
    glEnable(GL_COLOR_MATERIAL);

    defaultmat = createMaterial();
    setMaterialDiffuse(defaultmat, 1.0, 1.0, 1.0, 1.0);
    setMaterialSpecular(defaultmat, 0.8, 0.8, 0.8, 1.0);
    //setMaterialEmission(defaultmat, 0.2, 0.2, 0.2, 1.0);
    setMaterialShininess(defaultmat, 20);
    useMaterial(defaultmat);

    GLfloat ambient[4] = {0.27, 0.27, 0.3, 1.0};

    GLfloat diffuse0[4] = {0.05, 0.05, 0.05, 1.0};
    GLfloat specular0[4] = {0.3, 0.3, 0.3, 1.0};
    GLfloat position0[4] = {0.0, -1.0, -0.5, 0.0};

    glLoadIdentity();

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse0);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular0);
    glLightfv(GL_LIGHT0, GL_POSITION, position0);
    glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.5f);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0f);

    GLfloat diffuse1[4] = {0.0, 0.4, 0.4, 1.0};
    GLfloat specular1[4] = {0.0, 0.6, 0.6, 1.0};
    GLfloat position1[4] = {20.0, 30.0, -100.0, 1.0};

    glLoadIdentity();

    glLightfv(GL_LIGHT1, GL_DIFFUSE, diffuse1);
    glLightfv(GL_LIGHT1, GL_SPECULAR, specular1);
    glLightfv(GL_LIGHT1, GL_POSITION, position1);
    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT1, GL_LINEAR_ATTENUATION, 0.5f);
    glLightf(GL_LIGHT1, GL_QUADRATIC_ATTENUATION, 0.0f);

    GLfloat diffuse2[4] = {0.4, 0.0, 0.1, 1.0};
    GLfloat specular2[4] = {0.6, 0.0, 0.2, 1.0};
    GLfloat position2[4] = {-20.0, 30.0, -100.0, 1.0};

    glLoadIdentity();

    glLightfv(GL_LIGHT2, GL_DIFFUSE, diffuse2);
    glLightfv(GL_LIGHT2, GL_SPECULAR, specular2);
    glLightfv(GL_LIGHT2, GL_POSITION, position2);
    glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0f);
    glLightf(GL_LIGHT2, GL_LINEAR_ATTENUATION, 0.5f);
    glLightf(GL_LIGHT2, GL_QUADRATIC_ATTENUATION, 0.0f);
}

void initializeScene(void){
    cam = createCamera();
    midX = VIEWPORT_X/2;
    midY = VIEWPORT_Y/2;
    VIEWPORT_CURX = VIEWPORT_X;
    VIEWPORT_CURY = VIEWPORT_Y;
    initFrameBuffer();
    initShaders();
    initLight();
}
/* ----------------------------- SCENE DRAWING ------------------------------ */
