#ifndef GAME_H
#define GAME_H

#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>

// Konstanta game
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define GROUND_HEIGHT 420
#define GRAVITY 1
#define JUMP_STRENGTH -16
#define MOVE_SPEED 9
#define MAP_WIDTH 16
#define MAP_HEIGHT 12
#define TOTAL_MAP_WIDTH 120
#define PLAYER_SIZE 1.5
#define MONSTER_SIZE 17
#define SPIKE_SIZE 17
#define SPIKE 6
#define SCROLL_SPEED 9
#define ROWS 35// Jumlah baris dalam array Player
#define COLS 25// Jumlah kolom dalam array Player
#define MOVE_DELAY 50 // Tambahkan delay saat berjalan (dalam ms)



// Variabel global (hanya deklarasi, definisi di game.c)
extern int playerX, playerY;
extern int velocityY;
extern int isJumping;
extern int level;
extern int isAlive;
extern int maps[3][MAP_HEIGHT][TOTAL_MAP_WIDTH];
extern int cameraX;
extern int cameraOffset;
extern int monsterX, monsterY, monsterDirection;

extern int score;  // Skor pemain
extern int coins;  // Jumlah koin yang dikumpulkan
extern int playerLives;

extern int hasStarPower;   // Apakah pemain memiliki Star Power (0 = tidak, 1 = aktif)
extern int starPowerTimer; // Waktu tersisa untuk Star Power dalam frame (10 detik)




// Prototipe fungsi umum
void updateGame();
void displayGameOver();
void displayScore();
void findMarioStartPosition();


#endif
