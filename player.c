#include "game.h"
#include "player.h"

// Fungsi untuk menggambar karakter pemain
void drawCharacter(int x, int y) {
    if (hasStarPower) {
        // Efek aura Star Power
        setcolor(MAGENTA);
        setfillstyle(SOLID_FILL, MAGENTA);
        fillellipse(x, y, PLAYER_SIZE + 5, PLAYER_SIZE + 5); // Aura lebih besar

        // Warna karakter berubah jadi ungu
        setcolor(MAGENTA);
        setfillstyle(SOLID_FILL, MAGENTA);
        fillellipse(x, y, PLAYER_SIZE, PLAYER_SIZE);
    } else {
        // Warna normal (hijau)
        setcolor(GREEN);
        setfillstyle(SOLID_FILL, GREEN);
        fillellipse(x, y, PLAYER_SIZE, PLAYER_SIZE);
    }
}


// Fungsi untuk menangani input dari pemain
void handleInput() {
    if (!isAlive) return;

    if (kbhit()) {
        char key = getch();
        if (key == 'a' && playerX > 0) {
            if (playerX <= SCREEN_WIDTH / 2 && cameraX > 0) {
                cameraOffset -= SCROLL_SPEED;
                if (cameraOffset <= -SCREEN_WIDTH / MAP_WIDTH * 2) {
                    cameraOffset = 0;
                    cameraX -= 2; // Geser kamera per 2 kolom
                }
            } else {
                playerX -= MOVE_SPEED;
            }
        } else if (key == 'd' && playerX < SCREEN_WIDTH) {
            if (playerX >= SCREEN_WIDTH / 2 && cameraX < TOTAL_MAP_WIDTH - MAP_WIDTH) {
                cameraOffset += SCROLL_SPEED;
                if (cameraOffset >= SCREEN_WIDTH / MAP_WIDTH * 2) {
                    cameraOffset = 0;
                    cameraX += 2; // Geser kamera per 2 kolom
                }
            } else {
                playerX += MOVE_SPEED;
            }
        } else if (key == 'w' && !isJumping) {
            velocityY = JUMP_STRENGTH;
            isJumping = 1;
        }
    }
}