#include "game.h"
#include "collision.h"
#include <stdbool.h>

void drawHitbox(int left, int top, int right, int bottom, int color) {
    setcolor(color);
    rectangle(left, top, right, bottom);
}
// Fungsi untuk mendeteksi tabrakan dengan duri
int checkCollisionWithSpike() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[gameState.level][i][j] == SPIKE) {
                int spikeX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int spikeY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int spikeWidth = SCREEN_WIDTH / MAP_WIDTH;
                int spikeHeight = 20; // Sesuaikan tinggi spike

                // Fokus hanya pada bagian bawah spike
                int spikeTop = spikeY + 20;
                int spikeBottom = spikeY + 40; 

                // Hitbox Mario (gunakan konstanta)
                int playerLeft = player.x - (COLS / 2)+20;
                int playerRight = player.x + (COLS / 2)+10;
                int playerTop = player.y - ROWS-10;
                int playerBottom = player.y;

                // Hitbox Spike (hanya setengah bagian bawah)
                int spikeLeft = spikeX;
                int spikeRight = spikeX + spikeWidth;

                //drawHitbox(spikeLeft, spikeTop, spikeRight, spikeBottom, RED);   // Hitbox Spike (Merah)
               // drawHitbox(playerLeft, playerTop, playerRight, playerBottom, BLUE); // Hitbox Mario (Biru)

                // Deteksi tabrakan menggunakan AABB
                if (spikeX + spikeWidth > 0 && spikeX < SCREEN_WIDTH) {
                    if (playerRight > spikeLeft && playerLeft < spikeRight &&
                        playerBottom > spikeTop && playerTop < spikeBottom) {
                        
                        player.playerLives--; // Kurangi nyawa Mario
                        
                        if (player.playerLives <= 0) {
                            gameState.isAlive = 0;// Mario benar-benar mati jika nyawa habis
                        } else {
                            // Reset posisi Mario ke titik aman setelah kena spike
                            findMarioStartPosition();
                        }
                        return gameState.isAlive;
                    }
                }
            }
        }
    }
}


// Fungsi untuk mendeteksi tabrakan dengan monstervoid checkCollisionWithMonster() {
int checkCollisionWithMonster() {
        for (int i = 0; i < monsterCount; i++) {  // Loop untuk semua monster dalam level
            int screenMonsterX = monsters[i].x - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
            int screenMonsterY = monsters[i].y;
    
            int monsterSize = MONSTER_SIZE;
    
            // Hitbox Monster (menggunakan logika seperti spike)
            int monsterLeft   = screenMonsterX-20;
            int monsterRight  = screenMonsterX + monsterSize;
            int monsterTop    = screenMonsterY-10;
            int monsterBottom = screenMonsterY + monsterSize;
    
            // Hitbox Pemain (Mario)
            int playerLeft = player.x - (COLS / 2)+20;
            int playerRight = player.x + (COLS / 2)+10;
            int playerTop = player.y - ROWS-10;
            int playerBottom = player.y;
            //drawHitbox(monsterLeft, monsterTop, monsterRight, monsterBottom, RED);   // Hitbox monster (Merah)
             //drawHitbox(playerLeft, playerTop, playerRight, playerBottom, BLUE); // Hitbox Mario (Biru)
    
            // Cek tabrakan dengan logika yang sama seperti spike
            if (playerRight > monsterLeft && playerLeft < monsterRight &&
                playerBottom > monsterTop && playerTop < monsterBottom) {
    
                if (player.hasStarPower) {  
                    monsters[i].x = -999999;  // Pindahkan monster keluar layar
                    point.score += 15;       // Tambah skor
                } else {
                        if (gameState.level >= 2) {  // Monster hanya melukai di level 2 ke atas
                        player.playerLives--;
    
                            if (player.playerLives > 0) {  
                            findMarioStartPosition();  // Respawn Mario jika masih ada nyawa
                         
                        } else {
                        gameState.isAlive = 0;  // Game Over jika nyawa habis
                    }
                }
                return gameState.isAlive;
            }
        }
    }
}
        


bool checkCollisionWithCoin() {
    bool coinCollected = false; // Flag untuk mendeteksi apakah ada koin yang diambil

    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[gameState.level][i][j] == 3) {  // Jika ada koin di posisi ini
                int coinX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int coinY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int coinWidth = 25;
                int coinHeight = 25;

                // Hitbox Koin
                int coinLeft = coinX + 10;
                int coinRight = coinX + coinWidth;
                int coinTop = coinY;
                int coinBottom = coinY + coinHeight;

                // Hitbox Pemain (Mario)
                int playerLeft = player.x - (COLS / 2) + 20;
                int playerRight = player.x + (COLS / 2) + 10;
                int playerTop = player.y - ROWS - 10;
                int playerBottom = player.y;

                // Cek apakah hitbox pemain bertabrakan dengan hitbox koin (AABB Collision)
                if (playerRight > coinLeft && playerLeft < coinRight &&
                    playerBottom > coinTop && playerTop < coinBottom) {

                    maps[gameState.level][i][j] = 20;  // Hapus koin dari peta setelah diambil
                    coinCollected = true; // Set flag jika koin diambil
                }
            }
        }
    }

    return coinCollected; // Return true jika ada koin yang diambil, false jika tidak
}


void checkCollisionWithStar() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[gameState.level][i][j] == 5) {  // Jika ada Star Power (kode 5)
                int starX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int starY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int starWidth = 25;
                int starHeight = 25;

                // Hitbox Star Power
                int starLeft = starX;
                int starRight = starX + starWidth+10;
                int starTop = starY;
                int starBottom = starY + starHeight+5;

                // Hitbox Pemain
                int playerLeft = player.x - (COLS / 2)+20;
                int playerRight = player.x + (COLS / 2)+10;
                int playerTop = player.y - ROWS;
                int playerBottom = player.y;
                //drawHitbox(starLeft, starTop, starRight, starBottom, RED);   // Hitbox star (Merah)
                //drawHitbox(playerLeft, playerTop, playerRight, playerBottom, BLUE); // Hitbox Mario (Biru)

                // Deteksi tabrakan menggunakan AABB seperti spike
                if (playerRight > starLeft && playerLeft < starRight &&
                    playerBottom > starTop && playerTop < starBottom) {
                    
                    player.hasStarPower = 1;  // Aktifkan Star Power
                    player.starPowerTimer = 150;
                    maps[gameState.level][i][j] = 21; // Hapus Star Power dari peta
                }
            }
        }
    }
}

bool checkCollisionWithNextLevel() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[gameState.level][i][j] == 7) { // Jika blok ini adalah "Next Level"
                int nextX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int nextY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int nextWidth = SCREEN_WIDTH / MAP_WIDTH;
                int nextHeight = SCREEN_HEIGHT / MAP_HEIGHT;

                // Hitbox Next Level
                int nextLeft = nextX;
                int nextRight = nextX + nextWidth;
                int nextTop = nextY;
                int nextBottom = nextY + nextHeight;

                // Hitbox Pemain
                int playerLeft = player.x - (COLS / 2);
                int playerRight = player.x + (COLS / 2);
                int playerTop = player.y - ROWS;
                int playerBottom = player.y;

                //drawHitbox(nextLeft, nextTop, nextRight, nextBottom, RED);   // Hitbox next (Merah)
                //drawHitbox(playerLeft, playerTop, playerRight, playerBottom, BLUE); // Hitbox Mario (Biru)

                // Deteksi tabrakan menggunakan AABB
                if (playerRight > nextLeft && playerLeft < nextRight &&
                    playerBottom > nextTop && playerTop < nextBottom) {
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
            if (maps[gameState.level][i][j] == 1 || maps[gameState.level][i][j] == 2 || maps[gameState.level][i][j] == 8 || maps[gameState.level][i][j] == 11|| maps[gameState.level][i][j] == 13) {
                int platformX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int platformY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int platformWidth = SCREEN_WIDTH / MAP_WIDTH;
                int platformHeight = 40; // Tinggi platform tetap 40

                // Bounding box pemain (AABB) dengan ukuran Mario (25x35)
                int playerLeft = player.x - (COLS / 2)+10;
                int playerRight = player.x + (COLS / 2)+10;
                int playerTop = player.y - ROWS;
                int playerBottom = player.y +5;

                // Sesuaikan agar hitbox benar-benar berada di tengah sprite
                int hitboxX = player.x - (COLS/ 2) + (ROWS / 4);
                int hitboxY = player.y - COLS;

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
                    if (playerBottom > platformTop && playerTop < platformTop+ 2  && player.velocityY >= 0) {
                        player.y = platformTop;
                        player.velocityY = 0;
                        player.isJumping = 0;
                        continue;
                    }
                    // Cek tabrakan dari bawah
                    else if (playerTop < platformBottom && playerBottom > platformBottom && player.velocityY < 0) {
                        player.y = platformBottom + ROWS;
                        player.velocityY = 0;
                    }
                    // Cek tabrakan dari kiri (hanya jika pemain tidak sedang berdiri di atas platform)
                    else if(collisionX && playerRight > platformLeft && playerLeft < platformLeft && playerBottom > platformTop) {
                        player.x = platformLeft - (COLS / 2)-12;
                    }
                    // Cek tabrakan dari kanan (hanya jika pemain sejajar dengan platform, tidak berdiri di atasnya)
                    else if (collisionX && playerLeft < platformRight && playerRight > platformRight && playerBottom > platformTop) {
                        player.x = platformRight + (COLS / 2)-10;
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
            if (maps[gameState.level][i][j] == 14) { // 14 adalah kode bendera
                int poleX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int poleY = i * (SCREEN_HEIGHT / MAP_HEIGHT) - 300; // Tiang tinggi 300 px

                // Hitbox Tiang Bendera
                int poleLeft = poleX+20;
                int poleRight = poleX+30;
                int poleTop = poleY +20;
                int poleBottom = poleY + 340;

                // Hitbox Mario
                int playerLeft = player.x - (COLS / 2)+20;
                int playerRight = player.x + (COLS / 2)+10;
                int playerTop = player.y - ROWS-10;
                int playerBottom = player.y;

                // Gambar hitbox untuk debugging
                //drawHitbox(poleLeft, poleTop, poleRight, poleBottom, GREEN);  // Tiang bendera (Hijau)
                //drawHitbox(playerLeft, playerTop, playerRight, playerBottom, BLUE); // Mario (Biru)

                // Deteksi tabrakan dengan tiang (bukan kain bendera)
                if (playerRight > poleLeft && playerLeft < poleRight &&
                    playerBottom > poleTop && playerTop < poleBottom) {
                    point.score+=100;
                    gameState.hasWon = 1; // Mario menang
                    return gameState.hasWon; // Kembalikan nilai kemenangan
                }
            }
        }
    }
}