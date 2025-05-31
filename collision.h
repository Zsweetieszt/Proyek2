/*
 * Nama file: collision.c
 * 
 * File ini menangani berbagai logika deteksi tumbukan (collision detection) dalam permainan.
 * termasuk interaksi antara pemain dengan elemen-elemen seperti duri, monster, koin, bintang, blok/platform,
 * bendera (flag), dan titik perpindahan ke level berikutnya.
 * 
 * Penulis: Revan Ramdani Permana
 * Tanggal: Senin, 26 Mei 2025
 * 
*/

#ifndef COLLISION_H
#define COLLISION_H
#include <stdbool.h>

bool checkCollisionWithSpike();
int checkCollisionWithMonster();
bool checkCollisionWithCoin();
bool checkCollisionWithStar();
bool checkCollisionWithNextLevel();
void cheakCollisionWithBlock();
bool checkCollisionWithFlag();
void checkcollsionwithpipe();

#endif // COLLISION_H