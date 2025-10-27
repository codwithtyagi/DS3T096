#include "history.h"
#include <time.h>

// Global history stack
HistoryStack history;

// History Implementation using Stack Logic
void initHistory(HistoryStack *hist) 
{
    hist->top = -1;  // Empty stack
}

// Check if stack is empty
int isHistoryEmpty(HistoryStack *hist) 
{
    return hist->top == -1;
}

// Check if stack is full
int isHistoryFull(HistoryStack *hist) 
{
    return hist->top >= MAX_HISTORY - 1;
}

// Push action onto the stack
void pushHistory(HistoryStack *hist, const char* action) 
{
    if (isHistoryFull(hist)) 
    {
        // Stack is full, remove oldest element (bottom of stack)
        // Shift all elements down
        for (int i = 0; i < MAX_HISTORY - 1; i++) 
        {
            hist->actions[i] = hist->actions[i + 1];
        }
        hist->top = MAX_HISTORY - 2;
    }
    
    hist->top++;
    strcpy(hist->actions[hist->top].action, action);
    
    // Create timestamp
    time_t rawtime;
    struct tm *timeinfo;
    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(hist->actions[hist->top].timestamp, sizeof(hist->actions[hist->top].timestamp), 
             "%Y-%m-%d %H:%M:%S", timeinfo);
    
    printf("Action logged: %s\n", action);
}

// Pop action from the stack
HistoryAction popHistory(HistoryStack *hist) 
{
    HistoryAction emptyAction;
    strcpy(emptyAction.action, "");
    strcpy(emptyAction.timestamp, "");
    
    if (isHistoryEmpty(hist)) 
    {
        printf("History stack is empty. Cannot pop.\n");
        return emptyAction;
    }
    
    HistoryAction popped = hist->actions[hist->top];
    hist->top--;
    return popped;
}

// Peek at the top of the stack without removing
HistoryAction peekHistory(HistoryStack *hist) 
{
    HistoryAction emptyAction;
    strcpy(emptyAction.action, "");
    strcpy(emptyAction.timestamp, "");
    
    if (isHistoryEmpty(hist)) 
    {
        return emptyAction;
    }
    
    return hist->actions[hist->top];
}

// Wrapper function for backward compatibility
void addHistoryAction(const char* action) 
{
    pushHistory(&history, action);
}

// Display history (stack is LIFO, so newest is at top)
void displayHistory(HistoryStack *hist) 
{
    printf("\n=== ACTION HISTORY (STACK - LIFO) ===\n");
    if (isHistoryEmpty(hist)) 
    {
        printf("No actions recorded.\n");
        return;
    }
    
    printf("%-20s %-50s\n", "Timestamp", "Action");
    printf("------------------------------------------------------------------------\n");
    
    // Display from top to bottom (newest to oldest)
    for (int i = hist->top; i >= 0; i--) 
    {
        printf("%-20s %-50s\n", 
               hist->actions[i].timestamp, 
               hist->actions[i].action);
    }
    
    printf("\nTotal actions: %d\n", hist->top + 1);
}
