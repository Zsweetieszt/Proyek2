#include "game.h"
#include "map.h"

// Fungsi untuk menggambar baris 1 dan 3
void drawRow13(int x, int y, int gap, int blockSize) {
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
void drawRow24(int x, int y, int gap, int blockSize) {
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
    int blockSize = 25; // Tetapkan ukuran tetap untuk kotak/persegi panjang
    int gap = 1;        // Celah antar objek
    int rowHeight = 2 * (blockSize + gap); // Tinggi total semua baris

    // Pusatkan pola jika height melebihi tinggi pola
    int offsetY = (height > rowHeight) ? (height - rowHeight) / 2 : 0;
    y += offsetY; // Tambahkan offset vertikal untuk pusatkan pola

    // Gambar setiap baris
    for (int i = 0; i < 4; i++) {
        int rowType = (i % 2 == 0) ? 1 : 2; // Baris 1 & 3 = tipe 1, Baris 2 & 4 = tipe 2
        if (rowType == 1) {
            drawRow13(x, y, gap, blockSize);
        } else {
            drawRow24(x, y, gap, blockSize);
        }
        y += blockSize + gap; // Pindah ke posisi atas untuk baris berikutnya
    }
}



void drawGround(int x, int y) {
    int tileSizeX = SCREEN_WIDTH / MAP_WIDTH;  
    int tileSizeY = SCREEN_HEIGHT / MAP_HEIGHT;
    int borderWidth = 1; // Ketebalan border

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


void drawCoin(int x, int y) {
    int size = 15;
    int i;
    for (i = size; i > 0; i--) {
        int colorFactor = (255 * i) / size;
        setcolor(COLOR(255, 215, colorFactor)); // Gradasi warna kuning keemasan
        setfillstyle(SOLID_FILL, COLOR(255, 215, colorFactor));
        fillellipse(x, y, i, i);
    }
    
    // Efek pencahayaan
    setcolor(COLOR(255, 255, 200));
    setfillstyle(SOLID_FILL, COLOR(255, 255, 200));
    fillellipse(x - size / 4, y - size / 4, size / 5, size / 5);
    
    // Detail garis vertikal di tengah koin
    setcolor(COLOR(200, 150, 0));
    setlinestyle(SOLID_LINE, 0, 3);
    line(x, y - size / 2, x, y + size / 2);
}

void animationMonster() {
    for (int i = 0; i < monsterCount; i++) {
        int screenX = monsters[i].x - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
        int screenY = monsters[i].y;  
        drawMonster(screenX, screenY);
    }

    // Debug grid untuk melihat area monster
    //drawMonsterDebugGrid();
}

void drawMonster(int x, int y) {
    // Kepala hantu (lingkaran)
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y, 15, 20);

    // Badan hantu (bagian bawah bergelombang)
int body[] = {
    x - 15, y + 1, x - 17, y + 16, x - 12, y + 21, x - 7, y + 16,
    x - 2, y + 21, x + 2 , y + 16, x + 7, y + 21, x + 12, y + 16,
    x + 15, y + 1, x - 15, y + 1
};
    setfillstyle(SOLID_FILL, WHITE);
    fillpoly(10, body);

    // Mata hantu
    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x - 5, y - 5, 2, 4);
    fillellipse(x + 5, y - 5, 2, 4);

    // Mulut hantu
    arc(x, y + 8, 20, 160, 5); // Mulut berbentuk setengah lingkaran
}


void drawSpike(int x, int y) {
    int tileSizeX = SCREEN_WIDTH / MAP_WIDTH;  
    int spikeHeight = tileSizeX / 2;  // Setengah dari ukuran tile

    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);

    int points[] = {
        x, y + spikeHeight,               // Bawah kiri
        x + tileSizeX / 2, y,             // Ujung atas
        x + tileSizeX, y + spikeHeight    // Bawah kanan
    };
    fillpoly(3, points);
}


void drawCloud(int x, int y) {
    int size = 64; // Ukuran piksel 32
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y, x + size, y + size * 2 / 3);
    bar(x + size * 2 / 3, y - size / 3, x + size * 5 / 3, y + size / 3);
    bar(x + size * 4 / 3, y, x + size * 7 / 3, y + size * 2 / 3);
}

void drawGrid() {
    setcolor(WHITE);
    for (int i = 0; i <= MAP_WIDTH; i++) {
        int x = i * (SCREEN_WIDTH / MAP_WIDTH);
        line(x, 0, x, SCREEN_HEIGHT);  // Garis vertikal
    }
    for (int i = 0; i <= MAP_HEIGHT; i++) {
        int y = i * (SCREEN_HEIGHT / MAP_HEIGHT);
        line(0, y, SCREEN_WIDTH, y);  // Garis horizontal
    }
}

void drawStoneBlock(int x, int y) {
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(x, y, x + 32, y + 32);

    setcolor(LIGHTGRAY);
    for (int i = 5; i < 32; i += 10) {
        line(x + i, y, x + i, y + 32);
    }
    for (int i = 5; i < 32; i += 10) {
        line(x, y + i, x + 32, y + i);
    }
}

void drawBrickBlock(int x, int y) {
    setfillstyle(SOLID_FILL, BROWN);
    bar(x, y, x + 32, y + 32);

    setcolor(DARKGRAY);
    for (int i = 5; i < 32; i += 10) {
        line(x, y + i, x + 32, y + i);
    }
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
    bar(x, y, x + 80, y + 80);
    
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
    rectangle(x, y, x, y + 40);
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
    rectangle(x, y -20 , x , y + 40);
    
}

void drawCloudBlock(int x, int y) {
    int size = 32;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y, x + size, y + size * 2 / 3);
    bar(x + size * 2 / 3, y - size / 3, x + size * 5 / 3, y + size / 3);
    bar(x + size * 4 / 3, y, x + size * 7 / 3, y + size * 2 / 3);
}

void drawStar(int x, int y) {
    int radius = 10;
    int color;
    for (int i = radius; i > 0; i--) {
        color = COLOR(255 - (i * 255 / radius), 100, i * 255 / radius); // Gradasi RGB
        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        fillellipse(x, y, i, i);
    }
}

void drawBackground() {
    // Gambar langit biru
    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, SCREEN_WIDTH, GROUND_HEIGHT + 25);

    // Gambar matahari (lingkaran kuning)
    int sunX = SCREEN_WIDTH / 2;  // Posisi X matahari (tengah layar)
    int sunY = 100;               // Posisi Y matahari
    int sunRadius = 100;           // Radius matahari

    // Gambar lingkaran matahari dengan warna kuning
    setcolor(YELLOW);            // Set warna garis
    setfillstyle(SOLID_FILL, YELLOW);  // Set warna isi
    fillellipse(sunX, sunY, sunRadius, sunRadius);  // Gambar matahari
}

void drawNextLevel(int x, int y) {
    int radius = 10;
    
    // Efek pencahayaan
    for (int i = 0; i < 5; i++) {
        int color = COLOR(0, 100, 255);
        setcolor(color);
        circle(x, y, radius + i * 3);
    }
    
    // Portal utama dengan gradasi warna
    for (int i = 0; i < radius; i++) {
        int color = COLOR(50 + i, 50 + 2 * i, 255 - i);
        setcolor(color);
        circle(x, y, radius - i);
    }
    
    // Partikel di sekitar portal
    for (int i = 0; i < 10; i++) {
        int angle = rand() % 360;
        int px = x + cos(angle * 3.14 / 180) * (radius + 40);
        int py = y + sin(angle * 3.14 / 180) * (radius + 40);
        putpixel(px, py, COLOR(255, 255, 255));
    }
}


void renderLevel(GameState gameState) {
    if (gameState.level == 0 || gameState.level == 1) {
        drawBackground(); // Latar belakang siang
    } else if (gameState.level == 2) {
        drawNightBackground(); // Latar belakang malam
    }
}
void drawNightBackground() {
    // Gambar langit malam (warna biru gelap)
    int DARKBLUE = COLOR(22,38, 79);
    setfillstyle(SOLID_FILL, DARKBLUE);
    bar(0, 0, SCREEN_WIDTH, GROUND_HEIGHT + 25);

    // Gambar bulan (lingkaran putih)
    int moonX = SCREEN_WIDTH / 2 + 100;  // Posisi X bulan (sedikit di samping)
    int moonY = 100;                     // Posisi Y bulan
    int moonRadius = 40;                 // Radius bulan

    // Gambar lingkaran bulan dengan warna putih
    setcolor(WHITE);                     // Set warna garis
    setfillstyle(SOLID_FILL, WHITE);     // Set warna isi
    fillellipse(moonX, moonY, moonRadius, moonRadius);  // Gambar bulan

    // Gambar beberapa bintang kecil
    setcolor(WHITE);                     // Warna bintang putih
    for (int i = 0; i < 10; i++) {
        int starX = rand() % SCREEN_WIDTH;  // Posisi acak X untuk bintang
        int starY = rand() % (GROUND_HEIGHT + 25);  // Posisi acak Y untuk bintang
        putpixel(starX, starY, WHITE);  // Gambar bintang kecil
    }
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
void drawVictoryFlag(int x, int y) {
    int flagWidth = 50;
    int flagHeight = 30;
    int poleHeight = 300;
    int poleWidth = 5;
    
    int flagColor = COLOR(200, 0, 0);
    int poleColor = COLOR(100, 100, 100);
    int shadowColor = COLOR(150, 0, 0);
    int highlightColor = COLOR(255, 50, 50);
    int baseColor = COLOR(80, 80, 80);
    int textureColor = COLOR(120, 120, 120);
    int flagTextureColor = COLOR(220, 50, 50);
    int starColor = COLOR(255, 255, 0);
    
    // Gambar dasar tiang
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
    int shadowTriangle[6] = {x + poleWidth, y - poleHeight + 2, x + poleWidth - flagWidth, y - poleHeight + flagHeight / 2 + 2, x + poleWidth, y - poleHeight + flagHeight + 2};
    fillpoly(3, shadowTriangle);
    
    // Gambar bendera segitiga menghadap kiri
    setcolor(flagColor);
    setfillstyle(SOLID_FILL, flagColor);
    int triangle[6] = {x + poleWidth, y - poleHeight, x + poleWidth - flagWidth, y - poleHeight + flagHeight / 2, x + poleWidth, y - poleHeight + flagHeight};
    fillpoly(3, triangle);
    
    // Tambahkan tekstur pada bendera
    setcolor(flagTextureColor);
    for (int i = y - poleHeight; i < y - poleHeight + flagHeight; i += 3) {
        line(x + poleWidth, i, x + poleWidth - flagWidth / 2, i);
    }
    
    // Tambahkan highlight untuk efek pencahayaan
    setcolor(highlightColor);
    line(x + poleWidth - 2, y - poleHeight + 2, x + poleWidth - flagWidth / 2 + 2, y - poleHeight + flagHeight / 4);
    line(x + poleWidth - 2, y - poleHeight + 2, x + poleWidth - 2, y - poleHeight + flagHeight - 2);
    
    // Gambar tanda kemenangan (bintang di dalam bendera)
    setcolor(starColor);
    setfillstyle(SOLID_FILL, starColor);
    int star[10] = {
        x + poleWidth - flagWidth / 3, y - poleHeight + flagHeight / 2 - 6,
        x + poleWidth - flagWidth / 3 + 6, y - poleHeight + flagHeight / 2 + 3,
        x + poleWidth - flagWidth / 3 - 6, y - poleHeight + flagHeight / 2 - 2,
        x + poleWidth - flagWidth / 3 + 6, y - poleHeight + flagHeight / 2 - 2,
        x + poleWidth - flagWidth / 3 - 6, y - poleHeight + flagHeight / 2 + 3
    };
    fillpoly(5, star);
}

void drawMap() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < MAP_WIDTH; j++) {
            int actualX = j + camera.x; // Ambil posisi asli di peta besar
            if (actualX >= TOTAL_MAP_WIDTH) continue; // Hindari menggambar di luar batas

            int tile = maps[gameState.level][i][actualX];
            int x = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset; // Sesuaikan dengan offset kamera
            int y = i * (SCREEN_HEIGHT / MAP_HEIGHT);
            
            switch (tile) {
                case 1:
                    drawGround(x, y);
                    break;
                case 2:
                    drawPlatform(x, y, SCREEN_WIDTH / MAP_WIDTH, 10);
                    break;
                case 3:
                    drawCoin(x+20, y+15);  // Sekarang menggambar koin
                    break;                
                case 4:
                    animationMonster();
                    break;
                case 5:
                    drawStar(x + 20, y + 20);
                    break;
                case 6:
                    drawSpike(x, y +20);
                    break;                                
                case 7:
                    drawNextLevel(x+20, y+20);
                    break;
                case 8:
                    drawPipe(x + 10, y + 20);
                    break;
                case 9:
                    drawCloud(x + 20, y + 20);
                    break;
                case 10:
                    drawBrickBlock(x + 20, y + 20);
                    break;
                case 11:
                    drawStoneBlock(x + 20, y + 20);
                    break;
                case 12:
                    drawFlag(x +20, y +63);
                    break;
                case 13:
                    drawBodyPipe(x + 10, y + 20);
                    break;
                case 14:
                    drawVictoryFlag(x +20, y +202);
                    break;

            }
        }
    }
}

void drawMonsterDebugGrid() {
    setcolor(RED);  // Warna merah untuk grid
    for (int i = 0; i < monsterCount; i++) {
        int screenX = monsters[i].x - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
        int screenY = monsters[i].y;

        // Gambar kotak hitbox monster
        rectangle(screenX, screenY, screenX + MONSTER_SIZE, screenY + MONSTER_SIZE);
        
        // Gambar garis silang (X) di dalam grid
        line(screenX, screenY, screenX + MONSTER_SIZE, screenY + MONSTER_SIZE);
        line(screenX + MONSTER_SIZE, screenY, screenX, screenY + MONSTER_SIZE);
    }
}
