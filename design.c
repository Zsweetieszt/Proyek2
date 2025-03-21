#include "design.h"

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

void drawCloudBlock(int x, int y) {
    int size = 32;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y, x + size, y + size * 2 / 3);
    bar(x + size * 2 / 3, y - size / 3, x + size * 5 / 3, y + size / 3);
    bar(x + size * 4 / 3, y, x + size * 7 / 3, y + size * 2 / 3);
}

void drawMonster(int x, int y) {
    // Kepala hantu (lingkaran)
        setfillstyle(SOLID_FILL, WHITE);
        fillellipse(x, y, 30, 40);
    
        // Badan hantu (bagian bawah bergelombang)
        int body[] = {x - 30, y, x - 35, y + 30, x - 25, y + 40, x - 15, y + 30,
                    x - 5, y + 40, x + 5, y + 30, x + 15, y + 40, x + 25, y + 30,
                    x + 30, y, x - 30, y}; 
        setfillstyle(SOLID_FILL, WHITE);
        fillpoly(10, body);
    
        // Mata hantu
        setfillstyle(SOLID_FILL, BLACK);
        fillellipse(x - 10, y - 10, 5, 8);
        fillellipse(x + 10, y - 10, 5, 8);
    
        // Mulut hantu
        arc(x, y + 5, 200, 340, 10); // Mulut berbentuk setengah lingkaran
    
    }

    // Fungsi menggambar pipa dengan ukuran dan posisi fleksibel
void drawPipe(int x, int y, int width, int height) {
    int warna1 = COLOR(1, 166, 1);
    int warna2 = COLOR(111, 202, 48);

    // **1. Bagian Atas Pipa (Lebih Lebar)**
    setfillstyle(SOLID_FILL, warna1);
    bar(x - 10, y, x + width + 10, y + 20);

    // **2. Batang Pipa (Vertikal)**
    setfillstyle(SOLID_FILL, warna1);
    bar(x, y + 20, x + width, y + height);

    // **3. Detail Garis Hijau Tua**
    setcolor(warna1);
    for (int i = 0; i < 3; i++) {
        line(x + (i * 10) + 5, y + 20, x + (i * 10) + 5, y + height);
    }

    // **4. Efek Shading Kuning Tebal**
    setcolor(warna2);
    for (int i = 0; i < 3; i++) {
        line(x + (i * 5) + 2, y + 20, x + (i * 5) + 2, y + height);
    }

    setfillstyle(SOLID_FILL, warna2);
    bar(x + 10, y + 20, x + 15, y + height);  // Bar tambahan agar shading lebih nyata

    // **5. Outline Hitam Agar Lebih Tegas**
    setcolor(BLACK);
    setlinestyle(SOLID_LINE, 0, 3);

    // Garis luar (outline utama)
    rectangle(x - 10, y, x + width + 10, y + 20); // Bagian atas pipa
    rectangle(x, y + 20, x + width, y + height);  // Batang pipa

    // **6. Garis Hitam di Ujung Pipa (Atas & Bawah)**
    line(x - 10, y, x + width + 10, y);  // Garis atas pipa
    line(x - 10, y + 20, x + width + 10, y + 20); // Garis bawah bagian atas
    line(x, y + height, x + width, y + height);   // Garis bawah batang pipa
}