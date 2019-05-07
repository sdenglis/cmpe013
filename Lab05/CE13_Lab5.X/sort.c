/*****************
 *Samuel English *
 *CMPE13/L       *
 *Lab 05         *
 *5/04/2019      *
 *****************/

// Heap size 1024 required!

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


// **** Declare any function prototypes here ***
ListItem *CreateUnsortedList(void); //this function has been written for you
ListItem *SelectionSort(ListItem* list);
ListItem *InsertionSort(ListItem* list);

/* Students should not need to modify main! */
int main(void)
{
    BOARD_Init();

    printf("\n\nWelcome to sdenglis's sort.c, compiled on %s %s.\n", __DATE__, __TIME__);

    ListItem* listToSort;

    //Do a timing test 
    printf("\nStarting stopwatch for selection sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    SelectionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);


    printf("\nStarting stopwatch for insertion sort...\n");
    listToSort = CreateUnsortedList();
    __asm("nop"); //put a breakpoint on this line
    InsertionSort(listToSort);
    __asm("nop"); //put a breakpoint on this line, and record the stopwatch time
    LinkedListPrint(listToSort);

    while (1);
    return 0;
}

/**
 * SelectionSort() performs a selection sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *SelectionSort(ListItem* list)
{
    int i, j; // Create counter variables.
    // Turn list into pointer of first element in LinkedList.
    list = LinkedListGetFirst(list);

    // Create two Item variables to compare iterative data values.
    ListItem * firstItem->data = list->data;
    firstItem->nextItem = list->nextItem;

    ListItem * secondItem->data = list->data;
    secondItem->nextItem = list->nextItem;

    int length = LinkedListSize(list); // Get list size, set equal to length variable.

    for (i = 0; i < (length - 2); i++) {
        for (j = i + 1; j < (length - 1); j++) {

            if (strcmp(firstItem->data, secondItem->data) < 0) { // If first < second, execute block.
                LinkedListSwapData(firstItem, secondItem); // swap first and second.
                secondItem = secondItem->nextItem; // Increment secondItem++
            }
        }
        firstItem = firstItem->nextItem; // Increment firstItem++
    }

    return LinkedListGetFirst(list);

}

/**
 * InsertionSort() performs an insertion sort on a passed to it.  The list is sorted alphabetically,
 * as determined by string.h's strcmp().  
 *
 * @param list Any element in a linked list to sort.  
 * @return a pointer to the head of the sorted list.
 * 
 * SelectionSort() assumes that no list items have a NULL data member.  It also assumes that 'list'
 * is a valid, non-NULL pointer to a linked list.
 * 
 * This function does not print.
 */
ListItem *InsertionSort(ListItem* list)
{
    int i, j;
    int length = LinkedListSize(list); // Get list size, set equal to length variable.

    ListItem * firstSortedItem = LinkedListGetLast(list);

    while (firstSortedItem->previousItem != NULL) {
        ListItem * lastUnsortedItem = firstSortedItem->previousItem;
        if (strcmp(lastUnsortedItem, firstSortedItem) < 0) {
            // Only set data? Or all attributes?
            LinkedListSwapData(firstSortedItem, lastUnsortedItem);
        } else {
            F
            // What does this mean?
            insertAfter = firstSortedItem;
            while (insertAfter != tail of list || insertHere > lastUnsortedItem) {
                insertAfter = insertAfter next item;
                insert lastUnsortedItem after insertAfter;
            }
        }
    }


}

/* CreateUnsortedList() uses the functions in the LinkedList library to
 * generate an unsorted list.  
 * 
 * Students should not modify this function!
 * If an error occurs in this function, there is almost certainly 
 * a bug in your implementation of LinkedList.h.
 *   
 * @return A pointer to a ListItem which is the head of a new unsorted list. 
 */
ListItem *CreateUnsortedList(void)
/// <editor-fold defaultstate="collapsed" desc="CreateUnsortedList definition">
{
    char* wordList[] = {"decide", "toothpaste", "lowly", "robin", "reign", "crowd", "pies", "reduce", "tendency", "surround", "finger", "rake", "alleged", "hug", "nest", "punishment", "eggnog", "side", "beef", "exuberant", "sort", "scream", "zip", "hair", "ragged", "damage", "thought", "jump", "frequent", "substance", "head", "step", "faithful", "sidewalk", "pig", "raspy", "juggle", "shut", "maddening", "rock", "telephone", "selective"};
    //  char* wordList[] = {"D", "A", "C", "E", "B", NULL};

    int i = 0;
    ListItem* head = LinkedListNew(wordList[i]);
    ListItem* tail = head;
    for (i = 1; wordList[i] != NULL; i++) {
        tail = LinkedListCreateAfter(tail, wordList[i]);
    }
    return head;
}
// </editor-fold>
