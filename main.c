#include "game.h"
#include "player.h"
#include "map.h"
#include "collision.h"
#include "main.h"
#include "Main_menu.h"
#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>

void showGuide() {
    cleardevice();
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2); // Use a triplex font for a 90s game feel
    outtextxy(100, 100, "Guide:");
    outtextxy(100, 150, "1. Use arrow keys to navigate.");
    outtextxy(100, 200, "2. Press 'Enter' to select an option.");
    outtextxy(100, 250, "3. Enjoy the game!");
    outtextxy(100, 300, "Press any key or click to return to the main menu.");
    
    while (!kbhit() && !ismouseclick(WM_LBUTTONDOWN)); // Wait for a key press or mouse click
    getch(); // Clear the key press
    cleardevice(); // Clear the screen before returning to the main menu
}

void handleMouseClick(int mouseX, int mouseY) {
    if (mouseX >= 100 && mouseX <= 300 && mouseY >= 150 && mouseY <= 180) {
        // Start the game
        outtextxy(100, 350, "Game Starting...");
        delay(2000); // Simulate game start
    } else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 200 && mouseY <= 230) {
        // Show guide
        showGuide();
    } else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 250 && mouseY <= 280) {
        exit(0);  // Exit the program
    }
}

void showMainMenu() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI"); // Initialize graphics mode
    cleardevice();  // Clear the graphics screen

    // Set background color
    setbkcolor(LIGHTBLUE);
    cleardevice();

    // Draw a simple character icon
    setcolor(RED);
    circle(200, 300, 20); // Example character

    // Change font style for a retro look
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2); // Use a triplex font for a 90s game feel
    setcolor(WHITE);
    outtextxy(100, 150, "Start Game");
    outtextxy(100, 200, "Guide");
    outtextxy(100, 250, "Exit");

    while (1) { 
        int mouseX, mouseY;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            handleMouseClick(mouseX, mouseY);
        }
    }
}


int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI"); // Initialize graphics mode

    while (1) { // Main loop to allow restarting the game
        showMainMenu(); // Call the showMainMenu function

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
