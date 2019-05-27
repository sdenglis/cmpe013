// Heap size 2048 required!

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "BinaryTree.h"

// **** Set any macros or preprocessor directives here ****


// **** Define any module-level, global, or external variables here ****


// **** Declare any function prototypes here ****

int main()
{
    BOARD_Init();

    printf("\nWelcome to sdenglis's Binary Tree test harness, compiled on %s %s\n", __DATE__, __TIME__);

    //this is a simple test binary tree, included so you can write the relatively simple TreePrint() before implementing CreateTree().  In general, you should NOT create your binary trees this way.
    //level 1 (leaf) nodes
    Node nodeD = {NULL, NULL, 'D'};
    Node nodeE = {NULL, NULL, 'E'};
    Node nodeF = {NULL, NULL, 'F'};
    Node nodeG = {NULL, NULL, 'G'};
    //level 2 nodes:
    Node nodeB = {&nodeD, &nodeE, 'B'};
    Node nodeC = {&nodeF, &nodeG, 'C'};
    //level 3 node:
    Node nodeA = {&nodeB, &nodeC, 'A'};
    Node * root = &nodeA;

    //now, you can call TreePrint():
    TreePrint(root, 4);

    printf("\n_____________\n");

    //Now write TreeCreate() and try it again!
    Node *treeRoot = TreeCreate(3, "abdecfg");

    //Now we print the created tree!
    TreePrint(treeRoot, 4);

    printf("\n_____________\n");

    //And again:
    Node *bigTree = TreeCreate(4, "ABDHIEJKCFLMGNO");
    TreePrint(bigTree, 0);

    Node *nullTree = TreeCreate(0, "\0"); //??????
    TreePrint(nullTree, 0);

    printf("\n_____________\n");

    Node *morseTree = TreeCreate(6, "#EISH54V#3UF####2ARL#####WP##J#1TNDB6#X##KC##Y##MGZ7#Q##O#8##90"); //full morse tree.
    TreePrint(morseTree, 0);


    while (1);
}

