#include "file_handling.h"
#include "criminal.h"
#include "case.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void readfield(char* line, int* pos, char* field, int maxlen)
{
    int i = 0;
    while (line[*pos] != '|' && line[*pos] != '\n' && line[*pos] != '\0' && i < maxlen - 1) {
        field[i] = line[*pos];
        i++;
        (*pos)++;
    }
    field[i] = '\0';
    if (line[*pos] == '|') (*pos)++;
        }

void savecrim(CriminalList* crimlist)
{
    FILE *f = fopen("criminals.txt", "w");
    if (!f) {
        printf("error: cannot open file\n");
        return;
    }
    
    fprintf(f, "%d\n", crimlist->size);
    CriminalNode *curr = crimlist->head;
    while (curr) {
        fprintf(f, "%d|%s|%d|%s|%s\n", 
                curr->data.id, curr->data.name, curr->data.age, 
                curr->data.crime, curr->data.status);
        curr = curr->next;
    }
    fclose(f);
    printf("criminals saved\n");
}

void loadcrim(CriminalList* crimlist)
{
    FILE *f = fopen("criminals.txt", "r");
    if (!f) return;
    
    int count, i;
    fscanf(f, "%d\n", &count);
    
    crimlist->size = 0;
    crimlist->head = NULL;
    CriminalNode *last = NULL;
    
    for (i = 0; i < count; i++) {
        CriminalNode *n = (CriminalNode*)malloc(sizeof(CriminalNode));
        if (!n) break;
        
        char line[300];
        if (!fgets(line, 300, f)) break;
        
        int pos = 0;
        char field[100];
        
        readfield(line, &pos, field, 100);
        n->data.id = atoi(field);
        
        readfield(line, &pos, n->data.name, 50);
        
        readfield(line, &pos, field, 100);
        n->data.age = atoi(field);
        
        readfield(line, &pos, n->data.crime, 100);
        
        readfield(line, &pos, n->data.status, 20);
        
        n->next = NULL;
        if (!crimlist->head) {
            crimlist->head = last = n;
        } else {
            last->next = n;
            last = n;
        }
        crimlist->size++;
    }
    fclose(f);
}

void savecase(CaseQueue* casequeue)
{
    FILE *f = fopen("cases.txt", "w");
    if (!f) {
        printf("error: cannot open file\n");
        return;
    }
    
    fprintf(f, "%d\n", casequeue->size);
    CaseNode *curr = casequeue->front;
    while (curr) {
        fprintf(f, "%d|%s|%s|%d|%d|%s\n", 
                curr->data.caseid, curr->data.title, curr->data.description,
                curr->data.criminalid, curr->data.priority, curr->data.status);
        curr = curr->next;
    }
    fclose(f);
    printf("cases saved\n");
}

void loadcase(CaseQueue* casequeue)
{
    FILE *f = fopen("cases.txt", "r");
    if (!f) return;
    
    int count, i;
    fscanf(f, "%d\n", &count);
    
    casequeue->size = 0;
    casequeue->front = casequeue->rear = NULL;
    CaseNode *last = NULL;
    
    for (i = 0; i < count; i++) {
        CaseNode *n = (CaseNode*)malloc(sizeof(CaseNode));
        if (!n) break;
        
        char line[500];
        if (!fgets(line, 500, f)) break;
        
        int pos = 0;
        char field[100];
        
        readfield(line, &pos, field, 100);
        n->data.caseid = atoi(field);
        
        readfield(line, &pos, n->data.title, 100);
        
        readfield(line, &pos, n->data.description, 200);
        
        readfield(line, &pos, field, 100);
        n->data.criminalid = atoi(field);
        
        readfield(line, &pos, field, 100);
        n->data.priority = atoi(field);
        
        readfield(line, &pos, n->data.status, 20);
        
        n->next = NULL;
        if (!casequeue->front) {
            casequeue->front = casequeue->rear = last = n;
        } else {
            last->next = n;
            last = casequeue->rear = n;
        }
        casequeue->size++;
    }
    fclose(f);
}
