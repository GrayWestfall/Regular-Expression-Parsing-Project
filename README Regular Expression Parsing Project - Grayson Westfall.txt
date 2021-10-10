README Regular Expression Parsing Project
Grayson Westfall
EMAIL: graywestfall@gmail.com

This project repeatedly takes a line of input an determines if it forms a 'legal' regular expression.  This is achieved by using first the recursive-descent parsing method, then by using the table-driven parsing method.  The parse tree built by each method is printed separately to confirm their correctness. After the parse trees constructed by both methods have been printed, the project also prints a matching expression tree for the parse tree (both normally and in a prefix form of nested expressions).  If the input line does not form a valid regular expression, the program will print an error message and continue on the next line of input.  The program will terminate when the user inputs 'quit.'.
NOTE: although in typical regular expressions there is no explicit concatenation operator, this program requires one to be explicitly typed using a period ('.') in order to facilitate the parsing process (e.g. ab would become a.b)


The project contains the following files:

Stack.h & Stack.c - create the stack structure as used in table-driven parsing

Production.h & Production.c - a struct used to hold the values of a production, used as values held in the parse table struct

ParseTable.h & ParseTable.c - a struct that holds all the values necessary for a parsing table, initialized in the project runner

RegExpressionParseTree.h & RegExpressionParseTree.c - contain the infrastructure for creating a tree as well as the functions that actually run the project and parsing

All above files contain commentary on the specific uses and purposes of particular portions of the code.

In order to properly run the program, ensure that a file containing all the above files is in your home directory. First cd into this folder from your terminal (e.g. if the file is named RegExpressionParseProject, type 'cd RegExpressionParseProject').  Once you are in this folder, then use the following command line argument to compile and run the program:

gcc -o rexp. -Wall -Werror -std=c99 -g *.c && ./rexp