#include "main_menu.h"
#include "game.h"

void showGuide() {
    cleardevice();
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2); // Gunakan font triplex

    char guideTitle[] = "Guide:";
    char guideStep1[] = "1. Gunakan A D untuk bergerak.";
    char guideStep2[] = "2. Gunakan W untuk melompat.";
    char guideStep3[] = "3. Gunakan P untuk pause game";
    char backMsg[] = "Press any key or click to play game.";

    outtextxy(100, 100, guideTitle);
    outtextxy(100, 150, guideStep1);
    outtextxy(100, 200, guideStep2);
    outtextxy(100, 250, guideStep3);
    outtextxy(80, 300, backMsg);

    while (!kbhit() && !ismouseclick(WM_LBUTTONDOWN)); // Tunggu input keyboard atau mouse
    getch(); // Bersihkan input keyboard
    clearmouseclick(WM_LBUTTONDOWN); // Bersihkan input mouse
    cleardevice(); // Bersihkan layar sebelum kembali ke menu utama
}

void handleMouseClick(int mouseX, int mouseY) {
    if (mouseX >= 100 && mouseX <= 300 && mouseY >= 150 && mouseY <= 180) {
        // Start game
        cleardevice();
        char startMsg[] = "Game Starting...";
        outtextxy(100, 350, startMsg);
        delay(2000); // Simulasi loading game
    } else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 200 && mouseY <= 230) {
        // Show guide
        showGuide();
    } else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 250 && mouseY <= 280) {
        closegraph();  // Tutup mode grafis sebelum keluar
        exit(0);
    }
}

// Fungsi untuk menampilkan menu utama
void showMainMenu() {
        // Set halaman aktif dan visual ke 0
        setactivepage(0);
        setvisualpage(0);
        
        cleardevice();  // Bersihkan layar
    setbkcolor(LIGHTBLUE);
    cleardevice();

    // Gambar karakter sederhana
    setcolor(RED);
    circle(200, 300, 20);

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);

    char startText[] = "Start Game";
    char guideText[] = "Guide";
    char exitText[] = "Exit";

    outtextxy(100, 150, startText);
    outtextxy(100, 200, guideText);
    outtextxy(100, 250, exitText);

    while (1) { 
        int mouseX, mouseY;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            handleMouseClick(mouseX, mouseY);
            clearmouseclick(WM_LBUTTONDOWN); // Bersihkan klik agar tidak double-click
            break; // Keluar dari loop agar menu bisa di-refresh
        }
    }
}