#include "game.h"
#include "collision.h"

// Fungsi untuk mendeteksi tabrakan dengan duri
void checkCollisionWithSpike() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[level][i][j] == SPIKE) {
                int spikeX = j * (SCREEN_WIDTH / MAP_WIDTH) + 10 - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;
                int spikeY = i * (SCREEN_HEIGHT / MAP_HEIGHT) + 50;

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
    int screenMonsterX = monsterX - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;

    int dx = playerX - screenMonsterX;
    int dy = playerY - monsterY;
    int distance = sqrt(dx * dx + dy * dy);

    if (distance < PLAYER_SIZE + MONSTER_SIZE) {
        isAlive = 0;  // Game over jika kena monster
    }
}



