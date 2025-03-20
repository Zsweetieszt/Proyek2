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

void drawPlatform(int startX, int startY, int platformWidth, int platformHeight, int tileSize, int gap) {
    int rectHeight = platformHeight; // Tinggi persegi panjang
    int rectWidth = platformWidth / 2 - gap / 2; // Lebar persegi panjang
    int boxSize = tileSize; // Ukuran kotak persegi

    // Baris 1: Dua persegi panjang menyamping
    drawRectangle(startX, startY, rectWidth, rectHeight);
    drawRectangle(startX + rectWidth + gap, startY, rectWidth, rectHeight);

    // Baris 2: Satu persegi panjang diapit dua kotak
    drawSquare(startX, startY + rectHeight + gap, boxSize);
    drawRectangle(startX + boxSize + gap, startY + rectHeight + gap, rectWidth, rectHeight);
    drawSquare(startX + rectWidth + boxSize + 2 * gap, startY + rectHeight + gap, boxSize);

    // Baris 3: Dua persegi panjang menyamping
    drawRectangle(startX, startY + 2 * (rectHeight + gap), rectWidth, rectHeight);
    drawRectangle(startX + rectWidth + gap, startY + 2 * (rectHeight + gap), rectWidth, rectHeight);

    // Baris 4: Satu persegi panjang diapit dua kotak
    drawSquare(startX, startY + 3 * (rectHeight + gap), boxSize);
    drawRectangle(startX + boxSize + gap, startY + 3 * (rectHeight + gap), rectWidth, rectHeight);
    drawSquare(startX + rectWidth + boxSize + 2 * gap, startY + 3 * (rectHeight + gap), boxSize);
}