#include "graph.h"
#include "history.h"

// Graph Implementation
void initGraph(Graph *graph) 
{
    graph->num_connections = 0;
    printf("Criminal network graph initialized.\n");
}

void addConnection(Graph *graph, int criminal1_id, int criminal2_id) 
{
    if (graph->num_connections < MAX_CONNECTIONS) {
        graph->connections[graph->num_connections].criminal1_id = criminal1_id;
        graph->connections[graph->num_connections].criminal2_id = criminal2_id;
        graph->num_connections++;
        printf("Connection added between Criminal ID %d and %d\n", criminal1_id, criminal2_id);
        addHistoryAction("Added connection between criminals");
    } 
    else 
    {
        printf("Maximum connections reached.\n");
    }
}

void displayNetwork(Graph *graph) 
{
    printf("\n=== CRIMINAL NETWORK ===\n");
    if (graph->num_connections == 0) 
    {
        printf("No connections found in the network.\n");
        return;
    }
    
    printf("Criminal Connections:\n");
    printf("%-10s %-10s\n", "Criminal 1", "Criminal 2");
    printf("----------------------------------------\n");
    
    for (int i = 0; i < graph->num_connections; i++) 
    {
        printf("%-10d %-10d\n", 
               graph->connections[i].criminal1_id,
               graph->connections[i].criminal2_id);
    }
    printf("Total connections: %d\n", graph->num_connections);
}

void networkMenu(Graph *graph) 
{
    int choice;
    do 
    {
        printf("\n=== CRIMINAL NETWORK ===\n");
        printf("1. Display Network\n");
        printf("2. Add Connection\n");
        printf("3. Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) 
        {
            case 1: displayNetwork(graph); break;
            case 2: 
            {
                int id1, id2;
                printf("Enter Criminal ID 1: ");
                scanf("%d", &id1);
                printf("Enter Criminal ID 2: ");
                scanf("%d", &id2);
                addConnection(graph, id1, id2);
                break;
            }
            case 3: printf("Returning to main menu...\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } 
    while (choice != 3);
}
