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
#define JUMP_STRENGTH -15
#define MOVE_SPEED 5
#define MAP_WIDTH 20
#define MAP_HEIGHT 15
#define TOTAL_MAP_WIDTH 100
#define PLAYER_SIZE 20
#define MONSTER_SIZE 20
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

// Prototipe fungsi umum
void updateGame();
void displayGameOver();

#endif
