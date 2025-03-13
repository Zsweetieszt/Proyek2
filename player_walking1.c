#include "player.h"
#include "player_walking1.h"

// Representasi Mario dalam array 26x18

int player_walking1[ROWS][COLS]={
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, GREEN, GREEN, YELLOW, YELLOW, YELLOW, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, GREEN, GREEN, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, YELLOW, YELLOW, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, BLACK, BLACK, RED, RED, RED, RED, GREEN, GREEN, RED, BLACK, BLACK, BLACK, YELLOW, BLACK, BLACK},
    {BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, BLACK, YELLOW, YELLOW, YELLOW},
    {BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, RED, GREEN, YELLOW, YELLOW, YELLOW},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, YELLOW, YELLOW, YELLOW},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, GREEN, YELLOW, GREEN},
    {BLACK, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, GREEN, GREEN, RED, GREEN, GREEN, BLACK},
    {GREEN, GREEN, GREEN, GREEN, GREEN, GREEN, RED, RED, RED, YELLOW, RED, GREEN, YELLOW, GREEN, BLACK, BLACK},
    {GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, BLACK},
    {YELLOW, YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, BLACK, GREEN},
    {YELLOW, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, RED, RED, BLACK, GREEN, GREEN},
    {BLACK, YELLOW, YELLOW, YELLOW, RED, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, BLACK, RED, GREEN, RED, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {BLACK, BLACK, GREEN, RED, RED, GREEN, RED, RED, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, RED, RED, RED, GREEN, GREEN, RED, RED, RED, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, RED, RED, RED, RED, BLACK, BLACK, BLACK, GREEN, GREEN, GREEN, GREEN, GREEN},
    {GREEN, GREEN, GREEN, GREEN, GREEN, RED, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK},
    {BLACK, BLACK, GREEN, GREEN, GREEN, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK, BLACK}
};


int player_walking1_mirrored[ROWS][COLS];

// Fungsi untuk membuat mirrored array
    void mirrorPlayer(player_walking1, player_walking1_mirrored);