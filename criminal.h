#ifndef CRIMINAL_H
#define CRIMINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_CRIME_LEN 100

// Criminal data structure
typedef struct 
{
    int id;
    char name[MAX_NAME_LEN];
    int age;
    char crime[MAX_CRIME_LEN];
    char status[20]; // "Active", "Inactive", "Fugitive"
} Criminal;

// Linked list node for criminals
typedef struct CriminalNode 
{
    Criminal data;
    struct CriminalNode *next;
} CriminalNode;

// Linked list structure for criminals
typedef struct 
{
    CriminalNode *head;
    int size;
} CriminalList;

// Function prototypes
void initCriminalList(CriminalList *list);
void addCriminal(CriminalList *list);
void displayCriminals(CriminalList *list);
void searchCriminal(CriminalList *list);
void deleteCriminal(CriminalList *list);
void updateCriminal(CriminalList *list);
void criminalMenu(CriminalList *list);

#endif // CRIMINAL_H
