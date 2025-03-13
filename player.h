#ifndef PLAYER_H
#define PLAYER_H

#include <graphics.h>

#define PIXEL_SIZE 3 // Ukuran setiap kotak pixel
#define ROWS 26 // Jumlah baris dalam array Player
#define COLS 19 // Jumlah kolom dalam array Player

#define BLACK 0
#define RED COLOR(173, 58, 42)
#define GREEN COLOR(106, 107, 27)
#define YELLOW COLOR(227, 157, 37)

#define SCREEN_WIDTH getmaxwidth()
#define SCREEN_HEIGHT getmaxheight()


// Definisi tipe data untuk rintangan
typedef struct {
    int x;
    int y;
    int width;
    int height;
} Obstacle;

// Deklarasi fungsi umum
void mirrorPlayer(int original[ROWS][COLS], int mirrored[ROWS][COLS]);
void drawCharacter(int player[ROWS][COLS], int x, int y);
int checkCollision(int playerX, int playerY, int playerWidth, int playerHeight, Obstacle obstacle);
void drawObstacle(Obstacle obstacle);

#endif // PLAYER_H

