#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Inventory.h"
#include "Wine.h"


//void initInventory(Inventory* pInventory)
//{
//    setInventoryDefaults(pInventory);
//    pInventory->beersCount = 0;
//    pInventory->winesCount = 0;
//}

void setDefaults(Inventory* pInventory)
{
    pInventory->beerArray = NULL;
   // pInventory->whiskeyArray = NULL;
    //pInventory->wineArray = NULL;
}



int addBeer(Inventory* pInventory) {
    // Resize the beer array to accommodate the new beer
    Beer* tempArray = (Beer*)realloc(pInventory->beerArray, (pInventory->beersCount + 1) * sizeof(Beer));
    if (!tempArray) {
        // Memory allocation failed, return 0
        return 0;
    }

    // Memory reallocation successful, update beer array
    pInventory->beerArray = tempArray;

    // Initialize the newly added beer
    initBeer(&pInventory->beerArray[pInventory->beersCount], pInventory->beerArray, pInventory->beersCount);

    // Increment the beer count
    pInventory->beersCount++;

    return 1;
}


//int addBeer(Inventory* pInventory)
//{
//    pInventory->beerArray = (Beer*)realloc(pInventory->beerArray, (pInventory->beersCount + 1) * sizeof(Beer));
//    if (!pInventory->beerArray) return 0;
//
//    initBeer(&pInventory->beerArray[pInventory->winesCount], pInventory->beerArray, pInventory->beersCount);
//    pInventory->beersCount++;
//    return 1;
//}





//int addWine(Inventory* pInventory)
//{
//    pInventory->wineArray = (Wine*)realloc(pInventory->wineArray, (pInventory->winesCount + 1) * sizeof(Wine));
//    if (!pInventory->wineArray) return 0;
//    initWine(&pInventory->wineArray[pInventory->winesCount], pInventory->wineArray, pInventory->winesCount);
//    pInventory->winesCount++;
//    return 1;
//}