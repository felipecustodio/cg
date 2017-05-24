#include <stdlib.h>
#include "../includes/scene.h"

/* ------------------------------- GLOBALS ---------------------------------- */

/* ------ INPUT STATUS -----*/
char leftMouseButtonDown = 0;
char rightMouseButtonDown = 0;
char Adown = 0;
char Ddown = 0;

/* ------ AUDIOS -----*/
Mix_Chunk *bg = NULL;

/* ------------------------------- GLOBALS ---------------------------------- */

void cooldown(int value) {
    //glutPostRedisplay();
    // 100 milliseconds
    shoot_flag = 1;
    glutTimerFunc(500, cooldown, 0);
}

int loadTextures() {

        base_texture = loadTexture("./assets/textures/base.png");
        // Parallax
        parallax1_texture = loadTexture("./assets/textures/parallax1.png");
        parallax2_texture = loadTexture("./assets/textures/parallax2.png");

        if (!(/*texturas*/)) {
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
        if (key == 'a' || key == 'A') {
                Adown = 1; // hold A key
        } else if (key == 'd' || key == 'D') {
                Ddown = 1; // hold D key
        } else if (key == 'p' || key == 'P') {
                if (paused == 0)
                    paused = 1;
                else
                    paused = 0;
            }
        } else if (key == ' ') {
            if(screen == 0) {
                Mix_PlayChannel(-1, coin, 0);
                screen = 1;
            }
        } else if (key == 'r' || key == 'R') {
            if(screen == 1){
                Mix_PlayChannel(-1, wilhelm, 0);
                resetGame();
                screen = 0;
            }
        } else if (key == 'e' || key == 'E') {
                Mix_PlayChannel(-1, blaster2, 0);
                exit(0);
        } else if (key == 'g' || key == 'G') {
            if(screen == 1){
                gameover = 1;
            }
        } else if (key == 'k' || key == 'K') {
            if(screen == 1){
                Mix_PlayChannel(-1, powerup, 0);
                if(!powerup_flag) {
                        player->powerup = 1;
                        powerup_flag = 1;
                } else {
                        powerup_flag = 0;
                        player->powerup = 0;
                }
            }
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
                if((checkBorders(player->boundaryL - playerSpeed))) {
                        // move left
                        player->boundaryL -= playerSpeed;
                        player->boundaryR -= playerSpeed;
                        playerPosition -= playerSpeed;
                }
        } else if (Ddown) {
                // check for collision with window
                if((checkBorders(player->boundaryR + playerSpeed))) {
                        // move right
                        player->boundaryR += playerSpeed;
                        player->boundaryL += playerSpeed;
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

        // Audio assets
        char* BG = "./assets/audio/uncharted8bit.wav"; // BGM
        char* BLASTER = "./assets/audio/tie-blaster.wav"; // enemy blaster
        char* BLASTER2 = "./assets/audio/laser1.wav"; // player blaster
        char* DESTROY1 = "./assets/audio/explosion.wav"; // explosion
        char* WILHELM = "./assets/audio/wilhelm.wav"; // reset game
        char* VICTORY = "./assets/audio/victory.wav"; // victory fanfare
        char* COIN_SOUND = "./assets/audio/coin.wav"; // score
        char* LOSE_SOUND = "./assets/audio/lose.wav"; // game over
        char* POWERUP_SOUND = "./assets/audio/powerup.wav"; // powerup


        // Initialize SDL
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
                printf("ERROR SDL %s\n", Mix_GetError());
                return -1;
        }

	// Initialize SDL_mixer
	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1)
		return -1;

	// Load SFX
	blaster = Mix_LoadWAV(BLASTER);
	if (blaster == NULL) {
                printf("ERROR blaster %s\n", Mix_GetError());
                return -1;
        }

        blaster2 = Mix_LoadWAV(BLASTER2);
        if (blaster2 == NULL) {
                printf("ERROR blaster2 %s\n", Mix_GetError());
                return -1;
        }

        wilhelm = Mix_LoadWAV(WILHELM);
        if (wilhelm == NULL) {
                printf("ERROR wilhelm %s\n", Mix_GetError());
                return -1;
        }

        explosion = Mix_LoadWAV(DESTROY1);
        if (explosion == NULL) {
                printf("ERROR explosion %s\n", Mix_GetError());
                return -1;
        }

        fanfare = Mix_LoadWAV(VICTORY);
        if (fanfare == NULL) {
                printf("ERROR fanfare %s\n", Mix_GetError());
                return -1;
        }

        coin = Mix_LoadWAV(COIN_SOUND);
        if (coin == NULL) {
                printf("ERROR coin %s\n", Mix_GetError());
                // return -1;
        }

        lose = Mix_LoadWAV(LOSE_SOUND);
        if (lose == NULL) {
                printf("ERROR lose %s\n", Mix_GetError());
                // return -1;
        }

        powerup = Mix_LoadWAV(POWERUP_SOUND);
        if (lose == NULL) {
                printf("ERROR powerup %s\n", Mix_GetError());
                // return -1;
        }

        // Load BGM
        bg = Mix_LoadWAV(BG);
        if (bg == NULL) {
                printf("ERROR bg %s\n", Mix_GetError());
                // return -1;
        }

}

void audioCleanup() {
        Mix_FreeChunk(blaster);
	Mix_FreeChunk(blaster2);
        Mix_FreeChunk(bg);
}
/* -------------------------------- AUDIO ----------------------------------- */


/*-------------------------------- RENDERING ---------------------------------*/
void drawBackground(){
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

    // Move parallax relative to player
    int parallaxfactor = playerPosition / 12;

    glTranslatef(parallaxfactor, parallax_curYbg, 0.0f);

    Quadrilateral *parallax1Sprite = createQuad();
        setQuadCoordinates(parallax1Sprite, -VIEWPORT_X - 100, -VIEWPORT_Y - 100,
                            -VIEWPORT_X - 100, VIEWPORT_Y + 100,
                            VIEWPORT_X + 100, VIEWPORT_Y + 100,
                            VIEWPORT_X + 100, -VIEWPORT_Y - 100);
        setQuadTexture(parallax1Sprite, parallax1_texture);
        drawQuadTextured(parallax1Sprite);
        glTranslatef(0.0f, -(2*VIEWPORT_Y + 200), 0.0f);
        drawQuadTextured(parallax1Sprite);
    freeQuad(parallax1Sprite);

    // Refresh matrix for new object
    glLoadIdentity();

    parallaxfactor = playerPosition / 6;

    glTranslatef(parallaxfactor, parallax_curYfg, 0.0f);

    Quadrilateral *parallax2Sprite = createQuad();
        setQuadCoordinates(parallax2Sprite, -VIEWPORT_X - 200, -VIEWPORT_Y - 200,
                            -VIEWPORT_X - 200, VIEWPORT_Y + 200,
                            VIEWPORT_X + 200, VIEWPORT_Y + 200,
                            VIEWPORT_X + 200, -VIEWPORT_Y - 200);
        setQuadTexture(parallax2Sprite, parallax2_texture);
        drawQuadTextured(parallax2Sprite);
        glTranslatef(0.0f, -(2*VIEWPORT_Y + 200), 0.0f);
        drawQuadTextured(parallax2Sprite);
    freeQuad(parallax2Sprite);
    /*--------------------END--------------------*/
}

void drawMenu(){
    // Load matrix mode
    glMatrixMode(GL_MODELVIEW);

    drawBackground();

    // Refresh matrix for new object
    glLoadIdentity();

    glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glBegin(GL_QUADS);
            glVertex2f(-VIEWPORT_X, -VIEWPORT_Y);
            glVertex2f(-VIEWPORT_X, VIEWPORT_Y);
            glVertex2f(VIEWPORT_X, VIEWPORT_Y);
            glVertex2f(VIEWPORT_X, -VIEWPORT_Y);
        glEnd();
        glDisable(GL_BLEND);
    glColor3f(1.0f, 1.0f, 1.0f);

    glTranslatef(0.0f, 150.0f, 0.0f);
    Quadrilateral *logoSprite = createQuad();
        setQuadCoordinates(logoSprite, -265, -135,
                            -265, 135,
                            265, 135,
                            265, -135);
        setQuadTexture(logoSprite, logo);
        drawQuadTextured(logoSprite);
    freeQuad(logoSprite);

    // Refresh matrix for new object
    glLoadIdentity();

    glTranslatef(0.0f, -75.0f, 0.0f);
    glRotatef(-rotLogo, 0.0f, 0.0f, 1.0f);
    Quadrilateral *enemySprite = createQuad();
        setQuadCoordinates(enemySprite, -75, -75,
                            -75, 75,
                            75, 75,
                            75, -75);
        setQuadTexture(enemySprite, alien_1_1);
        drawQuadTextured(enemySprite);
    freeQuad(enemySprite);

    rotLogo += 1;
    if(rotLogo >= 360){
        rotLogo = 0;
    }

    // Refresh matrix for new object
    glLoadIdentity();

    glTranslatef(0.0f, -225.0f, 0.0f);
    Quadrilateral *startSprite = createQuad();
        setQuadCoordinates(startSprite, -325, -25,
                            -325, 25,
                            325, 25,
                            325, -25);
        setQuadTexture(startSprite, press_start);
        drawQuadTextured(startSprite);
    freeQuad(startSprite);
}

/*--------------------HUD--------------------*/
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

    Quadrilateral *hudL_text = createQuad();
        setQuadCoordinates(hudL_text, 0, 0, 0, 22, 72, 22, 72, 0);
        setQuadTexture(hudL_text , hudShips);
        glTranslatef(10.0f, 10.0f, 0.0f);
        drawQuadTextured(hudL_text);
        glTranslatef(-10.0f, -10.0f, 0.0f);
    freeQuad(hudL_text);

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

    Quadrilateral *hudM_text = createQuad();
        setQuadCoordinates(hudM_text, 0, 0, 0, 18, 72, 18, 72, 0);
        setQuadTexture(hudM_text , hudWave);
        glTranslatef(57.0f, 42.0f, 0.0f);
        drawQuadTextured(hudM_text);
        glTranslatef(-57.0f, -42.0f, 0.0f);
    freeQuad(hudM_text);

    char hudM_cnt_text[2];
    sprintf(hudM_cnt_text, "%d", level);
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

    Quadrilateral *hudR_text = createQuad();
        setQuadCoordinates(hudR_text, 0, 0, 0, 20, 84, 20, 84, 0);
        setQuadTexture(hudR_text , hudScore);
        glTranslatef(190.0f, 10.0f, 0.0f);
        drawQuadTextured(hudR_text);
        glTranslatef(-190.0f, -10.0f, 0.0f);
    freeQuad(hudR_text);

    char hudR_cnt_text[2];
    sprintf(hudR_cnt_text, "%d", player->score);
    Text* hudR_cnt = createText(GLUT_BITMAP_HELVETICA_18, hudR_cnt_text);
        drawText(hudR_cnt, VIEWPORT_X/2 - 317, 20);
    freeText(hudR_cnt);
    // -------------- RIGHT FRAME -------------- //
}

/*--------------------SCENE--------------------*/
void drawScene() {
        int i = 0;
        // Load matrix mode
        glMatrixMode(GL_MODELVIEW);

        drawBackground();

        /*--------------------BASE--------------------*/
        glLoadIdentity();

        int parallaxfactor = playerPosition / 4;

        glTranslatef(parallaxfactor, 50.0f, 0.0f);

        Quadrilateral *base = createQuad();
        setQuadCoordinates(base, -VIEWPORT_X, -VIEWPORT_Y - 200,
                                 -VIEWPORT_X, -200,
                                VIEWPORT_X, -200,
                                VIEWPORT_X, -VIEWPORT_Y - 200);
        setQuadTexture(base, base_texture);
        drawQuadTextured(base);
        freeQuad(base);
        /*--------------------END--------------------*/

        /*--------------------PLAYER--------------------*/
        // matrix for player
        glLoadIdentity();
        glColor3f(1.0f, 1.0f, 1.0f);
        if (player == NULL) {
            player = createPlayer();
        }
        drawPlayer(player);
        /*--------------------END--------------------*/

        /*--------------------LASERS--------------------*/

        /*------------------------ENEMY------------------------*/
        if(enemies == NULL) {
            enemies = createEnemyMatrix();
        }

        for (i = 0; i < TOTAL_ENEMIES; i++) {
            if(enemies[i] != NULL){
                if (enemies[i]->health > 0) {
                    drawEnemy(enemies[i]);
                }
            }
        }
        /*-------------------------END-------------------------*/

        /*--------------------LASERS--------------------*/
        i = 0;
        for(i = 0; i < shots_player_count; i++) {
            if (shots_player[i] != NULL) {
                drawLaser(shots_player[i]);
            }
        }

        i = 0;
        for(i = 0; i < shots_enemy_count; i++) {
            if (shots_enemy[i] != NULL) {
                drawLaser(shots_enemy[i]);
            }
        }
        /*--------------------END--------------------*/

        glColor3f(1.0f, 1.0f, 1.0f);

        // Draw HUD
        drawHUD();
}

void pauseScreen() {
        // Refresh matrix for new object
        glLoadIdentity();

        glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBegin(GL_QUADS);
                glVertex2f(-VIEWPORT_X, -VIEWPORT_Y);
                glVertex2f(-VIEWPORT_X, VIEWPORT_Y);
                glVertex2f(VIEWPORT_X, VIEWPORT_Y);
                glVertex2f(VIEWPORT_X, -VIEWPORT_Y);
            glEnd();
            glDisable(GL_BLEND);
        glColor3f(1.0f, 1.0f, 1.0f);

        Quadrilateral *pauseSprite = createQuad();
            setQuadCoordinates(pauseSprite, -200, -75,
                                -200, 75,
                                200, 75,
                                200, -75);
            setQuadTexture(pauseSprite, pause);
            drawQuadTextured(pauseSprite);
        freeQuad(pauseSprite);
}

void gameOverScreen() {
        // Refresh matrix for new object
        glLoadIdentity();

        glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBegin(GL_QUADS);
                glVertex2f(-VIEWPORT_X, -VIEWPORT_Y);
                glVertex2f(-VIEWPORT_X, VIEWPORT_Y);
                glVertex2f(VIEWPORT_X, VIEWPORT_Y);
                glVertex2f(VIEWPORT_X, -VIEWPORT_Y);
            glEnd();
            glDisable(GL_BLEND);
        glColor3f(1.0f, 1.0f, 1.0f);

        Quadrilateral *gameOver = createQuad();
            setQuadCoordinates(gameOver, -265, -75,
                                -265, 75,
                                265, 75,
                                265, -75);
            setQuadTexture(gameOver, game_over);
            drawQuadTextured(gameOver);
        freeQuad(gameOver);
}

void victoryScreen() {
        // Refresh matrix for new object
        glLoadIdentity();

        glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBegin(GL_QUADS);
                glVertex2f(-VIEWPORT_X, -VIEWPORT_Y);
                glVertex2f(-VIEWPORT_X, VIEWPORT_Y);
                glVertex2f(VIEWPORT_X, VIEWPORT_Y);
                glVertex2f(VIEWPORT_X, -VIEWPORT_Y);
            glEnd();
            glDisable(GL_BLEND);
        glColor3f(1.0f, 1.0f, 1.0f);

        Quadrilateral *victoryQuad = createQuad();
            setQuadCoordinates(victoryQuad, -265, -75,
                                -265, 75,
                                265, 75,
                                265, -75);
            setQuadTexture(victoryQuad, victory_screen);
            drawQuadTextured(victoryQuad);
        freeQuad(victoryQuad);
}
/*-------------------------------- RENDERING ---------------------------------*/

/* ----------------------------- SCENE DRAWING ------------------------------ */
void drawLoop() {
        // Background color
        glClearColor(0.0f, 0.0f, 0.0f, 1);
        glColor3f(1.0f, 1.0f, 1.0f);

        // Repaint screen
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(screen == 0){
            drawMenu();
        } else if(screen == 1){
            // Draw scene
            drawScene();

            if (!paused && !gameover && !victory) {
                // Enemy fire
                current_time = glutGet(GLUT_ELAPSED_TIME);
                int nextTime = 5000/level + rand() % 3000;
                if (shoot_timer - current_time < - nextTime) {
                    enemyShoot(&shots_enemy, enemies);
                    shoot_timer = current_time;
                }
                // Check for Game Over
                checkGameOver();

                // Check for Victory
                checkVictory();

                // Check for Level Up
                checkLevelUp();

                // Check for coins
                checkScore();

                // Enemy Movement
                moveEnemies(enemies);

                // Laser Movement
                lasersMotionY();

                // Check for collisions
                checkCollisions();

                // Check for key presses
                keyHold();
            }
        }

        // Parallax vertical motion
        parallaxMotionY();

        // Paused Screen
        if (paused)
            pauseScreen();

        // Game Over Screen
        if (gameover)
            gameOverScreen();

        // Victory screen
        if (victory) {
            victoryScreen();
        }

        // Clear buffer
        glutSwapBuffers();
}
/* ----------------------------- SCENE DRAWING ------------------------------ */
