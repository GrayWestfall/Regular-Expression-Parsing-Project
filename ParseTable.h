/*
 * ParseTable.h
 * Author: Grayson Westfall
 * Created Sep 29, 2021
 */

#include <stdio.h>
#include <stdlib.h>
#include "Production.h"

// ParseTable class used to hold productions, parsing table,
// and other elements as used in table driven parsing function

typedef struct ParseTable* ParseTable;

struct ParseTable {
    int numSyntacticCategories;
    int numProductions;
    char** productionHeads;
    int** parsingTable;
    Production* productionArray;
    
};

ParseTable new_ParseTable(int numSyntacticCategories, char** syntacticCategoryNames, int numProductions);
void ParseTable_free(ParseTable this);

void ParseTable_setProduction0(ParseTable this, int productionIndex, char* head, char* constituent1);
void ParseTable_setProduction1(ParseTable this, int productionIndex, char* head, char* constituent1, char* constituent2);
void ParseTable_setProduction2(ParseTable this, int productionIndex, char* head, char* constituent1, char* constituent2, char* constituent3);

