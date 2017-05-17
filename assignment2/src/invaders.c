#include "../includes/invaders.h"

/* -------------------------------- GLOBALS ----------------------------------- */
// Initialize external globals
GLfloat playerPosition = 0; // player position (x)
GLfloat laserSpeed = 3.0f; // laser vertical speed
GLfloat enemyPositionX = 0; // enemy position (x)
GLfloat enemyPositionY = 0; // enemy position (y)
GLfloat enemySpeed = 0; // enemy horizontal speed
GLfloat enemyApproach = 0; // enemy vertical speed (approaching player base)
/* -------------------------------- GLOBALS ----------------------------------- */

/* -------------------------------- PLAYER ----------------------------------- */
PLAYER* createPlayer() {

        // Allocate memory
        PLAYER* player = (PLAYER*)malloc(sizeof(PLAYER));

        // Set coordinates
        player->x[0] = -28;
        player->x[1] = -28;
        player->x[2] = 28;
        player->x[3] = 28;
        player->y[0] = -256;
        player->y[1] = -200;
        player->y[2] = -200;
        player->y[3] = -256;

        // Set boundaries
        player->boundary_left = -28;
        player->boundary_right = 28;

        // Gun is the center of the ship
        // where lasers will be shot from
        player->gun = -14;

        // Player can take 3 hits
        player->health = 3;

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
            // TODO use boundaries that move with the player
            drawQuadTextured(playerSprite); // draw player on screen
        freeQuad(playerSprite);
}

void destroyPlayer(PLAYER* player) {
        free(player);
}
/* -------------------------------- PLAYER ----------------------------------- */

/* -------------------------------- ENEMY ----------------------------------- */
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

}

// +--------------------------------------+
// |                                      |
// |                                      |
// XXXXX WORK IN PROGRESS XXXXXXXXXXXXXXXXX
// |                                      |
// |                                      |
// |                                      |
// +--------------------------------------+

// *********** going through some heavy work ********* !!!!! ******
// TODO: use texture switcher
// ********************************************
void drawEnemy(ENEMY* enemy) {
        Quadrilateral *enemySprite = createQuad();
            setQuadCoordinates(enemySprite,
            enemy->x[0], enemy->y[0],
            enemy->x[1], enemy->y[1],
            enemy->x[2], enemy->y[2],
            enemy->x[3], enemy->y[3]); // initial coordinates
            // TODO - para cada tipo de inimigo


            glTranslatef(enemyPositionX, enemyPositionY, 0.0f); // move enemy matrix
            // TODO use boundaries that move with the enemy
            drawQuadTextured(enemySprite); // draw enemy on screen
        freeQuad(enemySprite);
}


/* -------------------------------- ENEMY ----------------------------------- */

/* -------------------------------- MOVEMENT -------------------------------- */
// Avoids player moving out of window
char checkBorders(GLfloat x) {
        if (x <= -535|| x >= 535) {
                return 0;
        } else {
                return 1;
        }
}

// Action
void shootLaser(LASER** shots, int *amount, int playerX) {
        // Add laser to scene
        shots = (LASER **) realloc(shots, sizeof(LASER *) * (*amount) + 1);
        shots[(*amount)] = createLaser(playerX, -200);
        (*amount) = (*amount) + 1; // count ++
}

/* -------------------------------- MOVEMENT -------------------------------- */

/* -------------------------------- LASER ----------------------------------- */
LASER* createLaser(int x, int y) {
        LASER* laser = (LASER *) malloc(sizeof(LASER));

        laser->x[0] = x + 25;
        laser->x[1] = x + 25;
        laser->x[2] = x + 6 + 25;
        laser->x[3] = x + 6 + 25;

        laser->y[0] = y;
        laser->y[1] = y + 40;
        laser->y[2] = y + 40;
        laser->y[3] = y;

        laser->position = 0;
        laser->explosion = 0;

        return laser;
}

void drawLaser(LASER* laser) {
        Quadrilateral *laserSprite = createQuad();
            setQuadCoordinates(laserSprite,
            laser->x[0], laser->y[0],
            laser->x[1], laser->y[1],
            laser->x[2], laser->y[2],
            laser->x[3], laser->y[3]); // initial coordinates
            setQuadColor(laserSprite, 0.75f, 1.0f, 1.0f); // choose color
            glTranslatef(0.0f, laser->position, 0.0f); // move up while don't collide
            drawQuadFilled(laserSprite); // draw player on screen
        freeQuad(laserSprite);
}

void destroyLaser(LASER* laser) {
        free(laser);
}
/* -------------------------------- LASER ----------------------------------- */

/* -------------------------------- ANIMATIONS ----------------------------------- */
int switchTexture() {
        return 1;
}

/* -------------------------------- ANIMATIONS ----------------------------------- */

/* -------------------------------- GAME ----------------------------------- */
void saveGame() {
        // save point
}
void resetGame() {
        // pop matrix
}

/* -------------------------------- GAME ----------------------------------- */
