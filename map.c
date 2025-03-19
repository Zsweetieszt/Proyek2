#include "game.h"
#include "map.h"

// Fungsi untuk menggambar grid bata dengan celah
void drawPlatform(int startX, int startY, int brickWidth, int brickHeight, int rows = 5, int cols = 10) {
    int mainColor = COLOR(215, 108, 44); // Warna bata utama
    int gapColor = COLOR(60, 15, 5);    // Warna celah antar bata
    int borderColor = COLOR(60, 15, 5); // Warna border hitam

    // Menggambar bata dalam grid
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int x = startX + j * (brickWidth + 5);
            int y = startY + i * (brickHeight + 5);
            bool drawHorizontalGap = (i < rows - 1); // Menghindari celah horizontal di bagian bawah
            bool drawVerticalGap = (j < cols - 1);   // Menghindari celah vertikal di tepi kanan

            // Mengisi bata utama
            setfillstyle(SOLID_FILL, mainColor);
            bar(x, y, x + brickWidth, y + brickHeight);

            // Membuat celah horizontal antar bata
            if (drawHorizontalGap) {
                setfillstyle(SOLID_FILL, gapColor);
                bar(x, y + brickHeight, x + brickWidth, y + brickHeight + 5);
            }

            // Membuat celah vertikal antar bata
            if (drawVerticalGap) {
                setfillstyle(SOLID_FILL, gapColor);
                bar(x + brickWidth, y, x + brickWidth + 5, y + brickHeight);
            }

            // Menambahkan warna untuk sudut celah
            if (drawHorizontalGap && drawVerticalGap) {
                setfillstyle(SOLID_FILL, gapColor);
                bar(x + brickWidth, y + brickHeight, x + brickWidth + 5, y + brickHeight + 5);
            }
        }
    }

    // Menggambar border hitam tebal di sekitar kotak
    setcolor(borderColor);
    for (int i = 0; i < 4; i++) {
        rectangle(startX - 1 - i, startY - 1 - i, startX + cols * (brickWidth + 5) - 5 + i, startY + rows * (brickHeight + 5) - 5 + i);
    }
}



void drawGround(int x, int y) {
    int tileSizeX = SCREEN_WIDTH / MAP_WIDTH;  // Ukuran block sesuai grid
    int tileSizeY = SCREEN_HEIGHT / MAP_HEIGHT;
    setcolor(BROWN);
    setfillstyle(SOLID_FILL, BROWN);
    bar(x, y, x + tileSizeX, y + tileSizeY);
}


void drawCoin(int x, int y) {
    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(x + 15, y + 15, 10, 10);  // Gambar lingkaran kecil sebagai koin
}

void drawMonster() {
    int screenX = monsterX - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillellipse(screenX, monsterY, MONSTER_SIZE, MONSTER_SIZE);
}




void drawSpike(int x, int y) {
    int tileSizeX = SCREEN_WIDTH / MAP_WIDTH;  
    int spikeHeight = tileSizeX / 2;  // Setengah dari ukuran tile

    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);

    int points[] = {
        x, y + spikeHeight,               // Bawah kiri
        x + tileSizeX / 2, y,             // Ujung atas
        x + tileSizeX, y + spikeHeight    // Bawah kanan
    };
    fillpoly(3, points);
}


void drawCloud(int x, int y) {
    int size = 32; // Ukuran piksel 32
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y, x + size, y + size * 2 / 3);
    bar(x + size * 2 / 3, y - size / 3, x + size * 5 / 3, y + size / 3);
    bar(x + size * 4 / 3, y, x + size * 7 / 3, y + size * 2 / 3);
}

void drawGrid() {
    setcolor(WHITE);
    for (int i = 0; i <= MAP_WIDTH; i++) {
        int x = i * (SCREEN_WIDTH / MAP_WIDTH);
        line(x, 0, x, SCREEN_HEIGHT);  // Garis vertikal
    }
    for (int i = 0; i <= MAP_HEIGHT; i++) {
        int y = i * (SCREEN_HEIGHT / MAP_HEIGHT);
        line(0, y, SCREEN_WIDTH, y);  // Garis horizontal
    }
}

void drawStoneBlock(int startX, int startY, int rectWidth, int rectHeight, int boxSize, int gap) {
    int rectColor = COLOR(204, 102, 0); // Warna oranye
    int gapColor = BLACK;

    // Baris 1: Dua persegi panjang menyamping
    setfillstyle(SOLID_FILL, rectColor);
    bar(startX, startY, startX + rectWidth, startY + rectHeight);
    setcolor(gapColor);
    rectangle(startX, startY, startX + rectWidth, startY + rectHeight);

    bar(startX + rectWidth + gap, startY, startX + 2 * rectWidth + gap, startY + rectHeight);
    rectangle(startX + rectWidth + gap, startY, startX + 2 * rectWidth + gap, startY + rectHeight);

    // Baris 2: Persegi panjang diapit oleh dua kotak
    bar(startX, startY + rectHeight + gap, startX + boxSize, startY + rectHeight + gap + boxSize);
    rectangle(startX, startY + rectHeight + gap, startX + boxSize, startY + rectHeight + gap + boxSize);

    bar(startX + boxSize + gap, startY + rectHeight + gap, startX + boxSize + gap + rectWidth, startY + 2 * rectHeight + gap);
    rectangle(startX + boxSize + gap, startY + rectHeight + gap, startX + boxSize + gap + rectWidth, startY + 2 * rectHeight + gap);

    bar(startX + boxSize + rectWidth + 2 * gap, startY + rectHeight + gap, startX + 2 * boxSize + rectWidth + 2 * gap, startY + rectHeight + gap + boxSize);
    rectangle(startX + boxSize + rectWidth + 2 * gap, startY + rectHeight + gap, startX + 2 * boxSize + rectWidth + 2 * gap, startY + rectHeight + gap + boxSize);

    // Baris 3: Dua persegi panjang menyamping
    bar(startX, startY + 2 * (rectHeight + gap), startX + rectWidth, startY + 3 * rectHeight + 2 * gap);
    rectangle(startX, startY + 2 * (rectHeight + gap), startX + rectWidth, startY + 3 * rectHeight + 2 * gap);

    bar(startX + rectWidth + gap, startY + 2 * (rectHeight + gap), startX + 2 * rectWidth + gap, startY + 3 * rectHeight + 2 * gap);
    rectangle(startX + rectWidth + gap, startY + 2 * (rectHeight + gap), startX + 2 * rectWidth + gap, startY + 3 * rectHeight + 2 * gap);

    // Baris 4: Persegi panjang diapit oleh dua kotak
    bar(startX, startY + 3 * (rectHeight + gap), startX + boxSize, startY + 3 * rectHeight + 3 * gap + boxSize);
    rectangle(startX, startY + 3 * (rectHeight + gap), startX + boxSize, startY + 3 * rectHeight + 3 * gap + boxSize);

    bar(startX + boxSize + gap, startY + 3 * (rectHeight + gap), startX + boxSize + gap + rectWidth, startY + 4 * rectHeight + 3 * gap);
    rectangle(startX + boxSize + gap, startY + 3 * (rectHeight + gap), startX + boxSize + gap + rectWidth, startY + 4 * rectHeight + 3 * gap);

    bar(startX + boxSize + rectWidth + 2 * gap, startY + 3 * (rectHeight + gap), startX + 2 * boxSize + rectWidth + 2 * gap, startY + 3 * rectHeight + 3 * gap + boxSize);
    rectangle(startX + boxSize + rectWidth + 2 * gap, startY + 3 * (rectHeight + gap), startX + 2 * boxSize + rectWidth + 2 * gap, startY + 3 * rectHeight + 3 * gap + boxSize);
}



void drawBrickBlock(int x, int y) {
    setfillstyle(SOLID_FILL, BROWN);
    bar(x, y, x + 32, y + 32);

    setcolor(DARKGRAY);
    for (int i = 5; i < 32; i += 10) {
        line(x, y + i, x + 32, y + i);
    }
}
void drawPipe(int x, int y){
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    bar(x, y, x + 32, y + 32);   
}

void drawCloudBlock(int x, int y) {
    int size = 32;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y, x + size, y + size * 2 / 3);
    bar(x + size * 2 / 3, y - size / 3, x + size * 5 / 3, y + size / 3);
    bar(x + size * 4 / 3, y, x + size * 7 / 3, y + size * 2 / 3);
}

void drawStar(int x, int y) {
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(x + 15, y + 15, 12, 12);  // Gambar bintang kecil
}


void drawBackground() {
    // Gambar langit biru
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, SCREEN_WIDTH, GROUND_HEIGHT+25);

    // Gambar awan (contoh sederhana)
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(100, 100, 30, 20);
    fillellipse(150, 120, 40, 25);
    fillellipse(200, 110, 35, 22);

    fillellipse(300, 50, 25, 18);
    fillellipse(340, 60, 30, 20);

    fillellipse(450, 80, 40, 25);
    fillellipse(500, 70, 35, 22);
    fillellipse(550, 90, 45, 28);
}

void drawNextLevel(int x, int y) {
    setcolor(CYAN);  // Warna biru muda
    setfillstyle(SOLID_FILL, CYAN);
    bar(x, y, x + 32, y + 32);  // Kotak 32x32 sebagai blok teleportasi
}


void drawMap() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int actualX = j + cameraX; // Ambil posisi asli di peta besar
            if (actualX >= TOTAL_MAP_WIDTH) continue; // Hindari menggambar di luar batas

            int tile = maps[level][i][actualX];
            int x = j * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset; // Sesuaikan dengan offset kamera
            int y = i * (SCREEN_HEIGHT / MAP_HEIGHT);
            
            switch (tile) {
                case 1:
                    drawGround(x, y);
                    break;
                case 2:
                    drawPlatform(x, y, SCREEN_WIDTH / MAP_WIDTH, 10);
                    break;
                case 3:
                    drawCoin(x, y);  // Sekarang menggambar koin
                    break;                
                case 4:
                    drawMonster();
                    break;
                case 5:
                    drawStar(x + 20, y + 20);
                    break;
                case 6:
                    drawSpike(x, y + (SCREEN_HEIGHT / MAP_HEIGHT) - (SCREEN_HEIGHT / MAP_HEIGHT) / 2);
                    break;                                
                case 7:
                    drawNextLevel(x, y);
                    break;
                case 8:
                    drawPipe(x + 20, y + 20);
                    break;
                case 9:
                    drawCloud(x + 20, y + 20);
                    break;
                case 10:
                    drawBrickBlock(x + 20, y + 20);
                    break;
                case 11:
                    drawStoneBlock(x + 20, y + 20, 85, 40, 40, 5);
                    break;
            }
        }
    }
}