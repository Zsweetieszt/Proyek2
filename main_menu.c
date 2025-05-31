/**
 * Nama file: main_menu.c
 *
 * Modul ini berisi implementasi tampilan dan logika menu utama untuk game "Mario Bros".
 *
 * Penulis: Mahesa Fazrie
 * Tanggal: Jumat, 30 Mei 2025
 */
#include "main_menu.h"
#include "game.h"
#include "leaderboard.h"

char playerName[50] = "";
Leaderboard menuLeaderboard;

void askPlayerNameGraphics() {
    cleardevice();
    readimagefile("assets/leaderboard_background_24bit.bmp", 0, 0, getmaxwidth(), getmaxheight());
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    setcolor(YELLOW);
    char title[] = "Mario Bros Game";
    outtextxy(SCREEN_WIDTH/2 - 150, 100, title);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    char message[] = "Enter your name:";
    outtextxy(SCREEN_WIDTH/2 - 100, 250, message);
    
    
    setcolor(WHITE);
    rectangle(SCREEN_WIDTH/2 - 150, 300, SCREEN_WIDTH/2 + 150, 340);
    
    int i = 0;
    char ch;
    playerName[0] = '\0';

    while (1) {
        if (kbhit()) {
            ch = getch();
            
            if (ch == '\r' || ch == '\n') { 
                if (i > 0) { 
                    playerName[i] = '\0';
                    break;
                }
            } 
            else if (ch == '\b' && i > 0) { 
                i--;
                playerName[i] = '\0';
                
                
                setfillstyle(SOLID_FILL, BLACK);
                bar(SCREEN_WIDTH/2 - 145, 305, SCREEN_WIDTH/2 + 145, 335);
            } 
            else if (i < 49 && ch >= 32 && ch <= 126 && ch != ' ') { 
                playerName[i++] = ch;
                playerName[i] = '\0';
            }
            
            
            setfillstyle(SOLID_FILL, BLACK);
            bar(SCREEN_WIDTH/2 - 145, 305, SCREEN_WIDTH/2 + 145, 335);
            
            setcolor(WHITE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(SCREEN_WIDTH/2 - 140, 310, playerName);
            
            
            char cursor[] = "_";
            outtextxy(SCREEN_WIDTH/2 - 140 + (i * 10), 310, cursor);
        }
        
        delay(50); 
    }
    
    
    cleardevice();
    readimagefile("assets/leaderboard_background_24bit.bmp", 0, 0, getmaxwidth(), getmaxheight());
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    char welcome[100];
    sprintf(welcome, "Welcome, %s!", playerName);
    outtextxy(SCREEN_WIDTH/2 - 100, SCREEN_HEIGHT/2 - 50, welcome);
    
    char startMsg[] = "Game Starting...";
    outtextxy(SCREEN_WIDTH/2 - 80, SCREEN_HEIGHT/2, startMsg);
    delay(2000);
}

void showGuide() {
    cleardevice();
    readimagefile("assets/leaderboard_background_24bit.bmp", 0, 0, getmaxwidth(), getmaxheight());
    
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    setcolor(YELLOW);
    char guideTitle[] = "How to Play";
    outtextxy(SCREEN_WIDTH/2 - 120, 100, guideTitle);

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    char guideStep1[] = "1. Use A and D keys to move left and right";
    char guideStep2[] = "2. Use W key to jump";
    char guideStep3[] = "3. Use P key to pause the game";
    char guideStep4[] = "4. Collect coins to increase your score";
    char guideStep5[] = "5. Avoid monsters and spikes";
    char backMsg[] = "Press any key to return to main menu";

    outtextxy(100, 200, guideStep1);
    outtextxy(100, 240, guideStep2);
    outtextxy(100, 280, guideStep3);
    outtextxy(100, 320, guideStep4);
    outtextxy(100, 360, guideStep5);
    
    setcolor(YELLOW);
    outtextxy(SCREEN_WIDTH/2 - 180, 450, backMsg);

    getch(); 
    cleardevice();
}

void handleMouseClick(int mouseX, int mouseY) {
    
    if (mouseX >= SCREEN_WIDTH/2 - 100 && mouseX <= SCREEN_WIDTH/2 + 100 && 
        mouseY >= 200 && mouseY <= 240) {
        askPlayerNameGraphics();
    } 
    
    else if (mouseX >= SCREEN_WIDTH/2 - 100 && mouseX <= SCREEN_WIDTH/2 + 100 && 
             mouseY >= 260 && mouseY <= 300) {
        showGuide();
    } 
    
    else if (mouseX >= SCREEN_WIDTH/2 - 100 && mouseX <= SCREEN_WIDTH/2 + 100 && 
             mouseY >= 320 && mouseY <= 360) {
        showLeaderboardScreen();
    }
    
    else if (mouseX >= SCREEN_WIDTH/2 - 100 && mouseX <= SCREEN_WIDTH/2 + 100 && 
             mouseY >= 380 && mouseY <= 420) {
        freeLeaderboard(&menuLeaderboard);
        closegraph();
        exit(0);
    }
}

void showLeaderboardScreen() {
    cleardevice();
    readimagefile("assets/leaderboard_background_24bit.bmp", 0, 0, getmaxwidth(), getmaxheight());
    
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 7);
    setcolor(YELLOW);
    char title[] = "Top Scores";
    outtextxy(SCREEN_WIDTH/2 - 200, 50, title);
    
    
    displayLeaderboard(&menuLeaderboard, SCREEN_WIDTH/2 - 300, 150);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    char backMsg[] = "Press any key to return to main menu";
    outtextxy(SCREEN_WIDTH/2 - 270, SCREEN_HEIGHT - 100, backMsg);
    
    getch();
    cleardevice();
}

void showMainMenu() {
int leftX = SCREEN_WIDTH / 2 - 100;
    int rightX = SCREEN_WIDTH / 2 + 100;
    int nameWidth = 300;
    int nameHeight = 60;
    int nameX = SCREEN_WIDTH / 2 - nameWidth / 2;
    int nameY = 20;
    int activePage = 0;

    initLeaderboard(&menuLeaderboard);
    loadLeaderboard(&menuLeaderboard, "leaderboard.txt");

    while (1) {
        setactivepage(activePage);
        cleardevice(); 
        
        readimagefile("assets/background_fixed.bmp", 0, 0, getmaxwidth(), getmaxheight());
        readimagefile("assets/name_fixed.bmp", nameX, nameY, nameX + nameWidth, nameY + nameHeight);
        readimagefile("assets/start_button_final.bmp", leftX, 200, rightX, 240);
        readimagefile("assets/exit_button_final.bmp", leftX, 380, rightX, 420);
        readimagefile("assets/leaderboard.bmp", leftX, 320, rightX, 360); 
        readimagefile("assets/guide_final_fixed.bmp", leftX, 260, rightX, 300);
        
        setvisualpage(activePage); 
        activePage = 1 - activePage; 

        
        int mouseX, mouseY;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            handleMouseClick(mouseX, mouseY);
            clearmouseclick(WM_LBUTTONDOWN);
            
            
            if (strlen(playerName) > 0) {
                break;
            }
        }
        
        
        if (kbhit()) {
            char key = getch();
            switch (key) {
                case '1':
                    askPlayerNameGraphics();
                    if (strlen(playerName) > 0) {
                        freeLeaderboard(&menuLeaderboard);
                        return;
                    }
                    break;
                case '2':
                    showGuide();
                    break;
                case '3':
                    showLeaderboardScreen();
                    break;
                case '4':
                case 27: 
                    freeLeaderboard(&menuLeaderboard);
                    closegraph();
                    exit(0);
                    break;
            }
        }
        
        delay(50); 
    }
    
    freeLeaderboard(&menuLeaderboard);
}