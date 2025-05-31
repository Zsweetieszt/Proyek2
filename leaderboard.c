/**
 * Nama file: leaderboard.c
 * 
 * File ini mengelola sistem leaderboard (papan skor) untuk game.
 * Fungsionalitas yang disediakan meliputi:
 * File ini menggunakan struktur data linked list untuk menyimpan
 * dan mengelola entri leaderboard secara dinamis.
 * 
 * Penulis: Mahesa Fazrie 
 * Tanggal: Jumat, 30 Mei 2025
 */

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
    
    // Cek apakah nama sudah ada, jika ya dan skor baru lebih tinggi, update
    LeaderboardNode* current = lb->head;
    LeaderboardNode* prev = NULL;
    
    while (current != NULL) {
        if (strcmp(current->name, name) == 0) {
            if (score > current->score) {
                // Update score dan reposisi
                current->score = score;
                
                // Remove from current position
                if (prev != NULL) {
                    prev->next = current->next;
                } else {
                    lb->head = current->next;
                }
                
                // Find new position and insert
                if (lb->head == NULL || score > lb->head->score) {
                    current->next = lb->head;
                    lb->head = current;
                } else {
                    LeaderboardNode* temp = lb->head;
                    while (temp->next != NULL && temp->next->score >= score) {
                        temp = temp->next;
                    }
                    current->next = temp->next;
                    temp->next = current;
                }
            }
            return; // Nama sudah ada, tidak perlu menambahkan node baru
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

    if (lb->head == NULL || score > lb->head->score) {
        newNode->next = lb->head;
        lb->head = newNode;
    } else {
        current = lb->head;
        while (current->next != NULL && current->next->score >= score) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    
    node->next = current->next;
    current->next = node;
}

void displayLeaderboard(Leaderboard* lb, int x, int y) {
    if (lb == NULL) {
        return;
    }
    
    settextstyle(DEFAULT_FONT, HORIZ_DIR, 5);
    setcolor(YELLOW);
    char message[] = "LEADERBOARD";
    outtextxy(x, y, message);

    LeaderboardNode* current = lb->head;
    int offset = 40;
    int rank = 1;
    char buffer[100];

    settextstyle(DEFAULT_FONT, HORIZ_DIR, 3);
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