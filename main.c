#include "game.h"
#include "player.h"
#include "map.h"
#include "collision.h"
#include "main_menu.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");  // Inisialisasi mode grafik
    
    
    int buffer = 0;
 // Game berjalan saat isRunning = 1
 showMainMenu();
 while (isRunning) {  
    setactivepage(buffer);
    setvisualpage(1 - buffer);
    cleardevice();

    drawBackground();
    drawMap();
    drawCharacter(currentCharacter, playerX, playerY, hasStarPower);
    initializeMirrorSprites();

    if (isAlive) { 
        updateGame();
        handleInput();
        checkCollisionWithMonster();
        checkCollisionWithSpike();
        displayScore();
    } else {  
        // **MENAMPILKAN GAME OVER**
        displayGameOver();

        char key = getch();
        if (key == 'R' || key == 'r') {  
            // Restart game dari awal
            restartGame();
        } else if (key == 'M' || key == 'm') {  
            // Kembali ke Main Menu
            isRunning = 0;  // Hentikan game loop
            showMainMenu();
            return 0;     // Pastikan keluar dari main() agar tidak lanjut
        }
    }
    // Jika tombol Escape ditekan, keluar dari game
    if (GetAsyncKeyState(VK_ESCAPE)) {  
        isRunning = 0;  
    }

    buffer = 1 - buffer;
    delay(10);
}

showMainMenu();  // Setelah keluar dari game, kembali ke menu utama
}