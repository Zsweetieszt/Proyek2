#ifndef GAME_H
#define GAME_H

#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

// Konstanta game
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define GROUND_HEIGHT 425
#define GRAVITY 1
#define JUMP_STRENGTH -17
#define MOVE_SPEED 7
#define MAP_WIDTH 16
#define MAP_HEIGHT 12
#define TOTAL_MAP_WIDTH 120
#define PLAYER_SIZE 15
#define MONSTER_SIZE 17
#define SPIKE_SIZE 17
#define SPIKE 6
#define SCROLL_SPEED 5


// Variabel global (hanya deklarasi, definisi di game.c)
extern int playerX, playerY;
extern int velocityY;
extern int isJumping;
extern int level;
extern int isAlive;
extern int maps[2][MAP_HEIGHT][TOTAL_MAP_WIDTH];
extern int cameraX;
extern int cameraOffset;
extern int monsterX, monsterY, monsterDirection;


// Prototipe fungsi umum
void updateGame();
void displayGameOver();

#endif
