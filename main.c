#include <stdio.h>
#include <stdlib.h>
#include "criminal.h"
#include "case.h"
#include "graph.h"
#include "history.h"
#include "file_handling.h"


CriminalList criminals;
CaseQueue cases;
Graph criminal_network;


void mainMenu();


int main() 
{
    initCriminalList(&criminals);
    initCaseQueue(&cases);
    initGraph(&criminal_network);
    inithist();
    
    loadcrim(&criminals);
    loadcase(&cases);
    
    printf("=== CRIMINAL MANAGEMENT SYSTEM ===\n");
    printf("Welcome to the Criminal System\n");
    
    mainMenu();
    
    savecrim(&criminals);
    savecase(&cases);
    
    return 0;
}

void mainMenu() 
{
    int choice;
    int id;
    
    do 
    {
        printf("\n=== MAIN MENU ===\n");
        printf("1. Criminal Management (Linked List)\n");
        printf("2. Case Management (Queue - FIFO)\n");
        printf("3. Criminal Network\n");
        printf("4. View Criminal Detailed History\n");
        printf("5. View Case Detailed History\n");
        printf("6. View Change Log\n");
        printf("7. Save All Data\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1: 
                criminalMenu(&criminals); 
                break;
            case 2: 
                caseMenu(&cases); 
                break;
            case 3: 
                networkMenu(&criminal_network); 
                break;
            case 4: 
                printf("Enter Criminal ID: "); 
                scanf("%d", &id); 
                showcrimdethist(id); 
                break;
            case 5: 
                printf("Enter Criminal ID: "); 
                scanf("%d", &id); 
                showcasedethist(id); 
                break;
            case 6: 
                showlog(); 
                break;
            case 7:
                savecrim(&criminals);
                savecase(&cases);
                printf("All data saved successfully!\n");
                break;
            case 8: 
                printf("Thank you for using the system. Goodbye!\n"); 
                break;
            default: 
                printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 8);
}
