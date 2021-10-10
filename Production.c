/*
 * Production.c
 * Author: Grayson Westfall
 * Created Sep 29, 2021
 */

#include "Production.h"

// Initialize the production with only one constituent
Production new_Production0(char* head, char* constituent1) {
    Production this = (Production)malloc(sizeof(struct Production));
    this->head = strdup(head);
    this->constituent1 = strdup(constituent1);
    this->constituent2 = NULL;
    this->constituent3 = NULL;
    
    return this;
}

// Initialize the production with two constituents
Production new_Production1(char* head, char* constituent1, char* constituent2) {
    Production this = (Production)malloc(sizeof(struct Production));
    this->head = strdup(head);
    this->constituent1 = strdup(constituent1);
    this->constituent2 = strdup(constituent2);
    this->constituent3 = NULL;
    
    return this;
}

// Initialize the production with three constituents
Production new_Production2(char* head, char* constituent1, char* constituent2, char* constituent3) {
    Production this = (Production)malloc(sizeof(struct Production));
    this->head = strdup(head);
    this->constituent1 = strdup(constituent1);
    this->constituent2 = strdup(constituent2);
    this->constituent3 = strdup(constituent3);
    
    return this;
}

// Free the given Production
void Production_free(Production this) {
    free(this->head);
    if (this->constituent1 != NULL) {
        free(this->constituent1);
    }
    if (this->constituent2 != NULL) {
        free(this->constituent2);
    }
    if (this->constituent3 != NULL) {
        free(this->constituent3);
    }
}

// Production checker as used in table driven parser:
// pushes the constituents of the Production to the given Stack
void Production_checkProduction(Production curProduction, Stack symbolStack) {
    
    if (curProduction->constituent3 != NULL) {
        Stack_push(symbolStack, curProduction->constituent3);
    }
    if (curProduction->constituent2 != NULL) {
        Stack_push(symbolStack, curProduction->constituent2);
    }
    if (curProduction->constituent1 != NULL && strcmp(curProduction->constituent1, "eps")) {
        Stack_push(symbolStack, curProduction->constituent1);
    }
}


