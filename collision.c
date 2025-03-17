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

void checkCollisionWithCoin() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[level][i][j] == 3) {  // Jika ada koin di posisi ini
                int coinX = j * (SCREEN_WIDTH / MAP_WIDTH) - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;
                int coinY = i * (SCREEN_HEIGHT / MAP_HEIGHT);

                int coinWidth = 30;  // Lebarkan hitbox koin
                int coinHeight = 30; // Tinggikan hitbox koin
                int playerWidth = PLAYER_SIZE;
                int playerHeight = PLAYER_SIZE;

                // Cek apakah hitbox pemain bertabrakan dengan hitbox koin (AABB Collision)
                if (playerX < coinX + coinWidth &&
                    playerX + playerWidth > coinX &&
                    playerY < coinY + coinHeight &&
                    playerY + playerHeight > coinY) {
                    
                    coins++;     // Tambah jumlah koin yang dikumpulkan
                    score += 10; // Tambah skor pemain
                    maps[level][i][j] = 0;  // Hapus koin dari peta
                }
            }
        }
    }
}

