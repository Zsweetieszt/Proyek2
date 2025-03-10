#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <dos.h>

#define WORLD_WIDTH 40   // Total width of the game world
#define WORLD_HEIGHT 20  // Total height of the game world
#define VIEWPORT_WIDTH 20  // Width of the visible area (viewport)
#define VIEWPORT_HEIGHT 10 // Height of the visible area (viewport)


void showMainMenu() {
    cleardevice();  // Clear the graphics screen
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    outtextxy(100, 100, "Main Menu");
    outtextxy(100, 150, "1. Start Game");
    outtextxy(100, 200, "2. Exit");

    while (1) {
        int mouseX, mouseY;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            if (mouseX >= 100 && mouseX <= 300 && mouseY >= 150 && mouseY <= 180) {
                return;  // Start the game
            } else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 200 && mouseY <= 230) {
                exit(0);  // Exit the program
            }
        }
    }
}

int main(){
    initgraph(&gd,&gm, "C:\\TC\\BGI");
    showMainMenu();
}