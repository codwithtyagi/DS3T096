#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CONNECTIONS 100

// Structure for Graph Connection
typedef struct 
{
    int criminal1_id;
    int criminal2_id;
} Connection;

// Structure for Graph
typedef struct 
{
    Connection connections[MAX_CONNECTIONS];
    int num_connections;
} Graph;

// Function prototypes
void initGraph(Graph *graph);
void addConnection(Graph *graph, int criminal1_id, int criminal2_id);
void displayNetwork(Graph *graph);
void networkMenu(Graph *graph);

#endif // GRAPH_H
