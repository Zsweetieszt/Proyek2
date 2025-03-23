#include "player.h"
#include "game.h"
#include <stdbool.h>

DWORD lastMoveTime = 0;

Player player = {
        .walking1 = {    
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
    },
        .standing = { 
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
    },
        .walking2 = { 
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
    },
        .jumping = {
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
    },

        .dead = {
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
    }
};

bool frameToggle = false; 
bool isFacingLeft = false; // Default menghadap ke kanan
int (*currentCharacter)[COLS] = player.standing; // Default adalah standing

void initializeMirrorPlayer(Player *player) {
    mirrorPlayer(player->standing, player->mirroredStanding);
    mirrorPlayer(player->walking1, player->mirroredWalking1);
    mirrorPlayer(player->walking2, player->mirroredWalking2);
    mirrorPlayer(player->jumping, player->mirroredJumping);
}

// Fungsi mencerminkan (mirroring) sprite
void mirrorPlayer(int currentCharacter[ROWS][COLS], int mirrored[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mirrored[i][j] = currentCharacter[i][COLS - 1 - j]; // Membalikkan arah kolom
        }
    }
}

// Fungsi menggambar karakter pada layar
void drawCharacter(int player[ROWS][COLS], int x, int y, bool hasStarPower) {
    int characterHeight = 50; // Total tinggi karakter
    int adjustedY = y - characterHeight; // Sesuaikan Y agar kaki menjadi referensi

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (player[i][j] != BLACK) { // Hanya menggambar piksel yang bukan hitam
                int color = player[i][j];

                // Ubah warna berdasarkan kondisi power-up
                if (hasStarPower) {
                    if (color == RED) {
                        color = GREEN1;
                    } else if (color == GREEN) {
                        color = YELLOW1;
                    } else if (color == YELLOW) {
                        color = WHITE;
                    }
                }

                setfillstyle(SOLID_FILL, color);
                bar(
                    x + j * PLAYER_SIZE,
                    adjustedY + i * PLAYER_SIZE,
                    x + (j + 1) * PLAYER_SIZE,
                    adjustedY + (i + 1) * PLAYER_SIZE
                );
            }
        }
    }
}


// Fungsi untuk menangani input dari pemain
void handleInput() {
    if (!isAlive) { 
        // Ganti ke animasi mati jika karakter tidak hidup
        currentCharacter = player.dead; // Gunakan sprite dari `player`
        return;
    }

    bool movingLeft = GetAsyncKeyState('A') & 0x8000;
    bool movingRight = GetAsyncKeyState('D') & 0x8000;
    bool jumping = GetAsyncKeyState('W') & 0x8000;

    DWORD currentTime = GetTickCount();

    // Jika sedang melompat, gunakan sprite lompat
    if (isJumping) {  
        currentCharacter = isFacingLeft ? player.mirroredJumping : player.jumping;

        if (movingLeft && playerX > 0 && (currentTime - lastMoveTime > MOVE_DELAY)) {
            isFacingLeft = true;
            lastMoveTime = currentTime;

            if (playerX <= SCREEN_WIDTH / 2 && cameraX > 0) {
                cameraOffset -= SCROLL_SPEED;
                if (cameraOffset <= -SCREEN_WIDTH / MAP_WIDTH * 2) {
                    cameraOffset = 0;
                    cameraX -= 2;
                }
            } else {
                playerX -= MOVE_SPEED;
            }
        }

        if (movingRight && playerX < SCREEN_WIDTH && (currentTime - lastMoveTime > MOVE_DELAY)) {
            isFacingLeft = false;
            lastMoveTime = currentTime;

            if (playerX >= SCREEN_WIDTH / 2 && cameraX < TOTAL_MAP_WIDTH - MAP_WIDTH) {
                cameraOffset += SCROLL_SPEED;
                if (cameraOffset >= SCREEN_WIDTH / MAP_WIDTH * 2) {
                    cameraOffset = 0;
                    cameraX += 2;
                }
            } else {
                playerX += MOVE_SPEED;
            }
        }
    } else {  // Jika tidak melompat, gunakan animasi berjalan atau diam
        if (movingLeft && playerX > 0 && (currentTime - lastMoveTime > MOVE_DELAY)) { 
            isFacingLeft = true;
            lastMoveTime = currentTime;

            if (playerX <= SCREEN_WIDTH / 2 && cameraX > 0) {
                cameraOffset -= SCROLL_SPEED;
                if (cameraOffset <= -SCREEN_WIDTH / MAP_WIDTH * 2) {
                    cameraOffset = 0;
                    cameraX -= 2;
                }
            } else {
                playerX -= MOVE_SPEED;
            }
            currentCharacter = (frameToggle) ? player.mirroredWalking1 : player.mirroredWalking2;
            frameToggle = !frameToggle;
        }

        if (movingRight && playerX < SCREEN_WIDTH && (currentTime - lastMoveTime > MOVE_DELAY)) { 
            isFacingLeft = false;
            lastMoveTime = currentTime;

            if (playerX >= SCREEN_WIDTH / 2 && cameraX < TOTAL_MAP_WIDTH - MAP_WIDTH) {
                cameraOffset += SCROLL_SPEED;
                if (cameraOffset >= SCREEN_WIDTH / MAP_WIDTH * 2) {
                    cameraOffset = 0;
                    cameraX += 2;
                }
            } else {
                playerX += MOVE_SPEED;
            }
            currentCharacter = (frameToggle) ? player.walking1 : player.walking2;
            frameToggle = !frameToggle;
        }

        if (jumping && !isJumping) { 
            velocityY = JUMP_STRENGTH;
            isJumping = 1;
            currentCharacter = isFacingLeft ? player.mirroredJumping : player.jumping;
        }

        if (!movingLeft && !movingRight && velocityY == 0 && !isJumping) {
            currentCharacter = isFacingLeft ? player.mirroredStanding : player.standing;
        }
    }
}