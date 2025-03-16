#include <graphics.h>
#include <conio.h>

void drawBackground() {
    readimagefile("background.bmp", 0, 0, getmaxx(), getmaxy());
}

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    int x = 50, y = 100;
    
    drawBackground();  // Gambar background sekali saja

    getch();
    
    closegraph();
    return 0;
}