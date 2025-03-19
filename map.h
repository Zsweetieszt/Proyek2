#ifndef MAP_H
#define MAP_H

void drawPlatform(int startX, int startY, int brickWidth, int brickHeight, int rows, int cols);
void drawCoin(int x, int y);
void drawStar(int x, int y);
void drawMonster();
void drawCharacter(int x, int y);
void drawSpike();
void drawMap();
void drawGrid();
void drawGround(int x, int y);
void drawCloud(int x, int y);
void drawBackground();
void drawCloud(int x, int y);
void drawPipe(int x, int y);
void drawBrickBlock(int x, int y);
void drawStoneBlock(int startX, int startY, int rectWidth, int rectHeight, int boxSize, int gap);
void drawNextLevel(int x, int y);



#endif // MAP_H
