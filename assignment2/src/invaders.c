#include "../includes/invaders.h"

/* -------------------------------- PLAYER ----------------------------------- */
PLAYER* createPlayer() {
        PLAYER* player = (PLAYER*)malloc(sizeof(PLAYER));

        // Set coordinates
        player->x[0] = 0;
        player->x[1] = 0;
        player->x[2] = 0;
        player->x[3] = 0;

        player->y[0] = 0;
        player->y[1] = 0;
        player->y[2] = 0;
        player->y[3] = 0;

        player->pos_x = 0;
        player->pos_y = 0;
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
        GLfloat current_pos = p->pos_x;
        if (direction) {
                // MOVE RIGHT
        } else {
                // MOVE LEFT
        }

        if (!checkBorders(p->pos_x)) {
                p->pos_x = current_pos;
        }
}

void shootLaser(LASER** shots, int ammount) {
        shots = (LASER**)realloc(shots, sizeof(shots) * ammount + 1);



}

/* -------------------------------- MOVEMENT -------------------------------- */

/* -------------------------------- LASER ----------------------------------- */
LASER* createLaser() {
        LASER* laser = malloc(sizeof(*laser));

        laser->x[0] = 0;
        laser->x[1] = 0;
        laser->x[2] = 0;
        laser->x[3] = 0;

        laser->y[0] = 0;
        laser->y[1] = 0;
        laser->y[2] = 0;
        laser->y[3] = 0;

        laser->explosion = 0;
}

void destroyLaser(LASER* laser) {
        free(laser);
}
/* -------------------------------- LASER ----------------------------------- */
