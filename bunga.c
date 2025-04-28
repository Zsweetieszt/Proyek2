#include <graphics.h>
#include <conio.h>

// Fungsi untuk menggambar bunga pemakan
void drawPiranhaPlant(int x, int y) {
    // Menggambar batang hijau
    setcolor(GREEN);
    setfillstyle(SOLID_FILL, GREEN);
    rectangle(x - 10, y, x + 10, y + 60);
    floodfill(x, y + 30, GREEN);

    // Menggambar kepala bunga (merah)
    setcolor(RED);
    setfillstyle(SOLID_FILL, RED);
    fillellipse(x, y - 30, 30, 30);

    // Menambahkan bintik putih pada kepala
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x - 15, y - 40, 5, 5);
    fillellipse(x + 10, y - 35, 5, 5);
    fillellipse(x, y - 20, 5, 5);

    // Menggambar mulut bunga (hitam)
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, BLACK);
    pieslice(x, y - 30, 230, 310, 20); // Bentuk setengah lingkaran

    // Menggambar gigi (segitiga putih)
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    int gigiAtas[] = {x - 10, y - 35, x, y - 45, x + 10, y - 35, x - 10, y - 35};
    int gigiBawah[] = {x - 10, y - 25, x, y - 15, x + 10, y - 25, x - 10, y - 25};
    fillpoly(4, gigiAtas);
    fillpoly(4, gigiBawah);
}

int main() {
    // Inisialisasi graphics
    int gd = DETECT, gm;
    initgraph(&gd, &gm, ""); 

    // Gambar bunga pemakan di tengah layar
    drawPiranhaPlant(getmaxx() / 2, getmaxy() / 2);

    // Tunggu input sebelum menutup
    getch();
    closegraph();
    return 0;
}
