/*
 * ParseTable.c
 * Author: Grayson Westfall
 * Created Sep 29, 2021
 */

#include "ParseTable.h"

// ParseTable initializer
ParseTable new_ParseTable(int numSyntacticCategories, char** syntacticCategoryNames, int numProductions) {
    ParseTable this = (ParseTable)malloc(sizeof(struct ParseTable));
    
    this->numSyntacticCategories = numSyntacticCategories;
    this->numProductions = numProductions;
    
    this->productionHeads = malloc(sizeof(char*) * numSyntacticCategories);
    for (int i = 0; i < numSyntacticCategories; ++i) {
        this->productionHeads[i] = strdup(syntacticCategoryNames[i]);
    }
    
    
    this->parsingTable = malloc(sizeof(int*) * numSyntacticCategories);
    for (int i = 0; i < numSyntacticCategories; ++i) {
        this->parsingTable[i] = malloc(sizeof(int) * 128);
        
        // Initialize all values to -1
        for (int j = 0; j < 128; ++j) {
            this->parsingTable[i][j] = -1;
        }
    }
    
    this->productionArray = malloc(sizeof(struct Production) * numProductions);
    
    return this;
    
}

// Frees the given ParseTable
void ParseTable_free(ParseTable this) {
    
    for (int i = 0; i < this->numProductions; ++i) {
        if (this->productionArray[i] != NULL) {
            Production_free(this->productionArray[i]);
        }
    }
    free(this->productionArray);
    
    for (int i = 0; i < this->numSyntacticCategories; ++i) {
        free(this->parsingTable[i]);
    }
    free(this->parsingTable);
    
    for (int i = 0; i < this->numSyntacticCategories; ++i) {
        free(this->productionHeads[i]);
    }
    free(this->productionHeads);
    
    free(this);
}

// Set the Production at the given index in the productionArray with one constituent
void ParseTable_setProduction0(ParseTable this, int productionIndex, char* head, char* constituent1) {
    if (productionIndex < this->numProductions) {
        this->productionArray[productionIndex] = new_Production0(head, constituent1);
    }
}

// Set the Production at the given index in the productionArray with two constituent
void ParseTable_setProduction1(ParseTable this, int productionIndex, char* head, char* constituent1, char* constituent2) {
    if (productionIndex < this->numProductions) {
        this->productionArray[productionIndex] = new_Production1(head, constituent1, constituent2);
    }
}

// Set the Production at the given index in the productionArray with three constituent
void ParseTable_setProduction2(ParseTable this, int productionIndex, char* head, char* constituent1, char* constituent2, char* constituent3) {
    if (productionIndex < this->numProductions) {
        this->productionArray[productionIndex] = new_Production2(head, constituent1, constituent2, constituent3);
    }
}

