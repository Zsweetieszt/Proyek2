#include "blok1.h"

void drawRectangle(int x, int y, int width, int height) {
    int rectColor = COLOR(204, 102, 0); // RGB untuk oranye
    int gapColor = BLACK;

    setfillstyle(SOLID_FILL, rectColor);
    bar(x, y, x + width, y + height);

    setcolor(gapColor);
    rectangle(x, y, x + width, y + height);
}

void drawSquare(int x, int y, int size) {
    int rectColor = COLOR(204, 102, 0); // RGB untuk oranye
    int gapColor = BLACK;

    setfillstyle(SOLID_FILL, rectColor);
    bar(x, y, x + size, y + size);

    setcolor(gapColor);
    rectangle(x, y, x + size, y + size);
}

void drawBackground(int x, int y, int width, int height) {
    setfillstyle(SOLID_FILL, BLACK);
    bar(x, y, x + width, y + height);
}

void drawDesign() {
    int startX = 50, startY = 50;
    int rectWidth = 85, rectHeight = 40;
    int boxSize = 40;
    int gap = 5;

    // Menggambar latar belakang hitam di area desain
    int totalWidth = 2 * rectWidth + 3 * gap + boxSize;
    int totalHeight = 4 * (rectHeight + gap) + rectHeight;
    drawBackground(startX - gap, startY - gap, totalWidth, totalHeight);

    // Baris 1
    drawRectangle(startX, startY, rectWidth, rectHeight);
    drawRectangle(startX + rectWidth + gap, startY, rectWidth, rectHeight);

    // Baris 2
    drawSquare(startX, startY + rectHeight + gap, boxSize);
    drawRectangle(startX + boxSize + gap, startY + rectHeight + gap, rectWidth, rectHeight);
    drawSquare(startX + boxSize + rectWidth + 2 * gap, startY + rectHeight + gap, boxSize);

    // Baris 3
    drawRectangle(startX, startY + 2 * (rectHeight + gap), rectWidth, rectHeight);
    drawRectangle(startX + rectWidth + gap, startY + 2 * (rectHeight + gap), rectWidth, rectHeight);

    // Baris 4
    drawSquare(startX, startY + 3 * (rectHeight + gap), boxSize);
    drawRectangle(startX + boxSize + gap, startY + 3 * (rectHeight + gap), rectWidth, rectHeight);
    drawSquare(startX + boxSize + rectWidth + 2 * gap, startY + 3 * (rectHeight + gap), boxSize);
}
