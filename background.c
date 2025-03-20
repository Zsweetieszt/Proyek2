#include "background.h"

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