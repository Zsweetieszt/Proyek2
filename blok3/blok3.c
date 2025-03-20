#include <graphics.h>

void drawBrick(int x, int y, int width, int height, bool drawHorizontalGap, bool drawVerticalGap) {
    // Warna bata utama menjadi merah
    int mainColor = COLOR(215, 108, 44);
    // Warna gelap untuk celah antar bata menjadi hitam
    int gapColor = COLOR(60, 15, 5);
    
    // Mengisi bata utama
    setfillstyle(SOLID_FILL, mainColor);
    bar(x, y, x + width, y + height);
    
    // Membuat celah horizontal antar bata
    if (drawHorizontalGap) {
        setfillstyle(SOLID_FILL, gapColor);
        bar(x, y + height, x + width, y + height + 5); // Celah horizontal
    }

    // Membuat celah vertikal hanya jika diapit oleh dua bata
    if (drawVerticalGap) {
        setfillstyle(SOLID_FILL, gapColor);
        bar(x + width, y, x + width + 7, y + height); // Celah vertikal
    }

        // Menambahkan warna untuk sudut celah
    if (drawHorizontalGap && drawVerticalGap) {
        setfillstyle(SOLID_FILL, gapColor);
        bar(x + width, y + height, x + width + 7, y + height + 7); // Sudut celah
    }
    // Menambahkan warna untuk sudut celah
    if (drawHorizontalGap && drawVerticalGap) {
        setfillstyle(SOLID_FILL, gapColor);
        bar(x + width, y + height, x + width + 7, y + height + 7); // Sudut celah
    }    
}


int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");
    int borderColor = COLOR(60, 15, 5);

    // Mengatur background menjadi putih
    setbkcolor(WHITE);
    cleardevice();

    int startX = 50, startY = 50; // Koordinat awal
    int brickWidth = 40, brickHeight = 20; // Ukuran bata
    int rows = 5, cols = 3; // Jumlah baris dan kolom bata

    // Menggambar bata dalam grid
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < cols; j++) {
            bool drawHorizontalGap = (i < rows - 1); // Menghindari celah horizontal di bagian bawah
            bool drawVerticalGap = (j < cols - 1); // Menghindari celah vertikal di tepi kanan
            drawBrick(startX + j * (brickWidth + 5), startY + i * (brickHeight + 5), brickWidth, brickHeight, drawHorizontalGap, drawVerticalGap);
        }
    }

    // Menggambar border hitam tebal di sekitar kotak
    setcolor(borderColor);
    for(int i = 0; i < 4; i++) { // Menambahkan ketebalan border dengan menggambar beberapa rectangle
        rectangle(startX - 1 - i, startY - 1 - i, startX + cols * (brickWidth + 5) - 5 + i, startY + rows * (brickHeight + 5) - 5 + i);
    }

    getch();
    closegraph();
    return 0;
}
