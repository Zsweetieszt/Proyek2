#include "game.h"
#include "player.h"
#include <stdbool.h>

DWORD lastMoveTime = 0;

int player_standing[ROWS][COLS] = {
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, RED, GREEN, GREEN, GREEN, GREEN, RED, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, RED, GREEN, GREEN, GREEN, GREEN, RED, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, RED, GREEN, GREEN, GREEN, GREEN, RED, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, RED, GREEN, GREEN, GREEN, GREEN, RED, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, GREEN, GREEN, RED, YELLOW, RED, RED, RED, RED, YELLOW, RED, GREEN, GREEN, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, GREEN, RED, RED, RED, RED, RED, RED, RED, RED, GREEN, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, YELLOW, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, YELLOW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, RED, RED, RED,  RED, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, RED, RED, RED,  RED, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, RED, RED, RED,  RED, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK}
};
int player_walking1[ROWS][COLS]={
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, GREEN, GREEN, RED, BLACK, BLACK, BLACK, YELLOW, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, BLACK, YELLOW, YELLOW, YELLOW},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, RED, GREEN, YELLOW, YELLOW, YELLOW},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, YELLOW, YELLOW, YELLOW},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, GREEN, YELLOW, GREEN},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, GREEN, GREEN, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, RED, YELLOW, RED, GREEN, YELLOW, GREEN, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, GREEN},
    {YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, GREEN, GREEN},
    {BLACK, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, BLACK, RED, GREEN, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, GREEN, RED, RED, GREEN, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, RED, RED, RED, GREEN, GREEN, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK}
};
int player_walking2[ROWS][COLS]={
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, RED, RED, RED, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, RED, GREEN, GREEN, GREEN, RED, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, RED, GREEN, GREEN, GREEN, GREEN, RED, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, RED, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, YELLOW, YELLOW, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW},
    {BLACK, BLACK, BLACK, GREEN, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, RED, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, GREEN, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, RED, RED, RED, GREEN, RED, RED, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, RED, GREEN, GREEN, RED, RED, RED, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, GREEN, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, RED, RED, RED, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK}

};
int player_jumping[ROWS][COLS] = {
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK}, 
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, YELLOW, YELLOW, GREEN, GREEN, YELLOW, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, YELLOW, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, BLACK, BLACK, BLACK},  
    {BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, GREEN, GREEN, RED, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, RED, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN ,RED, GREEN, GREEN, RED, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, RED, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, RED, RED, RED, RED, GREEN, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, RED, RED, RED, RED, YELLOW, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, YELLOW, BLACK, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, RED, RED, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, GREEN, GREEN, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, RED, RED, GREEN, GREEN, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, RED, RED, RED, RED, BLACK, BLACK, RED, RED, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK}
};
int player_dead[ROWS][COLS] = {
    {BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, YELLOW, BLACK, RED, RED, RED, RED, RED, RED, BLACK, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, GREEN, YELLOW, GREEN, YELLOW, YELLOW, GREEN, YELLOW, GREEN, YELLOW, YELLOW, YELLOW},
    {YELLOW, YELLOW, GREEN, GREEN, YELLOW, GREEN, YELLOW, YELLOW, GREEN, YELLOW, GREEN, GREEN, YELLOW, YELLOW},
    {YELLOW, YELLOW, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, YELLOW, YELLOW},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, GREEN, GREEN, GREEN, GREEN, YELLOW, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, RED, RED, RED, YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, BLACK, BLACK},
    {BLACK, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, YELLOW, RED, RED, YELLOW, RED, GREEN, GREEN, GREEN, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, BLACK},
    {BLACK, BLACK, GREEN, GREEN, RED, RED, RED, RED, RED, RED, GREEN, GREEN, BLACK, BLACK}
};


bool frameToggle = false; 
bool isFacingLeft = false; // Default menghadap ke kanan
int (*currentCharacter)[COLS] = player_standing; // Default adalah standing

void drawCharacter(int player[ROWS][COLS], int x, int y, bool hasStarPower) {
    int characterHeight = 50; // Total tinggi karakter
    int adjustedY = y - characterHeight; // Sesuaikan Y agar kaki menjadi referensi

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (player[i][j] != BLACK) { // Hanya menggambar piksel yang bukan hitam
                int color = player[i][j]; // Warna asli dari array

                // Ubah warna berdasarkan kondisi power-up
                if (hasStarPower) {
                    if (player[i][j] != BLACK){
                        if (color == RED) {
                            color = GREEN1;
                        }else if (color == GREEN){
                            color = YELLOW1;}
                        else if (color == YELLOW) 
                        {color = WHITE;}
                    }
                }

                setfillstyle(SOLID_FILL, color); // Atur warna sesuai kondisi
                bar(
                    x + j * PLAYER_SIZE,                // Koordinat kiri atas pixel
                    adjustedY + i * PLAYER_SIZE,        // Koordinat atas pixel
                    x + (j + 1) * PLAYER_SIZE,          // Koordinat kanan bawah pixel
                    adjustedY + (i + 1) * PLAYER_SIZE   // Koordinat bawah pixel
                );
            }
        }
    }
}


int player_standing_mirrored[ROWS][COLS];
int player_walking1_mirrored[ROWS][COLS];
int player_walking2_mirrored[ROWS][COLS];
int player_jumping_mirrored[ROWS][COLS];

void initializeMirrorSprites() {
    mirrorPlayer(player_standing, player_standing_mirrored);
    mirrorPlayer(player_walking1, player_walking1_mirrored);
    mirrorPlayer(player_walking2, player_walking2_mirrored);
    mirrorPlayer(player_jumping, player_jumping_mirrored);
}

// Fungsi untuk mencerminkan (mirroring) array
void mirrorPlayer(int currentCharacter[ROWS][COLS], int mirrored[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mirrored[i][j] = currentCharacter[i][COLS - 1 - j]; // Membalikkan arah kolom
        }
    }
}


// Fungsi untuk menangani input dari pemain
void handleInput() {
    if (!gameState.isAlive) { 
        // Ganti ke animasi mati jika karakter tidak hidup
        currentCharacter = player_dead;
        return;
        
    }
    bool movingLeft = GetAsyncKeyState('A') & 0x8000;
    bool movingRight = GetAsyncKeyState('D') & 0x8000;
    bool jumping = GetAsyncKeyState('W') & 0x8000;

    DWORD currentTime = GetTickCount();

    // Jika sedang melompat, gunakan sprite lompat
    if (player.isJumping) {  
        currentCharacter = isFacingLeft ? player_jumping_mirrored : player_jumping;

        if (movingLeft && player.x > 0 && (currentTime - lastMoveTime > MOVE_DELAY)) {
            isFacingLeft = true;
            lastMoveTime = currentTime;

            if (player.x <= SCREEN_WIDTH / 2 && camera.x > 0) {
                camera.offset -= SCROLL_SPEED;
                if (camera.offset <= -SCREEN_WIDTH / MAP_WIDTH * 2) {
                    camera.offset = 0;
                    camera.x -= 2;
                }
            } else {
                player.x -= MOVE_SPEED;
            }
        }

        if (movingRight && player.x < SCREEN_WIDTH && (currentTime - lastMoveTime > MOVE_DELAY)) {
            isFacingLeft = false;
            lastMoveTime = currentTime;

            if (player.x >= SCREEN_WIDTH / 2 && camera.x < TOTAL_MAP_WIDTH - MAP_WIDTH) {
                camera.offset += SCROLL_SPEED;
                if (camera.offset >= SCREEN_WIDTH / MAP_WIDTH * 2) {
                    camera.offset = 0;
                    camera.x += 2;
                }
            } else {
                player.x += MOVE_SPEED;
            }
        }
    } 
    else {  // Jika tidak melompat, gunakan animasi berjalan atau diam
        if (movingLeft && player.x > 0 && (currentTime - lastMoveTime > MOVE_DELAY)) { 
            isFacingLeft = true;
            lastMoveTime = currentTime;

            if (player.x <= SCREEN_WIDTH / 2 && camera.x > 0) {
                camera.offset -= SCROLL_SPEED;
                if (camera.offset <= -SCREEN_WIDTH / MAP_WIDTH * 2) {
                    camera.offset = 0;
                    camera.x -= 2;
                }
            } else {
                player.x -= MOVE_SPEED;
            }
            currentCharacter = (frameToggle) ? player_walking1_mirrored : player_walking2_mirrored;
            frameToggle = !frameToggle;
        }
    
        if (movingRight && player.x < SCREEN_WIDTH && (currentTime - lastMoveTime > MOVE_DELAY)) { 
            isFacingLeft = false;
            lastMoveTime = currentTime;

            if (player.x >= SCREEN_WIDTH / 2 && camera.x < TOTAL_MAP_WIDTH - MAP_WIDTH) {
                camera.offset += SCROLL_SPEED;
                if (camera.offset >= SCREEN_WIDTH / MAP_WIDTH * 2) {
                    camera.offset = 0;
                    camera.x += 2;
                }
            } else {
                player.x += MOVE_SPEED;
            }
            currentCharacter = (frameToggle) ? player_walking1 : player_walking2;
            frameToggle = !frameToggle;
        }
    
        if (jumping && !player.isJumping) { 
            player.velocityY = JUMP_STRENGTH;
            player.isJumping = 1;
            currentCharacter = isFacingLeft ? player_jumping_mirrored : player_jumping;
        }

        if (!movingLeft && !movingRight && player.velocityY == 0 && !player.isJumping) {
            currentCharacter = isFacingLeft ? player_standing_mirrored : player_standing;
        }
    }
}