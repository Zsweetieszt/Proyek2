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
#define JUMP_STRENGTH -17
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
#define STATE_MENU 0
#define STATE_PLAYING 1
#define STATE_GAMEOVER 2

typedef struct {
    int x;
    int offset;
} Camera;
extern Camera camera;

typedef struct {
    int x, y;
    int velocityY;
    int isJumping;
    int hasStarPower;
    int starPowerTimer;
    int playerLives;
} Player;
extern Player player;

typedef struct {
    int score; // Skor permainan
    int coins; // Jumlah koin yang dikumpulkan
} Point;
extern Point point;

typedef struct {
    int isRunning;  // Apakah game sedang berjalan
    int isAlive;    // Apakah pemain masih hidup
    int level;      // Level saat ini
    int hasWon ;     //ketika menang
    int playing;
} GameState;

extern GameState gameState;

typedef struct {
    int x, y;
    int direction; // 1 untuk ke kanan, -1 untuk ke kiri
} Monster;
extern Monster monster;

extern int maps[3][MAP_HEIGHT][TOTAL_MAP_WIDTH];



// Prototipe fungsi umum
void updateGame();
void displayGameOver();
void displayScore();
void findMarioStartPosition();
void restartGame();
void displayWinScreen(Point point, Player player);


#endif
