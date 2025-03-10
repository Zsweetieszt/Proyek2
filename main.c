#include "game.h"
#include "player.h"
#include "map.h"
#include "collision.h"

void displayMainMenu() {
    int choice = 0; // 0 for Start Game, 1 for Guide, 2 for Exit
    while (1) {
        cleardevice(); // Clear the screen
        setcolor(WHITE);
        outtextxy(100, 100, "Main Menu");
        outtextxy(100, 150, choice == 0 ? "> Start Game" : "  Start Game");
        outtextxy(100, 200, choice == 1 ? "> Guide" : "  Guide");
        outtextxy(100, 250, choice == 2 ? "> Exit" : "  Exit");

        if (kbhit()) {
            char key = getch();
            if (key == 'w' && choice > 0) {
                choice--;
            } else if (key == 's' && choice < 2) {
                choice++;
            } else if (key == '\r') { // Enter key
                break; // Exit the menu loop
            }
        }
        delay(100); // Delay for smoother navigation
    }

    if (choice == 0) {
        // Start the game
        // Call the game loop or initialization function here
    } else if (choice == 1) {
        displayGuide(); // Show the guide
    } else {
        // Exit the game
        closegraph();
        exit(0);
    }
}

void displayGuide() {
    int choice = 0; // 0 for Back
    while (1) {
        cleardevice(); // Clear the screen
        setcolor(WHITE);
        outtextxy(100, 100, "Game Guide");
        outtextxy(100, 150, "W - Move Up");
        outtextxy(100, 200, "A - Move Left");
        outtextxy(100, 250, "S - Move Down");
        outtextxy(100, 300, "D - Move Right");
        outtextxy(100, 350, "Press Enter to Jump");
        outtextxy(100, 400, choice == 0 ? "> Back" : "  Back");

        if (kbhit()) {
            char key = getch();
            if (key == 'w' && choice > 0) {
                choice--;
            } else if (key == 's' && choice < 0) {
                choice++;
            } else if (key == '\r') { // Enter key
                break; // Exit the guide loop
            }
        }
        delay(100); // Delay for smoother navigation
    }
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");  // Initialize graphics mode

    while (1) { // Main loop to allow restarting the game
        displayMainMenu(); // Show the main menu

        // Main game loop
        while (isAlive) {  
            cleardevice();  // Clear the screen
            drawMap();  // Draw the level map
            drawCharacter(playerX, playerY);  // Draw the player
            updateGame();  // Update game status
            handleInput();  // Handle player input
            checkCollisionWithMonster();  // Check for collisions
            checkCollisionWithSpike();  // Check for spikes
            delay(10);  // Delay for game speed
        }

        displayGameOver();  // Show game over screen
        // Do not close the graph, return to main menu instead
    }

    closegraph();  // Close graphics
    return 0;
}
