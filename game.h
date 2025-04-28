#ifndef GAME_H
#define GAME_H

#include <graphics.h>
 #include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define SCREEN_WIDTH 1550
#define SCREEN_HEIGHT 840
#define GROUND_HEIGHT 780
#define GRAVITY 1
#define JUMP_STRENGTH -25
#define MOVE_SPEED 9
#define MAP_WIDTH 17
#define MAP_HEIGHT 13
#define TOTAL_MAP_WIDTH 150
#define PLAYER_SIZE 2.5
#define MONSTER_SIZE 17
#define SPIKE_SIZE 17
#define SPIKE 6
#define SCROLL_SPEED 9
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
void displayWinScreen(Point point, Player player);
void updateMonsters();

#endif