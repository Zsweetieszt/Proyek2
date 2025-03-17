#include "game.h"
#include "collision.h"
#include <stdbool.h>

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

    int monsterSize = MONSTER_SIZE;
    int playerSize = PLAYER_SIZE;

    // Cek tabrakan antara pemain dan monster
    if (playerX < screenMonsterX + monsterSize &&
        playerX + playerSize > screenMonsterX &&
        playerY < monsterY + monsterSize &&
        playerY + playerSize > monsterY) {
        
        if (hasStarPower) {
            // Jika dalam mode Star Power, bunuh monster dan tambah skor
            monsterX = -999999;  // Pindahkan monster keluar layar (anggap hilang)
            score += 15;       // Tambahkan skor sebanyak 15 poin
        } else {
            // Jika tidak punya Star Power, pemain mati
            isAlive = 0;
        }
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

void checkCollisionWithStar() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[level][i][j] == 5) {  // Jika ada Star Power (kode 5)
                int starX = j * (SCREEN_WIDTH / MAP_WIDTH) - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;
                int starY = i * (SCREEN_HEIGHT / MAP_HEIGHT);

                int starWidth = 40;  // Perbesar hitbox Star Power
                int starHeight = 40;
                int playerWidth = PLAYER_SIZE;
                int playerHeight = PLAYER_SIZE;

                // Cek apakah hitbox pemain bertabrakan dengan hitbox Star Power (AABB Collision)
                if (playerX < starX + starWidth &&
                    playerX + playerWidth > starX &&
                    playerY < starY + starHeight &&
                    playerY + playerHeight > starY) {
                    
                    hasStarPower = 1;  // Aktifkan Star Power
                    starPowerTimer = 300; // 300 frame (5 detik dalam game)
                    maps[level][i][j] = 0; // Hapus Star Power dari peta
                }
            }
        }
    }
}

void checkCollisionWithNextLevel() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[level][i][j] == 7) { // Jika blok ini adalah "Next Level"
                int nextX = j * (SCREEN_WIDTH / MAP_WIDTH) - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;
                int nextY = i * (SCREEN_HEIGHT / MAP_HEIGHT);

                int playerWidth = PLAYER_SIZE;
                int playerHeight = PLAYER_SIZE;
                int nextWidth = 32;
                int nextHeight = 32;

                if (playerX < nextX + nextWidth &&
                    playerX + playerWidth > nextX &&
                    playerY < nextY + nextHeight &&
                    playerY + playerHeight > nextY) {

                    level++;  // Pindah ke level berikutnya
                    if (level >= 3) {  // Jika sudah di level terakhir, kembali ke awal
                        level = 0;
                    }
                    playerX = 100; // Atur ulang posisi pemain
                    playerY = GROUND_HEIGHT - 30;
                    cameraX = 0;  // Reset kamera
                    cameraOffset = 0;
                }
            }
        }
    }
}

void cheakCollisionWithBlock(){
    
    // Cek apakah pemain bertabrakan dengan platform menggunakan AABB
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[level][i][j] == 1 || maps[level][i][j] == 2 || maps[level][i][j] == 8 || maps[level][i][j] == 11) {
                int platformX = j * (SCREEN_WIDTH / MAP_WIDTH) - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;
                int platformY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int platformWidth = SCREEN_WIDTH / MAP_WIDTH;
                int platformHeight = 40; // Tinggi platform diperbarui menjadi 40

                // Bounding box pemain (AABB)
                int playerLeft = playerX - PLAYER_SIZE;
                int playerRight = playerX + PLAYER_SIZE;
                int playerTop = playerY - PLAYER_SIZE;
                int playerBottom = playerY + PLAYER_SIZE;

                // Bounding box platform (AABB)
                int platformLeft = platformX;
                int platformRight = platformX + platformWidth;
                int platformTop = platformY;
                int platformBottom = platformY + platformHeight;

                /* Gambar hitbox pemain
                setcolor(RED);
                rectangle(playerLeft, playerTop, playerRight, playerBottom);

                // Gambar hitbox platform
                setcolor(GREEN);
                rectangle(platformLeft, platformTop, platformRight, platformBottom);
                    */
                // Deteksi tabrakan AABB
                bool collisionX = playerRight > platformLeft && playerLeft < platformRight;
                bool collisionY = playerBottom > platformTop && playerTop < platformBottom;

                if (collisionX && collisionY) {
                    // Cek tabrakan dari atas (agar pemain bisa berdiri di platform)
                    if (playerBottom > platformTop && playerTop < platformTop && velocityY >= 0) {
                        playerY = platformTop - PLAYER_SIZE;
                        velocityY = 0;
                        isJumping = 0;
                    }
                    // Cek tabrakan dari bawah
                    else if (playerTop < platformBottom && playerBottom > platformBottom && velocityY < 0) {
                        playerY = platformBottom + PLAYER_SIZE;
                        velocityY = 0;
                    }
                    // Cek tabrakan dari kiri (hanya jika pemain tidak sedang berdiri di atas platform)
                    if (playerRight > platformLeft && playerLeft < platformLeft && playerBottom > platformBottom) {
                        playerX = platformLeft - PLAYER_SIZE;
                    }
                    // Cek tabrakan dari kanan (hanya jika pemain tidak sedang berdiri di atas platform)
                    else if (playerLeft < platformRight && playerRight > platformRight && playerBottom > platformBottom) {
                        playerX = platformRight + PLAYER_SIZE;
                    }
                }
            }
        }
    }
}
