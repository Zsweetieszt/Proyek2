#ifndef GAME_H
#define GAME_H

#include <graphics.h>
#include <conio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>  // Library untuk pengelolaan waktu

// Konstanta game
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
#define GROUND_HEIGHT 740
#define GRAVITY 1
#define JUMP_STRENGTH -30
#define MOVE_SPEED 9
#define MAP_WIDTH 16
#define MAP_HEIGHT 12
#define TOTAL_MAP_WIDTH 150
#define PLAYER_SIZE 2.5
#define MONSTER_SIZE 17
#define SPIKE_SIZE 17
#define SPIKE 6
#define SCROLL_SPEED 9
#define ROWS 35// Jumlah baris dalam array Player
#define COLS 25// Jumlah kolom dalam array Player
#define MOVE_DELAY 60 // Delay saat berjalan (dalam ms)
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
    int score;
    int coins;
} Point;
extern Point point;

typedef struct {
    int isRunning;
    int isAlive;  
    int level;    
    int hasWon ;
    int playing;
} GameState;

extern GameState gameState;

typedef struct {
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

extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;





// Prototipe fungsi umum
void updateGame();
void displayGameOver();
void displayPoint();
int findMarioStartPosition();
int restartGame();
void displayWinScreen(Point point, const char* playerName); // Tambahkan parameter playerName
void updateMonsters();  // Deklarasi fungsi updateMonsters()



#endif