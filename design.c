#include "game.h"
#include "map.h"
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

void animationMonster() {
    // Hitung koordinat layar untuk monster
    int screenX = monsterX - cameraX * (SCREEN_WIDTH / MAP_WIDTH) - cameraOffset;
    int screenY = monsterY; // Koordinat Y tetap sama

    // Panggil fungsi desain baru dengan koordinat layar
    drawMonster(screenX, screenY);
}

void drawMonster(int x, int y) {
    // Kepala hantu (lingkaran)
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y, 15, 20);

    // Badan hantu (bagian bawah bergelombang)
    int body[] = {x - 15, y, x - 17, y + 15, x - 12, y + 20, x - 7, y + 15,
                  x - 2, y + 20, x + 2 , y + 15, x + 7, y + 20, x + 12, y + 15,
                  x + 15, y, x - 15, y};
    setfillstyle(SOLID_FILL, WHITE);
    fillpoly(10, body);

    // Mata hantu
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x - 5, y - 5, 2, 4);
    fillellipse(x + 5, y - 5, 2, 4);

    // Mulut hantu
    arc(x, y + 2, 200, 340, 5); // Mulut berbentuk setengah lingkaran
}


void drawBodyPipe(int x, int y){
    // Warna utama pipa hijau gelap
    int darkGreen = COLOR(0, 128, 0);
    // Warna hijau terang untuk efek cahaya
    int lightGreen = COLOR(0, 200, 0);
    // Warna bayangan lebih gelap
    int shadowGreen = COLOR(0, 100, 0);
    
    // Menggambar bagian bawah pipa (40x40 pixel)
    setcolor(darkGreen);
    setfillstyle(SOLID_FILL, darkGreen);
    bar(x, y, x + 40, y + 40);
    
    // Efek pencahayaan pada pipa
    setcolor(lightGreen);
    setfillstyle(SOLID_FILL, lightGreen);
    bar(x + 5, y, x + 15, y + 40);
    
    // Menambahkan bayangan di sisi kanan
    setcolor(shadowGreen);
    setfillstyle(SOLID_FILL, shadowGreen);
    bar(x + 30, y, x + 40, y + 40);
    
    // Menggambar bagian atas pipa (lebih lebar sedikit)
    setcolor(darkGreen);
    setfillstyle(SOLID_FILL, darkGreen);
    bar(x - 10, y - 20, x + 50, y);
    
    // Efek pencahayaan di bagian atas
    setcolor(lightGreen);
    setfillstyle(SOLID_FILL, lightGreen);
    bar(x - 5, y - 20, x + 10, y);
    
    // Menambahkan detail garis batas pada pipa
    setcolor(BLACK);
    rectangle(x, y, x + 40, y + 40);
    rectangle(x - 10, y - 20, x + 50, y);
}

void drawPipe(int x,int y){
    // Warna utama pipa hijau gelap
    int darkGreen = COLOR(0, 128, 0);
    // Warna hijau terang untuk efek cahaya
    int lightGreen = COLOR(0, 200, 0);
    // Warna bayangan lebih gelap
    int shadowGreen = COLOR(0, 100, 0);
    // Menggambar bagian bawah pipa (40x40 pixel)
    setcolor(darkGreen);
    setfillstyle(SOLID_FILL, darkGreen);
    bar(x, y, x + 40, y + 40);
    
    // Efek pencahayaan pada pipa
    setcolor(lightGreen);
    setfillstyle(SOLID_FILL, lightGreen);
    bar(x + 5, y, x + 15, y + 40);
    
    // Menambahkan bayangan di sisi kanan
    setcolor(shadowGreen);
    setfillstyle(SOLID_FILL, shadowGreen);
    bar(x + 30, y, x + 40, y + 40);
    // Menambahkan detail garis batas pada pipa
    setcolor(BLACK);
    rectangle(x, y, x , y + 40);
    
}

void drawCloudBlock(int x, int y) {
    int size = 32;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y, x + size, y + size * 2 / 3);
    bar(x + size * 2 / 3, y - size / 3, x + size * 5 / 3, y + size / 3);
    bar(x + size * 4 / 3, y, x + size * 7 / 3, y + size * 2 / 3);
}

void drawFlag(int x, int y) {
    int flagWidth = 50;  // Ukuran bendera diperbesar
    int flagHeight = 30;
    int poleHeight = 80; // Ukuran tiang diperbesar
    int poleWidth = 5;
    
    // Warna RGB untuk bendera (merah) dan tiang (abu-abu)
    int flagColor = COLOR(200, 0, 0);
    int poleColor = COLOR(100, 100, 100);
    int shadowColor = COLOR(150, 0, 0); // Bayangan lebih gelap
    int highlightColor = COLOR(255, 50, 50); // Efek pencahayaan
    int baseColor = COLOR(80, 80, 80); // Warna dasar tiang
    int textureColor = COLOR(120, 120, 120); // Tekstur tiang
    int flagTextureColor = COLOR(220, 50, 50); // Tekstur bendera
    
    // Gambar dasar tiang (lebih profesional dengan efek bayangan)
    setcolor(baseColor);
    setfillstyle(SOLID_FILL, baseColor);
    bar(x - 3, y, x + poleWidth + 3, y + 7);
    
    // Gambar tiang
    setcolor(poleColor);
    setfillstyle(SOLID_FILL, poleColor);
    bar(x, y - poleHeight, x + poleWidth, y);
    
    // Tambahkan tekstur pada tiang
    setcolor(textureColor);
    for (int i = y - poleHeight; i < y; i += 5) {
        line(x, i, x + poleWidth, i);
    }
    
    // Efek bayangan pada tiang
    setcolor(COLOR(60, 60, 60));
    line(x + poleWidth, y - poleHeight, x + poleWidth, y);
    
    // Gambar bayangan bendera
    setcolor(shadowColor);
    setfillstyle(SOLID_FILL, shadowColor);
    bar(x + poleWidth + 2, y - poleHeight + 2, x + poleWidth + flagWidth + 2, y - poleHeight + flagHeight + 2);
    
    // Gambar bendera
    setcolor(flagColor);
    setfillstyle(SOLID_FILL, flagColor);
    bar(x + poleWidth, y - poleHeight, x + poleWidth + flagWidth, y - poleHeight + flagHeight);
    
    // Tambahkan tekstur pada bendera
    setcolor(flagTextureColor);
    for (int i = y - poleHeight; i < y - poleHeight + flagHeight; i += 3) {
        line(x + poleWidth, i, x + poleWidth + flagWidth, i);
    }
    
    // Tambahkan highlight untuk efek pencahayaan
    setcolor(highlightColor);
    line(x + poleWidth + 2, y - poleHeight + 2, x + poleWidth + flagWidth - 2, y - poleHeight + 2);
    line(x + poleWidth + 2, y - poleHeight + 2, x + poleWidth + 2, y - poleHeight + flagHeight - 2);
}