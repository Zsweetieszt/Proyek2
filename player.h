#ifndef PLAYER_H
#define PLAYER_H

#define ROWS 35 // Jumlah baris dalam array Player
#define COLS 25 // Jumlah kolom dalam array Player

#define BLACK 0
#define RED COLOR(173, 58, 42)
#define GREEN COLOR(106, 107, 27)
#define YELLOW COLOR(227, 157, 37)
#define GREEN1 COLOR(58, 132, 0)
#define YELLOW1 COLOR(226, 158, 53)
#define WHITE 1



// Deklarasi array Mario
extern int player_standing[ROWS][COLS];
extern int player_walking1[ROWS][COLS];
extern int player_walking2[ROWS][COLS];
extern int player_jumping[ROWS][COLS];
extern int player_dead[ROWS][COLS];
extern int player_standing_mirrored[ROWS][COLS];
extern int player_walking1_mirrored[ROWS][COLS];
extern int player_walking2_mirrored[ROWS][COLS];
extern int player_jumping_mirrored[ROWS][COLS];

extern int (*currentCharacter)[COLS]; // Deklarasi sebagai variabel global

void initializeMirrorSprites();
void mirrorPlayer(int currentCharacter[ROWS][COLS], int mirrored[ROWS][COLS]);
void drawCharacter(int player[ROWS][COLS], int x, int y, bool hasStarPower);
void handleInput();

#endif // PLAYER_H
