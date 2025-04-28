#include "main_menu.h"
#include "game.h"

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

    while (!kbhit() && !ismouseclick(WM_LBUTTONDOWN))
        ;
    getch();
    clearmouseclick(WM_LBUTTONDOWN);
    cleardevice();
}

void handleMouseClick(int mouseX, int mouseY)
{
    if (mouseX >= 100 && mouseX <= 300 && mouseY >= 150 && mouseY <= 180)
    {

        cleardevice();
        char startMsg[] = "Game Starting...";
        outtextxy(210, 200, startMsg);
        delay(2000);
    }
    else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 200 && mouseY <= 230)
    {

        showGuide();
    }
    else if (mouseX >= 100 && mouseX <= 300 && mouseY >= 250 && mouseY <= 280)
    {
        closegraph();
        exit(0);
    }
}

void showMainMenu()
{

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

    while (1)
    {
        int mouseX, mouseY;
        if (ismouseclick(WM_LBUTTONDOWN))
        {
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            handleMouseClick(mouseX, mouseY);
            clearmouseclick(WM_LBUTTONDOWN);
            break;
        }
    }
}