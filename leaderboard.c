#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include "leaderboard.h"

void initLeaderboard(Leaderboard* lb) {
    lb->head = NULL;
}

void addScore(Leaderboard* lb, const char* name, int score) {
    LeaderboardNode* newNode = (LeaderboardNode*)malloc(sizeof(LeaderboardNode));
    strcpy(newNode->name, name);
    newNode->score = score;
    newNode->next = NULL;

    if (lb->head == NULL || score > lb->head->score) {
        newNode->next = lb->head;
        lb->head = newNode;
    } else {
        LeaderboardNode* current = lb->head;
        while (current->next != NULL && current->next->score >= score) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
}

void displayLeaderboard(Leaderboard* lb, int x, int y) {
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(WHITE);
    char message[] = "Leaderboard:";
    outtextxy(x, y, message);

    LeaderboardNode* current = lb->head;
    int offset = 30;
    int rank = 1;
    char buffer[100];

    while (current != NULL && rank <= 10) {
        sprintf(buffer, "%d. %s - %d", rank, current->name, current->score);
        outtextxy(x, y + offset, buffer);
        offset += 25;
        current = current->next;
        rank++;
    }
}

void saveLeaderboard(Leaderboard* lb, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) return;

    LeaderboardNode* current = lb->head;
    while (current != NULL) {
        fprintf(file, "%s %d\n", current->name, current->score);
        current = current->next;
    }

    fclose(file);
}

void loadLeaderboard(Leaderboard* lb, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) return;

    char name[50];
    int score;

    while (fscanf(file, "%s %d", name, &score) == 2) {
        addScore(lb, name, score);
    }

    fclose(file);
}

void freeLeaderboard(Leaderboard* lb) {
    LeaderboardNode* current = lb->head;
    while (current != NULL) {
        LeaderboardNode* temp = current;
        current = current->next;
        free(temp);
    }
    lb->head = NULL;
}
