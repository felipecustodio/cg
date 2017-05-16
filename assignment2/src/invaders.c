#include "../includes/invaders.h"

/* -------------------------------- GLOBALS ----------------------------------- */
// Initialize external globals
GLfloat playerPosition = 0; // player horizontal speed
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
        player->y[0] = -28;
        player->y[1] = 28;
        player->y[2] = 28;
        player->y[3] = -28;

        // Set boundaries
        player->boundary_left = -28;
        player->boundary_right = 28;

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
            glTranslatef(playerPosition, 0.0f, 0.0f); // update/move coordinates if has speed
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
        printf("CHECKING %f\n", x);
        if (x <= -535|| x >= 535) {
                return 0;
        } else {
                return 1;
        }
}

// Action
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
