#include "game.h"
#include "map.h"

void drawRectangle(int x, int y, int width, int height) {
    int rectColor = COLOR(204, 102, 0); // Warna oranye
    int gapColor = BLACK; // Warna pemisah

    setfillstyle(SOLID_FILL, rectColor);
    bar(x, y, x + width, y + height);

    setcolor(gapColor);
    rectangle(x, y, x + width, y + height);
}

void drawSquare(int x, int y, int size) {
    int rectColor = COLOR(204, 102, 0); // Warna oranye
    int gapColor = BLACK; 

    setfillstyle(SOLID_FILL, rectColor); 
    bar(x, y, x + size, y + size);

    setcolor(gapColor);
    rectangle(x, y, x + size, y + size);
}

void drawPlatform(int x, int y, int width, int height) {
    int tileSize = 40;  // Ukuran setiap elemen platform
    int gap = 0;  // Jarak antar elemen

    // Baris 1: Dua persegi panjang menyamping
    drawRectangle(x, y, width / 2 - gap / 2, height);
    drawRectangle(x + width / 2 + gap / 2, y, width / 2 - gap / 2, height);

    // Baris 2: Satu persegi panjang diapit dua kotak
    drawSquare(x, y + height + gap, tileSize);
    drawRectangle(x + tileSize + gap, y + height + gap, width - 2 * (tileSize + gap), height);
    drawSquare(x + width - tileSize, y + height + gap, tileSize);
}



void drawGround(int x, int y) {
    int tileSizeX = SCREEN_WIDTH / MAP_WIDTH;  
    int tileSizeY = SCREEN_HEIGHT / MAP_HEIGHT;
    int borderWidth = 3; // Ketebalan border

    // Warna utama tanah (oranye)
    int mainColor = COLOR(204, 102, 0); // RGB untuk oranye
    int borderColor = BLACK; // Warna border
    int dotColor = BLACK; // Warna titik di sudut

    // Mengisi kotak tanah
    setfillstyle(SOLID_FILL, mainColor);
    bar(x, y, x + tileSizeX, y + tileSizeY);

    // Menggambar border hitam di sekitar tanah
    setcolor(borderColor);
    for (int i = 0; i < borderWidth; i++) {
        rectangle(x - i, y - i, x + tileSizeX + i, y + tileSizeY + i);
    }

    // Menggambar titik di sudut blok tanah
    int dotDistance = 10; // Jarak titik dari sudut
    int dotRadius = 3; // Ukuran titik

    setcolor(dotColor);
    setfillstyle(SOLID_FILL, dotColor);

    // Titik di keempat sudut tanah
    fillellipse(x + dotDistance, y + dotDistance, dotRadius, dotRadius);
    fillellipse(x + tileSizeX - dotDistance, y + dotDistance, dotRadius, dotRadius);
    fillellipse(x + dotDistance, y + tileSizeY - dotDistance, dotRadius, dotRadius);
    fillellipse(x + tileSizeX - dotDistance, y + tileSizeY - dotDistance, dotRadius, dotRadius);
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

void drawStoneBlock(int x, int y) {
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(x, y, x + 32, y + 32);

    setcolor(LIGHTGRAY);
    for (int i = 5; i < 32; i += 10) {
        line(x + i, y, x + i, y + 32);
    }
    for (int i = 5; i < 32; i += 10) {
        line(x, y + i, x + 32, y + i);
    }
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
    bar(0, 0, SCREEN_WIDTH, GROUND_HEIGHT + 25);

    // Gambar matahari (lingkaran kuning)
    int sunX = SCREEN_WIDTH / 2;  // Posisi X matahari (tengah layar)
    int sunY = 100;               // Posisi Y matahari
    int sunRadius = 50;           // Radius matahari

    // Gambar lingkaran matahari dengan warna kuning
    setcolor(YELLOW);            // Set warna garis
    setfillstyle(SOLID_FILL, YELLOW);  // Set warna isi
    fillellipse(sunX, sunY, sunRadius, sunRadius);  // Gambar matahari
}

void drawNextLevel(int x, int y) {
    setcolor(CYAN);  // Warna biru muda
    setfillstyle(SOLID_FILL, CYAN);
    bar(x, y, x + 32, y + 32);  // Kotak 32x32 sebagai blok teleportasi
}

void drawFlag(int x, int y) {
    setcolor(WHITE);
    line(x, y, x, y + 60);  // Tiang lebih pendek sesuai ukuran bendera

    // Menggambar bagian atas bendera (merah)
    setfillstyle(SOLID_FILL, RED);
    rectangle(x, y, x + 40, y + 20);
    floodfill(x + 20, y + 10, WHITE);

    // Menggambar bagian bawah bendera (putih)
    setfillstyle(SOLID_FILL, WHITE);
    rectangle(x, y + 20, x + 40, y + 40);
    floodfill(x + 20, y + 30, WHITE);
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
                    drawSpike(x +20, y +20);
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
                    drawStoneBlock(x + 20, y + 20);
                    break;
                case 12:
                    drawFlag(x +20, y +20);
                    break;
            }
        }
    }
}