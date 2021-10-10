/*
 * Production.h
 * Author: Grayson Westfall
 * Created Sep 29, 2021
 */

#include <stdlib.h>
#include <string.h>
#include "Stack.h"

// Production class used to hold productions
// of the grammar in the ParseTable class

typedef struct Production* Production;

struct Production {
    char* head;
    char* constituent1;
    char* constituent2;
    char* constituent3;
};

Production new_Production0(char* head, char* constituent1);
Production new_Production1(char* head, char* constituent1, char* constituent2);
Production new_Production2(char* head, char* constituent1, char* constituent2, char* constituent3);

void Production_free(Production this);

void Production_checkProduction(Production curProduction, Stack symbolStack);
