#include <stdlib.h>
#include "../includes/scene.h"

/* ------------------------------- GLOBALS ---------------------------------- */
/* --- MECHANICS -- */
int screen = 0; // 0 = menu, 1 = game
int rotLogo = 0;

/* ------ BG ----- */
GLfloat parallax_curYbg = 0.0;
GLfloat parallax_curYfg = 0.0;
GLfloat parallax_speedY = 0.5;

/* ------ LASERS -----*/
int shoot_flag = 1;
int powerup_flag = 0;

/* ------ SCORE -----*/
int current_score = 50;

/* ------ UI -----*/
const char* UI_reset = "Press R to reset game";
const char* UI_shoot = "Press spacebar to shoot";
const char* UI_move = "Press A/D to move left/right";
const char* UI_exit = "Press E to exit";

/* ------ INPUT STATUS -----*/
char leftMouseButtonDown = 0;
char rightMouseButtonDown = 0;
char Adown = 0;
char Ddown = 0;

/* ------ TIMER -----*/
GLfloat shoot_timer = 0;
GLfloat current_time = 0;

/* ------ AUDIOS -----*/
Mix_Chunk *blaster = NULL;
Mix_Chunk *blaster2 = NULL;
Mix_Chunk *wilhelm = NULL;
Mix_Chunk *explosion = NULL;
Mix_Chunk *fanfare = NULL;
Mix_Chunk *coin = NULL;
Mix_Chunk *lose = NULL;
Mix_Chunk *powerup = NULL;
Mix_Chunk *bg = NULL;

/* ------------------------------- GLOBALS ---------------------------------- */

void cooldown(int value) {
    //glutPostRedisplay();
    // 100 milliseconds
    shoot_flag = 1;
    glutTimerFunc(500, cooldown, 0);
}

int loadTextures() {
        // HUD
        hudL = loadTexture("./assets/textures/hud/hudL.png");
        hudM = loadTexture("./assets/textures/hud/hudM.png");
        hudR = loadTexture("./assets/textures/hud/hudR.png");
        hudShips = loadTexture("./assets/textures/hud/ships.png");
        hudWave = loadTexture("./assets/textures/hud/wave.png");
        hudScore = loadTexture("./assets/textures/hud/score.png");

        // Background
        background_texture = loadTexture("./assets/textures/bg.png");
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

        expsprite = loadTexture("./assets/textures/explosion.png");

        laserblur = loadTexture("./assets/textures/laserblur.png");

        pause = loadTexture("./assets/textures/paused.png");
        game_over = loadTexture("./assets/textures/gameover.png");
        victory_screen = loadTexture("./assets/textures/youwin.png");

        logo = loadTexture("./assets/textures/spaceinvaders.png");
        press_start = loadTexture("./assets/textures/press_start.png");

        if (!(hudL || hudM || hudR || background_texture
                || player_texture ||alien_1_1 ||
                alien_1_2 || alien_2_1 ||
                alien_2_2 || alien_3_1 ||
                alien_3_2 || pause || game_over || victory_screen ||
                logo || press_start)) {
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
            if(!paused && !gameover && !victory && screen == 1)
                Adown = 1; // hold A key
        } else if (key == 'd' || key == 'D') {
            if(!paused && !gameover && !victory && screen == 1)
                Ddown = 1; // hold D key
        } else if (key == 'p' || key == 'P') {
            if (!gameover && !victory && screen == 1) {
                if(paused == 0)
                    paused = 1;
                else
                    paused = 0;
            }
        } else if (key == ' ') {
            if(screen == 0){
                Mix_PlayChannel(-1, coin, 0);
                screen = 1;
            } else if(screen == 1){
                if(!paused && !gameover && !victory && shoot_flag){
                    // PEW! PEW! play blaster audio
                    Mix_PlayChannel(-1, blaster2, 0);
                    // create new laser
                    if(shots_player == NULL) {
                        shots_player = (LASER **) malloc(sizeof(LASER *));
                    }
                    else {
                        shots_player = (LASER **) realloc(shots_player, sizeof(LASER *) * (shots_player_count + 1));
                    }
                    shootLaser_Player(shots_player, &shots_player_count, playerPosition);
                    if(!player->powerup) shoot_flag = 0;
                }
                else if(gameover || victory) {
                    resetGame();
                    screen = 0;
                }
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

/* ------------------------------- MECHANICS -------------------------------- */
void parallaxMotionY(){
    parallax_curYfg += parallax_speedY;
    parallax_curYbg += parallax_speedY/2;
    if(parallax_curYbg >= 2*VIEWPORT_Y + 200)
        parallax_curYbg = 0;
    if(parallax_curYfg >= 2*VIEWPORT_Y + 200)
        parallax_curYfg = 0;
}

void lasersMotionY() {
    /*--------------------LASER MOVEMENT--------------------*/
    // Player lasers Movement
    int i = 0;
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

/*--------------------DESTRUCTION--------------------*/

/*--------------------COLLISION CHECKING-------------------*/
void destroyDesallocLaser_Player(int i) {
    destroyLaser(shots_player[i]);
    int j = 0;
    for(j = i + 1; j < shots_player_count; j++) {
        shots_player[j - 1] = shots_player[j];
    }
    shots_player_count = shots_player_count - 1;
    shots_player = (LASER **) realloc(shots_player, sizeof(LASER *) * shots_player_count);
}

void destroyDesallocLaser_Enemy(int i) {
    destroyLaser(shots_enemy[i]);
    int j = 0;
    for(j = i + 1; j < shots_enemy_count; j++) {
        shots_enemy[j - 1] = shots_enemy[j];
    }
    shots_enemy_count = shots_enemy_count - 1;
    shots_enemy = (LASER **) realloc(shots_enemy, sizeof(LASER *) * shots_enemy_count);
}

void checkCollisions_Screen() {
    int i = 0, j = 0;
    // Player laser screen collision check
    for(i = 0; i < shots_player_count; i++) {
        // Check top boundary
        if(shots_player[i] != NULL && shots_player[i]->boundaryU >= 340) {
            destroyDesallocLaser_Player(i);
        }
    }

    // Enemy screen collision check
    for(i = 0; i < shots_enemy_count; i++) {
        // Check bottom boundary
        if(shots_enemy[i] != NULL && shots_enemy[i]->boundaryD <= -340) {
            destroyDesallocLaser_Enemy(i);
        }
    }
}

void checkCollisions_Player() {
    // player laser vs enemy
    int i = 0, j = 0;
    for (i = 0; i < shots_player_count; i++) {
        for (j = 0; j < TOTAL_ENEMIES; j++) {
            if (enemies != NULL) {
                if(enemies[j] != NULL){
                    if (enemies[j]->health > 0) {
                        // Check X boundaries
                        if (shots_player[i]->x[0] >= enemies[j]->boundaryL &&
                            shots_player[i]->x[2] <= enemies[j]->boundaryR) {
                            // Check Y boundaries
                            if (shots_player[i]->boundaryU <= enemies[j]->boundaryD && shots_player[i]->boundaryD >= enemies[j]->boundaryU) {
                                // HIT!
                                Mix_PlayChannel(-1, explosion, 0);
                                drawExplosion(shots_player[i]->x[0], shots_player[i]->boundaryU, 0);
                                destroyDesallocLaser_Player(i);
                                enemies[j]->health -= 1;
                                if (enemies[j]->health == 0) {
                                    switch(enemies[j]->shape) {
                                        case 1:
                                            player->score += 10; // update score
                                            break;
                                        case 2:
                                            player->score += 20; // update score
                                            break;
                                        case 3:
                                            player->score += 30; // update score
                                            break;
                                    }
                                    enemies_left -= 1; // one down, more to go
                                }
                                if(shots_player_count <= i){
                                    return;
                                }
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void checkCollisions_Enemy() {
    int i = 0, j = 0;
    /*--------------------ENEMY LASERS VS PLAYER--------------------*/
    for (i = 0; i < shots_enemy_count; i++) {
        if (shots_enemy[i]->x[0] >= player->boundaryL
            && shots_enemy[i]->x[2] <= player->boundaryR) {
            // Laser is aligned with player, check if hit
            if (shots_enemy[i]->boundaryD <= -200) {
                // Laser hit player!
                Mix_PlayChannel(-1, explosion, 0);
                drawExplosion(shots_enemy[i]->x[0], shots_enemy[i]->boundaryD, 0);
                killPlayer(player);
                destroyDesallocLaser_Enemy(i);
            }
        }
    }
    /*-------------------------END-------------------------*/

    /*--------------------ENEMY VS BASE--------------------*/
    i = 0;
    for (i = 0; i < TOTAL_ENEMIES; i++) {
        if(enemies){
            if(enemies[i]){
                if (enemies[i]->health > 0) {
                    if (enemies[i]->boundaryD <= -180) {
                            // Enemy hit base! Game Over!
                            gameover = 1;
                    }
                }
            }
        }
    }
    /*-------------------------END-------------------------*/
}

void checkCollisions() {
    /*--------------------PLAYER SHOTS--------------------*/
    // Refresh matrix for new object
    glLoadIdentity();

    checkCollisions_Screen();

    checkCollisions_Player();

    checkCollisions_Enemy();
}
/*--------------------COLLISION CHECKING-------------------*/

void checkGameOver() {
    if(player->health == 0) {
        Mix_PlayChannel(-1, lose, 0);
        powerup_flag = 0;
        gameover = 1;
    }
}

void checkLevelUp(){
    if (enemies_left == 0) {
        levelUp();
    }
}

void checkVictory() {
    if (level == 10 && enemies_left == 0) {
        victory = 1;
        Mix_PlayChannel(-1, fanfare, 0); // play fanfare
    }
}

void checkScore() {
    if (player->score > current_score) {
        Mix_PlayChannel(-1, coin, 0);
        current_score *= 2;
        player->health += 1;
    }
}
/* ------------------------------- MECHANICS -------------------------------- */

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
