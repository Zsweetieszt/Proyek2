#include "player.h"

int player_standing[ROWS][COLS] = {
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, RED, GREEN, GREEN, GREEN, GREEN, RED, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, RED, GREEN, GREEN, GREEN, GREEN, RED, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, RED, GREEN, GREEN, GREEN, GREEN, RED, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, RED, GREEN, GREEN, GREEN, GREEN, RED, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, GREEN, GREEN, RED, YELLOW, RED, RED, RED, RED, YELLOW, RED, GREEN, GREEN, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, GREEN, RED, RED, RED, RED, RED, RED, RED, RED, GREEN, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, YELLOW, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, YELLOW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, RED, RED, RED,  RED, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, RED, RED, RED,  RED, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, RED, RED, RED,  RED, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK}
};


int player_walking1[ROWS][COLS]={
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, GREEN, GREEN, RED, BLACK, BLACK, BLACK, YELLOW, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, BLACK, YELLOW, YELLOW, YELLOW},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, RED, GREEN, YELLOW, YELLOW, YELLOW},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, YELLOW, YELLOW, YELLOW},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, GREEN, YELLOW, GREEN},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, GREEN, GREEN, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, RED, YELLOW, RED, GREEN, YELLOW, GREEN, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, GREEN},
    {YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, GREEN, GREEN},
    {BLACK, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, BLACK, RED, GREEN, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, GREEN, RED, RED, GREEN, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, RED, RED, RED, GREEN, GREEN, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK}
};


int player_walking2[ROWS][COLS]={
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, RED, RED, RED, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, RED, GREEN, GREEN, GREEN, RED, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, RED, GREEN, GREEN, GREEN, GREEN, RED, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, RED, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, YELLOW, YELLOW, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW},
    {BLACK, BLACK, BLACK, GREEN, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, RED, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, GREEN, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, RED, RED, RED, GREEN, RED, RED, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, RED, GREEN, GREEN, RED, RED, RED, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, GREEN, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, GREEN, RED, RED, RED, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK},
    {BLACK, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK}

};

int player_dead[ROWS][COLS] = {
    {BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, YELLOW, BLACK, RED, RED, RED, RED, RED, RED, BLACK, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, GREEN, YELLOW, GREEN, YELLOW, YELLOW, GREEN, YELLOW, GREEN, YELLOW, YELLOW, YELLOW},
    {YELLOW, YELLOW, GREEN, GREEN, YELLOW, GREEN, YELLOW, YELLOW, GREEN, YELLOW, GREEN, GREEN, YELLOW, YELLOW},
    {YELLOW, YELLOW, GREEN, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, YELLOW, YELLOW},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, GREEN, GREEN, GREEN, GREEN, YELLOW, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, BLACK, BLACK, BLACK},
    {BLACK, BLACK, RED, RED, RED, YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, BLACK, BLACK},
    {BLACK, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, RED, GREEN, GREEN, GREEN, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, YELLOW, RED, RED, YELLOW, RED, GREEN, GREEN, GREEN, BLACK},
    {BLACK, GREEN, GREEN, GREEN, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, BLACK},
    {BLACK, BLACK, GREEN, GREEN, RED, RED, RED, RED, RED, RED, GREEN, GREEN, BLACK, BLACK}
};

int player_standing_mirrored[ROWS][COLS];
int player_walking1_mirrored[ROWS][COLS];
int player_walking2_mirrored[ROWS][COLS];

// Fungsi untuk mencerminkan (mirroring) array
void mirrorPlayer(int original[ROWS][COLS], int mirrored[ROWS][COLS]) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            mirrored[i][j] = original[i][COLS - 1 - j];
        }
    }
}

// Fungsi untuk menggambar player di layar
void drawCharacter(int player[ROWS][COLS], int x, int y) {
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            if (player[i][j] != BLACK) { // Hanya menggambar piksel yang bukan hitam
                setfillstyle(SOLID_FILL, player[i][j]); // Set warna berdasarkan array
                bar(
                    x + j * PIXEL_SIZE,            // Koordinat kiri atas pixel
                    y + i * PIXEL_SIZE,            // Koordinat atas pixel
                    x + (j + 1) * PIXEL_SIZE,      // Koordinat kanan bawah pixel
                    y + (i + 1) * PIXEL_SIZE       // Koordinat bawah pixel
                );
            }
        }
    }
}