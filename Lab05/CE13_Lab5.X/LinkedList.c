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

#define SUCCESS 1
#define STANDARD_ERROR 0

/**
 * This function starts a new linked list. Given an allocated pointer to data it will return a
 * pointer for a malloc()ed ListItem struct. If malloc() fails for any reason, then this function
 * returns NULL otherwise it should return a pointer to this new list item. data can be NULL.
 *
 * @param data The data to be stored in the first ListItem in this new list. Can be any valid 
 *             pointer value.
 * @return A pointer to the malloc()'d ListItem. May be NULL if an error occurred.
 */
ListItem * LinkedListNew(char *data)
{
    // Declare new ListItem struct named *item: allocate memory sizeof(ListItem).
    ListItem *newItem = malloc(sizeof (ListItem));

    if (newItem) { // Only executes if the malloc() executed without error.
        newItem->data = data; // Set data sub-member of item to char *data input.
        newItem->nextItem = NULL; // When initialized, single-item list should point head and tail to NULL.
        newItem->previousItem = NULL;
        return newItem; // Return the pointer to newly-created ListItem.
    } else {
        return NULL; // If malloc() fails, force function to return NULL.
    }
}

/**
 * This function allocates a new ListItem containing data and inserts it into the list directly
 * after item. It rearranges the pointers of other elements in the list to make this happen. If
 * passed a NULL item, CreateAfter() should still create a new ListItem, just with no previousItem.
 * It returns NULL if it can't malloc() a new ListItem, otherwise it returns a pointer to the new
 * item. The data parameter is also allowed to be NULL.
 *
 * @param item The ListItem that will be before the newly-created ListItem.
 * @param data The data the new ListItem will point to.
 * @return A pointer to the newly-malloc()'d ListItem.
 */
ListItem * LinkedListCreateAfter(ListItem *item, char *data)
{
    ListItem *newItem = LinkedListNew(data); // Creates a new list element with the char *data provided.

    if (newItem) { // Provided newItem is valid.
        if (item) { // Check if provided *item is NULL.
            if (item->nextItem) { // Check if item->nextItem points to another list element.

                // OTHER CASE, where *item already has a nextItem element.
                newItem->previousItem = item;
                newItem->nextItem = item->nextItem;
                // Set the previous nextItem for *item to updated values.
                item->nextItem->previousItem = newItem;
                item->nextItem = newItem;

            } else { // Else, item->nextItem is NULL, meaning there is no nextItem.

                // STANDARD CASE, where no list element exists after *item.
                newItem->previousItem = item;
                newItem->nextItem = NULL;
                item->nextItem = newItem;

            }
        } else { // If NULL *item, act with no previousItem.
            newItem->previousItem = NULL;

        }
        return newItem;

    } else { // Provided newItem is NULL.
        return NULL; // Return NULL if the malloc() in LinkedListNew() failed.
    }
}

/**
 * This function will remove a list item from the linked list and free() the memory that the
 * ListItem struct was using. It doesn't, however, free() the data pointer and instead returns it
 * so that the calling code can manage it.  If passed a pointer to NULL, LinkedListRemove() should
 * return NULL to signal an error.
 *
 * @param item The ListItem to remove from the list.
 * @return The data pointer from the removed item. May be NULL.
 */
char *LinkedListRemove(ListItem * item)
{
    if (item) {
        // Stitch gap in attributes of previous and next items.
        if (item->previousItem) {
            item->previousItem->nextItem = item->nextItem;
        }
        if (item->nextItem) {
            item->nextItem->previousItem = item->previousItem;
        }

        // Free up previously allocated space for ListItem element.
        free(item);
        return item->data; // Return data pointer from removed item.

    } else { // Signal ERROR if passed NULL value.
        return NULL;
    }

}

/**
 * This function returns the total size of the linked list. This means that even if it is passed a
 * ListItem that is not at the head of the list, it should still return the total number of
 * ListItems in the list. A NULL argument will result in 0 being returned.
 *
 * @param list An item in the list to be sized.
 * @return The number of ListItems in the list (0 if `list` was NULL).
 */
int LinkedListSize(ListItem * list)
{
    int ListItemCounter = 1;
    // Create a ListItem variable to store FirstListItem into.
    ListItem *first = LinkedListGetFirst(list);

    if (first) {
        while (first->nextItem != NULL) {
            first = first->nextItem;
            ListItemCounter++;
        }
        return ListItemCounter;
    } else {
        return 0; // If given list item is NULL, return 0.
    }


}

/**
 * This function returns the head of a list given some element in the list. If it is passed NULL,
 * it will just return NULL. If given the head of the list it will just return the pointer to the
 * head anyways for consistency.
 *
 * @param list An element in a list.
 * @return A pointer to the first element in the list. Or NULL if provided an invalid list.
 */
ListItem * LinkedListGetFirst(ListItem * list)
{
    if (list) {
        while (list->previousItem != NULL) {
            list = list->previousItem;
        }
        return list;
    } else {
        return NULL; // If given list item is NULL, return NULL.
    }

}

/**
 * This function operates identically to LinkedListGetFirst(), but returns
 * the tail of a linked list.
 * 
 * @param list An element in a list.
 * @return A pointer to the last element in the list. Or NULL if provided an invalid list.
 */
ListItem * LinkedListGetLast(ListItem * list)
{
    if (list) {
        while (list->nextItem != NULL) {
            list = list->nextItem;
        }
        return list;
    } else {
        return NULL; // If given list item is NULL, return NULL.
    }

}

/**
 * LinkedListSwapData() switches the data pointers of the two provided ListItems. This is most
 * useful when trying to reorder ListItems but when you want to preserve their location. This
 * function should return STANDARD_ERROR if either arguments are NULL, otherwise it should return
 * SUCCESS. If one or both of the data pointers are NULL in the given ListItems, it still does
 * perform the swap and returns SUCCESS.
 *
 * @param firstItem One of the items whose data will be swapped.
 * @param secondItem Another item whose data will be swapped.
 * @return SUCCESS if the swap worked or STANDARD_ERROR if it failed.
 */
int LinkedListSwapData(ListItem *firstItem, ListItem * secondItem)
{
    // Create a temporary 
    ListItem *tempItem = LinkedListNew(NULL);

    if (firstItem && secondItem) {
        tempItem->data = firstItem->data;
        firstItem->data = secondItem->data;
        secondItem->data = tempItem->data;

        // Free up the allocated space for the temporary ListItem.
        LinkedListRemove(tempItem);
        return SUCCESS;

    } else {
        return STANDARD_ERROR; // Return ERROR if either of the two inputs are NULL.

    }
}

/**
 * LinkedListPrint() prints out the complete list to stdout. This function prints out the given
 * list, starting at the head if the provided pointer is not the head of the list, like "[STRING1,
 * STRING2, ... ]" If LinkedListPrint() is called with a NULL list it does nothing, returning
 * STANDARD_ERROR. If passed a valid pointer, prints the list and returns SUCCESS.
 *
 * @param list Any element in the list to print.
 * @return SUCCESS or STANDARD_ERROR if passed NULL pointers.
 */
int LinkedListPrint(ListItem * list)
{
    ListItem *first = LinkedListGetFirst(list);
    int ListSize, i;

    if (first) {
        ListSize = LinkedListSize(first);
        for (i = 0; i < (ListSize - 1); i++) {
            printf("%s, ", first->data); // Print data of current ListItem.
            first = first->nextItem; // Increment ListItem to the next data value holder.
        }
        printf("%s", first->data); // Print data of LAST ListItem with formatting.

        return SUCCESS;

    } else {
        return STANDARD_ERROR; // Return ERROR if NULL list provided.
    }


}