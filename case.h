#ifndef CASE_H
#define CASE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CASE_TITLE_LEN 100

// Case data structure
typedef struct 
{
    int case_id;
    char title[MAX_CASE_TITLE_LEN];
    char description[200];
    int criminal_id;
    int priority; // 1 = Urgent, 0 = Normal
    char status[20]; // "Open", "Closed", "Under Investigation"
} Case;

// Queue node for cases
typedef struct CaseNode 
{
    Case data;
    struct CaseNode *next;
} CaseNode;

// Queue structure for cases (FIFO)
typedef struct 
{
    CaseNode *front;  // Front of the queue (oldest)
    CaseNode *rear;   // Rear of the queue (newest)
    int size;
} CaseQueue;

// Function prototypes
void initCaseQueue(CaseQueue *queue);
void enqueueCase(CaseQueue *queue);  // Add to rear
Case dequeueCase(CaseQueue *queue);  // Remove from front
Case peekCase(CaseQueue *queue);     // View front without removing
int isCaseQueueEmpty(CaseQueue *queue);
void addCase(CaseQueue *queue);  // Wrapper for enqueue
void displayCases(CaseQueue *queue);
void displayUrgentCases(CaseQueue *queue);
void caseMenu(CaseQueue *queue);

#endif 

