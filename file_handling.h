#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "criminal.h"
#include "case.h"

void savecrim(CriminalList* crimlist);
void loadcrim(CriminalList* crimlist);
void savecase(CaseQueue* casequeue);
void loadcase(CaseQueue* casequeue);

#endif
