#include <stdlib.h>
//#include "../includes/invaders.h"
#include "../includes/scene.h"

/* ------------------------------- GLOBALS ---------------------------------- */
/* ------ LASERS -----*/
int shoot_flag = 1;

/* ------ UI -----*/
const char* UI_reset = "Press R to reset game";
const char* UI_shoot = "Press spacebar to shoot";
const char* UI_move = "Press A/D to move left/right";
const char* UI_exit = "Press E to exit";
const char* UI_gameover = "GAME OVER";

/* ------ INPUT STATUS -----*/
char leftMouseButtonDown = 0;
char rightMouseButtonDown = 0;
char Adown = 0;
char Ddown = 0;

/* ------ AUDIOS -----*/
Mix_Chunk *blaster = NULL;
Mix_Chunk *blaster2 = NULL;
Mix_Chunk *wilhelm = NULL;
Mix_Chunk *explosion = NULL;
Mix_Chunk *fanfare = NULL;
Mix_Chunk *bg = NULL;

/* ------------------------------- GLOBALS ---------------------------------- */

void timer(int value){
    //glutPostRedisplay();
    // 100 milliseconds
    shoot_flag = 1;
    glutTimerFunc(500, timer, 0);
}

int loadTextures() {
        // HUD
        hudL = loadTexture("./assets/textures/hudL.png");
        hudM = loadTexture("./assets/textures/hudM.png");
        hudR = loadTexture("./assets/textures/hudR.png");

        // Background
        background_texture = loadTexture("./assets/textures/bg.png");
        // background_texture = loadTexture("./assets/textures/bgmaterial.png");
        base_texture = loadTexture("./assets/textures/base.png");

        // Parallax
        parallax1_texture = loadTexture("./assets/textures/parallax1.png");
        parallax2_texture = loadTexture("./assets/textures/parallax2.png");

        // Player sprite
        player_texture = loadTexture("./assets/textures/galaga.png");

        // Enemy sprites
        alien_1_1 = loadTexture("./assets/textures/alien1_1.png");
        alien_1_2 = loadTexture("./assets/textures/alien1_2.png");
        alien_2_1 = loadTexture("./assets/textures/alien2_1.png");
        alien_2_2 = loadTexture("./assets/textures/alien2_2.png");
        alien_3_1 = loadTexture("./assets/textures/alien3_1.png");
        alien_3_2 = loadTexture("./assets/textures/alien3_2.png");

        pause = loadTexture("./assets/textures/paused.png");
        game_over = loadTexture("./assets/textures/gameover.png");
        victory_screen = loadTexture("./assets/textures/victory_screen.png");

        if (!(hudL || hudM || hudR || background_texture
                || player_texture ||alien_1_1 ||
                alien_1_2 || alien_2_1 ||
                alien_2_2 || alien_3_1 ||
                alien_3_2 || pause || game_over || victory_screen)) {
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
            if(!paused && !gameover)
                Adown = 1; // hold A key
        } else if (key == 'd' || key == 'D') {
            if(!paused && !gameover)
                Ddown = 1; // hold D key
        } else if (key == 'p' || key == 'P') {
            if(!gameover){
                if(paused == 0)
                    paused = 1;
                else
                    paused = 0;
            }
        } else if (key == ' ' && shoot_flag) {
            if(!paused && !gameover){
                // PEW! PEW! play blaster audio
                Mix_PlayChannel(-1, blaster2, 0);
                // create new laser
                if(shots_player == NULL) {
                    shots_player = (LASER **) malloc(sizeof(LASER *));
                }
                else{
                    shots_player = (LASER **) realloc(shots_player, sizeof(LASER *) * (shots_player_count + 1));
                }
                shootLaser_Player(shots_player, &shots_player_count, playerPosition);
                shoot_flag = 0;
            }
            else if(gameover) {
                resetGame();
            }
        } else if (key == 'r' || key == 'R') {
                Mix_PlayChannel(-1, wilhelm, 0);
                resetGame();
        } else if (key == 'e' || key == 'E') {
                Mix_PlayChannel(-1, blaster2, 0);
                exit(0);
        } else if (key == 'g' || key == 'G') {
                gameover = 1;
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
                        playerPosition -= playerSpeed;
                }
        } else if (Ddown) {
                // check for collision with window
                if((checkBorders(player->boundary_right + playerSpeed))) {
                        // move right
                        player->boundary_right += playerSpeed;
                        player->boundary_left += playerSpeed;
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
        char* BG = "./assets/audio/unchartedworlds.wav";
        char* BLASTER = "./assets/audio/tie-blaster.wav";
        char* BLASTER2 = "./assets/audio/laser1.wav";
        char* DESTROY1 = "./assets/audio/explosion.wav";
        char* DESTROY2;
        char* WILHELM = "./assets/audio/wilhelm.wav";
        char* VICTORY = "./assets/audio/victory.wav";

        // Initialize SDL
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
		return -1;

	// Initialize SDL_mixer
	if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1)
		return -1;

	// Load SFX
	blaster = Mix_LoadWAV(BLASTER);
	if (blaster == NULL)
		return -1;

    blaster2 = Mix_LoadWAV(BLASTER2);
	if (blaster2 == NULL)
		return -1;

    wilhelm = Mix_LoadWAV(WILHELM);
	if (wilhelm == NULL)
		return -1;

        explosion = Mix_LoadWAV(DESTROY1);
        if (explosion == NULL)
    		return -1;

        fanfare = Mix_LoadWAV(VICTORY);
        if (victory == NULL)
    		return -1;

    // Load BGM
    bg = Mix_LoadWAV(BG);
	if (bg == NULL) {
        printf("ERROR %s\n", Mix_GetError());
        return -1;
    }

}

void audioCleanup() {
        Mix_FreeChunk(blaster);
	Mix_FreeChunk(blaster2);
        Mix_FreeChunk(bg);
}
/* -------------------------------- AUDIO ----------------------------------- */

/* ------------------------------- MECHANICS -------------------------------- */

/*--------------------COLLISION CHECKING-------------------*/
void destroyDesallocLaser(int i) {
    destroyLaser(shots_player[i]);
    int j = 0;
    for(j = i + 1; j < shots_player_count; j++) {
        shots_player[j - 1] = shots_player[j];
    }
    shots_player_count = shots_player_count - 1;
    shots_player = (LASER **) realloc(shots_player, sizeof(LASER *) * shots_player_count);
}

void checkCollisions() {
    /*--------------------PLAYER SHOTS--------------------*/
    // Refresh matrix for new object
    glLoadIdentity();

    // LASER MATRIX CHECKING
    // Laser enemy collision check
    int i, j;
    for (i = 0; i < shots_player_count; i++) {
        for (j = 0; j < 25; j ++) {
            if (enemies != NULL) {
                if (enemies[j]->health > 0) {
                        if(shots_player[i]->explosion == 0) {
                            // Check X boundaries
                            if (shots_player[i]->x[0] >= enemies[j]->boundaryL &&
                                shots_player[i]->x[2] <= enemies[j]->boundaryR) {
                                // Check Y boundaries
                                if (shots_player[i]->boundaryU >= enemies[j]->boundaryD) {
                                        Mix_PlayChannel(-1, explosion, 0);
                                        destroyLaser(shots_player[i]); // destroy laser
                                        destroyEnemy(enemies[j]); // destroy enemy
                                        enemies_left--;
                                        // check for victory
                                        if (enemies_left == 0) {
                                                Mix_PlayChannel(-1, fanfare, 0); // play fanfare
                                        }
                                        player->score = player->score + 10; // update score
                                }
                        }
                    }
                }
            }
        }
    }

    // Laser screen collision check
    i = 0, j = 0;
    for(i = 0; i < shots_player_count; i++) {
        // Check top boundary
        if(shots_player[i] != NULL && shots_player[i]->boundaryU >= 340) {
                destroyDesallocLaser(i);
        }
    }

    /*--------------------ENEMY LASERS VS PLAYER--------------------*/
    i = 0;
    for (i = 0; i < shots_enemy_count; i++) {
            if (shots_enemy[i]->x[0] >= player->boundary_left
                && shots_enemy[i]->x[2] <= player->boundary_right) {
                    // Laser is aligned with player, check if hit
                    if (shots_enemy[i]->boundaryD <= -200) {
                            // Laser hit player!
                            player->health--;
                            destroyDesallocLaser(i);
                    }
            }
    }
    /*-------------------------END-------------------------*/

    /*--------------------ENEMY VS BASE--------------------*/
    i = 0;
    for (i = 0; i < 25; i++) {
            if (enemies[i] != NULL) {
                    if (enemies[i]->boundaryD <= -200) {
                            // Enemy hit base! Game Over!
                            gameover = 1;
                    }
            }
    }
    /*-------------------------END-------------------------*/

    /*--------------------LASER MOVEMENT--------------------*/
    // Player lasers Movement
    i = 0;
    for(i = 0; i < shots_player_count; i++) {
        if (shots_player[i] != NULL) {
            // Move laser (player) up
            shots_player[i]->position += laserSpeed;
            // Move boundaries
            shots_player[i]->boundaryD += laserSpeed;
            shots_player[i]->boundaryU += laserSpeed;
        }
    }

    // Enemy lasers movement
    i = 0;
    for(i = 0; i < shots_enemy_count; i++) {
        if (shots_enemy[i] != NULL) {
            // Move laser (enemy) down
            shots_enemy[i]->position -= laserSpeed;
            // Move boundaries
            shots_enemy[i]->boundaryD -= laserSpeed;
            shots_enemy[i]->boundaryU -= laserSpeed;
        }
    }
    /*--------------------END--------------------*/
}
/*--------------------COLLISION CHECKING-------------------*/

/*--------------------GAME OVER CHECK-------------------*/
void checkGameOver(){
    if(player->health == 0)
        gameover = 1;
}

void checkVictory() {
        if (enemies_left == 0) {
                victory = 1;
        }
}
/*--------------------GAME OVER CHECK-------------------*/
/* ------------------------------- MECHANICS -------------------------------- */

/*-------------------------------- RENDERING ---------------------------------*/
/*--------------------SCENE--------------------*/
void drawScene() {
        int i;
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

        // Refresh matrix for new object
        glLoadIdentity();

        // Move parallax relative to player
        int parallaxfactor = playerPosition / 12;

        glTranslatef(parallaxfactor, 0.0f, 0.0f);

        Quadrilateral *parallax1Sprite = createQuad();
            setQuadCoordinates(parallax1Sprite, -VIEWPORT_X - 100, -VIEWPORT_Y - 100,
                                -VIEWPORT_X - 100, VIEWPORT_Y + 100,
                                VIEWPORT_X + 100, VIEWPORT_Y + 100,
                                VIEWPORT_X + 100, -VIEWPORT_Y - 100);
            setQuadTexture(parallax1Sprite, parallax1_texture);
            drawQuadTextured(parallax1Sprite);
        freeQuad(parallax1Sprite);

        // Refresh matrix for new object
        glLoadIdentity();

        parallaxfactor = playerPosition / 6;

        glTranslatef(parallaxfactor, 0.0f, 0.0f);

        Quadrilateral *parallax2Sprite = createQuad();
            setQuadCoordinates(parallax2Sprite, -VIEWPORT_X - 200, -VIEWPORT_Y - 200,
                                -VIEWPORT_X - 200, VIEWPORT_Y + 200,
                                VIEWPORT_X + 200, VIEWPORT_Y + 200,
                                VIEWPORT_X + 200, -VIEWPORT_Y - 200);
            setQuadTexture(parallax2Sprite, parallax2_texture);
            drawQuadTextured(parallax2Sprite);
        freeQuad(parallax2Sprite);
        /*--------------------END--------------------*/

        /*--------------------BASE--------------------*/
        glLoadIdentity();
        Quadrilateral *base = createQuad();
        setQuadCoordinates(base, -VIEWPORT_X, -VIEWPORT_Y,
                                 -VIEWPORT_X, -200,
                                VIEWPORT_X, -200,
                                VIEWPORT_X, -VIEWPORT_Y);
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

        for (i = 0; i < 25; i++) {
                if (enemies[i]->health > 0) {
                        drawEnemy(enemies[i]);
                }
        }

        if(!paused) moveEnemies(enemies);
        /*-------------------------END-------------------------*/

        /*--------------------LASERS--------------------*/
        // Player lasers Movement
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

    char const* hudL_text = "SHIPS";
    Text* hudL = createText(GLUT_BITMAP_9_BY_15, hudL_text);
        drawText(hudL, 10, 20);
    freeText(hudL);

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

    char const* hudM_text = "WAVE";
    Text* hudM = createText(GLUT_BITMAP_9_BY_15, hudM_text);
        drawText(hudM, VIEWPORT_X/4 - 130, 45);
    freeText(hudM);

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

    char const* hudR_text = "SCORE";
    Text* hudR = createText(GLUT_BITMAP_9_BY_15, hudR_text);
        drawText(hudR, VIEWPORT_X/2 - 188, 20);
    freeText(hudR);

    char hudR_cnt_text[2];
    sprintf(hudR_cnt_text, "%d", player->score);
    Text* hudR_cnt = createText(GLUT_BITMAP_HELVETICA_18, hudR_cnt_text);
        drawText(hudR_cnt, VIEWPORT_X/2 - 317, 20);
    freeText(hudR_cnt);
    // -------------- RIGHT FRAME -------------- //
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

        // Draw scene
        drawScene();

        glColor3f(1.0f, 1.0f, 1.0f);

        // Draw HUD
        drawHUD();

        // Check for Game Over
        checkGameOver();

        // Check for Victory
        checkVictory();
        printf("ENEMIES LEFT: %d\n", enemies_left);


        if(!paused && !gameover && !victory) {
            // Check for key presses
            keyHold();

            // Check for collisions
            checkCollisions();
        }

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
