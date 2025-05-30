#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include "leaderboard.h"

void initLeaderboard(Leaderboard* lb) {
    if (lb != NULL) {
        lb->head = NULL;
    }
}

void addScore(Leaderboard* lb, const char* name, int score) {
    if (lb == NULL || name == NULL || strlen(name) == 0) {
        return;
    }
    
    // Cek apakah nama sudah ada
    LeaderboardNode* current = lb->head;
    LeaderboardNode* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            // Nama sudah ada, update score jika lebih tinggi
            if (score > current->score) {
                // Update score
                current->score = score;
                
                // Remove node dari posisi saat ini
                if (prev != NULL) {
                    prev->next = current->next;
                } else {
                    lb->head = current->next;
                }
                
                // Insert kembali ke posisi yang tepat
                insertNodeSorted(lb, current);
            }
            // Jika score baru lebih rendah atau sama, tidak perlu update
            return;
        }
        prev = current;
        current = current->next;
    }
    
    // Nama belum ada, buat node baru
    LeaderboardNode* newNode = (LeaderboardNode*)malloc(sizeof(LeaderboardNode));
    if (newNode == NULL) {
        return; // Memory allocation failed
    }
    
    strncpy(newNode->name, name, sizeof(newNode->name) - 1);
    newNode->name[sizeof(newNode->name) - 1] = '\0'; // Ensure null termination
    newNode->score = score;
    newNode->next = NULL;

    // Insert dalam urutan terurut
    insertNodeSorted(lb, newNode);
}

// Helper function untuk insert node dalam urutan terurut (score tertinggi dulu)
void insertNodeSorted(Leaderboard* lb, LeaderboardNode* node) {
    if (lb == NULL || node == NULL) {
        return;
    }
    
    // Jika list kosong atau score node lebih tinggi dari head
    if (lb->head == NULL || node->score > lb->head->score) {
        node->next = lb->head;
        lb->head = node;
        return;
    }
    
    // Cari posisi yang tepat untuk insert
    LeaderboardNode* current = lb->head;
    while (current->next != NULL && current->next->score >= node->score) {
        current = current->next;
    }
    
    node->next = current->next;
    current->next = node;
}

void displayLeaderboard(Leaderboard* lb, int x, int y) {
    if (lb == NULL) {
        return;
    }
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 2);
    setcolor(YELLOW);
    char message[] = "LEADERBOARD";
    outtextxy(x, y, message);

    LeaderboardNode* current = lb->head;
    int offset = 40;
    int rank = 1;
    char buffer[100];

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 1);
    setcolor(WHITE);
    
    while (current != NULL && rank <= 10) {
        if (rank <= 3) {
            // Highlight top 3
            switch(rank) {
                case 1: setcolor(YELLOW); break;  // Gold
                case 2: setcolor(LIGHTGRAY); break; // Silver
                case 3: setcolor(BROWN); break;    // Bronze
            }
        } else {
            setcolor(WHITE);
        }
        
        sprintf(buffer, "%d. %-15s %d pts", rank, current->name, current->score);
        outtextxy(x, y + offset, buffer);
        offset += 25;
        current = current->next;
        rank++;
    }
    
    if (lb->head == NULL) {
        setcolor(LIGHTGRAY);
        char emptyMsg[] = "No scores yet!";
        outtextxy(x, y + 40, emptyMsg);
    }
}

void saveLeaderboard(Leaderboard* lb, const char* filename) {
    if (lb == NULL || filename == NULL) {
        return;
    }
    
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error: Cannot save leaderboard to %s\n", filename);
        return;
    }

    LeaderboardNode* current = lb->head;
    while (current != NULL) {
        fprintf(file, "%s %d\n", current->name, current->score);
        current = current->next;
    }

    fclose(file);
}

void loadLeaderboard(Leaderboard* lb, const char* filename) {
    if (lb == NULL || filename == NULL) {
        return;
    }
    
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        // File doesn't exist yet, create empty one
        file = fopen(filename, "w");
        if (file != NULL) {
            fclose(file);
        }
        return;
    }

    char name[50];
    int score;

    while (fscanf(file, "%49s %d", name, &score) == 2) {
        addScore(lb, name, score);
    }

    fclose(file);
}

void freeLeaderboard(Leaderboard* lb) {
    if (lb == NULL) {
        return;
    }
    
    LeaderboardNode* current = lb->head;
    while (current != NULL) {
        LeaderboardNode* temp = current;
        current = current->next;
        free(temp);
    }
    lb->head = NULL;
}

int getLeaderboardCount(Leaderboard* lb) {
    if (lb == NULL) {
        return 0;
    }
    
    int count = 0;
    LeaderboardNode* current = lb->head;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int getPlayerRank(Leaderboard* lb, const char* name) {
    if (lb == NULL || name == NULL) {
        return -1;
    }
    
    LeaderboardNode* current = lb->head;
    int rank = 1;
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            return rank;
        }
        current = current->next;
        rank++;
    }
    
    return -1; // Player not found
}