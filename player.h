#ifndef PLAYER_H
#define PLAYER_H

#include <graphics.h>

#define PIXEL_SIZE 3 // Ukuran setiap kotak pixel
#define ROWS 35 // Jumlah baris dalam array Player
#define COLS 25 // Jumlah kolom dalam array Player

#define BLACK 0
#define RED COLOR(173, 58, 42)
#define GREEN COLOR(106, 107, 27)
#define YELLOW COLOR(227, 157, 37)

// Deklarasi animasi dan array karakter
extern int player_standing[ROWS][COLS];
extern int player_walking1[ROWS][COLS];
extern int player_walking2[ROWS][COLS];
extern int player_jumping[ROWS][COLS];
extern int player_dead[ROWS][COLS];

extern int player_standing_mirrored[ROWS][COLS];
extern int player_walking1_mirrored[ROWS][COLS];
extern int player_walking2_mirrored[ROWS][COLS];
extern int player_jumping_mirrorred[ROWS][COLS];

// Deklarasi fungsi umum
void mirrorPlayer(int original[ROWS][COLS], int mirrored[ROWS][COLS]);
void drawCharacter(int player[ROWS][COLS], int x, int y);

#endif // PLAYER_H