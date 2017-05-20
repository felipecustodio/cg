#include "../includes/invaders.h"

/* ------------------------------- GLOBALS ---------------------------------- */
// Game mechanics
// Amount of lasers on screen
int shots_player_count = 0;
int shots_enemy_count = 0;
int enemies_left = 25;

// Current level
int level = 1;
int paused = 0;
int gameover = 0;
int victory = 0;

// Initialize external globals
GLfloat playerPosition = 0; // player position (x)
GLfloat playerSpeed = 6.0f;
GLfloat enemyXSpeed = 1.0f;
GLfloat enemyYSpeed = 10.0f;
GLfloat laserSpeed = 10.0f; // laser vertical speed

GLfloat matrix_boundR;
GLfloat matrix_boundL;

const int WIDTH_ENEMY_MATRIX = 5;
const int HEIGHT_ENEMY_MATRIX = 5;
const int TOTAL_ENEMIES = 25;

/* ------------------------------- GLOBALS ---------------------------------- */

/* ------------------------------- PLAYER ----------------------------------- */
/* ------ THE PLAYER -----*/
PLAYER* player;

PLAYER* createPlayer() {

        // Allocate memory
        PLAYER* player = (PLAYER*)malloc(sizeof(PLAYER));

        // Set coordinates
        player->x[0] = -22;
        player->x[1] = -22;
        player->x[2] = 22;
        player->x[3] = 22;
        player->y[0] = -250;
        player->y[1] = -200;
        player->y[2] = -200;
        player->y[3] = -250;

        // Set boundaries
        player->boundaryL = -28;
        player->boundaryR = 28;

        // Player can take 3 hits
        player->health = 3;

        // Player score starts in 0
        player->score = 0;

        // Player starts without powerup
        player->powerup = 0;

        // Timer before shooting again
        player->cooldown = 0;

        return player;
}

void drawPlayer(PLAYER* player) {
        Quadrilateral *playerSprite = createQuad();
            setQuadCoordinates(playerSprite,
            player->x[0], player->y[0],
            player->x[1], player->y[1],
            player->x[2], player->y[2],
            player->x[3], player->y[3]); // initial coordinates
            setQuadTexture(playerSprite, player_texture); // choose texture
            glTranslatef(playerPosition, 0.0f, 0.0f); // move player matrix
            drawQuadTextured(playerSprite); // draw player on screen
        freeQuad(playerSprite);
}

void destroyPlayer(PLAYER* player) {
        free(player);
}

// Avoids player moving out of window
char checkBorders(GLfloat x) {
        if (x <= -535 || x >= 535) {
                return 0;
        } else {
                return 1;
        }
}
/* ------------------------------- PLAYER ----------------------------------- */

/* ------------------------------- ENEMY ------------------------------------ */

/* ------ ENEMIES -----*/
ENEMY** enemies; // 25 enemies (5x5)

ENEMY **createEnemyMatrix() {
    int i = 0;

    ENEMY** enemat = (ENEMY**) malloc(sizeof(ENEMY*) * TOTAL_ENEMIES);

    for (i = 0; i < TOTAL_ENEMIES; i++) {
        enemat[i] = createEnemy(i/WIDTH_ENEMY_MATRIX,
                    (i - (i / WIDTH_ENEMY_MATRIX) * WIDTH_ENEMY_MATRIX));
    }

    matrix_boundR = enemat[14]->boundaryR;
    matrix_boundL = enemat[10]->boundaryL;

    return enemat;
}

void destroyEnemyMatrix(ENEMY** enemat) {
    int i = 0;

    for (i = 0; i < TOTAL_ENEMIES; i++) {
        if(enemat[i])
            destroyEnemy(enemat[i]);
    }

    free(enemat);
    enemat = NULL;
}

ENEMY *createEnemy(int xindex, int yindex) {
        ENEMY *enemy = (ENEMY*) malloc(sizeof(ENEMY));

        // Set coordinates
        enemy->x[0] = -220 + (yindex * 100);
        enemy->x[1] = -220 + (yindex * 100);
        enemy->x[2] = -180 + (yindex * 100);
        enemy->x[3] = -180 + (yindex * 100);

        enemy->y[0] = 120 - (xindex * 60);
        enemy->y[1] = 160 - (xindex * 60);
        enemy->y[2] = 160 - (xindex * 60);
        enemy->y[3] = 120 - (xindex * 60);

        // Set enemy shapes for each line
        if (xindex == 3 || xindex == 4) {
            enemy->shape = 1;
            enemy->health = 1;
        }
        else if (xindex == 0) {
            enemy->shape = 3;
            enemy->health = 3;
        }
        else {
            enemy->shape = 2;
            enemy->health = 2;
        }

        // Set animation frame
        enemy->frame = 1;
        enemy->current_time = glutGet(GLUT_ELAPSED_TIME);

        // Set boundaries
        enemy->boundaryL = enemy->x[0]; // left
        enemy->boundaryR = enemy->x[2]; // right
        enemy->boundaryD = enemy->y[1] - 30; // down
        enemy->boundaryU = enemy->y[0] - 30; // up

        // Reset variables
        enemy->pos_x = 0;
        enemy->pos_y = 0;
        enemy->cooldown = 0;
}


void moveEnemies(ENEMY** enemies) {
    int i = 0;

    // Check if enemy matrix reached window border (right)
    if(enemyXSpeed > 0 && (!checkBorders(matrix_boundR))) {
        // reverse, move left
        enemyXSpeed = -enemyXSpeed;
        for (i = 0; i < TOTAL_ENEMIES; i++) {
            if(enemies[i]){
                if(enemies[i]->health > 0) {
                    enemies[i]->pos_y -= enemyYSpeed; // update position
                    enemies[i]->boundaryD -= enemyYSpeed; // move boundary
                    enemies[i]->boundaryU -= enemyYSpeed; // move boundary
                }
            }
        }
    }

    i = 0;
    // Check if enemy matrix reached window border (left)
    if(enemyXSpeed < 0 && (!checkBorders(matrix_boundL))) {
        // reverse, move right
        enemyXSpeed = -enemyXSpeed;
        for (i = 0; i < TOTAL_ENEMIES; i++) {
            if(enemies[i]){
                if(enemies[i]->health > 0) {
                    enemies[i]->pos_y -= enemyYSpeed; // update position
                    enemies[i]->boundaryD -= enemyYSpeed; // move boundary
                    enemies[i]->boundaryU -= enemyYSpeed; // move boundary
                }
            }
        }
    }

    i = 0;
    // Update positions
    for (i = 0; i < TOTAL_ENEMIES; i++) {
        if(enemies[i]){
            if (enemies[i]->health > 0) {
                enemies[i]->pos_x += enemyXSpeed; // move enemy
                enemies[i]->boundaryL += enemyXSpeed; // move boundary
                enemies[i]->boundaryR += enemyXSpeed; // move boundary
            }
        }
    }

    matrix_boundL += enemyXSpeed;
    matrix_boundR += enemyXSpeed;
}

int changeFrame(int value) {
        switch(value) {
                case 1:
                        return 2;
                case 2:
                        return 1;
        }
}

void drawEnemy(ENEMY* enemy) {
        glLoadIdentity(); // load matrix for new enemy
        Quadrilateral *enemySprite = createQuad();
            setQuadCoordinates(enemySprite,
            enemy->x[0], enemy->y[0],
            enemy->x[1], enemy->y[1],
            enemy->x[2], enemy->y[2],
            enemy->x[3], enemy->y[3]); // initial coordinates

            // Change enemy animation frame every 500 ms
            int random = rand() % 20; // 0 to 19
            GLfloat time = glutGet(GLUT_ELAPSED_TIME);
            if (enemy->current_time - time < -500) {
                    // change animation frame
                    if (random <= 14) enemy->frame = changeFrame(enemy->frame); // only change when random <= 14
                    enemy->current_time = time;
            }

            // change color according to health
            switch(enemy->shape) {
                    case 3:
                        if (enemy->health == 2) {
                                setQuadColor(enemySprite, 0.96, 0.83, 0.25); // yellow
                        } else if (enemy->health == 1) {
                                setQuadColor(enemySprite, 0.91, 0.22, 0.22); // red
                        }
                        break;
                    case 2:
                    if (enemy->health == 1) {
                            setQuadColor(enemySprite, 0.91, 0.22, 0.22); // red
                    }
            }

            // set enemy shape
            switch(enemy->shape) {
                    case 1:
                            // Set texture
                            if (enemy->frame == 1) setQuadTexture(enemySprite, alien_1_1);
                            if (enemy->frame == 2) setQuadTexture(enemySprite, alien_1_2);
                            break;
                    case 2:
                            if (enemy->frame == 1) setQuadTexture(enemySprite, alien_2_1);
                            if (enemy->frame == 2) setQuadTexture(enemySprite, alien_2_2);
                            break;
                    case 3:
                            if (enemy->frame == 1) setQuadTexture(enemySprite, alien_3_1);
                            if (enemy->frame == 2) setQuadTexture(enemySprite, alien_3_2);
                            break;
            }

            glTranslatef(enemy->pos_x, enemy->pos_y, 0.0f); // move enemy
            drawQuadTextured(enemySprite); // draw enemy on screen
        freeQuad(enemySprite);
}

void destroyEnemy(ENEMY *enemy) {
    if(enemy) free(enemy);
}

/* ------------------------------- ENEMY ------------------------------------ */

/* ------------------------------- LASER ------------------------------------ */
// Lasers that exist
LASER** shots_player;
LASER** shots_enemy;

LASER* createLaser(int x, int y, int color) {
        LASER* laser = (LASER *) malloc(sizeof(LASER));

        laser->x[0] = x - 3;
        laser->x[1] = x - 3;
        laser->x[2] = x + 5 - 3;
        laser->x[3] = x + 5 - 3;

        laser->y[0] = y;
        laser->y[1] = y + 30;
        laser->y[2] = y + 30;
        laser->y[3] = y;

        // movement
        laser->position = 0;
        // boundaries
        laser->boundaryU = laser->y[1];
        laser->boundaryD = laser->y[0];

        laser->color = color;
        laser->explosion = 0;

        return laser;
}

void shootLaser_Player(LASER** shots, int *amount, int x) {
        // Add laser to scene
        shots[(*amount)] = createLaser(x, -200, 0);
        (*amount) = (*amount) + 1;
}

void shootLaser_Enemy(LASER** shots, int *amount, int x, int y) {
        // Add laser to scene
        shots[(*amount)] = createLaser(x, y, 1);
        (*amount) = (*amount) + 1;
}

void drawLaser(LASER* laser) {
        if (laser->explosion == 1) return;
        glLoadIdentity(); // load matrix for new laser
        Quadrilateral *laserSprite = createQuad();
            setQuadCoordinates(laserSprite,
            laser->x[0], laser->y[0],
            laser->x[1], laser->y[1],
            laser->x[2], laser->y[2],
            laser->x[3], laser->y[3]); // initial coordinates
            setQuadTexture(laserSprite, laserblur);
            switch(laser->color) {
                    case 0:
                        setQuadColor(laserSprite, 0.75f, 1.0f, 1.0f); // player laser = blue
                        break;
                    case 1:
                        setQuadColor(laserSprite, 0.88f, 0.2f, 0.2f); // enemy laser = red
                        break;
            }
            glTranslatef(0.0f, laser->position, 0.0f); // move laser
            drawQuadFilled(laserSprite); // draw player on screen
            setQuadCoordinates(laserSprite,
            laser->x[0] - 8, laser->y[0] - 8,
            laser->x[1] - 8, laser->y[1] + 8,
            laser->x[2] + 8, laser->y[2] + 8,
            laser->x[3] + 8, laser->y[3] - 8); // initial coordinates
            drawQuadTextured(laserSprite);
        freeQuad(laserSprite);
}

void destroyLaser(LASER *laser) {
    if(laser) free(laser);
}
/* -------------------------------- LASER ----------------------------------- */

/* ----------------------------- EXPLOSION ---------------------------------- */
void drawExplosion(float x, float y, int color){
    glLoadIdentity();
    Quadrilateral *expSprite = createQuad();
        setQuadCoordinates(expSprite,
            -30, -20,
            -30, 20,
            30, 20,
            30, -20); // initial coordinates
        setQuadTexture(expSprite, expsprite);
        switch(color) {
                case 0:
                    setQuadColor(expSprite, 0.75f, 1.0f, 1.0f); // player laser = blue
                    break;
                case 1:
                    setQuadColor(expSprite, 0.88f, 0.2f, 0.2f); // enemy laser = red
                    break;
        }
        glTranslatef(x, y, 0.0f);
        drawQuadTextured(expSprite);
    freeQuad(expSprite);
}
/* ----------------------------- EXPLOSION ---------------------------------- */

/* ----------------------------- ANIMATIONS --------------------------------- */
// Change animation frame
int switchTexture(int frame) {
        switch(frame) {
                case 1:
                        frame = 2;
                        break;
                case 2:
                        frame = 1;
                        break;
        }
        return frame;
}
/* ----------------------------- ANIMATIONS --------------------------------- */

/* -------------------------------- GAME ------------------------------------ */
void levelUp(){
    level += 1;
    enemyXSpeed = level;
    enemies_left = 25;

    destroyEnemyMatrix(enemies);
    enemies = createEnemyMatrix();
}

void saveGame() {

}

void resetGame() {
    // invaders.c variables
    shots_player_count = 0;
    shots_enemy_count = 0;
    enemies_left = 25;

    level = 1;
    paused = 0;
    gameover = 0;
    victory = 0;

    playerPosition = 0;
    enemyXSpeed = 1.0f;

    // scene.c variables
    destroyPlayer(player);
    player = createPlayer();

    destroyEnemyMatrix(enemies);
    enemies = createEnemyMatrix();

    int i = 0;
    for(i = 0; i < shots_player_count; i++) {
        destroyLaser(shots_player[i]);
    }
    free(shots_player);
    shots_player = NULL;

    i = 0;
    for(i = 0; i < shots_enemy_count; i++){
        destroyLaser(shots_enemy[i]);
    }
    free(shots_enemy);
    shots_enemy = NULL;
}
/* -------------------------------- GAME ------------------------------------ */
