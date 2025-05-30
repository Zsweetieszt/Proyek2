#ifndef LEADERBOARD_H
#define LEADERBOARD_H

typedef struct LeaderboardNode {
    char name[50];
    int score;
    struct LeaderboardNode* next;
} LeaderboardNode;

typedef struct {
    LeaderboardNode* head;
} Leaderboard;

void initLeaderboard(Leaderboard* lb);
void addScore(Leaderboard* lb, const char* name, int score);
void displayLeaderboard(Leaderboard* lb, int startX, int startY);
void saveLeaderboard(Leaderboard* lb, const char* filename);
void loadLeaderboard(Leaderboard* lb, const char* filename);
void freeLeaderboard(Leaderboard* lb);


#endif