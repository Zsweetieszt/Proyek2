#include "blok1.h"

int main() {
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "");

    // Mengatur background keseluruhan menjadi putih
    setbkcolor(WHITE);
    cleardevice();

    // Memanggil fungsi desain utama
    drawDesign();

    getch();
    closegraph();
    return 0;
}
