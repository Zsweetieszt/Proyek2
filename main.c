#include "game.h"
#include "player.h"
#include "map.h"
#include "collision.h"
#include "main_menu.h"
#include <conio.h>  // Untuk getch()

// Misal variabel global
 // Status pemain hidup atau mati

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");  // Inisialisasi mode grafik

    while (1) {  
        // **Bersihkan layar sebelum menampilkan menu utama**
        showMainMenu();
    findAllMonsters();
        
        // **Hapus input buffer agar tidak ada input sisa**
        while (kbhit()) getch();  

        // **Jika pemain memilih Start Game, reset permainan**
        restartGame();     
        isRunning = 1;     

        int buffer = 0;
        
        // **Loop permainan utama**
        while (isRunning) {  
            setactivepage(buffer);
            setvisualpage(1 - buffer);
            cleardevice();

            drawBackground();
            drawMap();
            drawCharacter(currentCharacter, playerX, playerY, hasStarPower);
            initializeMirrorSprites();
        findAllMonsters();  // Cari semua monster yang ada di level

            if (isAlive) { 
                updateGame();
                handleInput();
                checkCollisionWithMonster();
                checkCollisionWithSpike();
                displayScore();
            } else {  
                // **Tampilan Game Over**
                displayGameOver();

                // **Gunakan getch() agar blocking, menunggu input pemain**
                char key = getch();
                if (key == 'R' || key == 'r') {  
                    restartGame();
                } else if (key == 'M' || key == 'm') {  
                    // **Bersihkan layar sebelum kembali ke menu**
                    cleardevice();
                    isRunning = 0;  
                    break;  // **Keluar dari loop permainan, kembali ke menu utama**
                }
            }

            // **Jika tombol Escape ditekan, keluar dari permainan sepenuhnya**
            if (GetAsyncKeyState(VK_ESCAPE) & 0x8000) {  
                isRunning = 0;
                closegraph();
                return 0;
            }

            buffer = 1 - buffer;
            delay(10);
        }
    }

    closegraph();
    return 0;
}
