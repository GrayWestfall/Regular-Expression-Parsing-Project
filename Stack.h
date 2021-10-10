/*
 * Stack.h
 * Author: Grayson Westfall
 * Created Sep 27, 2021
 */

// Stack class as used in table-driven parsing

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

typedef struct Stack* Stack;
typedef struct StackNode* StackNode;

struct StackNode {
    char* label;
    StackNode next;
};
struct Stack {
    StackNode first;
};

StackNode new_StackNode(char* label);
Stack new_Stack();
void Stack_free(Stack this);
void Stack_push(Stack stack, char* label);
char* Stack_pop(Stack stack);
bool Stack_isEmpty(Stack stack);
char* strdup(const char* s);
