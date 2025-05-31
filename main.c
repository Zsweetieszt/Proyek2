#include "game.h"
#include "player.h"
#include "map.h"
#include "collision.h"
#include "main_menu.h"
#include "leaderboard.h"
#include <conio.h>
#include <graphics.h>
Leaderboard gameLeaderboard;
int main()
{
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int windowWidth = screenWidth;
    int windowHeight = screenHeight;
    SCREEN_WIDTH = screenWidth;
    SCREEN_HEIGHT = screenHeight;
    initwindow(windowWidth, windowHeight, "Mario Bros Adaptif");
    playBackgroundMusic();
    initLeaderboard(&gameLeaderboard);
    loadLeaderboard(&gameLeaderboard, "leaderboard.txt");
    while (1)
    {
        memset(playerName, 0, sizeof(playerName));
        showMainMenu();
        if (strlen(playerName) == 0)
        {
            break;
        }
        while (kbhit())
            getch();
        restartGame();
        gameState.isRunning = 1;
        int buffer = 0;


        while (gameState.isRunning)
        {
            setactivepage(buffer);
            setvisualpage(1 - buffer);
            cleardevice();
            renderLevel(gameState);
            drawMap();
            drawCharacter(currentCharacter, player.x, player.y, player.hasStarPower);
            initializeMirrorSprites();
            if (gameState.isAlive)
            {
                updateGame();
                handleInput();
                displayPoint();
            }
            else
            {
                displayGameOver();
                playGameOverMusic();
                char key = getch();
                if (key == 'R' || key == 'r')
                {
                    restartGame();
                    playBackgroundMusic();
                }
                else if (key == 'M' || key == 'm')
                {
                    cleardevice();
                    playBackgroundMusic();
                    gameState.isRunning = 0;
                    break;
                }
            }
            if (gameState.hasWon)
            {
                addScore(&gameLeaderboard, playerName, point.score);
                saveLeaderboard(&gameLeaderboard, "leaderboard.txt");
                displayWinScreen(point, playerName);
                playWinMusic();
                while (1)
                {
                    char key = getch();
                    if (key == 'M' || key == 'm')
                    {
                        cleardevice();
                        playBackgroundMusic();
                        gameState.hasWon = 0;
                        gameState.isRunning = 0;
                        break;
                    }
                    else if (key == 'Q' || key == 'q')
                    {
                        freeLeaderboard(&gameLeaderboard);
                        closegraph();
                        return 0;
                    }
                }
                break;
            }
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                freeLeaderboard(&gameLeaderboard);
                closegraph();
                return 0;
            }
            buffer = 1 - buffer;
            delay(10);
        }
    }
    freeLeaderboard(&gameLeaderboard);
    closegraph();
    return 0;
}