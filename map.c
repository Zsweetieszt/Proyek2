#include "game.h"
#include "map.h"

void drawMonsterDebugGrid()
{
    setcolor(RED);
    for (int i = 0; i < monsterCount; i++)
    {
        int screenX = monsters[i].x - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
        int screenY = monsters[i].y;

        rectangle(screenX, screenY, screenX + MONSTER_SIZE, screenY + MONSTER_SIZE);

        line(screenX, screenY, screenX + MONSTER_SIZE, screenY + MONSTER_SIZE);
        line(screenX + MONSTER_SIZE, screenY, screenX, screenY + MONSTER_SIZE);
    }
}

void drawPlatform(int x, int y)
{
    int tileSizeX = SCREEN_WIDTH / MAP_WIDTH;
    int tileSizeY = SCREEN_HEIGHT / MAP_HEIGHT;
    int platformColor = COLOR(204, 102, 0);
    int gapColor = COLOR(0, 0, 0);

    int rowCount = 4;
    int gap = tileSizeY / (rowCount * 10);
    int blockHeight = (tileSizeY - (rowCount - 1) * gap) / rowCount;

    int yPos = y;
    for (int i = 0; i < rowCount; i++)
    {
        int left = x;
        int top = yPos;
        int bottom = top + blockHeight;

        if (i % 2 == 0)
        {

            int totalGap = 2 * gap;
            int boxW = (tileSizeX - totalGap) / 4;
            int rectW = 2 * boxW;

            setfillstyle(SOLID_FILL, gapColor);
            bar(left - gap, top - gap, left + boxW + gap, bottom + gap);
            setfillstyle(SOLID_FILL, platformColor);
            bar(left, top, left + boxW, bottom);

            left += boxW + gap;
            setfillstyle(SOLID_FILL, gapColor);
            bar(left - gap, top - gap, left + rectW + gap, bottom + gap);
            setfillstyle(SOLID_FILL, platformColor);
            bar(left, top, left + rectW, bottom);

            left += rectW + gap;
            setfillstyle(SOLID_FILL, gapColor);
            bar(left - gap, top - gap, left + boxW + gap, bottom + gap);
            setfillstyle(SOLID_FILL, platformColor);
            bar(left, top, left + boxW, bottom);
        }
        else
        {

            int rectW = (tileSizeX - gap) / 2;

            setfillstyle(SOLID_FILL, gapColor);
            bar(left - gap, top - gap, left + rectW + gap, bottom + gap);
            setfillstyle(SOLID_FILL, platformColor);
            bar(left, top, left + rectW, bottom);

            left += rectW + gap;
            setfillstyle(SOLID_FILL, gapColor);
            bar(left - gap, top - gap, left + rectW + gap, bottom + gap);
            setfillstyle(SOLID_FILL, platformColor);
            bar(left, top, left + rectW, bottom);
        }

        yPos += blockHeight + gap;
    }
}

void drawGround(int x, int y)
{
    int tileSizeX = SCREEN_WIDTH / MAP_WIDTH;
    int tileSizeY = SCREEN_HEIGHT / MAP_HEIGHT;
    int borderWidth = 1;

    int mainColor = COLOR(204, 102, 0);
    int borderColor = BLACK;
    int dotColor = BLACK;

    setfillstyle(SOLID_FILL, mainColor);
    bar(x, y, x + tileSizeX, y + tileSizeY);

    setcolor(borderColor);
    for (int i = 0; i < borderWidth; i++)
    {
        rectangle(x - i, y - i, x + tileSizeX + i, y + tileSizeY + i);
    }

    int dotDistance = 10;
    int dotRadius = 3;

    setcolor(dotColor);
    setfillstyle(SOLID_FILL, dotColor);

    fillellipse(x + dotDistance, y + dotDistance, dotRadius, dotRadius);
    fillellipse(x + tileSizeX - dotDistance, y + dotDistance, dotRadius, dotRadius);
    fillellipse(x + dotDistance, y + tileSizeY - dotDistance, dotRadius, dotRadius);
    fillellipse(x + tileSizeX - dotDistance, y + tileSizeY - dotDistance, dotRadius, dotRadius);
}

void drawCoin(int x, int y)
{
    int size = 15;
    int i;
    for (i = size; i > 0; i--)
    {
        int colorFactor = (255 * i) / size;
        setcolor(COLOR(255, 215, colorFactor));
        setfillstyle(SOLID_FILL, COLOR(255, 215, colorFactor));
        fillellipse(x, y, i, i);
    }

    setcolor(COLOR(255, 255, 200));
    setfillstyle(SOLID_FILL, COLOR(255, 255, 200));
    fillellipse(x - size / 4, y - size / 4, size / 5, size / 5);

    setcolor(COLOR(200, 150, 0));
    setlinestyle(SOLID_LINE, 0, 3);
    line(x, y - size / 2, x, y + size / 2);
}

void drawStar(int x, int y)
{
    int radius = 10;
    int color;
    for (int i = radius; i > 0; i--)
    {
        color = COLOR(255 - (i * 255 / radius), 100, i * 255 / radius);
        setcolor(color);
        setfillstyle(SOLID_FILL, color);
        fillellipse(x, y, i, i);
    }
}

void drawMonster(int x, int y)
{

    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(x, y, 15, 20);

    int body[] = {
        x - 15, y + 1, x - 17, y + 16, x - 12, y + 21, x - 7, y + 16,
        x - 2, y + 21, x + 2, y + 16, x + 7, y + 21, x + 12, y + 16,
        x + 15, y + 1, x - 15, y + 1};
    setfillstyle(SOLID_FILL, WHITE);
    fillpoly(10, body);

    setfillstyle(SOLID_FILL, BLACK);
    fillellipse(x - 5, y - 5, 2, 4);
    fillellipse(x + 5, y - 5, 2, 4);

    arc(x, y + 8, 20, 160, 5);
}

void animationMonster()
{
    for (int i = 0; i < monsterCount; i++)
    {
        int screenX = monsters[i].x - camera.x * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
        int screenY = monsters[i].y;
        drawMonster(screenX, screenY);
    }
}

void drawSpike(int x, int y)
{
    int tileSizeX = SCREEN_WIDTH / MAP_WIDTH;
    int spikeHeight = tileSizeX / 2;

    setcolor(DARKGRAY);
    setfillstyle(SOLID_FILL, DARKGRAY);

    int points[] = {
        x, y + spikeHeight,
        x + tileSizeX / 2, y,
        x + tileSizeX, y + spikeHeight};
    fillpoly(3, points);
}

void drawCloud(int x, int y)
{
    int size = 64;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y, x + size, y + size * 2 / 3);
    bar(x + size * 2 / 3, y - size / 3, x + size * 5 / 3, y + size / 3);
    bar(x + size * 4 / 3, y, x + size * 7 / 3, y + size * 2 / 3);
}

void drawGrid()
{
    setcolor(WHITE);
    for (int i = 0; i <= MAP_WIDTH; i++)
    {
        int x = i * (SCREEN_WIDTH / MAP_WIDTH);
        line(x, 0, x, SCREEN_HEIGHT);
    }
    for (int i = 0; i <= MAP_HEIGHT; i++)
    {
        int y = i * (SCREEN_HEIGHT / MAP_HEIGHT);
        line(0, y, SCREEN_WIDTH, y);
    }
}

void drawStoneBlock(int x, int y)
{
    setfillstyle(SOLID_FILL, DARKGRAY);
    bar(x, y, x + 32, y + 32);

    setcolor(LIGHTGRAY);
    for (int i = 5; i < 32; i += 10)
    {
        line(x + i, y, x + i, y + 32);
    }
    for (int i = 5; i < 32; i += 10)
    {
        line(x, y + i, x + 32, y + i);
    }
}

void drawBrickBlock(int x, int y)
{
    setfillstyle(SOLID_FILL, BROWN);
    bar(x, y, x + 32, y + 32);

    setcolor(DARKGRAY);
    for (int i = 5; i < 32; i += 10)
    {
        line(x, y + i, x + 32, y + i);
    }
}

void drawCloudBlock(int x, int y)
{
    int size = 32;
    setcolor(WHITE);
    setfillstyle(SOLID_FILL, LIGHTGRAY);
    bar(x, y, x + size, y + size * 2 / 3);
    bar(x + size * 2 / 3, y - size / 3, x + size * 5 / 3, y + size / 3);
    bar(x + size * 4 / 3, y, x + size * 7 / 3, y + size * 2 / 3);
}

void drawBodyPipe(int x, int y)
{

    int darkGreen = COLOR(0, 128, 0);

    int lightGreen = COLOR(0, 200, 0);

    int shadowGreen = COLOR(0, 100, 0);

    setcolor(darkGreen);
    setfillstyle(SOLID_FILL, darkGreen);
    bar(x, y, x + 80, y + 80);

    setcolor(lightGreen);
    setfillstyle(SOLID_FILL, lightGreen);
    bar(x + 5, y, x + 15, y + 40);

    setcolor(shadowGreen);
    setfillstyle(SOLID_FILL, shadowGreen);
    bar(x + 30, y, x + 40, y + 40);

    setcolor(darkGreen);
    setfillstyle(SOLID_FILL, darkGreen);
    bar(x - 10, y - 20, x + 50, y);

    setcolor(lightGreen);
    setfillstyle(SOLID_FILL, lightGreen);
    bar(x - 5, y - 20, x + 10, y);

    setcolor(BLACK);
    rectangle(x, y, x, y + 40);
    rectangle(x - 10, y - 20, x + 50, y);
}

void drawPipe(int x, int y)
{

    int darkGreen = COLOR(0, 128, 0);

    int lightGreen = COLOR(0, 200, 0);

    int shadowGreen = COLOR(0, 100, 0);

    setcolor(darkGreen);
    setfillstyle(SOLID_FILL, darkGreen);
    bar(x, y, x + 40, y + 40);

    setcolor(lightGreen);
    setfillstyle(SOLID_FILL, lightGreen);
    bar(x + 5, y, x + 15, y + 40);

    setcolor(shadowGreen);
    setfillstyle(SOLID_FILL, shadowGreen);
    bar(x + 30, y, x + 40, y + 40);

    setcolor(BLACK);
    rectangle(x, y - 20, x, y + 40);
}

void drawBackground()
{

    setfillstyle(SOLID_FILL, LIGHTBLUE);
    bar(0, 0, SCREEN_WIDTH, GROUND_HEIGHT + 25);

    int sunX = SCREEN_WIDTH / 2;
    int sunY = 100;
    int sunRadius = 100;

    setcolor(YELLOW);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(sunX, sunY, sunRadius, sunRadius);
}

void drawNextLevel(int x, int y)
{
    int radius = 10;

    for (int i = 0; i < 5; i++)
    {
        int color = COLOR(0, 100, 255);
        setcolor(color);
        circle(x, y, radius + i * 3);
    }

    for (int i = 0; i < radius; i++)
    {
        int color = COLOR(50 + i, 50 + 2 * i, 255 - i);
        setcolor(color);
        circle(x, y, radius - i);
    }

    for (int i = 0; i < 10; i++)
    {
        int angle = rand() % 360;
        int px = x + cos(angle * 3.14 / 180) * (radius + 40);
        int py = y + sin(angle * 3.14 / 180) * (radius + 40);
        putpixel(px, py, COLOR(255, 255, 255));
    }
}

void renderLevel(GameState gameState)
{
    if (gameState.level == 0 || gameState.level == 1)
    {
        drawBackground();
    }
    else if (gameState.level == 2)
    {
        drawNightBackground();
    }
}

void drawNightBackground()
{

    int DARKBLUE = COLOR(22, 38, 79);
    setfillstyle(SOLID_FILL, DARKBLUE);
    bar(0, 0, SCREEN_WIDTH, GROUND_HEIGHT + 25);

    int moonX = SCREEN_WIDTH / 2 + 100;
    int moonY = 100;
    int moonRadius = 40;

    setcolor(WHITE);
    setfillstyle(SOLID_FILL, WHITE);
    fillellipse(moonX, moonY, moonRadius, moonRadius);

    setcolor(WHITE);
    for (int i = 0; i < 10; i++)
    {
        int starX = rand() % SCREEN_WIDTH;
        int starY = rand() % (GROUND_HEIGHT + 25);
        putpixel(starX, starY, WHITE);
    }
}

void drawFlag(int x, int y)
{
    int flagWidth = 50;
    int flagHeight = 30;
    int poleHeight = 80;
    int poleWidth = 5;

    int flagColor = COLOR(200, 0, 0);
    int poleColor = COLOR(100, 100, 100);
    int shadowColor = COLOR(150, 0, 0);
    int highlightColor = COLOR(255, 50, 50);
    int baseColor = COLOR(80, 80, 80);
    int textureColor = COLOR(120, 120, 120);
    int flagTextureColor = COLOR(220, 50, 50);

    setcolor(baseColor);
    setfillstyle(SOLID_FILL, baseColor);
    bar(x - 3, y, x + poleWidth + 3, y + 7);

    setcolor(poleColor);
    setfillstyle(SOLID_FILL, poleColor);
    bar(x, y - poleHeight, x + poleWidth, y);

    setcolor(textureColor);
    for (int i = y - poleHeight; i < y; i += 5)
    {
        line(x, i, x + poleWidth, i);
    }

    setcolor(COLOR(60, 60, 60));
    line(x + poleWidth, y - poleHeight, x + poleWidth, y);

    setcolor(shadowColor);
    setfillstyle(SOLID_FILL, shadowColor);
    bar(x + poleWidth + 2, y - poleHeight + 2, x + poleWidth + flagWidth + 2, y - poleHeight + flagHeight + 2);

    setcolor(flagColor);
    setfillstyle(SOLID_FILL, flagColor);
    bar(x + poleWidth, y - poleHeight, x + poleWidth + flagWidth, y - poleHeight + flagHeight);

    setcolor(flagTextureColor);
    for (int i = y - poleHeight; i < y - poleHeight + flagHeight; i += 3)
    {
        line(x + poleWidth, i, x + poleWidth + flagWidth, i);
    }

    setcolor(highlightColor);
    line(x + poleWidth + 2, y - poleHeight + 2, x + poleWidth + flagWidth - 2, y - poleHeight + 2);
    line(x + poleWidth + 2, y - poleHeight + 2, x + poleWidth + 2, y - poleHeight + flagHeight - 2);
}

void drawVictoryFlag(int x, int y)
{
    int flagWidth = 50;
    int flagHeight = 30;
    int poleHeight = 300;
    int poleWidth = 5;

    int flagColor = COLOR(200, 0, 0);
    int poleColor = COLOR(100, 100, 100);
    int shadowColor = COLOR(150, 0, 0);
    int highlightColor = COLOR(255, 50, 50);
    int baseColor = COLOR(80, 80, 80);
    int textureColor = COLOR(120, 120, 120);
    int flagTextureColor = COLOR(220, 50, 50);
    int starColor = COLOR(255, 255, 0);

    setcolor(baseColor);
    setfillstyle(SOLID_FILL, baseColor);
    bar(x - 3, y, x + poleWidth + 3, y + 7);

    setcolor(poleColor);
    setfillstyle(SOLID_FILL, poleColor);
    bar(x, y - poleHeight, x + poleWidth, y);

    setcolor(textureColor);
    for (int i = y - poleHeight; i < y; i += 5)
    {
        line(x, i, x + poleWidth, i);
    }

    setcolor(COLOR(60, 60, 60));
    line(x + poleWidth, y - poleHeight, x + poleWidth, y);

    setcolor(shadowColor);
    setfillstyle(SOLID_FILL, shadowColor);
    int shadowTriangle[6] = {x + poleWidth, y - poleHeight + 2, x + poleWidth - flagWidth, y - poleHeight + flagHeight / 2 + 2, x + poleWidth, y - poleHeight + flagHeight + 2};
    fillpoly(3, shadowTriangle);

    setcolor(flagColor);
    setfillstyle(SOLID_FILL, flagColor);
    int triangle[6] = {x + poleWidth, y - poleHeight, x + poleWidth - flagWidth, y - poleHeight + flagHeight / 2, x + poleWidth, y - poleHeight + flagHeight};
    fillpoly(3, triangle);

    setcolor(flagTextureColor);
    for (int i = y - poleHeight; i < y - poleHeight + flagHeight; i += 3)
    {
        line(x + poleWidth, i, x + poleWidth - flagWidth / 2, i);
    }

    setcolor(highlightColor);
    line(x + poleWidth - 2, y - poleHeight + 2, x + poleWidth - flagWidth / 2 + 2, y - poleHeight + flagHeight / 4);
    line(x + poleWidth - 2, y - poleHeight + 2, x + poleWidth - 2, y - poleHeight + flagHeight - 2);

    setcolor(starColor);
    setfillstyle(SOLID_FILL, starColor);
    int star[10] = {
        x + poleWidth - flagWidth / 3, y - poleHeight + flagHeight / 2 - 6,
        x + poleWidth - flagWidth / 3 + 6, y - poleHeight + flagHeight / 2 + 3,
        x + poleWidth - flagWidth / 3 - 6, y - poleHeight + flagHeight / 2 - 2,
        x + poleWidth - flagWidth / 3 + 6, y - poleHeight + flagHeight / 2 - 2,
        x + poleWidth - flagWidth / 3 - 6, y - poleHeight + flagHeight / 2 + 3};
    fillpoly(5, star);
}

void drawMap()
{
    for (int i = 0; i < MAP_HEIGHT; i++)
    {
        for (int j = 0; j < MAP_WIDTH; j++)
        {
            int actualX = j + camera.x;
            if (actualX >= TOTAL_MAP_WIDTH)
                continue;

            int tile = maps[gameState.level][i][actualX];
            int x = j * (SCREEN_WIDTH / MAP_WIDTH) - camera.offset;
            int y = i * (SCREEN_HEIGHT / MAP_HEIGHT);

            switch (tile)
            {
            case 1:
                drawGround(x, y);
                break;
            case 2:
                drawPlatform(x, y);
                break;
            case 3:
                drawCoin(x + 20, y + 15);
                break;
            case 4:
                animationMonster();
                break;
            case 5:
                drawStar(x + 20, y + 20);
                break;
            case 6:
                drawSpike(x, y + 20);
                break;
            case 7:
                drawNextLevel(x + 20, y + 20);
                break;
            case 8:
                drawPipe(x + 10, y + 20);
                break;
            case 9:
                drawCloud(x + 20, y + 20);
                break;
            case 10:
                drawBrickBlock(x + 20, y + 20);
                break;
            case 11:
                drawStoneBlock(x + 20, y + 20);
                break;
            case 12:
                drawFlag(x + 20, y + 63);
                break;
            case 13:
                drawBodyPipe(x + 10, y + 20);
                break;
            case 14:
                drawVictoryFlag(x + 20, y + 202);
                break;
            }
        }
    }
}