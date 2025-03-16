#include <graphics.h>
#include <stdlib.h>
#include <time.h>

// Fungsi untuk menggambar retakan dari pinggir kotak ke titik pusat
void drawCrack(int centerX, int centerY, int x1, int y1) {
    // Menggambar garis dari (x1, y1) ke (centerX, centerY)
    line(x1, y1, centerX, centerY);
}

void drawCrackedStone(int x, int y, int width, int height) {
    // Warna batu
    int stoneColor = COLOR(150, 150, 150); // Abu-abu
    // Warna retakan
    int crackColor = COLOR(50, 50, 50);   // Abu-abu gelap

    // Mengisi kotak dengan warna batu
    setfillstyle(SOLID_FILL, stoneColor);
    bar(x, y, x + width, y + height);

    // Titik pusat untuk retakan
    int centerX = x + width / 2;
    int centerY = y + height / 2;

    // Mengatur warna untuk retakan
    setcolor(crackColor);

    // Menggambar retakan dari tiap sisi kotak menuju pusat
    srand(time(0)); // Seed random
    for (int i = 0; i < 8; i++) { // Membuat 8 retakan
        int startX, startY;

        // Memilih sisi secara acak (kiri, kanan, atas, bawah)
        int side = rand() % 4;
        if (side == 0) { // Sisi kiri
            startX = x;
            startY = y + rand() % height;
        } else if (side == 1) { // Sisi kanan
            startX = x + width;
            startY = y + rand() % height;
        } else if (side == 2) { // Sisi atas
            startX = x + rand() % width;
            startY = y;
        } else { // Sisi bawah
            startX = x + rand() % width;
            startY = y + height;
        }

        // Menggambar retakan ke titik pusat
        drawCrack(centerX, centerY, startX, startY);
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Mengatur background menjadi putih
    setbkcolor(WHITE);
    cleardevice();

    // Lokasi dan ukuran blok
    int blockX = 100, blockY = 100;
    int blockWidth = 100, blockHeight = 100;

    // Menggambar border kotak
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, THICK_WIDTH);
    rectangle(blockX - 1, blockY - 1, blockX + blockWidth + 1, blockY + blockHeight + 1);

    // Menggambar blok batu dengan retakan
    drawCrackedStone(blockX, blockY, blockWidth, blockHeight);

    getch();
    closegraph();
    return 0;
}
