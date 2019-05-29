/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 08         *
 *5/28/2019      *
 *****************/
// Heap size 2048 required!

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <stdlib.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "BinaryTree.h"

/**
 * @file
 *
 * This file implements an API for creating and printing a binary tree built of Nodes. Each node can
 * store a single character. There are no function for manipulating the tree as it is assumed that
 * the tree will be traversed and manipulated depending on the data contained within and no generic
 * solution would work.
 * 
 * @note This libraries relies on malloc() being available and usage, therefore a heap must be set.
 *
 * Example usage for creating a tree:
 * char treeData[7] = "abdecfg";        //< This is not a string! It's missing ending '\0'>
 * Node *root = TreeCreate(3, treeData);
 */

/**
 * A node in the binary tree. This is the only element used for representing the tree and there is no
 * object used to represent the tree as a whole. It has a left child, right child, and single char.
 * If either leftChild or rightChild are NULL, it implies that that child doesn't exist. Note that
 * this structure has no way to refer to the parent, therefore it's impossible to traverse up the
 * tree without having first traversed down it.
 */

#define LEVEL_SPACES 4

/**
 * This function creates a binary tree of a given size given a serialized array of data. All nodes
 * are allocated on the heap via `malloc()` and store the input data in their data member. Note that
 * this parameter is serialized in a top-down, left-to-right order. This means it follows the
 * left-hand-side of the tree to the bottom and then backs it's way back up.
 *
 * So for a tree like:
 *           A
 *        B     C
 *      D   E F   G
 * The data variable is ordered as [A B D E C F G].
 * 
 * This function uses recursion for generating the tree in this top-down, left-right order. This
 * tree, and therefore the input data set, is assumed to be full and balanced. Therefore, creating
 * a tree with n levels will have 2^n - 1 nodes.  If the `data` input is not this size, then this 
 * function's behavior is undefined. 
 *
 * If allocating memory fails during TreeCreate() then it will return NULL. Additionally, if the
 * creation of either of the subtrees fails within TreeCreate(), it should return NULL. This means
 * that if TreeCreate() returns a non-NULL value, that means that a perfect tree has been created,
 * so all nodes that should exist have been successfully malloc()'d onto the heap.
 *
 * This function does NOT completely clean up after itself if malloc() fails at any point. So, 
 * a malloc() failure in TreeCreate() is likely to leave memory in the heap unaccessible.
 *
 * @param level How many vertical levels the tree will have.
 * @param data A serialized array of the character data that will be stored in all nodes. This array
 *              should be of length `2^level - 1`.
 * @return A pointer to the root node of the created tree, or NULL if malloc fails for any node.
 */
Node *TreeCreate(int level, const char *data)
{
    int exp = 1 << (level - 1); //obtain 2^(n-1) using bit shifts.

    if (level == 0) {
        return NULL;
    } else {
        Node *root = malloc(sizeof (Node)); //allocate current node.
        if (root) { //check if valid memory.
            root->data = data[0]; //store first character of dataString.
            root->rightChild = TreeCreate(level - 1, data + exp); //data + 2^(n-1).
            root->leftChild = TreeCreate(level - 1, data + 1); //data + 1.
            return root;
        } else { //if allocation fails, 
            return NULL; //return NULL.
        }
    }



}

/**
 * This function returns the left child of the node passed into the function. The function should return
 * NULL if the node passed in has no left child. You will also need to be careful not to dereference the
 * NULL pointer if called with an empty node.
 *
 * @param root Pointer to root node
 * @return The pointer to the left child of the node, NULL if there is no child.
 */
Node *GetLeftChild(Node *root)
{
    if (root) { //make sure root isn't NULL itself!
        if (root->leftChild == NULL) { //if NULL,
            return NULL; //return NULL.
        } else {
            return root->leftChild; //return leftChild pointer.
        }
    } else {
        return NULL;
    }



}

/**
 * This function returns the right child of the node passed into the function. The function should return
 * NULL if the node passed in has no right child. You will also need to be careful not to dereference the
 * NULL pointer if called with an empty node.
 *
 * @param root Pointer to root node
 * @return The pointer to the right child of the node, NULL if there is no child.
 */
Node *GetRightChild(Node *root)
{
    if (root) { //make sure root isn't NULL itself!
        if (root->rightChild == NULL) { //if NULL,
            return NULL; //return NULL.
        } else {
            return root->rightChild; //return rightChild pointer.
        }
    } else {
        return NULL;
    }

}

/**
 * This function prints the tree rotated 90 degrees counter clockwise using recursive calls. To print the
 * full tree, it should be called as PrintTree(root, 0).
 *
 * If the tree is: 
 *         A
 *       /   \
 *      B     C
 *     / \   / \
 *    D   E F   G  
 * Then calling PrintTree(root, 0) will print:
 *       G
 *    C
 *       F
 * A
 *       E
 *    B
 *       D
 *
 * The function should be robust to being called on an empty tree (a NULL pointer), and should be 
 * implemented recursively. If the data is NULL or non-printable, then the print should be blank.
 *  See the lab write up for details on the
 * print tree algorithm.
 *
 * @param node The node to print the tree from
 * @param space The number of spaces to print before printing the node data 
 * @return none
 */

void TreePrint(Node *node, int space)
{
    int count = space;
    if (node) {
        space += LEVEL_SPACES; //increment n_spaces.
        TreePrint(GetRightChild(node), space); //print right child.

        printf("\n"); //print a newline.
        for (; count > 0; count--) { //print n_spaces.
            printf(" ");
        }
        printf("%c", node->data); //print current node's char.

        TreePrint(GetLeftChild(node), space); //print left child.
        return; //EXIT.



    } else {
        return; //don't print anything, EXIT.
    }




}