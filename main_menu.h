#ifndef MAINMENU_H
#define MAINMENU_H

#define WORLD_WIDTH 40   
#define WORLD_HEIGHT 20  
#define VIEWPORT_WIDTH 20  
#define VIEWPORT_HEIGHT 10

extern char playerName[50];

void showGuide();
void askPlayerNameGraphics();
void handleMouseClick(int mouseX, int mouseY);
void showMainMenu();

#endif