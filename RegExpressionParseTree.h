/*
 * RegExpressionParseTree.h
 * Author: Grayson Westfall
 * Created Sep 26, 2021
 */

#include "ParseTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Regular Expression Parse Tree as used for both types of
// parsing.  Stores both the structure of the parse tree
// as well as runs the project itself

typedef struct Node *Tree;
typedef struct RegExpressionParseTree* RegExpressionParseTree;

struct Node {
    char* label;
    Tree leftChild;
    Tree middleChild;
    Tree rightChild;
};

struct RegExpressionParseTree {
    char* stringToParse;
    int parseIndex;
    Tree root;
};

RegExpressionParseTree new_RegExpressionParseTree_RecDescent(char* stringToParse);
RegExpressionParseTree new_RegExpressionParseTree_TableDriven(char* stringToParse);
void RegExpressionParseTree_free(RegExpressionParseTree REPtree);
void freeTree(Tree root);
void freeTree_Rec(Tree curNode);
char RegExpressionParseTree_nextChar(RegExpressionParseTree REPtree);
void RegExpressionParseTree_print(RegExpressionParseTree REPtree);
void printParseTreeRec(Tree curNode, int tabIndex);

Tree makeNode0(char* label);
Tree makeNode1(char* label, Tree t1);
Tree makeNode2(char* label, Tree t1, Tree t2);
Tree makeNode3(char* label, Tree t1, Tree t2, Tree t3);

Tree checkE_Rec(RegExpressionParseTree REPtree);
Tree checkET_Rec(RegExpressionParseTree REPtree);
Tree checkC_Rec(RegExpressionParseTree REPtree);
Tree checkCT_Rec(RegExpressionParseTree REPtree);
Tree checkS_Rec(RegExpressionParseTree REPtree);
Tree checkST_Rec(RegExpressionParseTree REPtree);
Tree checkA_Rec(RegExpressionParseTree REPtree);
Tree checkX_Rec(RegExpressionParseTree REPtree);


bool nodeIsLeaf(Tree n1);
Tree searchLeafFromLeft(Tree root, char* label);
Tree searchLeafFromLeft_Rec(Tree curNode, char* label);

ParseTable initializeRegExpressionParseTable();
void initializeRegExpressionProductions(ParseTable parser);
Tree tableDrivenParse(RegExpressionParseTree REPtree, ParseTable parser);


void printExpressionTree(Tree root);
void printExpressionTreeRec(Tree curNode, int tabIndex);
void printExpressionTree_PrefixForm(Tree root);
void printExpressionTree_PrefixForm_Rec(Tree curNode);

Tree convertToExpressionTree(RegExpressionParseTree REPtree);
Tree convertToExpressionTree_Rec(char* expressionString, int startIndex, int endIndex);
