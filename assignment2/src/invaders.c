#include "../includes/invaders.h"

/* ------------------------------- GLOBALS ---------------------------------- */
// Textures
GLuint laserblur;

// Game mechanics
// Amount of lasers on screen
int shots_player_count = 0;
int shots_enemy_count = 0;

// Current level
int level = 1;
int paused = 0;
int gameover = 0;

// Initialize external globals
GLfloat playerPosition = 0; // player position (x)
GLfloat playerSpeed = 7.0f; // player speed
GLfloat laserSpeed = 10.0f; // laser vertical speed
GLfloat enemyPositionX = 0; // enemy position (x)
GLfloat enemyPositionY = 0; // enemy position (y)
GLfloat enemySpeed = 0; // enemy horizontal speed
GLfloat enemyApproach = 0; // enemy vertical speed (approaching player base)
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
        player->boundary_left = -28;
        player->boundary_right = 28;

        // Player can take 3 hits
        player->health = 3;

        // Player score starts in 0
        player->score = 0;

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
        if (x <= -535|| x >= 535) {
                return 0;
        } else {
                return 1;
        }
}
/* ------------------------------- PLAYER ----------------------------------- */

/* ------------------------------- ENEMY ------------------------------------ */
/* ------ ENEMIES -----*/
ENEMY** enemies; // 25 enemies (5x5)

ENEMY* createEnemy(int design) {
        ENEMY* enemy = (ENEMY*)malloc(sizeof(ENEMY));

        // Set coordinates
        enemy->x[0] = 0;
        enemy->x[1] = 0;
        enemy->x[2] = 0;
        enemy->x[3] = 0;

        enemy->y[0] = 0;
        enemy->y[1] = 0;
        enemy->y[2] = 0;
        enemy->y[3] = 0;

        enemy->shape = 0;

        // Reset variables
        enemy->pos_x = 0;
        enemy->pos_y = 0;
        enemy->health = 1;
        enemy->cooldown = 0;
        return enemy;
}
void destroyEnemy(ENEMY* enemy) {
    free(enemy);
}

void drawEnemy(ENEMY* enemy) {
        glLoadIdentity(); // load matrix for new laser
        Quadrilateral *enemySprite = createQuad();
            setQuadCoordinates(enemySprite,
            enemy->x[0], enemy->y[0],
            enemy->x[1], enemy->y[1],
            enemy->x[2], enemy->y[2],
            enemy->x[3], enemy->y[3]); // initial coordinates
            glTranslatef(enemy->pos_x, enemy->pos_y, 0.0f); // move enemy
            drawQuadTextured(enemySprite); // draw enemy on screen
        freeQuad(enemySprite);
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

        laser->position = 0;
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

void destroyLaser(LASER* laser) {
        free(laser);
}
/* -------------------------------- LASER ----------------------------------- */

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
void saveGame() {

}

void resetGame(){
    // invaders.c variables
    playerPosition = 0;
    enemyPositionX = 0; // enemy position (x)
    enemyPositionY = 0; // enemy position (y)

    // scene.c variables
    destroyPlayer(player);
    player = createPlayer();

    int i = 0;
    if(enemies){
        for(i = 0; i < 25; i++){
            if(enemies[i]){
                destroyEnemy(enemies[i]);
            }
        }
    }

    i = 0;
    for(i = 0; i < shots_player_count; i++){
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

    shots_player_count = 0;
    shots_enemy_count = 0;

    level = 1;
    paused = 0;
    gameover = 0;
}
/* -------------------------------- GAME ------------------------------------ */
