


#include "UNIXBOARD.h"
#include <stdint.h>
// Define how big the player's inventory is.
#define INVENTORY_SIZE 4

typedef struct {
    uint8_t item1;
    uint8_t item2;
    uint8_t item3;
    uint8_t item4;
    uint8_t inventory_count;
} Inventory;

static Inventory player_inventory;

/**
 * Adds the specified item to the player's inventory if the inventory isn't full.
 * @param item The item number to be stored: valid values are 0-255.
 * @return SUCCESS if the item was added, STANDARD_ERRROR if the item couldn't be added.
 */
int AddToInventory(uint8_t item)
{
    switch (player_inventory.inventory_count) {
    case 0:
        player_inventory.item1 = item;
        player_inventory.inventory_count++;
        return SUCCESS;
    case 1:
        player_inventory.item2 = item;
        player_inventory.inventory_count++;
        return SUCCESS;
    case 2:
        player_inventory.item3 = item;
        player_inventory.inventory_count++;
        return SUCCESS;
    case 3:
        player_inventory.item4 = item;
        player_inventory.inventory_count++;
        return SUCCESS;
        break;
    default: //inventory_count > INVENTORY_SIZE:
        return STANDARD_ERROR;

    }
    //else:
    return STANDARD_ERROR;
}

/**
 * Check if the given item exists in the player's inventory.
 * @param item The number of the item to be searched for: valid values are 0-255.
 * @return SUCCESS if it was found or STANDARD_ERROR if it wasn't.
 */
int FindInInventory(uint8_t item)
{
    if (player_inventory.item1 == item) {
        return SUCCESS;
    }
    if (player_inventory.item2 == item) {
        return SUCCESS;
    }
    if (player_inventory.item3 == item) {
        return SUCCESS;
    }
    if (player_inventory.item4 == item) {
        return SUCCESS;
    }
    //else:
    return STANDARD_ERROR;

}
