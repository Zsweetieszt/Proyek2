#ifndef GAME_H
#define GAME_H

#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

// Konstanta game
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define GROUND_HEIGHT 400
#define GRAVITY 1
#define JUMP_STRENGTH -15
#define MOVE_SPEED 5
#define MAP_WIDTH 10
#define MAP_HEIGHT 5
#define PLAYER_SIZE 20
#define MONSTER_SIZE 20
#define SPIKE 6

// Variabel global (hanya deklarasi, definisi di game.c)
extern int playerX, playerY;
extern int velocityY;
extern int isJumping;
extern int level;
extern int isAlive;
extern int maps[2][MAP_HEIGHT][MAP_WIDTH];

// Prototipe fungsi umum
void updateGame();
void displayGameOver();

#endif // GAME_H
