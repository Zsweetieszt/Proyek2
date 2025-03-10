#include "game.h"
#include "collision.h"  // Tambahkan ini untuk akses fungsi tabrakan
#include "map.h"

// Definisi variabel global
int playerX = 100, playerY = GROUND_HEIGHT - 30;
int velocityY = 0;
int isJumping = 0;
int level = 0;
int isAlive = 1;

// Peta level
int maps[2][MAP_HEIGHT][MAP_WIDTH] = {
    {
        {0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
        {0, 2, 0, 0, 3, 0, 2, 0, 2, 0},
        {0, 0, 0, 0, 0, 2, 2, 0, 0, 0},
        {0, 2, 6, 0, 0, 2, 4, 6, 2, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    },
    {
        {0, 0, 5, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 2, 0, 3, 0, 2, 0, 0, 0},
        {0, 0, 2, 4, 0, 0, 0, 4, 0, 0},
        {0, 0, 2, 0, 0, 2, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    }
};

// Fungsi untuk memperbarui status game
void updateGame() {
    if (!isAlive) return;
    
    playerY += velocityY;
    velocityY += GRAVITY;
    
    // Cek apakah pemain berdiri di platform
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (maps[level][i][j] == 2) {
                int platformX = j * (SCREEN_WIDTH / MAP_WIDTH);
                int platformY = i * (SCREEN_HEIGHT / MAP_HEIGHT);
                int platformWidth = SCREEN_WIDTH / MAP_WIDTH;
                
                if (playerX + PLAYER_SIZE > platformX && playerX - PLAYER_SIZE < platformX + platformWidth && playerY + PLAYER_SIZE >= platformY && playerY + PLAYER_SIZE <= platformY + 10) {
                    playerY = platformY - PLAYER_SIZE;
                    velocityY = 0;
                    isJumping = 0;
                }
            }
        }
    }
    
    if (playerY >= GROUND_HEIGHT - 30) {
        playerY = GROUND_HEIGHT - 30;
        isJumping = 0;
    }
    
    if (maps[level][playerY / (SCREEN_HEIGHT / MAP_HEIGHT)][playerX / (SCREEN_WIDTH / MAP_WIDTH)] == 5) {
        level = (level + 1) % 2;
        playerX = 100;
        playerY = GROUND_HEIGHT - 30;
    }
    
    // Cek tabrakan dengan musuh dan duri
    checkCollisionWithMonster();
    checkCollisionWithSpike();
}

// Fungsi untuk menampilkan layar Game Over
void displayGameOver() {
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, (char*)"GAME OVER");
    getch();
    closegraph();
    exit(0);
}
