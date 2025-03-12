#include "game.h"
#include "player.h"
#include "map.h"
#include "collision.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char*)"");  // Inisialisasi mode grafik

    while (isAlive) {  // Loop utama game
        cleardevice();  // Bersihkan layar
        drawMap();  // Gambar peta level
        drawCharacter(playerX, playerY);  // Gambar pemain
        updateGame();  // Perbarui status game
        handleInput();  // Tangani input pemain
        checkCollisionWithMonster();  // Periksa tabrakan dengan monster
        checkCollisionWithSpike();  // Periksa tabrakan dengan duri
        delay(20);  // Delay untuk kecepatan game
    }

    displayGameOver();  // Tampilkan layar game over
    closegraph();  // Tutup grafik
    return 0;
}
