#include "game.h"
#include "collision.h"  // Tambahkan ini untuk akses fungsi tabrakan
#include "map.h"

// Definisi variabel global

Monster monsters[MAX_MONSTERS];  // Array monster
int monsterCount = 0;  // Jumlah monster dalam level saat ini

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




int levelMonsterCounts[1] = {20};  // Jumlah monster di tiap level


//inisiasi camera
Camera camera = {
    0, //camera.x
    0  //camera.offside
}; 

// Inisialisasi Player
Player player = { 
    80,                  // x (posisi awal)
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
    0,   //level game
};




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
        {0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 13, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 12, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 6, 6, 1, 1, 6, 6, 1, 1, 0, 6, 0, 0, 0, 0, 0, 0, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 1, 1, 0, 0, 0, 0, 0 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    },
    {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 3, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 9, 9, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 6, 3, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 6, 0, 6, 0, 2, 6, 2, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 7, 0, 0, 0, 0, 3, 0, 3, 3, 3, 6, 0, 0, 0, 0, 0, 3, 3, 0, 0, 13, 13, 0, 0, 13, 13, 3, 3, 0, 0, 0, 0, 0, 0, 3, 6, 3, 0, 0, 0, 0, 0, 0, 0, 0, 6, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 6, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 13, 13, 0, 1, 1, 0, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 2, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 13, 13, 0, 0, 8, 8, 0, 0, 8, 8, 0, 0, 13, 13, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 1, 1, 0, 0, 0, 0 },
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 0, 0, 8, 8, 0, 0, 8, 8, 0, 0, 8, 8, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 2, 0, 6, 6, 3, 0, 0, 6, 6, 0, 0, 0, 8, 8, 0, 0, 0, 1, 1, 0, 0, 0 },
        {0, 12, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 8, 8, 6, 6, 8, 8, 6, 6, 8, 8, 6, 6, 8, 8, 0, 6, 6, 0, 0, 0, 6, 6, 6, 6, 6, 0, 6, 3, 6, 3, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 , 1, 1 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
    },
    {
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 9, 0, 0, 0, 0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 3, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 4, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 2, 2, 2, 2, 0, 0, 2, 2, 4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 4, 2, 2, 2, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 2, 0, 3, 0, 2, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 6, 3, 3, 6, 0, 0, 3, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 3, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 2, 2, 0, 0, 3, 0, 2, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 2, 0, 2, 0, 2, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 6, 0, 0, 0, 0, 0, 0, 0, 0, 14, 0, 0, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
        {2, 12, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 2, 0, 2, 6, 2, 6, 2, 6, 6, 6, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1 }
    },
};

// Fungsi untuk memperbarui status game
void updateGame() {
    if (!gameState.hasWon) {  // Jika belum menang, cek tabrakan
        checkCollisionWithFlag();
    }
    if (checkCollisionWithNextLevel()) {
        gameState.level++;  // Pindah ke level berikutnya
        if (gameState.level >= 3) {  
            gameState.level = 0; // Reset jika sudah level terakhir
        }
        findMarioStartPosition();
    }

    if (checkCollisionWithCoin()) {
        point.coins++;     // Tambah jumlah koin yang dikumpulkan
        point.score += 10; // Tambah skor pemain
    }

    player.y += player.velocityY;
    player.velocityY += GRAVITY;


    if (player.y >= GROUND_HEIGHT +17) {
        player.y = GROUND_HEIGHT +17;
        player.isJumping = 0;
    }
    

    // Cek tabrakan dengan musuh, duri, coin, starpower, nextLevel,Block
    cheakCollisionWithBlock();
    checkCollisionWithMonster();
    checkCollisionWithSpike();
    checkCollisionWithCoin();
    checkCollisionWithStar();
    checkCollisionWithNextLevel();

    // Gerakan musuh
    updateMonsters();  // Update semua monster


    // Untuk Star Power
    if (player.hasStarPower) {
        player.starPowerTimer--;
        if (player.starPowerTimer <= 0) {
            player.hasStarPower = 0;  // Matikan Star Power setelah 10 detik
        }
    }
    

}
int restartGame() {
    player.playerLives = 3;  
    gameState.isAlive = 1;  
    gameState.playing = 1;  
    point.score = 0; 
    point.coins = 0;  

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

    // 🔥 Reset monster sebelum mengisi ulang!
    monsterCount = 0;
    memset(monsters, 0, sizeof(monsters));  // Hapus semua monster dari level sebelumnya

    // 🔥 Ambil data monster sesuai level baru
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

    char scoreText[20];
    sprintf(scoreText, "Score: %d", point.score);
    outtextxy(10, 10, scoreText);  // Menampilkan skor di pojok kiri atas

    char coinText[20];
    sprintf(coinText, "Coins: %d", point.coins);
    outtextxy(10, 30, coinText);  // Menampilkan jumlah koin
    char livesText[20];
    sprintf(livesText, "live: %d", player.playerLives);
    outtextxy(10, 50, livesText);
}



// Fungsi untuk menampilkan layar Game Over
void displayGameOver() {
    setcolor(RED);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);

    char gameOverText[] = "GAME OVER";
    char retryText[] = "Press R to Retry";
    char menuText[] = "Press M for Main Menu";

    outtextxy(SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 2, gameOverText);
    outtextxy(SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 + 50, retryText);
    outtextxy(SCREEN_WIDTH / 2 - 220, SCREEN_HEIGHT / 2 + 100, menuText);
}


int findMarioStartPosition() {
    for (int i = 0; i < MAP_HEIGHT; i++) {
        for (int j = 0; j < TOTAL_MAP_WIDTH; j++) {
            if (maps[gameState.level][i][j] == 12) {
                player.x = j * (SCREEN_WIDTH / MAP_WIDTH);
                player.y = i * (SCREEN_HEIGHT / MAP_HEIGHT);

                // Atur kamera agar langsung melihat Mario
                camera.x = player.x - (SCREEN_WIDTH / 2);

                // Pastikan kamera tidak keluar batas level
                if (camera.x < 0) camera.x = 0;
                if (camera.x > TOTAL_MAP_WIDTH * (SCREEN_WIDTH / MAP_WIDTH) - SCREEN_WIDTH)
                    camera.x = TOTAL_MAP_WIDTH * (SCREEN_WIDTH / MAP_WIDTH) - SCREEN_WIDTH;

                return 1; //mario di temukan
            }
        }
    }
    return 0;//mario tidak di temukan
}

void displayWinScreen(Point point, Player player) {
    setactivepage(0);
    setvisualpage(0);
    cleardevice();
    
    setcolor(WHITE);
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    
    outtextxy(130, 150, (char*)"CONGRATULATIONS!");
    outtextxy(200, 200, (char*)"YOU WIN!");
    
    char scoreText[50], coinText[50], livesText[50];
    sprintf(scoreText, "SCORE: %d", point.score);
    sprintf(coinText, "COINS: %d", point.coins);
    sprintf(livesText, "LIVES LEFT: %d", player.playerLives);
    
    outtextxy(200, 250, scoreText);
    outtextxy(200, 280, coinText);
    outtextxy(200, 310, livesText);
    
    outtextxy(70, 350, (char*)"Press 'M' to Menu");
    outtextxy(70, 380, (char*)"Press 'Q' to Quit Game");
}

void updateMonsters() {
    for (int i = 0; i < monsterCount; i++) {  
        if (monsters[i].x != -999999) { // 🔥 Cek apakah monster masih ada di level
            monsters[i].x += monsters[i].direction * 2;

            // Batasi gerakan monster sesuai batas maxDistance
            if (monsters[i].x < monsters[i].startX - monsters[i].maxDistance || 
                monsters[i].x > monsters[i].startX + monsters[i].maxDistance) {
                monsters[i].direction *= -1;
            }
        }
    }
}



