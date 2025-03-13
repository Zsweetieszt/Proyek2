<<<<<<< HEAD
#ifndef PLAYER_H
#define PLAYER_H
=======
#ifndef MARIO_H
#define MARIO_H
>>>>>>> d744a3fb3fdbe53b26318372bea3aad8e6f39fb4

#include <graphics.h>
#include <conio.h>

<<<<<<< HEAD
#define PIXEL_SIZE 10 // Ukuran setiap kotak pixel
#define ROWS 26 // Jumlah baris dalam array Mario
#define COLS 19 // Jumlah kolom dalam array Mario
=======
#define PIXEL_SIZE 3 // Ukuran setiap kotak pixel
#define ROWS 26 // Jumlah baris dalam array Mario
#define COLS 18 // Jumlah kolom dalam array Mario
>>>>>>> d744a3fb3fdbe53b26318372bea3aad8e6f39fb4

// Warna dalam graphics.h
#define BLACK 0
#define RED COLOR(173, 58, 42)
#define GREEN COLOR(106, 107, 27)
#define YELLOW COLOR(227, 157, 37)

// Deklarasi array Mario
extern int mario[ROWS][COLS];

// Deklarasi fungsi
void drawCharacter(int x, int y);
<<<<<<< HEAD
=======
void handleInput();
>>>>>>> d744a3fb3fdbe53b26318372bea3aad8e6f39fb4

#endif // MARIO_H
