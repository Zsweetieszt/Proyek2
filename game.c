#include "game.h"
#include "collision.h"
#include "map.h"
#include "leaderboard.h"

// Definisi variabel global

Monster monsters[MAX_MONSTERS];
int monsterCount = 0;
int SCREEN_WIDTH = 1550;
int SCREEN_HEIGHT = 840;

Monster levelMonsters[1][MAX_MONSTERS] = {
    {
        {320,  GROUND_HEIGHT - 50,  1,  320,  130},
        {600,  GROUND_HEIGHT - 100, -1, 600,  150},
        {900,  GROUND_HEIGHT - 70,  1,  900,  200},
        {1200, GROUND_HEIGHT - 80, -1, 1200, 180},
        {1500, GROUND_HEIGHT - 200, 1,  1500, 140},
        {1750, GROUND_HEIGHT - 90, -1, 1750, 160},
        {2000, GROUND_HEIGHT - 50,  1,  2000, 240},
        {2250, GROUND_HEIGHT - 120, -1, 2250, 170},
        {2500, GROUND_HEIGHT - 60,  1,  2500, 150},
        {2750, GROUND_HEIGHT - 100, -1, 2750, 120},
        {3000, GROUND_HEIGHT - 250, 1,  3000, 210},
        {3200, GROUND_HEIGHT - 70, -1, 3200, 140},
        {3400, GROUND_HEIGHT - 40,  1,  3400, 160},
        {350,  GROUND_HEIGHT - 30, -1, 350,  220},
        {680,  GROUND_HEIGHT - 200, 1,  680,  130},
        {1280, GROUND_HEIGHT - 150, -1, 1280, 180},
        {1800, GROUND_HEIGHT - 80,  1,  1800, 170},
        {2400, GROUND_HEIGHT - 220, -1, 2400, 190},
        {2900, GROUND_HEIGHT - 140, 1,  2900, 200},
        {3350, GROUND_HEIGHT - 90, -1, 3350, 230},
    }
};




int levelMonsterCounts[1] = {20};


//inisiasi camera
Camera camera = {
    0, //camera.x
    0  //camera.offside
}; 

// Inisialisasi Player
Player player = { 
    80,                   // x (posisi awal)
    GROUND_HEIGHT - 30,   // y (posisi awal)
    0,                    // player.velocity
    0,                    // player.isJumping (tidak lompat)
    0,                    // hasStarPower
    0,                    // starPowerTimer
    3                     // lives (nyawa awal)
};

// Inisialisasi Point (score & coins)
Point point = { 
    0,  // score awal
    0   // coins awal
};

GameState gameState = { 
    1,   // isRunning (game dimulai)
    1,   // gameState.isAlive (pemain masih hidup)
    0,   // level (mulai dari level 0)
    0,   // kemenangan
    0,   // level game
};

clock_t startClock = 0;
clock_t endClock = 0;
double gameDurationMs = 0;


// Peta level
int maps[3][MAP_HEIGHT][TOTAL_MAP_WIDTH] = {
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 3, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 3, 0, 3, 0, 3, 6, 2, 2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 1, 2, 3, 3, 3, 3, 0, 0, 0, 14, 0, 0, 0, 0, 6, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 13, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 1, 1, 6, 6, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 1, 1, 0, 0, 0, 0, 0 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 3, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 3, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 6, 0, 6, 0, 2, 6, 2, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 1, 1, 0, 0, 0, 0 },
        {0, 7, 0, 0, 0, 0, 3, 0, 3, 3, 3, 6, 0, 0, 0, 0, 0, 3, 3, 0, 0, 13, 13, 0, 0, 13, 13, 0, 0, 3, 3, 0, 0, 0, 0, 3, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 6, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 6, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 13, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 13, 13, 0, 0, 8, 8, 0, 0, 8, 8, 0, 0, 13, 13, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 8, 8, 0, 0, 8, 8, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 0, 6, 6, 3, 0, 0, 6, 6, 0, 0, 0, 8, 8, 0, 0, 0, 1, 1, 0, 0, 0 },
        {0, 12, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 6, 6, 8, 8, 6, 6, 8, 8, 6, 6, 8, 8, 0, 6, 6, 0, 0, 0, 6, 6, 6, 6, 6, 0, 6, 3, 6, 3, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 , 1, 1 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    },
    {
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 4, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 2, 2, 2, 0, 0, 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 2, 2, 2, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 2, 0, 3, 0, 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 6, 3, 3, 6, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 3, 0, 2, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 12, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 2, 0, 2, 6, 2, 6, 2, 6, 6, 6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 },
    },
};

void updateGame() {
    int monsterHit = checkCollisionWithMonster();
    // Cek apakah Mario sedang naik atau jatuh
    if (player.velocityY < 0) {
        player.velocityY += GRAVITY_UP;
    } else {
        player.velocityY += GRAVITY_DOWN;
    }

    player.y += player.velocityY;

    // Cek apakah Mario menyentuh tanah
    if (player.y >= GROUND_HEIGHT - 30) {
        player.y = GROUND_HEIGHT - 30;
        player.isJumping = 0;
        player.velocityY = 0;
    }

    if (monsterHit != -1){
        int screenMonsterX = monsters[monsterHit].x - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
        int screenMonsterY = monsters[monsterHit].y;
         if (player.hasStarPower){
                monsters[monsterHit].x = -999999;
                point.score += 15;
            }
            else{
                if (gameState.level >= 2){
                    player.playerLives--;

                    if (player.playerLives > 0){
                        findMarioStartPosition();
                    }
                    else{
                        gameState.isAlive = 0;
                    }
                }
            }
    }

    if (checkCollisionWithStar()){
        player.hasStarPower = 1;
        player.starPowerTimer = 150;
    }

    if (checkCollisionWithFlag()){
        point.score += 100;
        gameState.hasWon = 1;
    }
    if (checkCollisionWithCoin()) {
        point.coins++;
        point.score += 10;
    }

    if (checkCollisionWithSpike()) {
        player.playerLives--;
        if (player.playerLives <= 0) {
            gameState.isAlive = 0;
        } else {
            findMarioStartPosition();
        }
    }

    if (!gameState.hasWon) {
        checkCollisionWithFlag();
    }

    if (checkCollisionWithNextLevel()) {
        gameState.level++;
        if (gameState.level >= 3) {
            gameState.level = 0;
        }
        findMarioStartPosition();
    }
    cheakCollisionWithBlock();

    updateMonsters();

    if (player.hasStarPower) {
        player.starPowerTimer--;
        if (player.starPowerTimer <= 0) {
            player.hasStarPower = 0;
        }
    }
}

int restartGame() {
    player.playerLives = 3;  
    gameState.isAlive = 1;  
    gameState.playing = 1;  
    point.score = 0; 
    point.coins = 0;
    startClock = clock();
    gameDurationMs = 0;

    findMarioStartPosition();  

    gameState.level = 0;
    for (int lvl = 0; lvl <= 3; lvl++) {  
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
                if (maps[lvl][i][j] == 20) {
                    maps[lvl][i][j] = 3;  
                }
            }
        }
    }
    for (int lvl = 0; lvl <= 3; lvl++) {  
        for (int i = 0; i < MAP_HEIGHT; i++) {
            for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
                if (maps[lvl][i][j] == 21) {
                    maps[lvl][i][j] = 5;  
                }
            }
        }
    }

    monsterCount = 0;
    memset(monsters, 0, sizeof(monsters));
    monsterCount = levelMonsterCounts[gameState.level];

    for (int i = 0; i < monsterCount; i++) {
        monsters[i] = levelMonsters[gameState.level][i];
    }
    gameState.isRunning = 1;
    return gameState.isRunning;
}



void displayPoint() {
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);

    char scoreText[20], coinText[20], livesText[20], timeText[30];

    double currentTimeMs = ((double)(clock() - startClock) / CLOCKS_PER_SEC) * 1000;
    sprintf(timeText, "%.2f sec", currentTimeMs / 1000);

    sprintf(scoreText, "Score: %d", point.score);
    sprintf(coinText, "Coins: %d", point.coins);
    sprintf(livesText, "Lives: %d", player.playerLives);

    outtextxy(10, 10, scoreText);
    outtextxy(10, 30, coinText);   
    outtextxy(10, 50, livesText);   

    int textWidth = textwidth(timeText);
    int screenCenterX = (SCREEN_WIDTH / 2) - (textWidth / 2);
    outtextxy(screenCenterX, 10, timeText); 
}


void displayGameOver() {
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    char gameOverText[] = "GAME OVER";
    char retryText[] = "Press R to Retry";
    char menuText[] = "Press M for Main Menu";

    outtextxy(SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 2, gameOverText);
    outtextxy(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 50, retryText);
    outtextxy(SCREEN_WIDTH / 2 - 260, SCREEN_HEIGHT / 2 + 100, menuText);
}


int findMarioStartPosition() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[gameState.level][i][j] == 12) {
                player.x = j * (SCREEN_WIDTH / MAP_WIDTH);
                player.y = i * (SCREEN_HEIGHT / MAP_HEIGHT);

                camera.x = player.x - (SCREEN_WIDTH / 2);

                if (camera.x < 0) camera.x = 0;
                if (camera.x > TOTAL_MAP_WIDTH * (SCREEN_WIDTH / MAP_WIDTH) - SCREEN_WIDTH)
                    camera.x = TOTAL_MAP_WIDTH * (SCREEN_WIDTH / MAP_WIDTH) - SCREEN_WIDTH;

                return 1;
            }
        }
    }
    return 0;
}

void displayWinScreen(Point point, const char* playerName) //update untuk playerName
{
    setactivepage(0);
    setvisualpage(0);
    cleardevice();

    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    int centerX = SCREEN_WIDTH / 2 - 250; 
    int startY = 80;

    outtextxy(centerX, startY, (char*)"  CONGRATULATIONS!");
    outtextxy(centerX + 40, startY + 40, (char*)"    YOU WIN!");

    
    if (endClock == 0) {
        endClock = clock();
        gameDurationMs = ((double)(endClock - startClock) / CLOCKS_PER_SEC) * 1000;
    }

    char scoreText[50], coinText[50], livesText[50], timeText[50];
    sprintf(scoreText, "SCORE      : %d", point.score);
    sprintf(coinText, "COINS      : %d", point.coins);
    sprintf(livesText, "LIVES LEFT : %d", player.playerLives);
    sprintf(timeText, "TIME       : %.2f sec (%.0f ms)", gameDurationMs / 1000, gameDurationMs);

    int textX = SCREEN_WIDTH / 2 - 200;
    int textY = startY + 100;
    int gap = 30;

    outtextxy(textX, textY, scoreText);
    outtextxy(textX, textY + gap, coinText);
    outtextxy(textX, textY + (gap * 2), livesText);
    outtextxy(textX, textY + (gap * 3), timeText);

    int menuX = SCREEN_WIDTH / 2 - 260;
    int menuY = textY + (gap * 5);

    outtextxy(menuX, menuY, (char*)"Press 'M' to Menu");
    outtextxy(menuX, menuY + 30, (char*)"Press 'Q' to Quit Game");
}



void updateMonsters() {
    for (int i = 0; i < monsterCount; i++) {  
        if (monsters[i].x != -999999) { 
            monsters[i].x += monsters[i].direction * 2;

            // Batasi gerakan monster sesuai batas maxDistance
            if (monsters[i].x < monsters[i].startX - monsters[i].maxDistance || 
                monsters[i].x > monsters[i].startX + monsters[i].maxDistance) {
                monsters[i].direction *= -1;
            }
        }
    }
}