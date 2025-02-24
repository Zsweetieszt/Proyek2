#include <graphics.h>
#include <conio.h>

int main() {
    int gd = DETECT, gm;
    
    // Inisialisasi mode grafik
    initgraph(&gd, &gm, "C:\\Mingw-w64\\mingw64\\lib\\");

    // Menggambar lingkaran dengan pusat (250, 250) dan radius 100
    circle(250, 250, 100);

    // Tunggu input pengguna sebelum menutup
    getch();
    
    // Menutup mode grafik
    closegraph();
    
    return 0;
}
