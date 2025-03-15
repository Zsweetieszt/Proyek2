
#include "player_standing.h"
#include "player_walking1.h"
#include "player_walking2.h"
#include "player_dead.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, (char *)"");

    // Hasilkan versi mirrored langsung
    mirrorPlayer(player_walking1, player_walking1_mirrored);
    mirrorPlayer(player_walking2, player_walking2_mirrored);
    mirrorPlayer(player_standing, player_standing_mirrored);

    int playerX = 100, playerY = 300; // Posisi awal karakter
    int playerWidth = PIXEL_SIZE * COLS, playerHeight = PIXEL_SIZE * ROWS;
    int frame = 0; // Indeks frame animasi
    int key = 0;
    int direction = 1; // Default menghadap kanan (1: kanan, -1: kiri)
    int falling = 0;
    int velocity = 5;

    Obstacle obstacle = {SCREEN_WIDTH / playerX + 165, 300, 20, 100}; // Rintangan

    while (1) {
        cleardevice();

        // Gambar rintangan
        drawObstacle(obstacle);

        if (falling) {
            // Jika karakter jatuh, tampilkan animasi player_dead
            drawCharacter(player_dead, playerX, playerY);
            playerY += velocity; // Jatuh ke bawah
            if (playerY > SCREEN_HEIGHT) break; // Keluar layar = game selesai
        } else if (kbhit()) {
            // Jika ada input keyboard
            key = getch();
            if (key == 77) { // Panah kanan
                playerX += PIXEL_SIZE;
                direction = 1; // Perbarui arah ke kanan
                frame = (frame + 1) % 2; // Bergantian antara frame 0 dan 1
                drawCharacter(frame == 0 ? player_walking1 : player_walking2, playerX, playerY);
            } else if (key == 75) { // Panah kiri
                playerX -= PIXEL_SIZE;
                direction = -1; // Perbarui arah ke kiri
                frame = (frame + 1) % 2;
                drawCharacter(frame == 0 ? player_walking1_mirrored : player_walking2_mirrored, playerX, playerY);
            }
        } else {
            // Jika tidak ada input, gunakan player_standing
            if (direction == 1) {
                drawCharacter(player_standing, playerX, playerY); // Menghadap kanan
            } else {
                int player_standing_mirrored[ROWS][COLS]; // Buat array mirrored
                mirrorPlayer(player_standing, player_standing_mirrored);
                drawCharacter(player_standing_mirrored, playerX, playerY); // Menghadap kiri
            }
        }

        // Periksa tabrakan dengan rintangan
        if (checkCollision(playerX, playerY, playerWidth, playerHeight, obstacle)) {
            falling = 1; // Aktifkan status jatuh
        }

        delay(500); // Jeda untuk animasi
    }

    closegraph();
    return 0;

}