#include "player.h"

// Fungsi untuk mencerminkan (mirroring) array
void mirrorPlayer(int original[ROWS][COLS], int mirrored[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mirrored[i][j] = original[i][COLS - 1 - j];
        }
    }
}

// Fungsi untuk menggambar player di layar
void drawCharacter(int player[ROWS][COLS], int x, int y) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (player[i][j] != BLACK) { // Hanya menggambar piksel yang bukan hitam
                setfillstyle(SOLID_FILL, player[i][j]); // Set warna berdasarkan array
                bar(
                    x + j * PIXEL_SIZE,            // Koordinat kiri atas pixel
                    y + i * PIXEL_SIZE,            // Koordinat atas pixel
                    x + (j + 1) * PIXEL_SIZE,      // Koordinat kanan bawah pixel
                    y + (i + 1) * PIXEL_SIZE       // Koordinat bawah pixel
                );
            }
        }
    }
}

void drawObstacle(Obstacle obstacle) {
    setfillstyle(SOLID_FILL, RED);
    bar(obstacle.x, obstacle.y, obstacle.x + obstacle.width, obstacle.y + obstacle.height);
}

int checkCollision(int playerX, int playerY, int playerWidth, int playerHeight, Obstacle obstacle) {
    return (playerX < obstacle.x + obstacle.width &&
            playerX + playerWidth > obstacle.x &&
            playerY < obstacle.y + obstacle.height &&
            playerY + playerHeight > obstacle.y);
}
