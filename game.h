#ifndef GAME_H
#define GAME_H

#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>  // Library untuk pengelolaan waktu

// Konstanta game
#define SCREEN_WIDTH 1550
#define SCREEN_HEIGHT 840
#define GROUND_HEIGHT 740
#define GRAVITY 1
#define JUMP_STRENGTH -30
#define MOVE_SPEED 9
#define MAP_WIDTH 16
#define MAP_HEIGHT 13
#define TOTAL_MAP_WIDTH 150
#define PLAYER_SIZE 2.5
#define MONSTER_SIZE 17
#define SPIKE_SIZE 17
#define SPIKE 6
#define SCROLL_SPEED 9
#define ROWS 35// Jumlah baris dalam array Player
#define COLS 25// Jumlah kolom dalam array Player
#define MOVE_DELAY 60 // Tambahkan delay saat berjalan (dalam ms)
#define MAX_MONSTERS 20
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
    int x, y;           // Posisi monster
    int direction;      // Arah gerak: 1 = kanan, -1 = kiri
    int startX;         // Posisi awal monster (agar dia tidak bergerak jauh)
    int maxDistance;    // Seberapa jauh monster bisa bergerak dari startX
} Monster;

// 🔥 Hapus duplikasi & tetap deklarasikan hanya sekali
extern Monster monsters[MAX_MONSTERS];  // Array monster dalam level saat ini
extern int monsterCount;                // Jumlah monster dalam level saat ini

extern int levelMonsterCounts[1];       // Jumlah monster di tiap level
extern Monster levelMonsters[1][MAX_MONSTERS]; // Daftar monster di setiap level

extern int maps[3][MAP_HEIGHT][TOTAL_MAP_WIDTH];  // Peta level

extern clock_t startClock;
extern clock_t endClock;
extern double gameDurationMs;  // Durasi dalam milidetik





// Prototipe fungsi umum
void updateGame();
void displayGameOver();
void displayPoint();
int findMarioStartPosition();
int restartGame();
void displayWinScreen(Point point, Player player);
void updateMonsters();  // Deklarasi fungsi updateMonsters()



#endif