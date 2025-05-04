#ifndef MAP_H
#define MAP_H

void drawPlatform(int x, int y);
void drawCoin(int x, int y);
void drawStar(int x, int y);
void drawMonster(int x, int y);
void drawSpike(int x, int y);
void drawMap();
void drawGrid();
void drawGround(int x, int y);
void drawCloud(int x, int y);
void drawBackground();
void drawCloud(int x, int y);
void drawPipe(int x, int y);
void drawBrickBlock(int x, int y);
void drawStoneBlock(int x, int y);
void drawNextLevel(int x, int y);
void drawFlag(int x, int y);
void drawBodyPipe(int x, int y);
void drawVictoryFlag(int x, int y);
void animationMonster();
void drawMonsterDebugGrid();
void renderLevel(GameState gameState);
void drawNightBackground();



#endif // MAP_H