#include "main_menu.h"
#include "game.h"
#include "leaderboard.h"

char playerName[50] = "";

Leaderboard leaderboard;


void askPlayerNameGraphics() {
    cleardevice();
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    char message[] = "Enter your name:";
    outtextxy(200, 150, message);

    int i = 0;
    char ch;
    playerName[0] = '\0';

    while (1) {
        ch = getch();

        if (ch == '\r') {
            playerName[i] = '\0';
            break;
        } else if (ch == '\b' && i > 0) {
            i--;
            playerName[i] = '\0';
        } else if (i < 49 && ch >= 32 && ch <= 126) {
            playerName[i++] = ch;
            playerName[i] = '\0';
        }

        setfillstyle(SOLID_FILL, BLACK);
        bar(200, 200, 600, 230);
        outtextxy(200, 200, playerName);
    }
}

void showGuide()
{
    cleardevice();
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);

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

    while (!kbhit() && !ismouseclick(WM_LBUTTONDOWN)); 
    getch(); 
    clearmouseclick(WM_LBUTTONDOWN); 
    cleardevice(); 
}

void handleMouseClick(int mouseX, int mouseY)
{
    if (mouseX >= 100 && mouseX <= 300 && mouseY >= 150 && mouseY <= 180)
    {

        cleardevice();
        askPlayerNameGraphics();
        char startMsg[] = "Game Starting...";
        outtextxy(210, 200, startMsg);
        delay(2000); 
    } else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 200 && mouseY <= 230) {
        showGuide();
    } else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 250 && mouseY <= 280) {
        closegraph();  
        exit(0);
    }
}

void showMainMenu() {
    setactivepage(0);
    setvisualpage(0);

    cleardevice();
    setbkcolor(LIGHTBLUE);
    cleardevice();

    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);

    char gameName[] = "Mario Bros";
    char startText[] = "Start Game";
    char guideText[] = "Guide";
    char exitText[] = "Exit";

    outtextxy(230, 80, gameName);
    outtextxy(100, 150, startText);
    outtextxy(100, 200, guideText);
    outtextxy(100, 250, exitText);

    initLeaderboard(&leaderboard);
    loadLeaderboard(&leaderboard, "leaderboard.txt");
    displayLeaderboard(&leaderboard, 1000, 100); 

    while (1) {
        int mouseX, mouseY;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            handleMouseClick(mouseX, mouseY);
            clearmouseclick(WM_LBUTTONDOWN);

            freeLeaderboard(&leaderboard);
            break;
        }
    }
}