#include "main_menu.h"
#include "game.h"
#include "leaderboard.h"

char playerName[50] = "";
Leaderboard menuLeaderboard;

void askPlayerNameGraphics() {
    cleardevice();
    setbkcolor(BLACK);
    cleardevice();
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
    setcolor(YELLOW);
    char title[] = "Mario Bros Game";
    outtextxy(SCREEN_WIDTH/2 - 150, 100, title);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    char message[] = "Enter your name:";
    outtextxy(SCREEN_WIDTH/2 - 100, 250, message);
    
    // Gambar box untuk input
    setcolor(WHITE);
    rectangle(SCREEN_WIDTH/2 - 150, 300, SCREEN_WIDTH/2 + 150, 340);
    
    int i = 0;
    char ch;
    playerName[0] = '\0';

    while (1) {
        if (kbhit()) {
            ch = getch();
            
            if (ch == '\r' || ch == '\n') { // Enter key
                if (i > 0) { // Pastikan nama tidak kosong
                    playerName[i] = '\0';
                    break;
                }
            } 
            else if (ch == '\b' && i > 0) { // Backspace
                i--;
                playerName[i] = '\0';
                
                // Clear area input
                setfillstyle(SOLID_FILL, BLACK);
                bar(SCREEN_WIDTH/2 - 145, 305, SCREEN_WIDTH/2 + 145, 335);
            } 
            else if (i < 49 && ch >= 32 && ch <= 126 && ch != ' ') { // Karakter valid (tanpa spasi)
                playerName[i++] = ch;
                playerName[i] = '\0';
            }
            
            // Clear area input dan tampilkan nama
            setfillstyle(SOLID_FILL, BLACK);
            bar(SCREEN_WIDTH/2 - 145, 305, SCREEN_WIDTH/2 + 145, 335);
            
            setcolor(WHITE);
            settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
            outtextxy(SCREEN_WIDTH/2 - 140, 310, playerName);
            
            // Cursor sederhana
            char cursor[] = "_";
            outtextxy(SCREEN_WIDTH/2 - 140 + (i * 10), 310, cursor);
        }
        
        delay(50); // Prevent high CPU usage
    }
    
    // Konfirmasi nama
    cleardevice();
    setcolor(GREEN);
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
    setbkcolor(BLUE);
    cleardevice();
    
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

    getch(); // Wait for any key
    cleardevice();
}

void handleMouseClick(int mouseX, int mouseY) {
    // Start Game button
    if (mouseX >= SCREEN_WIDTH/2 - 100 && mouseX <= SCREEN_WIDTH/2 + 100 && 
        mouseY >= 200 && mouseY <= 240) {
        askPlayerNameGraphics();
    } 
    // Guide button
    else if (mouseX >= SCREEN_WIDTH/2 - 100 && mouseX <= SCREEN_WIDTH/2 + 100 && 
             mouseY >= 260 && mouseY <= 300) {
        showGuide();
    } 
    // Leaderboard button
    else if (mouseX >= SCREEN_WIDTH/2 - 100 && mouseX <= SCREEN_WIDTH/2 + 100 && 
             mouseY >= 320 && mouseY <= 360) {
        showLeaderboardScreen();
    }
    // Exit button
    else if (mouseX >= SCREEN_WIDTH/2 - 100 && mouseX <= SCREEN_WIDTH/2 + 100 && 
             mouseY >= 380 && mouseY <= 420) {
        freeLeaderboard(&menuLeaderboard);
        closegraph();
        exit(0);
    }
}

void showLeaderboardScreen() {
    cleardevice();
    setbkcolor(DARKGRAY);
    cleardevice();
    
    settextstyle(TRIPLEX_FONT, HORIZ_DIR, 3);
    setcolor(YELLOW);
    char title[] = "Top Scores";
    outtextxy(SCREEN_WIDTH/2 - 100, 50, title);
    
    // Display leaderboard
    displayLeaderboard(&menuLeaderboard, SCREEN_WIDTH/2 - 150, 150);
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    char backMsg[] = "Press any key to return to main menu";
    outtextxy(SCREEN_WIDTH/2 - 180, SCREEN_HEIGHT - 100, backMsg);
    
    getch();
    cleardevice();
}

void showMainMenu() {
    setactivepage(0);
    setvisualpage(0);

    // Initialize leaderboard
    initLeaderboard(&menuLeaderboard);
    loadLeaderboard(&menuLeaderboard, "leaderboard.txt");

    while (1) {
  readimagefile("c:\\Proyek2\\background.bmp", 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Game title
        settextstyle(TRIPLEX_FONT, HORIZ_DIR, 4);
        setcolor(RED);
        char gameName[] = "MARIO BROS";
        outtextxy(SCREEN_WIDTH/2 - 150, 80, gameName);

        // Menu buttons
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
        setcolor(WHITE);
        
        // Draw button backgrounds
        setfillstyle(SOLID_FILL, DARKGRAY);
        bar(SCREEN_WIDTH/2 - 100, 200, SCREEN_WIDTH/2 + 100, 240); // Start Game
        bar(SCREEN_WIDTH/2 - 100, 260, SCREEN_WIDTH/2 + 100, 300); // Guide
        bar(SCREEN_WIDTH/2 - 100, 320, SCREEN_WIDTH/2 + 100, 360); // Leaderboard
        bar(SCREEN_WIDTH/2 - 100, 380, SCREEN_WIDTH/2 + 100, 420); // Exit
        
        // Button borders
        setcolor(WHITE);
        rectangle(SCREEN_WIDTH/2 - 100, 200, SCREEN_WIDTH/2 + 100, 240);
        rectangle(SCREEN_WIDTH/2 - 100, 260, SCREEN_WIDTH/2 + 100, 300);
        rectangle(SCREEN_WIDTH/2 - 100, 320, SCREEN_WIDTH/2 + 100, 360);
        rectangle(SCREEN_WIDTH/2 - 100, 380, SCREEN_WIDTH/2 + 100, 420);
        
        // Button text
        char startText[] = "Start Game";
        char guideText[] = "Guide";
        char leaderText[] = "Leaderboard";
        char exitText[] = "Exit";

        outtextxy(SCREEN_WIDTH/2 - 50, 215, startText);
        outtextxy(SCREEN_WIDTH/2 - 25, 275, guideText);
        outtextxy(SCREEN_WIDTH/2 - 60, 335, leaderText);
        outtextxy(SCREEN_WIDTH/2 - 20, 395, exitText);

        // Mini leaderboard preview
        settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
        setcolor(YELLOW);
        char previewTitle[] = "Top 5 Scores:";
        outtextxy(50, 200, previewTitle);
        
        LeaderboardNode* current = menuLeaderboard.head;
        int yOffset = 220;
        int rank = 1;
        char buffer[60];
        
        setcolor(WHITE);
        while (current != NULL && rank <= 5) {
            sprintf(buffer, "%d. %s - %d", rank, current->name, current->score);
            outtextxy(50, yOffset, buffer);
            yOffset += 20;
            current = current->next;
            rank++;
        }

        // Handle mouse clicks
        int mouseX, mouseY;
        if (ismouseclick(WM_LBUTTONDOWN)) {
            getmouseclick(WM_LBUTTONDOWN, mouseX, mouseY);
            handleMouseClick(mouseX, mouseY);
            clearmouseclick(WM_LBUTTONDOWN);
            
            // If start game was clicked, break out of menu loop
            if (strlen(playerName) > 0) {
                break;
            }
        }
        
        // Handle keyboard input
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
                case 27: // ESC key
                    freeLeaderboard(&menuLeaderboard);
                    closegraph();
                    exit(0);
                    break;
            }
        }
        
        delay(50); // Prevent high CPU usage
    }
    
    freeLeaderboard(&menuLeaderboard);
}