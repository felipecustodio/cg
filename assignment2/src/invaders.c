#include "../includes/invaders.h"

/* -------------------------------- PLAYER ----------------------------------- */
PLAYER* createPlayer() {
        PLAYER* player = (PLAYER*)malloc(sizeof(PLAYER));
        // Set coordinates
        player->x[0] = 0;
        player->x[1] = 0;
        player->x[2] = 0;
        player->y[0] = 0;
        player->y[1] = 0;
        player->y[2] = 0;

        player->pos_x = 0;
        player->pos_y = 0;
        // Player can take 3 hits
        player->health = 3;
        player->cooldown = 0;

        return player;
}
void destroyPlayer(PLAYER* player) {

}
/* -------------------------------- PLAYER ----------------------------------- */

/* -------------------------------- ENEMY ----------------------------------- */
ENEMY* createEnemy(int design) {
        ENEMY* enemy = (ENEMY*)malloc(sizeof(ENEMY));

        // Set coordinates
        enemy->x[0] = 0;
        enemy->x[1] = 0;
        enemy->x[2] = 0;
        enemy->y[0] = 0;
        enemy->y[1] = 0;
        enemy->y[2] = 0;

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

        enemy->pos_x = 0;
        enemy->pos_y = 0;
        enemy->health = 1;
        enemy->cooldown = 0;
        return enemy;
}
void destroyEnemy(ENEMY* enemy) {

}

// Movement

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

/* -------------------------------- ENEMY ----------------------------------- */
