#ifndef MARIO_H
#define MARIO_H

#include <graphics.h>
#include <conio.h>

#define PIXEL_SIZE 10 // Ukuran setiap kotak pixel
#define ROWS 26 // Jumlah baris dalam array Mario
#define COLS 18 // Jumlah kolom dalam array Mario

// Warna dalam graphics.h
#define BLACK 0
#define RED COLOR(173, 58, 42)
#define GREEN COLOR(106, 107, 27)
#define YELLOW COLOR(227, 157, 37)

// Deklarasi array Mario
extern int mario[ROWS][COLS];

// Deklarasi fungsi
void drawCharacter(int x, int y);
void handleInput();

#endif // MARIO_H
