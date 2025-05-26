#include "game.h"
#include "player.h"
#include "map.h"
#include "collision.h"
#include "main_menu.h"
#include <conio.h>
#include <graphics.h>


int main() {
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);  
    int screenHeight = GetSystemMetrics(SM_CYSCREEN); 

    int windowWidth = screenWidth;
    int windowHeight = screenHeight; 

    SCREEN_WIDTH = screenWidth;
    SCREEN_HEIGHT = screenHeight;

    initwindow(windowWidth, windowHeight, "Mario Bros Adaptif");

    char playerName[50];
    printf("Enter your name: ");
    scanf("%s", playerName);

        showMainMenu();

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
            if (gameState.isAlive) { 
                updateGame();
                handleInput();
                displayPoint();
            }
            else
            {

                displayGameOver();

                char key = getch();
                if (key == 'R' || key == 'r')
                {
                    restartGame();
                }
                else if (key == 'M' || key == 'm')
                {

                    cleardevice();
                    gameState.isRunning = 0;
                    break;
                }
            }

            if (gameState.hasWon) {  
                displayWinScreen(point, playerName); 
                while (1) {  
                    char key = getch();
                    if (key == 'M' || key == 'm')
                    {
                        cleardevice();
                        gameState.hasWon = 0;
                        break;
                    }
                    else if (key == 'Q' || key == 'q')
                    {
                        closegraph();
                        return 0;
                    }
                }
                break;
            }

            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000)
            {
                gameState.isRunning = 0;
                closegraph();
                return 0;
            }

            buffer = 1 - buffer;
            delay(10);
        }
        
        closegraph();
        return 0;
    }