/* 
* Nama file: game.h
* Fungsi: 
* - Mendeklarasikan seluruh struktur data inti yang digunakan dalam game: seperti Camera, Player, Monster, Point, 
* GameState.
* - Menyimpan seluruh definisi konstanta penting: ukuran layar, kecepatan, jumlah level, ukuran peta, 
* dan lain-lain.
* - Mendeklarasikan fungsi-fungsi logika utama: seperti updateGame(), restartGame(), displayGameOver(), 
* playGameOverMusic() dan lain-lain.
*
*  Penulis: Dinanda Khayra Hutama
*  Tanggal: Sabtu, 31 Mei 2025
*/

#ifndef GAME_H
#define GAME_H

#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h>

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;

#define GROUND_HEIGHT 740
#define GRAVITY_UP 4
#define GRAVITY_DOWN 4
#define JUMP_STRENGTH -45
#define MOVE_SPEED 18
#define MAP_WIDTH 16
#define MAP_HEIGHT 13
#define TOTAL_MAP_WIDTH 150
#define PLAYER_SIZE 2.5
#define MONSTER_SIZE 17
#define SPIKE_SIZE 17
#define SPIKE 6
#define SCROLL_SPEED 18
#define ROWS 35
#define COLS 25
#define MOVE_DELAY 60
#define MAX_MONSTERS 20

typedef struct
{
    int x;
    int offset;
} Camera;
extern Camera camera;
typedef struct
{
    int x, y;
    int velocityY;
    int isJumping;
    int hasStarPower;
    int starPowerTimer;
    int playerLives;
} Player;
extern Player player;
typedef struct
{
    int score;
    int coins;
} Point;
extern Point point;
typedef struct
{
    int isRunning;
    int isAlive;
    int level;
    int hasWon;
    int playing;
} GameState;
extern GameState gameState;
typedef struct
{
    int x, y;
    int direction;
    int startX;
    int maxDistance;
} Monster;
extern Monster monsters[MAX_MONSTERS];
extern int monsterCount;
extern int levelMonsterCounts[1];
extern Monster levelMonsters[1][MAX_MONSTERS];
extern int maps[3][MAP_HEIGHT][TOTAL_MAP_WIDTH];
extern clock_t startClock;
extern clock_t endClock;
extern double gameDurationMs;

void updateGame();
void displayGameOver();
void displayPoint();
int findMarioStartPosition();
int restartGame();
void displayWinScreen(Point point, const char *playerName);
void updateMonsters();
void playBackgroundMusic();
void playWinMusic();
void playGameOverMusic();

#endif