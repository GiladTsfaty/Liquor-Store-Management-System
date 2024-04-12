#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Inventory.h"
#include "Wine.h"
#include "Beer.h"
#include "Filefunctions.h"



void setInventoryDefaults(Inventory* pInventory)
{
    pInventory->beerArray = NULL;
    pInventory->whiskeyArray = NULL;
    pInventory->wineArray = NULL;
}

void initInventory(Inventory* pInventory)
{
    setInventoryDefaults(pInventory);
    pInventory->beersCount = 0;
    pInventory->winesCount = 0;
    pInventory->whiskeysCount = 0;
}

int addBeer(Inventory* pInventory)
{
    pInventory->beerArray = (Beer*)realloc(pInventory->beerArray, (size_t)(pInventory->beersCount + 1) * sizeof(Beer));//(size_t)
    if (!pInventory->beerArray)
        return 0;
    initBeer(&pInventory->beerArray[pInventory->beersCount], pInventory->beerArray, pInventory->beersCount);
    pInventory->beersCount++;
    return 1;
}

int addWine(Inventory* pInventory)
{
    pInventory->wineArray = (Wine*)realloc(pInventory->wineArray, (size_t)(pInventory->winesCount + 1) * sizeof(Wine));//(size_t)
    if (!pInventory->wineArray)
        return 0;
    initWine(&pInventory->wineArray[pInventory->winesCount], pInventory->wineArray, pInventory->winesCount);
    pInventory->winesCount++;
    return 1;
}

int addWhiskey(Inventory* pInventory)
{
    pInventory->whiskeyArray = (Whiskey*)realloc(pInventory->whiskeyArray, (size_t)(pInventory->whiskeysCount + 1) * sizeof(Whiskey));//(size_t)
    if (!pInventory->whiskeyArray)
        return 0;
    initWhiskey(&pInventory->whiskeyArray[pInventory->whiskeysCount], pInventory->whiskeyArray, pInventory->whiskeysCount);
    pInventory->whiskeysCount++;
    return 1;
}

//int addBeveragesToInventory(Inventory* pInventory)
//{
//    int choice;
//    printf("Enter the type of beverage to add (0 for beer, 1 for wine, 2 for whiskey): ");
//    scanf("%d", &choice);
//
//    if (choice == 0)
//        addBeer(pInventory);
//    else if (choice == 1)
//        addWine(pInventory);
//    else if (choice == 2)
//        addWhiskey(pInventory);
//    else
//        printf("Invalid choice.\n");
//
//}

int addBeveragesToInventory(Inventory* pInventory)
{
    int choice;
    while (1) {
        printf("Enter the type of beverage to add (0 for beer, 1 for wine, 2 for whiskey): ");
        scanf("%d", &choice);

        if (choice == 0) {
            if (!addBeer(pInventory))
                return 0;
            return 1; // Return success
        }
        else if (choice == 1) {
            if (!addWine(pInventory))
                return 0;
            return 1; // Return success
        }
        else if (choice == 2) {
            if (!addWhiskey(pInventory))
                return 0;
            return 1; // Return success
        }
        else {
            printf("Invalid choice.\n");
        }
    }
}


void initInventoryFromFile(Inventory* pInventory, const char* filename) {
    pInventory->beerArray = NULL;
    pInventory->beersCount = 0;
    pInventory->whiskeyArray = NULL;
    pInventory->whiskeysCount = 0;
    pInventory->wineArray = NULL;
    pInventory->winesCount = 0;


    readInventoryFromFile(pInventory, filename);
    printf("---Init Inventory From File---");
}



// shit one just to check
void printInventory(const Inventory* pInventory) {
    printf("Inventory:\n");

    // Print Beers
    printf("\nBeers (%d):\n", pInventory->beersCount);
    for (int i = 0; i < pInventory->beersCount; i++) 
    {
        printf("Brand: %s, Serial: %d, Available: %d, Price: %d, Sold:%d , Size: % s \n",
               pInventory->beerArray[i].brand,
               pInventory->beerArray[i].itemSerial,
               pInventory->beerArray[i].amountAvailable,
               pInventory->beerArray[i].price,
               pInventory->beerArray[i].numOfSolds
              ,BeerSizeStr[pInventory->beerArray[i].bSize]
        );
    }

    // Print Whiskeys
    printf("\nWhiskeys (%d):\n", pInventory->whiskeysCount);
    for (int i = 0; i < pInventory->whiskeysCount; i++) {
        printf("Brand: %s, Serial: %d, Available: %d, Price: %d, Sold: %d, Type: %s\n",
               pInventory->whiskeyArray[i].brand,
               pInventory->whiskeyArray[i].itemSerial,
               pInventory->whiskeyArray[i].amountAvailable,
               pInventory->whiskeyArray[i].price,
               pInventory->whiskeyArray[i].numOfSolds,
               WhiskeyTypeStr[pInventory->whiskeyArray[i].whiskeyType]);
    }

    // Print Wines
    printf("\nWines (%d):\n", pInventory->winesCount);
    for (int i = 0; i < pInventory->winesCount; i++) {
        printf("Brand: %s, Serial: %d, Available: %d, Price: %d, Sold: %d, Type: %s\n",
               pInventory->wineArray[i].brand,
               pInventory->wineArray[i].itemSerial,
               pInventory->wineArray[i].amountAvailable,
               pInventory->wineArray[i].price,
               pInventory->wineArray[i].numOfSolds,
               WineTypeStr[pInventory->wineArray[i].wType]);
    }
}

int isSerialNumberUnique(void* arr, int count, int serialNumber, int elementSize, int (*getSerialNumber)(void*)) {
    for (int i = 0; i < count; i++) {
        void* item = (char*)arr + i * elementSize;
        if (getSerialNumber(item) == serialNumber) {
            return 0; // Serial number already exists
        }
    }
    return 1; // Serial number is unique
}

int getValidSerialNumber(int minSerial, int maxSerial) {
    int serialNumber;
    do {
        printf("Enter the serial number (%d-%d): ", minSerial, maxSerial);
        scanf("%d", &serialNumber);
    } while (serialNumber < minSerial || serialNumber > maxSerial);
    return serialNumber;
}

int getBeerSerialNumber(void* pBeer) {
    return ((Beer*)pBeer)->itemSerial;
}

int getWhiskeySerialNumber(void* pWhiskey) {
    return ((Whiskey*)pWhiskey)->itemSerial;
}

int getWineSerialNumber(void* pWine) {
    return ((Wine*)pWine)->itemSerial;
}

int getUniqueSerialNumber(void* arr, int count, int minSerial, int maxSerial, int elementSize, int (*getSerialNumber)(void*)) {
    int serialNumber;
    do {
        serialNumber = getValidSerialNumber(minSerial, maxSerial);
    } while (!isSerialNumberUnique(arr, count, serialNumber, elementSize, getSerialNumber));
    return serialNumber;
}




void freeInventory(Inventory* inventory) {
    // Free memory for beer brands
    for (int i = 0; i < inventory->beersCount; i++)
    {
        if (inventory->beerArray[i].brand != NULL) {
            free(inventory->beerArray[i].brand);
            inventory->beerArray[i].brand = NULL;
        }
    }
    free(inventory->beerArray);
    inventory->beerArray = NULL;

    // Free memory for whiskey brands
    for (int i = 0; i < inventory->whiskeysCount; i++)
    {
        if (inventory->whiskeyArray[i].brand != NULL) {
            free(inventory->whiskeyArray[i].brand);
            inventory->whiskeyArray[i].brand = NULL;
        }
    }
    free(inventory->whiskeyArray);
    inventory->whiskeyArray = NULL;

    // Free memory for wine brands
    for (int i = 0; i < inventory->winesCount; i++)
    {
        if (inventory->wineArray[i].brand != NULL) {
            free(inventory->wineArray[i].brand);
            inventory->wineArray[i].brand = NULL;
        }
    }
    free(inventory->wineArray);
    inventory->wineArray = NULL;
}