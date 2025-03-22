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

        // **Cek tombol untuk Restart atau kembali ke Main Menu**
        if (GetAsyncKeyState('R') & 0x8000) {  
            delay(200); // Hindari deteksi ganda
            restartGame();  
        } else if (GetAsyncKeyState('M') & 0x8000) {  
            delay(200);  
            isRunning = 0;  // **Pastikan loop utama berhenti**
            showMainMenu();  
            return 0;  // **Agar tidak kembali ke game loop setelah menu**
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