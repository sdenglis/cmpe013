/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 05         *
 *5/04/2019      *
 *****************/

// **** Include libraries here ****
// Standard libraries
#include <stdio.h>
#include <string.h>

//CMPE13 Support Library
#include "BOARD.h"

// Microchip libraries
#include <xc.h>

// User libraries
#include "LinkedList.h"

int main(void)
{
    BOARD_Init();

    printf("\n\n\n###### Beginning sdenglis's LinkedList.c test harness: ######\n\n\n");

    float percentageCorrect = 0;
    //char* wordList[] = {"decide", "toothpaste", "lowly", "robin", "reign", NULL};
    char data[] = {"floss"};
    char nextData[] = {"toothpaste"};
    char finalData[] = {"water"};
    char nullData[] = {NULL};


    /******************************************************************************
     * ListItem * LinkedListNew(char *data)
     *****************************************************************************/
    // ListItem * LinkedListNew(char *data);
    ListItem *pointer = LinkedListNew(data);
    if (pointer) { // If LinkedListNew returns a valid pointer...
        percentageCorrect++;
    }

    ListItem *nullPointer = LinkedListNew(nullData);
    if (nullPointer) { // If LinkedListNew returns a valid pointer...
        percentageCorrect++;
    }

    printf("LinkedListNew(\"floss\"): ");
    LinkedListPrint(pointer); // Try to print "floss."
    printf("\n"); // Spoilers, it prints correctly into stdout.



    /******************************************************************************
     * ListItem * LinkedListCreateAfter(ListItem *item, char *data)
     *****************************************************************************/
    // ListItem * LinkedListCreateAfter(ListItem *item, char *data);
    ListItem *nextPointer = LinkedListCreateAfter(pointer, nextData);
    if (nextPointer) { // If LinkedListCreateAfter returns a valid pointer...
        percentageCorrect++;
    }

    printf("LinkedListCreateAfter(&floss, \"toothpaste\"): ");
    LinkedListPrint(pointer);
    printf("\n");

    ListItem *finalPointer = LinkedListCreateAfter(pointer, finalData);
    // Should print from data -> nextData.
    printf("LinkedListCreateAfter(&floss, \"water\"): ");
    LinkedListPrint(finalPointer);
    printf("\n");

    if (nextPointer->previousItem == finalPointer && finalPointer->previousItem == pointer) {
        percentageCorrect++;
    }

    // Should print: "floss, water, toothpaste"
    // With "pointer, finalPointer, & nextPointer" respectively.



    /******************************************************************************
     * char *LinkedListRemove(ListItem * item)
     *****************************************************************************/
    // char *LinkedListRemove(ListItem * item);
    LinkedListRemove(finalPointer);
    if (pointer->nextItem == nextPointer) { // &floss->nextItem should point to &toothpaste now.
        percentageCorrect++;
    }
    // We should no longer have the last item, "water."
    printf("LinkedListRemove(\"water\"): ");
    LinkedListPrint(pointer);
    printf("\n");

    LinkedListRemove(nextPointer);
    if (pointer->nextItem == NULL && pointer->previousItem == NULL) {
        // &floss->nextItem & previousItem should point to NULL.
        percentageCorrect++;
    }

    // We should no longer have the last item, "toothpaste."
    printf("LinkedListRemove(\"toothpaste\"): ");
    LinkedListPrint(pointer);
    printf("\n");

    // Should print: "floss"
    // With "pointer" respectively.



    /******************************************************************************
     * int LinkedListSize(ListItem * list)
     *****************************************************************************/
    // int LinkedListSize(ListItem * list);
    int listSize = LinkedListSize(nextPointer);
    printf("LinkedListSize(): %d\n", listSize);
    if (listSize == 1) { // "floss" only contains 1 item.
        percentageCorrect++;
    }
    // Should be only 1.

    finalPointer = LinkedListCreateAfter(pointer, finalData);
    printf("LinkedListCreateAfter(&floss, \"water\"): ");
    // Update list to "floss, water."
    LinkedListPrint(pointer);
    printf("\n");

    listSize = LinkedListSize(pointer);
    printf("LinkedListSize(): %d\n", listSize);
    if (listSize == 2) { // "floss, water"
        percentageCorrect++;
    }
    // Should be only 2.




    /******************************************************************************
     * ListItem * LinkedListGetFirst(ListItem * list)
     *****************************************************************************/
    // ListItem * LinkedListGetFirst(ListItem * list);
    ListItem *firstItem = LinkedListGetFirst(finalPointer);

    nextPointer = LinkedListCreateAfter(pointer, nextData);
    printf("LinkedListCreateAfter(&floss, \"toothpaste\"): ");
    LinkedListPrint(pointer);
    printf("\n");

    //printf("%p\n", pointer); // These two should be the same address.
    //printf("%p\n", firstItem);
    if (pointer == firstItem) {
        percentageCorrect++;
    }

    printf("LinkedListGetFirst(): %s\n", firstItem->data);

    ListItem *errorFirst = LinkedListGetFirst(NULL);
    if (errorFirst == NULL) {
        percentageCorrect++; // LinkedListGetFirst() should return NULL for invalid list.
    }


    /******************************************************************************
     * ListItem * LinkedListGetLast(ListItem * list)
     *****************************************************************************/
    // ListItem * LinkedListGetLast(ListItem * list);
    ListItem *lastItem = LinkedListGetLast(pointer);

    //printf("%p\n", finalPointer); // These two should be the same address.
    //printf("%p\n", lastItem);
    if (finalPointer == lastItem) {
        percentageCorrect++;
    }

    printf("LinkedListGetLast(): %s\n", lastItem->data);

    ListItem *errorLast = LinkedListGetFirst(NULL);
    if (errorLast == NULL) {
        percentageCorrect++; // LinkedListGetLast() should return NULL for invalid list.
    }


    /******************************************************************************
     * int LinkedListSwapData(ListItem *firstItem, ListItem * secondItem)
     *****************************************************************************/
    // int LinkedListSwapData(ListItem *firstItem, ListItem * secondItem);
    int returnValue = LinkedListSwapData(pointer, nextPointer); // Swap floss & toothpaste data values.
    printf("LinkedListSwapData(\"floss,\" \"toothpaste\"): ");
    LinkedListPrint(pointer); // Print out the values.

    if (returnValue == SUCCESS) {
        percentageCorrect++; // LinkedListSwapData() should return SUCCESS!
    }

    // Should print "toothpaste, floss, water."

    int returnNULLValue = LinkedListSwapData(pointer, NULL);
    if (returnNULLValue == STANDARD_ERROR) {
        percentageCorrect++; // LinkedListSwapData() should return NULL for invalid list.
    }

    printf("\n");

    LinkedListSwapData(finalPointer, nextPointer); // Swap floss & water data values.
    printf("LinkedListSwapData(\"floss,\" \"water\"): ");
    int printValue = LinkedListPrint(pointer); // Print out the values.

    // Should be "toothpaste, water, floss."
    printf("\n\n");



    /******************************************************************************
     * int LinkedListPrint(ListItem * list)
     *****************************************************************************/
    // int LinkedListPrint(ListItem * list);
    // At this point, the actual printing functionality of LinkedListPrint() has been demonstrated.

    // int printValue DEFINED above to prevent duplicate LinkedListPrint() calls.
    if (printValue == SUCCESS) {
        percentageCorrect++; // LinkedListSwapData() should return SUCCESS.
    }

    int printNULLValue = LinkedListPrint(NULL);
    if (printNULLValue == STANDARD_ERROR) {
        percentageCorrect++; // LinkedListSwapData() should return NULL for invalid list.
    }



    /******************************************************************************
     * LinkedListTest - OUTPUT
     *****************************************************************************/

    printf("\nPass Rate: %.3f%%\n", ((percentageCorrect / 16.0) * 100));


    while (1);
    return 0;
}