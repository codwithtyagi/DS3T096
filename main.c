#include <stdio.h>
#include <stdlib.h>
#include "criminal.h"
#include "case.h"
#include "graph.h"
#include "history.h"

// Global variables using linked lists and queue
CriminalList criminals;
CaseQueue cases;
Graph criminal_network;
HistoryStack history;

// Function prototypes
void mainMenu();

// Main function
int main() 
{
    // Initialize systems
    initCriminalList(&criminals);
    initCaseQueue(&cases);
    initGraph(&criminal_network);
    initHistory(&history);
    
    printf("=== CRIMINAL MANAGEMENT SYSTEM ===\n");
    printf("Welcome to the Criminal System\n");
    
    mainMenu();
    return 0;
}

void mainMenu() 
{
    int choice;
    
    do 
    {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Criminal Management (Linked List)\n");
        printf("2. Case Management (Queue - FIFO)\n");
        printf("3. Criminal Network\n");
        printf("4. View Action History (Stack)\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1: criminalMenu(&criminals); break;
            case 2: caseMenu(&cases); break;
            case 3: networkMenu(&criminal_network); break;
            case 4: displayHistory(&history); break;
            case 5: printf("Thank you for using the system. Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 5);
}
