/*
 * Stack.c
 * Author: Grayson Westfall
 * Created Sep 27, 2021
 */

#include "Stack.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

// Initializer for Stack nodes (differentiates from Tree nodes)
StackNode new_StackNode(char* label) {
    StackNode this = (StackNode)malloc(sizeof(struct StackNode));
    this->label = strdup(label);
    this->next = NULL;
    return this;
}

// Stack initializer
Stack new_Stack() {
   Stack this = (Stack)malloc(sizeof(struct Stack));
   this->first = NULL;
   
   return this;
}

// Frees the given Stack
void Stack_free(Stack this) {
    while (!Stack_isEmpty(this)) {
        Stack_pop(this);
    }
    free(this);
}

// Push the item 'label' onto the stack
void Stack_push(Stack stack, char* label) {
    StackNode newFirst = new_StackNode(label);
    newFirst->next = stack->first;
    stack->first = newFirst;
}

// Pop the first item off the stack and return it
char* Stack_pop(Stack stack) {
    if (stack->first == NULL) {
        return NULL;
    }
    else {
        char* returnVal = strdup(stack->first->label);
        StackNode hold = stack->first;
        stack->first = stack->first->next;
        free(hold->label);
        free(hold);
        return returnVal;
    }
}

// Returns true if the stack has no items in it
bool Stack_isEmpty(Stack stack) {
    return stack->first == NULL;
}

// String duplication method used to malloc
// string objects in structs
char* strdup(const char* s) {
    char *t = (char*)malloc(strlen(s)+1);
    strcpy(t, s);
    return t;
}
