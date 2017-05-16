#include "../includes/invaders.h"

/* -------------------------------- GLOBALS ----------------------------------- */
GLfloat playerSpeed = 3.5f; // player movement speed
GLfloat enemySpeed = 0; // enemy horizontal speed
GLfloat enemyApproach = 0; // enemy vertical speed (approaching player base)

/* -------------------------------- GLOBALS ----------------------------------- */

/* -------------------------------- PLAYER ----------------------------------- */
PLAYER* createPlayer() {
        PLAYER* player = (PLAYER*)malloc(sizeof(PLAYER));

        // Set coordinates
        player->x[0] = -28;
        player->x[1] = -28;
        player->x[2] = 28;
        player->x[3] = 28;
        player->y[0] = -28;
        player->y[1] = 28;
        player->y[2] = 28;
        player->y[3] = -28;

        player->pos_x = 0;
        // Player can take 3 hits
        player->health = 3;
        player->cooldown = 0;

        return player;
}

void drawPlayer(PLAYER* player) {
        Quadrilateral *playerSprite = createQuad();
            setQuadCoordinates(playerSprite,
            player->x[0], player->y[0],
            player->x[1], player->y[1],
            player->x[2], player->y[2],
            player->x[3], player->y[3]);
            setQuadTexture(playerSprite, player_texture);
            drawQuadTextured(playerSprite);
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

        // set enemy shape
        switch(design) {
                case 1:
                        // set enemy to shape 1
                        break;
                case 2:
                        // set enemy to shape 2
                        break;
                case 3:
                        // set enemy to shape 3
                        break;
        }

        // Reset variables
        enemy->pos_x = 0;
        enemy->pos_y = 0;
        enemy->health = 1;
        enemy->cooldown = 0;
        return enemy;
}
void destroyEnemy(ENEMY* enemy) {

}

/* -------------------------------- ENEMY ----------------------------------- */

/* -------------------------------- MOVEMENT -------------------------------- */
// Avoids player moving out of window
char checkBorders(GLfloat x) {
        if (x <= 0 || x >= VIEWPORT_X) {
                return 0;
        } else {
                return 1;
        }
}

// Move player left/right
void movePlayer(PLAYER* p, char direction) {
        //
        // TODO Felupio: translate when drawing the player (the matrix will be loaded there).
        // Use this function to increase velocity (checking for treshold).
        // Repeat for enemies and lasers
        //
    if (direction) {
        // MOVE RIGHT
        glTranslatef(playerSpeed, 0, 0);
        // p->x[0] += playerSpeed;
        // p->x[1] += playerSpeed;
        // p->x[2] += playerSpeed;
        // p->x[3] += playerSpeed;
    } else {
        // MOVE LEFT
        glTranslatef(-playerSpeed, 0, 0);
        // p->x[0] -= playerSpeed;
        // p->x[1] -= playerSpeed;
        // p->x[2] -= playerSpeed;
        // p->x[3] -= playerSpeed;
    }

}

void shootLaser(LASER** shots, int amount) {
        // Add laser to scene
        shots = (LASER**)realloc(shots, sizeof(shots) * amount + 1);
        shots[amount] = createLaser();




}

/* -------------------------------- MOVEMENT -------------------------------- */

/* -------------------------------- LASER ----------------------------------- */
LASER* createLaser() {
        LASER* laser = (LASER *) malloc(sizeof(*laser));

        laser->x[0] = 0;
        laser->x[1] = 0;
        laser->x[2] = 0;
        laser->x[3] = 0;

        laser->y[0] = 0;
        laser->y[1] = 0;
        laser->y[2] = 0;
        laser->y[3] = 0;

        laser->explosion = 0;

        return laser;
}

void destroyLaser(LASER* laser) {
        free(laser);
}
/* -------------------------------- LASER ----------------------------------- */
