#ifndef PLAYER_H
#define PLAYER_H

#include "game.h"
#include <graphics.h>
#include <stdbool.h>

// Definisi warna
#define BLACK 0
#define RED COLOR(173, 58, 42)
#define GREEN COLOR(106, 107, 27)
#define YELLOW COLOR(227, 157, 37)
#define GREEN1 COLOR(58, 132, 0)
#define YELLOW1 COLOR(226, 158, 53)
#define WHITE COLOR(255, 255, 255)

typedef struct {
    int standing[ROWS][COLS];
    int walking1[ROWS][COLS];
    int walking2[ROWS][COLS];
    int jumping[ROWS][COLS];
    int dead[ROWS][COLS];
    int mirroredStanding[ROWS][COLS];
    int mirroredWalking1[ROWS][COLS];
    int mirroredWalking2[ROWS][COLS];
    int mirroredJumping[ROWS][COLS];
} Player;

extern Player player;
extern int (*currentCharacter)[COLS]; // Deklarasi sebagai variabel global untuk sprite aktif

// Deklarasi fungsi
void drawCharacter(int player[ROWS][COLS], int x, int y, bool hasStarPower);
void initializeMirrorPlayer(Player *player);
void mirrorPlayer(int currentCharacter[ROWS][COLS], int mirrored[ROWS][COLS]);
void handleInput();

#endif // PLAYER_H
