#include "game.h"
#include "player.h"
#include "map.h"
#include "collision.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");  // Inisialisasi mode grafik

    int buffer = 0;
    while (isAlive) {  // Loop utama game
        setactivepage(buffer);  // Aktifkan buffer
        setvisualpage(1 - buffer);  // Tampilkan halaman yang sudah digambar

        cleardevice();  // Bersihkan buffer sebelum menggambar ulang
        drawBackground();
        drawMap();  // Gambar peta level
        //drawGrid();// Gambar Grid
      
        drawCharacter(playerX, playerY);  // Gambar pemain
        updateGame();  // Perbarui status game
        handleInput();  // Tangani input pemain
        checkCollisionWithMonster();  // Periksa tabrakan dengan monster
        checkCollisionWithSpike();  // Periksa tabrakan dengan duri
        displayScore();  // Tampilkan skor di layar
        
        buffer = 1 - buffer;  // Tukar buffer untuk frame berikutnya
        delay(15);  // Delay untuk kecepatan game
    }

    displayGameOver();  // Tampilkan layar game over
    closegraph();  // Tutup grafik
    return 0;
}