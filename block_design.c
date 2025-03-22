#include "game.h"
#include "map.h"
#include "block_design.h"

// Fungsi untuk menggambar baris 1 dan 3
void drawRow(int x, int y, int gap, int blockSize) {
    int platformColor = COLOR(204, 102, 0); // Warna kotak/persegi panjang
    int gapColor = COLOR(0, 0, 0);          // Warna celah (hitam)
    int left = x, right, top = y, bottom = top + blockSize;

    // Kotak kiri dengan celah
    setfillstyle(SOLID_FILL, gapColor);
    bar(left - gap, top - gap, left + blockSize + gap, bottom + gap);

    setfillstyle(SOLID_FILL, platformColor);
    bar(left, top, left + blockSize, bottom);

    // Persegi panjang tengah dengan celah
    left = left + blockSize + gap;
    right = left + (2 * blockSize) - 1;

    setfillstyle(SOLID_FILL, gapColor);
    bar(left - gap, top - gap, right + gap, bottom + gap);

    setfillstyle(SOLID_FILL, platformColor);
    bar(left, top, right, bottom);

    // Kotak kanan dengan celah
    left = right + gap;
    right = left + blockSize;

    setfillstyle(SOLID_FILL, gapColor);
    bar(left - gap, top - gap, right + gap, bottom + gap);

    setfillstyle(SOLID_FILL, platformColor);
    bar(left, top, right, bottom);
}

// Fungsi untuk menggambar baris 2 dan 4
void drawRow2(int x, int y, int gap, int blockSize) {
    int platformColor = COLOR(204, 102, 0); // Warna persegi panjang
    int gapColor = COLOR(0, 0, 0);          // Warna celah (hitam)
    int left = x, right, top = y, bottom = top + blockSize;

    // Persegi panjang pertama dengan celah
    right = left + (2 * blockSize);

    setfillstyle(SOLID_FILL, gapColor);
    bar(left - gap, top - gap, right + gap, bottom + gap);

    setfillstyle(SOLID_FILL, platformColor);
    bar(left, top, right, bottom);

    // Persegi panjang kedua dengan celah
    left = right + gap;
    right = left + (2 * blockSize);

    setfillstyle(SOLID_FILL, gapColor);
    bar(left - gap, top - gap, right + gap, bottom + gap);

    setfillstyle(SOLID_FILL, platformColor);
    bar(left, top, right, bottom);
}

// Fungsi untuk menggambar seluruh pola menggunakan ukuran fleksibel
void drawPlatform(int x, int y, int width, int height) {
    // Parameter pola
    int blockSize = 10; // Tetapkan ukuran tetap untuk kotak/persegi panjang
    int gap = 1;        // Celah antar objek
    int rowHeight = 2 * (blockSize + gap); // Tinggi total semua baris

    // Pusatkan pola jika height melebihi tinggi pola
    int offsetY = (height > rowHeight) ? (height - rowHeight) / 2 : 0;
    y += offsetY; // Tambahkan offset vertikal untuk pusatkan pola

    // Gambar setiap baris
    for (int i = 0; i < 4; i++) {
        int rowType = (i % 2 == 0) ? 1 : 2; // Baris 1 & 3 = tipe 1, Baris 2 & 4 = tipe 2
        if (rowType == 1) {
            drawRow(x, y, gap, blockSize);
        } else {
            drawRow2(x, y, gap, blockSize);
        }
        y += blockSize + gap; // Pindah ke posisi atas untuk baris berikutnya
    }
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