#include "game.h"
#include "collision.h"

// Fungsi untuk mendeteksi tabrakan dengan duri
void checkCollisionWithSpike() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (maps[level][i][j] == SPIKE) {
                int spikeX = j * (SCREEN_WIDTH / MAP_WIDTH) + 10;
                int spikeY = i * (SCREEN_HEIGHT / MAP_HEIGHT) + 100;

                int dx = playerX - spikeX;
                int dy = playerY - spikeY;
                int distance = sqrt(dx * dx + dy * dy);

                if (distance < PLAYER_SIZE + 17) {
                    isAlive = 0;
                }
            }
        }
    }
}

// Fungsi untuk mendeteksi tabrakan dengan monster
void checkCollisionWithMonster() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (maps[level][i][j] == 4) {
                int monsterX = j * (SCREEN_WIDTH / MAP_WIDTH) + 20;
                int monsterY = i * (SCREEN_HEIGHT / MAP_HEIGHT) + 20;

                int dx = playerX - monsterX;
                int dy = playerY - monsterY;
                int distance = sqrt(dx * dx + dy * dy);

                if (distance < PLAYER_SIZE + MONSTER_SIZE) {
                    isAlive = 0;
                }
            }
        }
    }
}

