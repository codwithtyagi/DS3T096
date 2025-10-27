#include "criminal.h"
#include "history.h"

// Initialize criminal linked list
void initCriminalList(CriminalList *list) 
{
    list->head = NULL;
    list->size = 0;
}

// Criminal Module Implementation using Linked List
void addCriminal(CriminalList *list) 
{
    CriminalNode *newNode = (CriminalNode*)malloc(sizeof(CriminalNode));
    if (newNode == NULL) 
    {
        printf("Memory allocation failed.\n");
        return;
    }
    
    printf("\n=== ADD NEW CRIMINAL ===\n");
    printf("Enter Criminal ID: ");
    scanf("%d", &newNode->data.id);
    
    // Check if ID already exists
    CriminalNode *current = list->head;
    while (current != NULL) 
    {
        if (current->data.id == newNode->data.id) 
        {
            printf("Criminal ID already exists.\n");
            free(newNode);
            return;
        }
        current = current->next;
    }
    
    printf("Enter Name: ");
    getchar(); 
    fgets(newNode->data.name, MAX_NAME_LEN, stdin);
    newNode->data.name[strcspn(newNode->data.name, "\n")] = 0; 
    
    printf("Enter Age: ");
    scanf("%d", &newNode->data.age);
    
    printf("Enter Crime: ");
    getchar();
    fgets(newNode->data.crime, MAX_CRIME_LEN, stdin);
    newNode->data.crime[strcspn(newNode->data.crime, "\n")] = 0;
    
    printf("Enter Status (Active/Inactive/Fugitive): ");
    scanf("%s", newNode->data.status);
    
    // Insert at the end
    newNode->next = NULL;
    if (list->head == NULL) 
    {
        list->head = newNode;
    } 
    else 
    {
        current = list->head;
        while (current->next != NULL) 
        {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
    
    printf("Criminal added successfully!\n");
    addHistoryAction("Added new criminal");
}

void displayCriminals(CriminalList *list) 
{
    printf("\n=== ALL CRIMINALS ===\n");
    if (list->head == NULL) 
    {
        printf("No criminals found.\n");
        return;
    }
    
    printf("%-5s %-20s %-5s %-30s %-15s\n", "ID", "Name", "Age", "Crime", "Status");
    printf("------------------------------------------------------------------------\n");
    
    CriminalNode *current = list->head;
    while (current != NULL) 
    {
        printf("%-5d %-20s %-5d %-30s %-15s\n",
               current->data.id,
               current->data.name,
               current->data.age,
               current->data.crime,
               current->data.status);
        current = current->next;
    }
    printf("\nTotal criminals: %d\n", list->size);
}

void searchCriminal(CriminalList *list) 
{
    int search_id;
    printf("\n=== SEARCH CRIMINAL ===\n");
    printf("Enter Criminal ID to search: ");
    scanf("%d", &search_id);
    
    CriminalNode *current = list->head;
    while (current != NULL) 
    {
        if (current->data.id == search_id) 
        {
            printf("\nCriminal Found:\n");
            printf("ID: %d\n", current->data.id);
            printf("Name: %s\n", current->data.name);
            printf("Age: %d\n", current->data.age);
            printf("Crime: %s\n", current->data.crime);
            printf("Status: %s\n", current->data.status);
            addHistoryAction("Searched for criminal");
            return;
        }
        current = current->next;
    }
    printf("Criminal not found.\n");
}

void deleteCriminal(CriminalList *list) 
{
    int delete_id;
    printf("\n=== DELETE CRIMINAL ===\n");
    printf("Enter Criminal ID to delete: ");
    scanf("%d", &delete_id);
    
    if (list->head == NULL) 
    {
        printf("No criminals to delete.\n");
        return;
    }
    
    // If head node is to be deleted
    if (list->head->data.id == delete_id) 
    {
        CriminalNode *temp = list->head;
        list->head = list->head->next;
        free(temp);
        list->size--;
        printf("Criminal deleted successfully!\n");
        addHistoryAction("Deleted criminal");
        return;
    }
    
    // Search for the criminal to delete
    CriminalNode *current = list->head;
    while (current->next != NULL) 
    {
        if (current->next->data.id == delete_id) 
        {
            CriminalNode *temp = current->next;
            current->next = current->next->next;
            free(temp);
            list->size--;
            printf("Criminal deleted successfully!\n");
            addHistoryAction("Deleted criminal");
            return;
        }
        current = current->next;
    }
    
    printf("Criminal not found.\n");
}

void updateCriminal(CriminalList *list) 
{
    int update_id;
    printf("\n=== UPDATE CRIMINAL ===\n");
    printf("Enter Criminal ID to update: ");
    scanf("%d", &update_id);
    
    CriminalNode *current = list->head;
    while (current != NULL) 
    {
        if (current->data.id == update_id) 
        {
            printf("Current details:\n");
            printf("Name: %s\n", current->data.name);
            printf("Age: %d\n", current->data.age);
            printf("Crime: %s\n", current->data.crime);
            printf("Status: %s\n", current->data.status);
            
            printf("\nEnter new details:\n");
            printf("Enter Name: ");
            getchar();
            fgets(current->data.name, MAX_NAME_LEN, stdin);
            current->data.name[strcspn(current->data.name, "\n")] = 0;
            
            printf("Enter Age: ");
            scanf("%d", &current->data.age);
            
            printf("Enter Crime: ");
            getchar();
            fgets(current->data.crime, MAX_CRIME_LEN, stdin);
            current->data.crime[strcspn(current->data.crime, "\n")] = 0;
            
            printf("Enter Status: ");
            scanf("%s", current->data.status);
            
            printf("Criminal updated successfully!\n");
            addHistoryAction("Updated criminal details");
            return;
        }
        current = current->next;
    }
    printf("Criminal not found.\n");
}

void criminalMenu(CriminalList *list) 
{
    int choice;
    do 
    {
        printf("\n=== CRIMINAL MANAGEMENT ===\n");
        printf("1. Add Criminal\n");
        printf("2. Display All Criminals\n");
        printf("3. Search Criminal\n");
        printf("4. Update Criminal\n");
        printf("5. Delete Criminal\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1: addCriminal(list); break;
            case 2: displayCriminals(list); break;
            case 3: searchCriminal(list); break;
            case 4: updateCriminal(list); break;
            case 5: deleteCriminal(list); break;
            case 6: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 6);
}
