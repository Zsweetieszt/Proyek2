#include "game.h"
#include "player.h"

// Fungsi untuk menggambar karakter pemain
void drawCharacter(int x, int y) {
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(x, y, PLAYER_SIZE, PLAYER_SIZE);
}

// Fungsi untuk menangani input dari pemain
void handleInput() {
    if (!isAlive) return;

    if (kbhit()) {
        char key = getch();
        if (key == 'a' && playerX > 0) {
            playerX -= MOVE_SPEED;
        } else if (key == 'd' && playerX < SCREEN_WIDTH) {
            playerX += MOVE_SPEED;
        } else if (key == 'w' && !isJumping) {
            velocityY = JUMP_STRENGTH;
            isJumping = 1;
        } else if (key == 'w' && key == 'd' && !isJumping) {
            playerX += MOVE_SPEED; // Move right
            velocityY = JUMP_STRENGTH; // Move up
            isJumping = 1; // Set jumping state
        } else if (key == 'w' && key == 'a' && !isJumping){
            playerX -= MOVE_SPEED;
            velocityY = JUMP_STRENGTH;
            isJumping = 1;
        }
    }
}
