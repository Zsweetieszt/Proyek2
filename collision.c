#include "game.h"
#include "collision.h"
#include <stdbool.h>

void drawHitbox(int left, int top, int right, int bottom, int color) {
    setcolor(color);
    rectangle(left, top, right, bottom);
}
// Fungsi untuk mendeteksi tabrakan dengan duri
void checkCollisionWithSpike() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[level][i][j] == SPIKE) {
                int spikeX = j * (SCREEN_WIDTH / MAP_WIDTH) - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;
                int spikeY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int spikeWidth = SCREEN_WIDTH / MAP_WIDTH;
                int spikeHeight = 20; // Sesuaikan tinggi spike

                // Fokus hanya pada bagian bawah spike
                int spikeTop = spikeY + 20;
                int spikeBottom = spikeY + 40; 

                // Hitbox Mario (gunakan konstanta)
                int playerLeft = playerX - (COLS / 2)+20;
                int playerRight = playerX + (COLS / 2)+10;
                int playerTop = playerY - ROWS;
                int playerBottom = playerY;

                // Hitbox Spike (hanya setengah bagian bawah)
                int spikeLeft = spikeX;
                int spikeRight = spikeX + spikeWidth;

                //drawHitbox(spikeLeft, spikeTop, spikeRight, spikeBottom, RED);   // Hitbox Spike (Merah)
               // drawHitbox(playerLeft, playerTop, playerRight, playerBottom, BLUE); // Hitbox Mario (Biru)

                // Deteksi tabrakan menggunakan AABB
                if (spikeX + spikeWidth > 0 && spikeX < SCREEN_WIDTH) {
                    if (playerRight > spikeLeft && playerLeft < spikeRight &&
                        playerBottom > spikeTop && playerTop < spikeBottom) {
                        
                        playerLives--; // Kurangi nyawa Mario
                        
                        if (playerLives <= 0) {
                            isAlive = 0;// Mario benar-benar mati jika nyawa habis
                        } else {
                            // Reset posisi Mario ke titik aman setelah kena spike
                            findMarioStartPosition();
                        }

                    }
                }
            }
        }
    }
}


// Fungsi untuk mendeteksi tabrakan dengan monster
void checkCollisionWithMonster() {
    for (int i = 0; i < totalMonsters; i++) {
        int screenMonsterX = monsterX[i] - (cameraX * (SCREEN_WIDTH / MAP_WIDTH)) - cameraOffset;
        int monsterHitboxLeft   = screenMonsterX - 25;
        int monsterHitboxRight  = screenMonsterX + MONSTER_SIZE + 25;
        int monsterHitboxTop    = monsterY[i] - 20;
        int monsterHitboxBottom = monsterY[i] + MONSTER_SIZE + 20;

        int playerHitboxLeft   = playerX + 20;
        int playerHitboxRight  = playerX + COLS + 4;
        int playerHitboxTop    = playerY - 4;
        int playerHitboxBottom = playerY;

        if (playerHitboxRight > monsterHitboxLeft &&
            playerHitboxLeft < monsterHitboxRight &&
            playerHitboxBottom > monsterHitboxTop &&
            playerHitboxTop < monsterHitboxBottom) {

            if (hasStarPower) {
                // **1. Pindahkan monster ke luar layar**
                monsterX[i] = -9999;
                monsterY[i] = -9999;
                monsterDirection[i] = 0;  

                // **2. Hapus dari array peta**
                for (int row = 0; row < MAP_HEIGHT; row++) {
                    for (int col = 0; col < TOTAL_MAP_WIDTH; col++) {
                        if (maps[level][row][col] == 4) {
                            maps[level][row][col] = 0;  // Ubah jadi kosong
                            break;  // Keluar dari loop setelah menemukan satu monster
                        }
                    }
                }

                score += 15;
            } else {
                playerLives--;
                if (playerLives > 0) {  
                    findMarioStartPosition();  
                } else {
                    isAlive = 0;
                }
            }
        }
    }
}







void checkCollisionWithCoin() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[level][i][j] == 3) {  // Jika ada koin di posisi ini
                int coinX = j * (SCREEN_WIDTH / MAP_WIDTH) - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;
                int coinY = i * (SCREEN_HEIGHT / MAP_HEIGHT);

                int coinWidth = 50;  // Lebarkan hitbox koin
                int coinHeight = 50; // Tinggikan hitbox koin
                int playerWidth = PLAYER_SIZE;
                int playerHeight = PLAYER_SIZE;

                // Cek apakah hitbox pemain bertabrakan dengan hitbox koin (AABB Collision)
                if (playerX < coinX + coinWidth &&
                    playerX + playerWidth > coinX &&
                    playerY < coinY + coinHeight &&
                    playerY + playerHeight > coinY) {
                    
                    coins++;     // Tambah jumlah koin yang dikumpulkan
                    score += 10; // Tambah skor pemain
                    maps[level][i][j] =20;  // Hapus koin dari peta
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

                int starWidth = 50;  // Perbesar hitbox Star Power
                int starHeight = 50;
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
                int nextWidth = 50;
                int nextHeight = 50;

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
    
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[level][i][j] == 1 || maps[level][i][j] == 2 || maps[level][i][j] == 8 || maps[level][i][j] == 11|| maps[level][i][j] == 13) {
                int platformX = j * (SCREEN_WIDTH / MAP_WIDTH) - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;
                int platformY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int platformWidth = SCREEN_WIDTH / MAP_WIDTH;
                int platformHeight = 40; // Tinggi platform tetap 40

                // Bounding box pemain (AABB) dengan ukuran Mario (25x35)
                int playerLeft = playerX - (COLS / 2)+10;
                int playerRight = playerX + (COLS / 2)+10;
                int playerTop = playerY - ROWS;
                int playerBottom = playerY +5;

                // Sesuaikan agar hitbox benar-benar berada di tengah sprite
                int hitboxX = playerX - (COLS/ 2) + (ROWS / 4);
                int hitboxY = playerY - COLS;

                // Bounding box platform (AABB)
                int platformLeft = platformX;
                int platformRight = platformX + platformWidth;
                int platformTop = platformY;
                int platformBottom = platformY + platformHeight;

                /* Gambar hitbox pemain
                setcolor(RED);
                rectangle(hitboxX, hitboxY, hitboxX + 25, hitboxY + 35+5 );

                // Gambar hitbox platform
                setcolor(GREEN);
                rectangle(platformLeft, platformTop, platformRight, platformBottom);*/

                // Deteksi tabrakan AABB
                bool collisionX = playerRight > platformLeft && playerLeft < platformRight;
                bool collisionY = playerBottom > platformTop && playerTop < platformBottom;


                if (collisionX && collisionY) {
                    // Cek tabrakan dari atas (agar pemain bisa berdiri di platform)
                    if (playerBottom > platformTop && playerTop < platformTop+ 2  && velocityY >= 0) {
                        playerY = platformTop;
                        velocityY = 0;
                        isJumping = 0;
                        continue;
                    }
                    // Cek tabrakan dari bawah
                    else if (playerTop < platformBottom && playerBottom > platformBottom && velocityY < 0) {
                        playerY = platformBottom + ROWS;
                        velocityY = 0;
                    }
                    // Cek tabrakan dari kiri (hanya jika pemain tidak sedang berdiri di atas platform)
                    else if(collisionX && playerRight > platformLeft && playerLeft < platformLeft && playerBottom > platformTop) {
                        playerX = platformLeft - (COLS / 2)-12;
                    }
                    // Cek tabrakan dari kanan (hanya jika pemain sejajar dengan platform, tidak berdiri di atasnya)
                    else if (collisionX && playerLeft < platformRight && playerRight > platformRight && playerBottom > platformTop) {
                        playerX = platformRight + (COLS / 2)-10;
                    }
                }
            }
        }
    }
    
}

// Fungsi mengecek tabrakan dengan bendera
int checkCollisionWithFlag() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[level][i][j] == 14) { // 14 adalah kode bendera
                int poleX = j * (SCREEN_WIDTH / MAP_WIDTH) - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;
                int poleY = i * (SCREEN_HEIGHT / MAP_HEIGHT) - 300; // Tiang tinggi 300 px

                // Hitbox Tiang Bendera
                int poleLeft = poleX+20;
                int poleRight = poleX+30;
                int poleTop = poleY +20;
                int poleBottom = poleY + 340;

                // Hitbox Mario
                int playerLeft = playerX - (COLS / 2)+20;
                int playerRight = playerX + (COLS / 2)+10;
                int playerTop = playerY - ROWS;
                int playerBottom = playerY;

                // Gambar hitbox untuk debugging
                drawHitbox(poleLeft, poleTop, poleRight, poleBottom, GREEN);  // Tiang bendera (Hijau)
                drawHitbox(playerLeft, playerTop, playerRight, playerBottom, BLUE); // Mario (Biru)

                // Deteksi tabrakan dengan tiang (bukan kain bendera)
                if (playerRight > poleLeft && playerLeft < poleRight &&
                    playerBottom > poleTop && playerTop < poleBottom) {
                    score+=100;
                    hasWon = 1; // Mario menang
                    return hasWon; // Kembalikan nilai kemenangan
                }
            }
        }
    }
}