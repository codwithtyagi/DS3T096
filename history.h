#ifndef HISTORY_H
#define HISTORY_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_HISTORY 50

// Structure for History Action
typedef struct 
{
    char action[100];
    char timestamp[50];
} HistoryAction;

// Stack structure for History (proper LIFO stack)
typedef struct 
{
    HistoryAction actions[MAX_HISTORY];
    int top;  // Points to the top of the stack
} HistoryStack;

// Function prototypes
void initHistory(HistoryStack *hist);
void pushHistory(HistoryStack *hist, const char* action);  // Push to stack
HistoryAction popHistory(HistoryStack *hist);  // Pop from stack
HistoryAction peekHistory(HistoryStack *hist);  // Peek at top
int isHistoryEmpty(HistoryStack *hist);
int isHistoryFull(HistoryStack *hist);
void addHistoryAction(const char* action);  // Wrapper for push
void displayHistory(HistoryStack *hist);

#endif // HISTORY_H
