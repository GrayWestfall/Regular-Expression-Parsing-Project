/* 
 * Author: Grayson Westfall
 * Created Sep 26, 2021
 */

#include "RegExpressionParseTree.h"

void readRegExpressions();
//void readRegExpressions_TableDriven();
//void convertRegExpressionToExpressionTree();

// The main runner of the project
int main(int argc, char* argv[]) {
    
    printf("\n");
    
    // Call the function to read
    // and parse regular expressions
    readRegExpressions();
    printf("\n");

    return 0;
}

// Initializes a regular expression parse tree using the recursive descent parser
RegExpressionParseTree new_RegExpressionParseTree_RecDescent(char* stringToParse) {
    
    // Initialize the values of the parse tree
    RegExpressionParseTree this = (RegExpressionParseTree)malloc(sizeof(struct RegExpressionParseTree));
    this->stringToParse = strdup(stringToParse);
    this->parseIndex = 0;
    
    // Begin recursive descent parsing to
    // build parse tree then set the root
    // of the actual parse tree struct
    this->root = checkE_Rec(this);
    
    // If not all of the input has been read, reset the
    // root to NULL since the parse has actually failed
    if (this->parseIndex != strlen(this->stringToParse)) {
        freeTree(this->root);
        this->root = NULL;
    }
    
    return this;
}

// Frees the given RegExpressionParseTree
void RegExpressionParseTree_free(RegExpressionParseTree REPtree) {
    if (REPtree->root != NULL) {
        freeTree(REPtree->root);
    }
    free(REPtree);
}

// Frees a Tree when given the root
void freeTree(Tree root) {
    freeTree_Rec(root);
}

// Recursive helper method to help free the given tree
void freeTree_Rec(Tree curNode) {
    if (curNode != NULL) {
        freeTree_Rec(curNode->leftChild);
        freeTree_Rec(curNode->middleChild);
        freeTree_Rec(curNode->rightChild);
        free(curNode->label);
        free(curNode);
    }
}

// Returns the next character to parse based on the current parse index
char RegExpressionParseTree_nextChar(RegExpressionParseTree REPtree) {
    return REPtree->stringToParse[REPtree->parseIndex];
}

// Prints the given RegExpressionParseTree
void RegExpressionParseTree_print(RegExpressionParseTree REPtree) {
    
    // If the root is null, there is no valid parse
    // tree for the given string to parse
    if (REPtree->root == NULL) {
        printf("Invalid input. Try again.\n\n");
        return;
    }
    // else print the tree
    printParseTreeRec(REPtree->root, 0);
    printf("\n");
}

// Recursive helper method to help print the parse tree
void printParseTreeRec(Tree curNode, int tabIndex) {
    if (curNode == NULL) {
        return;
    }
    
    for (int i = 0; i < tabIndex; ++i) {
        printf("    ");
    }
    printf("%s\n", curNode->label);
    printParseTreeRec(curNode->leftChild, tabIndex + 1);
    printParseTreeRec(curNode->middleChild, tabIndex + 1);
    printParseTreeRec(curNode->rightChild, tabIndex + 1);
}

// Initialize a Tree node with no children
Tree makeNode0(char* label) {
    
    Tree root = (Tree)malloc(sizeof(struct Node));
    root->label = strdup(label);
    root->leftChild = NULL;
    root->middleChild = NULL;
    root->rightChild = NULL;
    
    return root;
}

// Initialize a Tree node with one child
Tree makeNode1(char* label, Tree t1) {
    
    Tree root = makeNode0(label);
    root->leftChild = t1;
    
    return root;
}

// Initialize a Tree node with two children
Tree makeNode2(char* label, Tree t1, Tree t2) {
    Tree root = makeNode0(label);
    root->leftChild = t1;
    root->middleChild = t2;
    
    return root;
}

// Initialize a Tree node with three children
Tree makeNode3(char* label, Tree t1, Tree t2, Tree t3) {
    Tree root = makeNode0(label);
    root->leftChild = t1;
    root->middleChild = t2;
    root->rightChild = t3;
    
    return root;
}

// Recursive method that checks the production <E> -> <C><ET>
Tree checkE_Rec(RegExpressionParseTree REPtree) {
    
    Tree curNode1 = checkC_Rec(REPtree);
    Tree curNode2 = checkET_Rec(REPtree);
    
    if (curNode1 != NULL && curNode2 != NULL) {
        return makeNode2("E", curNode1, curNode2);
    }
    return NULL;
}

// Recursive method that checks the production(s) <ET> -> |<E> | eps
Tree checkET_Rec(RegExpressionParseTree REPtree) {
    
    Tree curNode;
    char nextChar = RegExpressionParseTree_nextChar(REPtree);
    
    if (nextChar == '|') {
        ++REPtree->parseIndex;
        curNode = checkE_Rec(REPtree);
        
        if (curNode != NULL) {
            return makeNode2("ET", makeNode0("|"), curNode);
        }
        else {
            return NULL;
        }
    }
    else {
        return makeNode1("ET", makeNode0("eps"));
    }

}

// Recursive method that checks the production <C> -> <S><CT>
Tree checkC_Rec(RegExpressionParseTree REPtree) {
    
    Tree curNode1 = checkS_Rec(REPtree);
    Tree curNode2 = checkCT_Rec(REPtree);
    
    if (curNode1 != NULL && curNode2 != NULL) {
        return makeNode2("C", curNode1, curNode2);
    }
    return NULL;
}

// Recursive method that checks the production(s) <CT> -> .<C> | eps
Tree checkCT_Rec(RegExpressionParseTree REPtree) {
    
    Tree curNode;
    char nextChar = RegExpressionParseTree_nextChar(REPtree);
    
    if (nextChar == '.') {
        ++REPtree->parseIndex;
        curNode = checkC_Rec(REPtree);
        
        if (curNode != NULL) {
            return makeNode2("CT", makeNode0("."), curNode);
        }
        else {
            return NULL;
        }
    }
    else {
        return makeNode1("CT", makeNode0("eps"));
    }
}

// Recursive method that checks the production <S> -> <A><ST>
Tree checkS_Rec(RegExpressionParseTree REPtree) {
    
    Tree curNode1 = checkA_Rec(REPtree);
    Tree curNode2 = checkST_Rec(REPtree);
    
    if (curNode1 != NULL && curNode2 != NULL) {
        return makeNode2("S", curNode1, curNode2);
    }
    return NULL;
}

// Recursive method that checks the production(s) <ST> -> *<ST> | eps
Tree checkST_Rec(RegExpressionParseTree REPtree) {
    
    Tree curNode;
    char nextChar = RegExpressionParseTree_nextChar(REPtree);
    
    if (nextChar == '*') {
        ++REPtree->parseIndex;
        curNode = checkST_Rec(REPtree);
        
        if (curNode != NULL) {
            return makeNode2("ST", makeNode0("*"), curNode);
        }
        else {
            return NULL;
        }
    }
    else {
        return makeNode1("ST", makeNode0("eps"));
    }

}

// Recursive method that checks the production(s) <A> -> (<E>) | <X>
Tree checkA_Rec(RegExpressionParseTree REPtree) {
    
    Tree curNode;
    char nextChar = RegExpressionParseTree_nextChar(REPtree);
    
    if (nextChar == '(') {
        ++REPtree->parseIndex;

        curNode = checkE_Rec(REPtree);
        
        nextChar = RegExpressionParseTree_nextChar(REPtree);

        if (curNode != NULL && nextChar == ')') {
            ++REPtree->parseIndex;
            return makeNode3("A", makeNode0("("), curNode, makeNode0(")"));
        }
    }
    else {
        curNode = checkX_Rec(REPtree);
        
        if (curNode != NULL) {
            return makeNode1("A", curNode);
        }
    }
    return NULL;
}

// Recursive method that checks the production(s) <X> -> a|b|c|...|z
Tree checkX_Rec(RegExpressionParseTree REPtree) {
    
    Tree leafNode;
    
    char nextChar = REPtree->stringToParse[REPtree->parseIndex];
    ++REPtree->parseIndex;
    
    switch (nextChar) {
        case 'a':
            leafNode = makeNode0("a");
            break;
        case 'b':
            leafNode = makeNode0("b");
            break;
        case 'c':
            leafNode = makeNode0("c");
            break;
        case 'd':
            leafNode = makeNode0("d");
            break;
        case 'e':
            leafNode = makeNode0("e");
            break;
        case 'f':
            leafNode = makeNode0("f");
            break;
        case 'g':
            leafNode = makeNode0("g");
            break;
        case 'h':
            leafNode = makeNode0("h");
            break;
        case 'i':
            leafNode = makeNode0("i");
            break;
        case 'j':
            leafNode = makeNode0("j");
            break;
        case 'k':
            leafNode = makeNode0("k");
            break;
        case 'l':
            leafNode = makeNode0("l");
            break;
        case 'm':
            leafNode = makeNode0("m");
            break;
        case 'n':
            leafNode = makeNode0("n");
            break;
        case 'o':
            leafNode = makeNode0("o");
            break;
        case 'p':
            leafNode = makeNode0("p");
            break;
        case 'q':
            leafNode = makeNode0("q");
            break;
        case 'r':
            leafNode = makeNode0("r");
            break;
        case 's':
            leafNode = makeNode0("s");
            break;
        case 't':
            leafNode = makeNode0("t");
            break;
        case 'u':
            leafNode = makeNode0("u");
            break;
        case 'v':
            leafNode = makeNode0("v");
            break;
        case 'w':
            leafNode = makeNode0("w");
            break;
        case 'x':
            leafNode = makeNode0("x");
            break;
        case 'y':
            leafNode = makeNode0("y");
            break;
        case 'z':
            leafNode = makeNode0("z");
            break;
        default:
            return NULL;
    }
    return makeNode1("X", leafNode);
}

// Initializes a regular expression parse tree using the table driven parser
RegExpressionParseTree new_RegExpressionParseTree_TableDriven(char* stringToParse) {
    RegExpressionParseTree this = (RegExpressionParseTree)malloc(sizeof(struct RegExpressionParseTree));
    this->stringToParse = stringToParse;
    this->parseIndex = 0;
    this->root = NULL;
    
    // Create ParseTable object to be used to parse
    ParseTable parsingTable = initializeRegExpressionParseTable();

    this->root = tableDrivenParse(this, parsingTable);

    // Free the parse table as it is no longer needed
    ParseTable_free(parsingTable);
    
    return this;
}


// Returns true if the node has no children
bool nodeIsLeaf(Tree n1) {
    return (n1->leftChild == NULL && n1->middleChild == NULL && n1->rightChild == NULL);
}

// Finds the first leaf matching the specified label
// starting from the left of the tree
Tree searchLeafFromLeft(Tree root, char* label) {
    return searchLeafFromLeft_Rec(root, label);
}

// Recursive helper method to help find matching leaf node
Tree searchLeafFromLeft_Rec(Tree curNode, char* label) {
    
    if (curNode == NULL) {
        return NULL;
    }
    
    if (nodeIsLeaf(curNode) && strcmp(label, curNode->label) == 0) {
        return curNode;
    }
    
    Tree possibleReturn1 = searchLeafFromLeft_Rec(curNode->leftChild, label);
    if (possibleReturn1 != NULL) {
        return possibleReturn1;
    }
    
    Tree possibleReturn2 = searchLeafFromLeft_Rec(curNode->middleChild, label);
    if (possibleReturn2 != NULL) {
        return possibleReturn2;
    }
    
    Tree possibleReturn3 = searchLeafFromLeft_Rec(curNode->rightChild, label);
    if (possibleReturn3 != NULL) {
        return possibleReturn3;
    }
    
    return NULL;
    
}

// Initializes the parsing table values for regular expressions
// and returns the appropriate ParseTable object to match
ParseTable initializeRegExpressionParseTable() {
    
    char** regExpressionSyntacticCategories = malloc(sizeof(char*) * 8);
    
    regExpressionSyntacticCategories[0] = "E";

    regExpressionSyntacticCategories[1] = "ET";

    regExpressionSyntacticCategories[2] = "C";

    regExpressionSyntacticCategories[3] = "CT";

    regExpressionSyntacticCategories[4] = "S";

    regExpressionSyntacticCategories[5] = "ST";

    regExpressionSyntacticCategories[6] = "A";

    regExpressionSyntacticCategories[7] = "X";
    
    ParseTable regExpressionParseTable = new_ParseTable(8, regExpressionSyntacticCategories, 37);
    
    free(regExpressionSyntacticCategories);
    
    char* alphabetString = "abcdefghijklmnopqrstuvwxyz";
    
    for (int i = 0; i < strlen(alphabetString); ++i) {
        char curLetter = alphabetString[i];
        regExpressionParseTable->parsingTable[0][(int)curLetter] = 0;
        regExpressionParseTable->parsingTable[1][(int)curLetter] = 2;
        regExpressionParseTable->parsingTable[2][(int)curLetter] = 3;
        regExpressionParseTable->parsingTable[3][(int)curLetter] = 5;
        regExpressionParseTable->parsingTable[4][(int)curLetter] = 6;
        regExpressionParseTable->parsingTable[5][(int)curLetter] = 8;
        regExpressionParseTable->parsingTable[6][(int)curLetter] = 10;
        switch (curLetter) {
            case 'a':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 11;
                break;
            case 'b':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 12;
                break;
            case 'c':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 13;
                break;
            case 'd':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 14;
                break;
            case 'e':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 15;
                break;
            case 'f':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 16;
                break;
            case 'g':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 17;
                break;
            case 'h':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 18;
                break;
            case 'i':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 19;
                break;
            case 'j':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 20;
                break;
            case 'k':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 21;
                break;
            case 'l':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 22;
                break;
            case 'm':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 23;
                break;
            case 'n':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 24;
                break;
            case 'o':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 25;
                break;
            case 'p':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 26;
                break;
            case 'q':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 27;
                break;
            case 'r':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 28;
                break;
            case 's':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 29;
                break;
            case 't':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 30;
                break;
            case 'u':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 31;
                break;
            case 'v':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 32;
                break;
            case 'w':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 33;
                break;
            case 'x':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 34;
                break;
            case 'y':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 35;
                break;
            case 'z':
                regExpressionParseTable->parsingTable[7][(int)curLetter] = 36;
                break;
        }
    }
    
    char* operatorsString = "|.*()";
    
    for (int i = 0; i < strlen(operatorsString); ++i) {
        char curOperator = operatorsString[i];
        if (curOperator == '(') {
            regExpressionParseTable->parsingTable[0][(int)curOperator] = 0;
        }
        else {
            regExpressionParseTable->parsingTable[0][(int)curOperator] = -1;
        }
    }
    
    for (int i = 0; i < strlen(operatorsString); ++i) {
        char curOperator = operatorsString[i];
        if (curOperator == '|') {
            regExpressionParseTable->parsingTable[1][(int)curOperator] = 1;
        }
        else {
            regExpressionParseTable->parsingTable[1][(int)curOperator] = 2;
        }
    }
    
    for (int i = 0; i < strlen(operatorsString); ++i) {
        char curOperator = operatorsString[i];
        if (curOperator == '(') {
            regExpressionParseTable->parsingTable[2][(int)curOperator] = 3;
        }
        else {
            regExpressionParseTable->parsingTable[2][(int)curOperator] = -1;
        }
    }

    for (int i = 0; i < strlen(operatorsString); ++i) {
        char curOperator = operatorsString[i];
        if (curOperator == '.') {
            regExpressionParseTable->parsingTable[3][(int)curOperator] = 4;
        }
        else {
            regExpressionParseTable->parsingTable[3][(int)curOperator] = 5;
        }
    }
    
    for (int i = 0; i < strlen(operatorsString); ++i) {
        char curOperator = operatorsString[i];
        if (curOperator == '(') {
            regExpressionParseTable->parsingTable[4][(int)curOperator] = 6;
        }
        else {
            regExpressionParseTable->parsingTable[4][(int)curOperator] = -1;
        }
    }
    
    for (int i = 0; i < strlen(operatorsString); ++i) {
        char curOperator = operatorsString[i];
        if (curOperator == '*') {
            regExpressionParseTable->parsingTable[5][(int)curOperator] = 7;
        }
        else {
            regExpressionParseTable->parsingTable[5][(int)curOperator] = 8;
        }
    }
    
    for (int i = 0; i < strlen(operatorsString); ++i) {
        char curOperator = operatorsString[i];
        if (curOperator == '(') {
            regExpressionParseTable->parsingTable[6][(int)curOperator] = 9;
        }
        else {
            regExpressionParseTable->parsingTable[6][(int)curOperator] = -1;
        }
    }
    
    for (int i = 0; i < strlen(operatorsString); ++i) {
        char curOperator = operatorsString[i];
        regExpressionParseTable->parsingTable[7][(int)curOperator] = -1;
    }
    
    // Account for null character (end of string)
    regExpressionParseTable->parsingTable[1][0] = 2;
    regExpressionParseTable->parsingTable[3][0] = 5;
    regExpressionParseTable->parsingTable[5][0] = 8;
    
    initializeRegExpressionProductions(regExpressionParseTable);
    
    return regExpressionParseTable;
}

// Initializes the productions in the parse table for regular expressions
void initializeRegExpressionProductions(ParseTable parser) {
    ParseTable_setProduction1(parser, 0, "E", "C", "ET");
    ParseTable_setProduction1(parser, 1, "ET", "|", "E");
    ParseTable_setProduction0(parser, 2, "ET", "eps");
    ParseTable_setProduction1(parser, 3, "C", "S", "CT");
    ParseTable_setProduction1(parser, 4, "CT", ".", "C");
    ParseTable_setProduction0(parser, 5, "CT", "eps");
    ParseTable_setProduction1(parser, 6, "S", "A", "ST");
    ParseTable_setProduction1(parser, 7, "ST", "*", "ST");
    ParseTable_setProduction0(parser, 8, "ST", "eps");
    ParseTable_setProduction2(parser, 9, "A", "(", "E", ")");
    ParseTable_setProduction0(parser, 10, "A", "X");
    ParseTable_setProduction0(parser, 11, "X", "a");
    ParseTable_setProduction0(parser, 12, "X", "b");
    ParseTable_setProduction0(parser, 13, "X", "c");
    ParseTable_setProduction0(parser, 14, "X", "d");
    ParseTable_setProduction0(parser, 15, "X", "e");
    ParseTable_setProduction0(parser, 16, "X", "f");
    ParseTable_setProduction0(parser, 17, "X", "g");
    ParseTable_setProduction0(parser, 18, "X", "h");
    ParseTable_setProduction0(parser, 19, "X", "i");
    ParseTable_setProduction0(parser, 20, "X", "j");
    ParseTable_setProduction0(parser, 21, "X", "k");
    ParseTable_setProduction0(parser, 22, "X", "l");
    ParseTable_setProduction0(parser, 23, "X", "m");
    ParseTable_setProduction0(parser, 24, "X", "n");
    ParseTable_setProduction0(parser, 25, "X", "o");
    ParseTable_setProduction0(parser, 26, "X", "p");
    ParseTable_setProduction0(parser, 27, "X", "q");
    ParseTable_setProduction0(parser, 28, "X", "r");
    ParseTable_setProduction0(parser, 29, "X", "s");
    ParseTable_setProduction0(parser, 30, "X", "t");
    ParseTable_setProduction0(parser, 31, "X", "u");
    ParseTable_setProduction0(parser, 32, "X", "v");
    ParseTable_setProduction0(parser, 33, "X", "w");
    ParseTable_setProduction0(parser, 34, "X", "x");
    ParseTable_setProduction0(parser, 35, "X", "y");
    ParseTable_setProduction0(parser, 36, "X", "z");
}

// Function that performs a table-driven parse given the appropriate parse table
Tree tableDrivenParse(RegExpressionParseTree REPtree, ParseTable parser) {
    
    bool parseFailed = false;
    Stack symbolStack = new_Stack();
    
    // Begin stack with the initial syntactic category: <E>
    Stack_push(symbolStack, parser->productionHeads[0]);
    Tree parseTreeRoot = makeNode0(parser->productionHeads[0]);
    
    // As long as the stack still contains items, there is
    // still parsing to do (unless it has already been failed)
    while (!Stack_isEmpty(symbolStack) && !parseFailed) {
        
        // Check the next item on the stack and
        // get the current lookahead symbol
        char* nextItem = Stack_pop(symbolStack);
        char nextChar = RegExpressionParseTree_nextChar(REPtree);
        bool itemIsSyntacticCategory = false;
        
        
        // First check if the item matches any syntactic category names
        for (int i = 0; i < parser->numSyntacticCategories && !itemIsSyntacticCategory; ++i) {
            
            if (strcmp(nextItem, parser->productionHeads[i]) == 0) {
                
                itemIsSyntacticCategory = true;
                
                int productionNum = parser->parsingTable[i][(int)nextChar];
                                
                // If the parse table value is negative,
                // then there is no matching production
                // for the current item + lookahead symbol
                if (productionNum < 0) {
                    parseFailed = true;
                }
                else {
                    
                    // If it does match a production, find the proper parent node and give it
                    // children that match its body's constituents
                    
                    Production curProduction = parser->productionArray[productionNum];
                    Tree parentNode = searchLeafFromLeft(parseTreeRoot, parser->productionHeads[i]);
                    
                    if (curProduction->constituent1 != NULL) {
                        parentNode->leftChild = makeNode0(curProduction->constituent1);
                    }
                    if (curProduction->constituent2 != NULL) {
                        parentNode->middleChild = makeNode0(curProduction->constituent2);
                    }
                    
                    if (curProduction->constituent3 != NULL) {
                        parentNode->rightChild = makeNode0(curProduction->constituent3);
                    }
                    
                    // Use the checkProduction method to alter the stack
                    Production_checkProduction(curProduction, symbolStack);
                    
                }
            }
        }
        
        // If it is not a syntactic category,
        // it should be a terminal symbol instead
        if (!itemIsSyntacticCategory) {

            // Should be only one character, terminal symbol
            char terminalSymbol = nextItem[0];
            
            if (terminalSymbol == nextChar) {
                ++REPtree->parseIndex;
            }
            else {
                parseFailed = true;
            }
        }
        
        free(nextItem);
    }
    
    // If not all of the input has been read, the parse has failed
    if (REPtree->parseIndex < strlen(REPtree->stringToParse)) {
        parseFailed = true;
    }
    
    // If the parse has failed, throw away
    // the parse tree we have created
    if (parseFailed) {
        freeTree(parseTreeRoot);
        parseTreeRoot = NULL;
    }
    
    Stack_free(symbolStack);
    
    return parseTreeRoot;
}


// Tree printer used for expression trees
void printExpressionTree(Tree root) {
    printExpressionTreeRec(root, 0);
    printf("\n");
}

// Recursive helper method to help print expression trees
void printExpressionTreeRec(Tree curNode, int tabIndex) {
    if (curNode == NULL) {
        return;
    }
    
    for (int i = 0; i < tabIndex; ++i) {
        printf("    ");
    }
    printf("%s\n", curNode->label);
    printParseTreeRec(curNode->leftChild, tabIndex + 1);
    printParseTreeRec(curNode->middleChild, tabIndex + 1);
    printParseTreeRec(curNode->rightChild, tabIndex + 1);
}

// Converts the string from the RegExpressionParseTree
// into an expression tree
Tree convertToExpressionTree(RegExpressionParseTree REPtree) {
    if (REPtree->root == NULL) {
        return NULL;
    }
    else {
        char* expressionString = strdup(REPtree->stringToParse);
        Tree expressionTreeRoot = convertToExpressionTree_Rec(expressionString, 0, strlen(expressionString) - 1);
        free(expressionString);
        
        return expressionTreeRoot;
    }
}

// Recursive helper method that helps convert the RegExpressionParseTree into an expression tree
Tree convertToExpressionTree_Rec(char* expressionString, int startIndex, int endIndex) {
    
    // If we just have an expression wrapped in parentheses, 'unwrap' it
    if (expressionString[startIndex] == '(' && expressionString[endIndex] == ')') {
        return convertToExpressionTree_Rec(expressionString, startIndex + 1, endIndex - 1);
    }
    
    // If we have only one character left, it should be an operand
    else if (startIndex == endIndex) {
        switch (expressionString[startIndex]) {
            case 'a':
                return makeNode0("a");
                break;
            case 'b':
                return makeNode0("b");
                break;
            case 'c':
                return makeNode0("c");
                break;
            case 'd':
                return makeNode0("d");
                break;
            case 'e':
                return makeNode0("e");
                break;
            case 'f':
                return makeNode0("f");
                break;
            case 'g':
                return makeNode0("g");
                break;
            case 'h':
                return makeNode0("h");
                break;
            case 'i':
                return makeNode0("i");
                break;
            case 'j':
                return makeNode0("j");
                break;
            case 'k':
                return makeNode0("k");
                break;
            case 'l':
                return makeNode0("l");
                break;
            case 'm':
                return makeNode0("m");
                break;
            case 'n':
                return makeNode0("n");
                break;
            case 'o':
                return makeNode0("o");
                break;
            case 'p':
                return makeNode0("p");
                break;
            case 'q':
                return makeNode0("q");
                break;
            case 'r':
                return makeNode0("r");
                break;
            case 's':
                return makeNode0("s");
                break;
            case 't':
                return makeNode0("t");
                break;
            case 'u':
                return makeNode0("u");
                break;
            case 'v':
                return makeNode0("v");
                break;
            case 'w':
                return makeNode0("w");
                break;
            case 'x':
                return makeNode0("x");
                break;
            case 'y':
                return makeNode0("y");
                break;
            case 'z':
                return makeNode0("z");
                break;
            default:
                return NULL;
        }
    }
    
    else {
        
        // Searches for instances of operators in
        // reverse order of their precedence (also
        // accounts for expressions within parentheses)
        
        bool inParens = false; // will help ignore operators within parentheses
        int parensCount = 0;   // count number of parentheses to ensure we account for all pairs
        for (int i = startIndex; i <= endIndex; ++i) {
            
            // Account for if we are within parentheses
            if (expressionString[i] == '(') {
                ++parensCount;
                inParens = true;
            }
            
            // Search for instances of the '|' operator first
            else if (expressionString[i] == '|' && !inParens) {
                return makeNode2("|", convertToExpressionTree_Rec(expressionString, startIndex, i - 1), convertToExpressionTree_Rec(expressionString, i + 1, endIndex));
            }
            
            // Adjust number of parentheses we are still within
            else if (expressionString[i] == ')') {
                --parensCount;
                if (parensCount == 0) {
                    inParens = false;
                }
            }
        }
        
        // Perform the same process for the '.' operator
        
        inParens = false;
        parensCount = 0;
        for (int i = startIndex; i <= endIndex; ++i) {
            
            if (expressionString[i] == '(') {
                ++parensCount;
                inParens = true;
            }
            
            else if (expressionString[i] == '.' && !inParens) {
                return makeNode2(".", convertToExpressionTree_Rec(expressionString, startIndex, i - 1), convertToExpressionTree_Rec(expressionString, i + 1, endIndex));
            }
            
            else if (expressionString[i] == ')') {
                --parensCount;
                if (parensCount == 0) {
                    inParens = false;
                }
            }
        }
        
        // Perform the same process for the '*' operator (must go
        // backward since multiple '*'s can be stacked adjacently)
        
        inParens = false;
        parensCount = 0;
        for (int i = endIndex; i >= startIndex; --i) {
            
            if (expressionString[i] == ')') {
                ++parensCount;
                inParens = true;
            }
            
            else if (expressionString[i] == '*' && !inParens) {
                return makeNode1("*", convertToExpressionTree_Rec(expressionString, startIndex, i - 1));
            }
            
            else if (expressionString[i] == '(') {
                --parensCount;
                if (parensCount == 0) {
                    inParens = false;
                }
            }
        }
    }
    return NULL;
}

// Caller function for printing the given
// expression tree in prefix form
void printExpressionTree_PrefixForm(Tree root) {
    printExpressionTree_PrefixForm_Rec(root);
    printf("\n");
}

// Recursive helper method to print the given
// expression tree in prefix form
void printExpressionTree_PrefixForm_Rec(Tree curNode) {
    if (curNode == NULL) {
        return;
    }
    else {
        printf("(");
        if (strcmp(curNode->label, "|") == 0) {
            printf("UNION ");
            printExpressionTree_PrefixForm_Rec(curNode->leftChild);
            printExpressionTree_PrefixForm_Rec(curNode->middleChild);
            printExpressionTree_PrefixForm_Rec(curNode->rightChild);
            printf(")");
            return;
        }
        else if (strcmp(curNode->label, ".") == 0) {
            printf("CONCAT ");
            printExpressionTree_PrefixForm_Rec(curNode->leftChild);
            printExpressionTree_PrefixForm_Rec(curNode->middleChild);
            printExpressionTree_PrefixForm_Rec(curNode->rightChild);
            printf(")");
            return;
        }
        else if (strcmp(curNode->label, "*") == 0) {
            printf("CLOSURE ");
            printExpressionTree_PrefixForm_Rec(curNode->leftChild);
            printExpressionTree_PrefixForm_Rec(curNode->middleChild);
            printExpressionTree_PrefixForm_Rec(curNode->rightChild);
            printf(")");
            return;
        }
        else {
            printf("ATOMIC %s) ", curNode->label);
            return;
        }
    }
}

// Method that continues reading regular expressions and
// parsing them using first the recursive descent method,
// then the table driven parsing method, then finally translating
// the recursive descent tree into an expression tree
void readRegExpressions() {
    
    char line[256];
    printf("Enter a regular expression (or 'quit.' to quit): ");
    
    while (fgets(line, 255, stdin) != NULL && strcmp(line, "quit.\n") != 0) {
        
        int len = strlen(line);
        char* lineCopy = line;
        if (lineCopy[len - 1] == '\n') {
            lineCopy[len - 1] = 0;
        }
        
        printf("Testing recursive descent parsing...\n");
        RegExpressionParseTree REPtree1 = new_RegExpressionParseTree_RecDescent(lineCopy);
        RegExpressionParseTree_print(REPtree1);
        
        printf("Testing table driven parsing...\n");
        RegExpressionParseTree REPtree2 = new_RegExpressionParseTree_TableDriven(lineCopy);
        RegExpressionParseTree_print(REPtree2);
        RegExpressionParseTree_free(REPtree2);
        REPtree2 = NULL;

        printf("Testing expression tree translation...\n");
        Tree expressionTreeRoot = convertToExpressionTree(REPtree1);
        if (expressionTreeRoot != NULL) {
            printf("Now printing expression tree...\n");
            printExpressionTree(expressionTreeRoot);
            printf("\n");
            
            printf("Now printing prefix form of expression tree...\n");
            printExpressionTree_PrefixForm(expressionTreeRoot);
            printf("\n");
        }
        
        RegExpressionParseTree_free(REPtree1);
        REPtree1 = NULL;
        
        printf("Enter a regular expression (or 'quit.' to quit): ");
    }
}
