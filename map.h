#ifndef MAP_H
#define MAP_H

void drawMonsterDebugGrid();
void drawPlatform(int x, int y);
void drawGround(int x, int y);
void drawCoin(int x, int y);
void drawStar(int x, int y);
void drawMonster(int x, int y);
void animationMonster();
void drawSpike(int x, int y);
void drawCloud(int x, int y);
void drawGrid();
void drawStoneBlock(int x, int y);
void drawBrickBlock(int x, int y);
void drawCloudBlock(int x, int y)
void drawBodyPipe(int x, int y);
void drawPipe(int x, int y);
void drawBackground();
void drawNextLevel(int x, int y);
void renderLevel(GameState gameState);
void drawNightBackground();
void drawFlag(int x, int y);
void drawVictoryFlag(int x, int y);
void drawMap();

#endif // MAP_H