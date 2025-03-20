#include <graphics.h>

// Fungsi untuk menggambar kotak dengan border dan titik di sudutnya
void drawRectangleWithBorderAndDots(int x, int y, int width, int height, int borderWidth) {
    // Warna utama kotak (oranye)
    int mainColor = COLOR(204, 102, 0); // RGB untuk oranye
    // Warna border dan titik
    int borderColor = BLACK;
    // Warna titik
    int dotColor = BLACK;

    // Mengisi kotak utama
    setfillstyle(SOLID_FILL, mainColor);
    setcolor(mainColor); // Set warna untuk fungsi bar
    bar(x, y, x + width, y + height);

    // Menggambar border hitam
    setcolor(borderColor);
    for(int i = 0; i < borderWidth; i++) {
        rectangle(x - i, y - i, x + width + i, y + height + i);
    }
    
    // Menggambar titik di dalam sudut dengan jarak
    int dotDistance = 10; // Jarak titik dari sudut kotak
    int dotRadius = 3; // Radius titik ditambah untuk lebih tebal

    setcolor(dotColor);
    setfillstyle(SOLID_FILL, dotColor);

    // Titik sudut kiri atas
    fillellipse(x + dotDistance, y + dotDistance, dotRadius, dotRadius);
    // Titik sudut kanan atas
    fillellipse(x + width - dotDistance, y + dotDistance, dotRadius, dotRadius);
    // Titik sudut kiri bawah
    fillellipse(x + dotDistance, y + height - dotDistance, dotRadius, dotRadius);
    // Titik sudut kanan bawah
    fillellipse(x + width - dotDistance, y + height - dotDistance, dotRadius, dotRadius);
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Mengatur background menjadi putih
    setbkcolor(WHITE);
    cleardevice();

    int startX = 100, startY = 100; // Koordinat awal
    int rectWidth = 100, rectHeight = 100; // Ukuran kotak
    int borderWidth = 3; // Ketebalan border

    // Menggambar kotak dengan border hitam dan titik di sudut
    drawRectangleWithBorderAndDots(startX, startY, rectWidth, rectHeight, borderWidth);

    getch();
    closegraph();
    return 0;
}