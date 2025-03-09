#include <graphics.h>

void drawRectangle(int x, int y, int width, int height) {
    // Warna persegi panjang
    int rectColor = COLOR(204, 102, 0); // RGB untuk oranye
    // Warna pemisah
    int gapColor = BLACK;
    
    // Mengisi persegi panjang
    setfillstyle(SOLID_FILL, rectColor);
    bar(x, y, x + width, y + height);

    // Menggambar pemisah hitam di sekeliling persegi panjang
    setcolor(gapColor);
    rectangle(x, y, x + width, y + height);
}

void drawSquare(int x, int y, int size) {
    // Warna kotak
    int rectColor = COLOR(204, 102, 0); // RGB untuk oranye
    // Warna pemisah
    int gapColor = BLACK; 

    // Mengisi kotak
    setfillstyle(SOLID_FILL, rectColor); 
    bar(x, y, x + size, y + size);

    // Menggambar pemisah hitam di sekeliling kotak
    setcolor(gapColor);
    rectangle(x, y, x + size, y + size);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Mengatur background menjadi putih 
    setbkcolor(WHITE);
    cleardevice();

    int startX = 50, startY = 50; // Koordinat awal
    int rectWidth = 85, rectHeight = 40; // Ukuran persegi panjang
    int boxSize = 40; // Ukuran kotak
    int gap = 5; // Ukuran pemisah

    // Baris 1: Dua persegi panjang menyamping
    drawRectangle(startX, startY, rectWidth, rectHeight);
    drawRectangle(startX + rectWidth + gap, startY, rectWidth, rectHeight);

    // Baris 2: Satu persegi panjang diapit oleh dua kotak di samping kanan dan kiri
    drawSquare(startX, startY + rectHeight + gap, boxSize);
    drawRectangle(startX + boxSize + gap, startY + rectHeight + gap, rectWidth, rectHeight);
    drawSquare(startX + boxSize + rectWidth + 2 * gap, startY + rectHeight + gap, boxSize);

    // Baris 3: Dua persegi panjang menyamping
    drawRectangle(startX, startY + 2 * (rectHeight + gap), rectWidth, rectHeight);
    drawRectangle(startX + rectWidth + gap, startY + 2 * (rectHeight + gap), rectWidth, rectHeight);

    // Baris 4: Satu persegi panjang diapit oleh dua kotak di samping kanan dan kiri
    drawSquare(startX, startY + 3 * (rectHeight + gap), boxSize);
    drawRectangle(startX + boxSize + gap, startY + 3 * (rectHeight + gap), rectWidth, rectHeight);
    drawSquare(startX + boxSize + rectWidth + 2 * gap, startY + 3 * (rectHeight + gap), boxSize);

    getch();
    closegraph();
    return 0;
}