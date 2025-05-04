#ifndef PLAYER_H
#define PLAYER_H
#include <stdbool.h>

#define BLACK 0
#define RED COLOR(173, 58, 42)
#define GREEN COLOR(106, 107, 27)
#define YELLOW COLOR(227, 157, 37)
#define GREEN1 COLOR(58, 132, 0)
#define YELLOW1 COLOR(226, 158, 53)
#define WHITE COLOR(255,255,255)

extern int player_standing[ROWS][COLS];
extern int player_walking1[ROWS][COLS];
extern int player_walking2[ROWS][COLS];
extern int player_jumping[ROWS][COLS];
extern int player_dead[ROWS][COLS];
extern int player_standing_mirrored[ROWS][COLS];
extern int player_walking1_mirrored[ROWS][COLS];
extern int player_walking2_mirrored[ROWS][COLS];
extern int player_jumping_mirrored[ROWS][COLS];
extern int playerLeft, playerRight, playerTop, playerBottom; 

extern int (*currentCharacter)[COLS]; 

void initializeMirrorSprites();
void mirrorPlayer(int currentCharacter[ROWS][COLS], int mirrored[ROWS][COLS]);
void drawCharacter(int player[ROWS][COLS], int x, int y, bool hasStarPower);
int handleInput();
void updatePlayerBounds();

#endif 