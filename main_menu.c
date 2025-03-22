#include "main_menu.h"
#include "game.h"

// Fungsi untuk menampilkan panduan permainan
void showGuide() {
    cleardevice();
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);

    char guideTitle[] = "Guide:";
    char guideStep1[] = "1. Use arrow keys to navigate.";
    char guideStep2[] = "2. Press 'Enter' to select an option.";
    char guideStep3[] = "3. Enjoy the game!";
    char backMsg[] = "Press any key or click to return to the main menu.";

    outtextxy(100, 100, guideTitle);
    outtextxy(100, 150, guideStep1);
    outtextxy(100, 200, guideStep2);
    outtextxy(100, 250, guideStep3);
    outtextxy(100, 300, backMsg);

    while (!kbhit() && !ismouseclick(WM_LBUTTONDOWN));
    getch();
    clearmouseclick(WM_LBUTTONDOWN);
    cleardevice();
}

// Fungsi untuk menangani klik mouse di menu utama
void handleMouseClick(int mouseX, int mouseY) {
    if (mouseX >= 100 && mouseX <= 300 && mouseY >= 150 && mouseY <= 180) {
        restartGame();
        cleardevice();
        setcolor(WHITE);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);

        char startMsg[] = "Game Starting...";
        outtextxy(100, 350, startMsg);
        delay(2000);

        isRunning = 1;
    } 
    else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 180 && mouseY <= 210) {
        cleardevice();
        setcolor(WHITE);
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);

        char continueMsg[] = "Continuing Game...";
        outtextxy(100, 350, continueMsg);
        delay(2000);

        isRunning = 1;
    } 
    else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 210 && mouseY <= 240) {
        showGuide();
    } 
    else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 240 && mouseY <= 270) {
        closegraph();
        exit(0);
    }
}

// Fungsi untuk menampilkan menu utama
void showMainMenu() {
    setbkcolor(LIGHTBLUE);
    cleardevice();

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);

    char startText[] = "Start Game";
    char continueText[] = "Continue";
    char guideText[] = "Guide";
    char exitText[] = "Exit";

    outtextxy(100, 150, startText);
    outtextxy(100, 180, continueText);
    outtextxy(100, 210, guideText);
    outtextxy(100, 240, exitText);

    while (1) { 
        int mouseX, mouseY;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            handleMouseClick(mouseX, mouseY);
            clearmouseclick(WM_LBUTTONDOWN);
            break;
        }
    }
}
