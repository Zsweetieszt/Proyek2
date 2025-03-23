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
                int playerTop = player.y - ROWS;
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

                    }
                }
            }
        }
    }
}


// Fungsi untuk mendeteksi tabrakan dengan monstervoid checkCollisionWithMonster() {
    void checkCollisionWithMonster() {
        for (int i = 0; i < monsterCount; i++) {  // Loop untuk semua monster dalam level
            int screenMonsterX = monsters[i].x - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
            int monsterSize = MONSTER_SIZE;
            int playerSize = PLAYER_SIZE;
    
            if (player.x < screenMonsterX + monsterSize &&
                player.x + playerSize > screenMonsterX &&
                player.y < monsters[i].y + monsterSize &&
                player.y + playerSize > monsters[i].y) {
                
                int hitboxMarginX = 25;  
                int hitboxMarginY = 20;  
    
                int monsterHitboxLeft   = screenMonsterX - hitboxMarginX;
                int monsterHitboxRight  = screenMonsterX + monsterSize + hitboxMarginX;
                int monsterHitboxTop    = monsters[i].y - hitboxMarginY;
                int monsterHitboxBottom = monsters[i].y + monsterSize + hitboxMarginY;
    
                int playerHitboxLeft   = player.x + 20;
                int playerHitboxRight  = player.x + COLS + 4;
                int playerHitboxTop    = player.y - 4;
                int playerHitboxBottom = player.y;
    
                if (playerHitboxRight > monsterHitboxLeft &&
                    playerHitboxLeft < monsterHitboxRight &&
                    playerHitboxBottom > monsterHitboxTop &&
                    playerHitboxTop < monsterHitboxBottom) {
    
                    if (player.hasStarPower) {
                        monsters[i].x = -999999;  // Pindahkan monster keluar layar
                        point.score += 15;       
                    } else {
                        player.playerLives--;
    
                        if (player.playerLives > 0) {  
                            findMarioStartPosition();  
                        } else {
                            gameState.isAlive = 0;
                        }
                    }
                }
            }
        }
    }
        


void checkCollisionWithCoin() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[gameState.level][i][j] == 3) {  // Jika ada koin di posisi ini
                int coinX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int coinY = i * (SCREEN_HEIGHT / MAP_HEIGHT);

                int coinWidth = 30;  // Lebarkan hitbox koin
                int coinHeight = 30; // Tinggikan hitbox koin
                int playerWidth = PLAYER_SIZE;
                int playerHeight = PLAYER_SIZE;

                // Cek apakah hitbox pemain bertabrakan dengan hitbox koin (AABB Collision)
                if (player.x < coinX + coinWidth &&
                    player.x + playerWidth > coinX &&
                    player.y < coinY + coinHeight &&
                    player.y + playerHeight > coinY) {
                    
                    point.coins++;     // Tambah jumlah koin yang dikumpulkan
                    point.score += 10; // Tambah skor pemain
                    maps[gameState.level][i][j] =20;  // Hapus koin dari peta
                }
            }
        }
    }
}

void checkCollisionWithStar() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[gameState.level][i][j] == 5) {  // Jika ada Star Power (kode 5)
                int starX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int starY = i * (SCREEN_HEIGHT / MAP_HEIGHT);

                int starWidth = 40;  // Perbesar hitbox Star Power
                int starHeight = 40;
                int playerWidth = PLAYER_SIZE;
                int playerHeight = PLAYER_SIZE;

                // Cek apakah hitbox pemain bertabrakan dengan hitbox Star Power (AABB Collision)
                if (player.x < starX + starWidth &&
                    player.x + playerWidth > starX &&
                    player.y < starY + starHeight &&
                    player.y + playerHeight > starY) {
                    
                    player.hasStarPower = 1;  // Aktifkan Star Power
                    player.starPowerTimer = 300; // 300 frame (5 detik dalam game)
                    maps[gameState.level][i][j] = 0; // Hapus Star Power dari peta
                }
            }
        }
    }
}

void checkCollisionWithNextLevel() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[gameState.level][i][j] == 7) { // Jika blok ini adalah "Next Level"
                int nextX = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
                int nextY = i * (SCREEN_HEIGHT / MAP_HEIGHT);

                int playerWidth = PLAYER_SIZE;
                int playerHeight = PLAYER_SIZE;
                int nextWidth = 32;
                int nextHeight = 32;

                if (player.x < nextX + nextWidth &&
                    player.x + playerWidth > nextX &&
                    player.y < nextY + nextHeight &&
                    player.y + playerHeight > nextY) {

                    gameState.level++;  // Pindah ke level berikutnya
                    if (gameState.level >= 3) {  // Jika sudah di level terakhir, kembali ke awal
                        gameState.level = 0;
                    };
                    player.x = 100; // Atur ulang posisi pemain
                    player.y = GROUND_HEIGHT - 30;
                    camera.x * 0;  // Reset kamera
                    camera.offset = 0;
                }
            }
        }
    }
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
                int playerTop = player.y - ROWS;
                int playerBottom = player.y;

                // Gambar hitbox untuk debugging
                drawHitbox(poleLeft, poleTop, poleRight, poleBottom, GREEN);  // Tiang bendera (Hijau)
                drawHitbox(playerLeft, playerTop, playerRight, playerBottom, BLUE); // Mario (Biru)

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