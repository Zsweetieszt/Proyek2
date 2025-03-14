#include "game.h"
#include "map.h"

// Fungsi untuk menggambar peta berdasarkan data di array maps
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
// Kepala hantu (lingkaran)
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y, 30, 40);

    // Badan hantu (bagian bawah bergelombang)
    int body[] = {x - 30, y, x - 35, y + 30, x - 25, y + 40, x - 15, y + 30,
                x - 5, y + 40, x + 5, y + 30, x + 15, y + 40, x + 25, y + 30,
                x + 30, y, x - 30, y}; 
    setfillstyle(SOLID_FILL, WHITE);
    fillpoly(10, body);

    // Mata hantu
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x - 10, y - 10, 5, 8);
    fillellipse(x + 10, y - 10, 5, 8);

    // Mulut hantu
    arc(x, y + 5, 200, 340, 10); // Mulut berbentuk setengah lingkaran

}

void drawSpike(int x, int y) {
    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);
    int points[] = {x, y, x + 10, y - 30, x + 20, y}; // Ubah posisi y duri
    fillpoly(3, points);
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
                case 6:
                    drawSpike(x, y + 100);
                    break;
            }
        }
    }
}