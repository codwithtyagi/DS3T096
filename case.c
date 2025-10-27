#include<stdio.h>
#include<string.h>
#include "case.h"
#include "history.h"

// Initialize case queue
void initCaseQueue(CaseQueue *queue) 
{
    queue->front = NULL;
    queue->rear = NULL;
    queue->size = 0;
}

// Check if queue is empty
int isCaseQueueEmpty(CaseQueue *queue) 
{
    return queue->front == NULL;
}

// Enqueue case (Add to rear of queue)
void enqueueCase(CaseQueue *queue) 
{
    CaseNode *newNode = (CaseNode*)malloc(sizeof(CaseNode));
    if (newNode == NULL) 
    {
        printf("Memory allocation failed.\n");
        return;
    }
    
    printf("\n=== ADD NEW CASE (QUEUE) ===\n");
    printf("Enter Case ID: ");
    scanf("%d", &newNode->data.case_id);
    
    // Check if Case ID already exists
    CaseNode *current = queue->front;
    while (current != NULL) 
    {
        if (current->data.case_id == newNode->data.case_id) 
        {
            printf("Case ID already exists.\n");
            free(newNode);
            return;
        }
        current = current->next;
    }
    
    printf("Enter Case Title: ");
    getchar();
    fgets(newNode->data.title, MAX_CASE_TITLE_LEN, stdin);
    newNode->data.title[strcspn(newNode->data.title, "\n")] = 0;
    
    printf("Enter Description: ");
    fgets(newNode->data.description, 200, stdin);
    newNode->data.description[strcspn(newNode->data.description, "\n")] = 0;
    
    printf("Enter Associated Criminal ID: ");
    scanf("%d", &newNode->data.criminal_id);
    
    printf("Enter Priority (1 for Urgent, 0 for Normal): ");
    scanf("%d", &newNode->data.priority);
    
    printf("Enter Status (Open/Closed/Under Investigation): ");
    scanf("%s", newNode->data.status);
    
    // Enqueue operation: Add to rear
    newNode->next = NULL;
    
    if (isCaseQueueEmpty(queue)) 
    {
        // Queue is empty
        queue->front = queue->rear = newNode;
    } 
    else 
    {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    
    queue->size++;
    printf("Case added to queue successfully! (FIFO - Rear)\n");
    addHistoryAction("Added new case to queue");
}

// Dequeue case (Remove from front of queue)
Case dequeueCase(CaseQueue *queue) 
{
    Case emptyCase = {0, "", "", 0, 0, ""};
    
    if (isCaseQueueEmpty(queue)) 
    {
        printf("Queue is empty. Cannot dequeue.\n");
        return emptyCase;
    }
    
    CaseNode *temp = queue->front;
    Case data = temp->data;
    
    // Move front pointer
    queue->front = queue->front->next;
    
    // If queue becomes empty
    if (queue->front == NULL) 
    {
        queue->rear = NULL;
    }
    
    free(temp);
    queue->size--;
    
    return data;
}

// Peek at front of queue without removing
Case peekCase(CaseQueue *queue) 
{
    Case emptyCase = {0, "", "", 0, 0, ""};
    
    if (isCaseQueueEmpty(queue)) 
    {
        return emptyCase;
    }
    
    return queue->front->data;
}

// Wrapper function for backward compatibility
void addCase(CaseQueue *queue) 
{
    enqueueCase(queue);
}

// Display all cases in queue (from front to rear)
void displayCases(CaseQueue *queue) 
{
    printf("\n=== ALL CASES (QUEUE - FIFO) ===\n");
    if (isCaseQueueEmpty(queue)) 
    {
        printf("Queue is empty.\n");
        return;
    }
    
    printf("%-8s %-30s %-15s %-5s %-10s %-20s\n", "Case ID", "Title", "Criminal ID", "Priority", "Status", "Description");
    printf("----------------------------------------------------------------------------------------\n");
    
    CaseNode *current = queue->front;
    while (current != NULL) 
    {
        char priority_text[10];
        strcpy(priority_text, (current->data.priority == 1) ? "Urgent" : "Normal");
        printf("%-8d %-30s %-15d %-10s %-10s %-20s\n",
               current->data.case_id,
               current->data.title,
               current->data.criminal_id,
               priority_text,
               current->data.status,
               current->data.description);
        current = current->next;
    }
    printf("\nTotal cases in queue: %d\n", queue->size);
    printf("Front (oldest): Case ID %d\n", queue->front->data.case_id);
    printf("Rear (newest): Case ID %d\n", queue->rear->data.case_id);
}

void displayUrgentCases(CaseQueue *queue) 
{
    printf("\n=== URGENT CASES (QUEUE) ===\n");
    if (isCaseQueueEmpty(queue)) 
    {
        printf("Queue is empty.\n");
        return;
    }
    
    int urgent_count = 0;
    CaseNode *current = queue->front;
    
    while (current != NULL) 
    {
        if (current->data.priority == 1) 
        {
            if (urgent_count == 0) 
            {
                printf("%-8s %-30s %-15s %-10s %-20s\n", "Case ID", "Title", "Criminal ID", "Status", "Description");
                printf("----------------------------------------------------------------------------------------\n");
            }
            printf("%-8d %-30s %-15d %-10s %-20s\n",
                   current->data.case_id,
                   current->data.title,
                   current->data.criminal_id,
                   current->data.status,
                   current->data.description);
            urgent_count++;
        }
        current = current->next;
    }
    
    if (urgent_count == 0) 
    {
        printf("No urgent cases found.\n");
    } 
    else 
    {
        printf("\nTotal urgent cases: %d\n", urgent_count);
    }
}

void caseMenu(CaseQueue *queue) 
{
    int choice;
    do 
    {
        printf("\n=== CASE MANAGEMENT (QUEUE - FIFO) ===\n");
        printf("1. Add Case (Enqueue)\n");
        printf("2. Remove Oldest Case (Dequeue)\n");
        printf("3. View Next Case (Peek)\n");
        printf("4. Display All Cases\n");
        printf("5. Display Urgent Cases\n");
        printf("6. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1: 
                addCase(queue); 
                break;
            case 2: 
            {
                Case dequeued = dequeueCase(queue);
                if (dequeued.case_id != 0) {
                    printf("\nDequeued Case:\n");
                    printf("ID: %d\n", dequeued.case_id);
                    printf("Title: %s\n", dequeued.title);
                    printf("Description: %s\n", dequeued.description);
                    printf("Criminal ID: %d\n", dequeued.criminal_id);
                    printf("Priority: %s\n", dequeued.priority == 1 ? "Urgent" : "Normal");
                    printf("Status: %s\n", dequeued.status);
                    addHistoryAction("Dequeued case from queue");
                }
                break;
            }
            case 3: 
            {
                Case front = peekCase(queue);
                if (front.case_id != 0) {
                    printf("\nNext Case to Process (Front):\n");
                    printf("ID: %d\n", front.case_id);
                    printf("Title: %s\n", front.title);
                    printf("Description: %s\n", front.description);
                    printf("Criminal ID: %d\n", front.criminal_id);
                    printf("Priority: %s\n", front.priority == 1 ? "Urgent" : "Normal");
                    printf("Status: %s\n", front.status);
                    addHistoryAction("Peeked at front of queue");
                } else {
                    printf("Queue is empty.\n");
                }
                break;
            }
            case 4: 
                displayCases(queue); 
                break;
            case 5: 
                displayUrgentCases(queue); 
                break;
            case 6: 
                printf("Returning to main menu...\n"); 
                break;
            default: 
                printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 6);
}
