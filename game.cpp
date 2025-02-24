#include <graphics.h>
#include <conio.h>
#include <stdio.h>

#define WIDTH 600
#define HEIGHT 600
#define CELL_SIZE 50
#define ROWS (HEIGHT / CELL_SIZE)
#define COLS (WIDTH / CELL_SIZE)

int maze[ROWS][COLS] = {
    {1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,1,0,1,0,0,0,0,1},
    {1,0,1,0,1,0,1,0,1,1,0,1},
    {1,0,1,0,0,0,0,0,1,1,0,1},
    {1,0,1,1,1,1,1,0,1,1,0,1},
    {1,0,0,0,0,0,0,0,1,1,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1}
};

int playerX = 1, playerY = 1;

void drawMaze() {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (maze[i][j] == 1) {
                setfillstyle(SOLID_FILL, BLUE);
                bar(j * CELL_SIZE, i * CELL_SIZE, (j + 1) * CELL_SIZE, (i + 1) * CELL_SIZE);
            }
        }
    }
}

void drawPlayer() {
    setfillstyle(SOLID_FILL, RED);
    fillellipse(playerX * CELL_SIZE + CELL_SIZE / 2, playerY * CELL_SIZE + CELL_SIZE / 2, CELL_SIZE / 3, CELL_SIZE / 3);
}

void updateGame() {
    cleardevice();
    drawMaze();
    drawPlayer();
}

int main() {
    int gd = DETECT, gm;
    char path[] = "C:\\minGW\\lib";
    initgraph(&gd, &gm, path);
    
    while (1) {
        updateGame();
        char ch = getch();
        
        if (ch == 27) // ESC to exit
            break;
        
        int newX = playerX, newY = playerY;
        if (ch == 75) newX--; // Left
        if (ch == 77) newX++; // Right
        if (ch == 72) newY--; // Up
        if (ch == 80) newY++; // Down
        
        if (maze[newY][newX] == 0) {
            playerX = newX;
            playerY = newY;
        }
    }
    
    closegraph();
    return 0;
}
