#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define GROUND_HEIGHT 400
#define GRAVITY 1
#define JUMP_STRENGTH -15
#define MOVE_SPEED 5
#define MAP_WIDTH 10
#define MAP_HEIGHT 5
#define PLAYER_SIZE 20
#define MONSTER_SIZE 20

int playerX = 100, playerY = GROUND_HEIGHT - 30;
int velocityY = 0;
int isJumping = 0;
int level = 0;
int isAlive = 1;

// Peta level (0 = kosong, 1 = tanah, 2 = platform, 3 = rintangan, 4 = monster, 5 = bintang)
int maps[2][MAP_HEIGHT][MAP_WIDTH] = {
    {
        {0, 0, 0, 0, 0, 0, 5, 0, 0, 0},
        {0, 2, 0, 0, 3, 0, 2, 0, 2, 0},
        {0, 0, 0, 0, 0, 2, 2, 0, 0, 0},
        {0, 0, 0, 4, 0, 2, 4, 0, 2, 0},
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

void drawPlatform(int x, int y, int width, int height) {
    setcolor(BLUE);
    setfillstyle(SOLID_FILL, BLUE);
    bar(x, y, x + width, y + height);
}

void drawObstacle(int x, int y) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    bar(x, y, x + 20, y + 20);
}

void drawStar(int x, int y) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y, 10, 10);
}

void drawMonster(int x, int y) {
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillellipse(x, y, MONSTER_SIZE, MONSTER_SIZE);
}

void drawCharacter(int x, int y) {
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    fillellipse(x, y, PLAYER_SIZE, PLAYER_SIZE);
}

void drawMap() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int tile = maps[level][i][j];
            int x = j * (SCREEN_WIDTH / MAP_WIDTH);
            int y = i * (SCREEN_HEIGHT / MAP_HEIGHT);
            
            switch (tile) {
                case 1:
                    drawPlatform(x, y, SCREEN_WIDTH / MAP_WIDTH, 10);
                    break;
                case 2:
                    drawPlatform(x, y, SCREEN_WIDTH / MAP_WIDTH, 10);
                    break;
                case 3:
                    drawObstacle(x, y + 10);
                    break;
                case 4:
                    drawMonster(x + 20, y + 20);
                    break;
                case 5:
                    drawStar(x + 20, y + 20);
                    break;
            }
        }
    }
}

void checkCollisionWithMonster() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            if (maps[level][i][j] == 4) {
                int monsterX = j * (SCREEN_WIDTH / MAP_WIDTH) + 20;
                int monsterY = i * (SCREEN_HEIGHT / MAP_HEIGHT) + 20;
                
                int dx = playerX - monsterX;
                int dy = playerY - monsterY;
                int distance = sqrt(dx * dx + dy * dy);
                
                if (distance < PLAYER_SIZE + MONSTER_SIZE) {
                    isAlive = 0;
                }
            }
        }
    }
}

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
    
    checkCollisionWithMonster();
}

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
        }
    }
}

void displayGameOver() {
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    outtextxy(SCREEN_WIDTH / 2 - 50, SCREEN_HEIGHT / 2, "GAME OVER");
    getch();
    closegraph();
    exit(0);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\minGW\\lib");
    
    while (1) {
        cleardevice();
        drawMap();
        drawCharacter(playerX, playerY);
        
        handleInput();
        updateGame();
        
        if (!isAlive) {
            displayGameOver();
        }
        
        delay(20);
    }
    
    closegraph();
    return 0;
}