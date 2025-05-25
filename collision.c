#include "game.h"
#include "collision.h"
#include <stdbool.h>
#include "player.h"

void drawHitbox(int left, int top, int right, int bottom, int color)
{
    setcolor(color);
    rectangle(left, top, right, bottom);
}

bool checkCollisionWithSpike(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++){
            if (maps[gameState.level][i][j] == SPIKE){
                int spikeX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int spikeY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int spikeWidth = SCREEN_WIDTH / MAP_WIDTH;
                int spikeHeight = 20;

                int spikeTop = spikeY + 20;
                int spikeBottom = spikeY + 40;

                int spikeLeft = spikeX;
                int spikeRight = spikeX + spikeWidth;

                updatePlayerBounds();

                if (spikeX + spikeWidth > 0 && spikeX < SCREEN_WIDTH){
                    if (playerRight > spikeLeft && playerLeft < spikeRight &&
                        playerBottom > spikeTop && playerTop < spikeBottom){

                        return true;
                    }
                }
            }
        }
    }
    return false;
}

int checkCollisionWithMonster(){
    for (int i = 0; i < monsterCount; i++){
        int screenMonsterX = monsters[i].x - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
        int screenMonsterY = monsters[i].y;

        int monsterSize = MONSTER_SIZE;
        int monsterLeft = screenMonsterX - 20;
        int monsterRight = screenMonsterX + monsterSize;
        int monsterTop = screenMonsterY - 10;
        int monsterBottom = screenMonsterY + monsterSize;

        updatePlayerBounds();

        if (playerRight > monsterLeft && playerLeft < monsterRight &&
            playerBottom > monsterTop && playerTop < monsterBottom){
           return i;
        }
    }
    return -1;
}

bool checkCollisionWithCoin(){
    bool coinCollected = false;
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++){
            if (maps[gameState.level][i][j] == 3){
                int coinX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int coinY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int coinWidth = 25;
                int coinHeight = 25;

                int coinLeft = coinX + 10;
                int coinRight = coinX + coinWidth;
                int coinTop = coinY;
                int coinBottom = coinY + coinHeight;

                updatePlayerBounds();
                //setcolor(GREEN);
                //rectangle(coinLeft, coinTop, coinRight, coinBottom);

                if (playerRight > coinLeft && playerLeft < coinRight &&
                    playerBottom > coinTop && playerTop < coinBottom){

                    maps[gameState.level][i][j] = 20;
                    coinCollected = true;
                }
            }
        }
    }

    return coinCollected;
}

bool checkCollisionWithStar(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++){
            if (maps[gameState.level][i][j] == 5){
                int starX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int starY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int starWidth = 25;
                int starHeight = 25;

                int starLeft = starX;
                int starRight = starX + starWidth + 10;
                int starTop = starY;
                int starBottom = starY + starHeight + 5;

                updatePlayerBounds();

                if (playerRight > starLeft && playerLeft < starRight &&
                    playerBottom > starTop && playerTop < starBottom){
                        maps[gameState.level][i][j] = 21;
                        return true;
                }
            }
        }
    }
    return false;
}

bool checkCollisionWithNextLevel(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++){
            if (maps[gameState.level][i][j] == 7){
                int nextX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int nextY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int nextWidth = SCREEN_WIDTH / MAP_WIDTH;
                int nextHeight = SCREEN_HEIGHT / MAP_HEIGHT;

                int nextLeft = nextX;
                int nextRight = nextX + nextWidth;
                int nextTop = nextY;
                int nextBottom = nextY + nextHeight;

                updatePlayerBounds();

                if (playerRight > nextLeft && playerLeft < nextRight &&
                    playerBottom > nextTop && playerTop < nextBottom){
                    return true;
                }
            }
        }
    }
    return false;
}

void cheakCollisionWithBlock(){ 
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[gameState.level][i][j] == 1 || maps[gameState.level][i][j] == 2 || 
                maps[gameState.level][i][j] == 8 || maps[gameState.level][i][j] == 11 || 
                maps[gameState.level][i][j] == 13) {
                
                int platformX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int platformY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int platformWidth = SCREEN_WIDTH / MAP_WIDTH;
                int platformHeight = 40;

                updatePlayerBounds();

                int hitboxX = player.x - (COLS / 2) + (ROWS / 4);
                int hitboxY = player.y - COLS;

                int platformLeft = platformX;
                int platformRight = platformX + platformWidth;
                int platformTop = platformY - 28;
                int platformBottom = platformY + platformHeight+20;

                // Debug hitbox
                //setcolor(RED);
                //drawHitbox(playerLeft, playerTop, playerRight, playerBottom, BLUE); 
                //setcolor(GREEN);
                //rectangle(platformLeft, platformTop, platformRight, platformBottom);

                bool collisionX = playerRight > platformLeft && playerLeft < platformRight;
                bool collisionY = playerBottom > platformTop && playerTop < platformBottom;

                if (collisionX && collisionY) {
                    // Dari atas platform
                    if (playerBottom > platformTop && playerTop < platformTop + 2 && player.velocityY >= 0) {
                        player.y = platformTop;
                        player.velocityY = 0;
                        player.isJumping = 0;
                        continue;
                    }
                    // Dari bawah platform
                    else if (playerTop < platformBottom && playerBottom > platformBottom && player.velocityY < 0) {
                        player.y = platformBottom + ROWS;
                        player.velocityY = 0;
                    }
                    // Dari kiri platform (menabrak sisi kiri blok)
                    else if(collisionX && playerRight > platformLeft && playerLeft < platformLeft && playerBottom > platformTop) {
                        player.x = platformLeft-40;
                    }
                    // Dari kanan platform (menabrak sisi kanan blok)
                    else if (playerLeft < platformRight && playerRight > platformRight && playerBottom > platformTop) {
                        player.x = platformRight + (COLS / 2);
                    }
                }
            }
        }
    }
}


bool checkCollisionWithFlag(){
    for (int i = 0; i < MAP_HEIGHT; i++){
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++){
            if (maps[gameState.level][i][j] == 14){
                int poleX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int poleY = i * (SCREEN_HEIGHT / MAP_HEIGHT) - 300;

                int poleLeft = poleX + 20;
                int poleRight = poleX + 30;
                int poleTop = poleY + 200;
                int poleBottom = poleY + 500;

                updatePlayerBounds();

                // Gambar hitbox untuk debugging
                //drawHitbox(poleLeft, poleTop, poleRight, poleBottom, GREEN);
                //drawHitbox(playerLeft, playerTop, playerRight, playerBottom, BLUE); 

                if (playerRight > poleLeft && playerLeft < poleRight &&
                    playerBottom > poleTop && playerTop < poleBottom){
                    return true;
                }
            }
        }
    }
    return false;
}