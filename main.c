#include "game.h"
#include "player.h"
#include "map.h"
#include "collision.h"


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

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");  // Inisialisasi mode grafik

    showMainMenu();


    while (isAlive) {  // Loop utama game
        cleardevice();  // Bersihkan layar
        drawMap();  // Gambar peta level
        drawCharacter(playerX, playerY);  // Gambar pemain
        updateGame();  // Perbarui status game
        handleInput();  // Tangani input pemain
        checkCollisionWithMonster();  // Periksa tabrakan dengan monster
        checkCollisionWithSpike();  // Periksa tabrakan dengan duri
        delay(10);  // Delay untuk kecepatan game
    }

    displayGameOver();  // Tampilkan layar game over
    closegraph();  // Tutup grafik
    return 0;
}
