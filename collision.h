#ifndef COLLISION_H
#define COLLISION_H

bool isCollidingWithSpike();
void checkCollisionWithMonster();

bool isCollidingWithCoin(int *coinX, int *coinY);
void checkCollisionWithStar();
void checkCollisionWithNextLevel();
void cheakCollisionWithBlock();
int checkCollisionWithFlag();



#endif // COLLISION_H
