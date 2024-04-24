#pragma once


#include "Beer.h"
#include "Wine.h"
#include "Whiskey.h"

#define START_NUM_UNITS_OF_BEER 75
#define START_NUM_UNITS_OF_WINE 50
#define START_NUM_UNITS_OF_WHISKEY 30


typedef struct
{
    Beer*  beerArray;
    int    beersCount;
    Whiskey* whiskeyArray;
    int      whiskeysCount;
    Wine* wineArray;
    int   winesCount;

}Inventory;

void initInventory(Inventory* pInventory);
void setInventoryDefaults(Inventory* pInventory);
int  addBeer(Inventory* pInventory);
int  addWine(Inventory* pInventory);

int addBeveragesToInventory(Inventory* pInventory);

int  addWhiskey(Inventory* pInventory);
//void initInventoryFromFile(Inventory* pInventory, const char* filename);
void printInventory(const Inventory* pInventory);
int isSerialNumberUnique(void* arr, int count, int serialNumber, int elementSize, int (*getSerialNumber)(void*));
int getUniqueSerialNumber(void* arr, int count, int minSerial, int maxSerial, int elementSize, int (*getSerialNumber)(void*));
int getValidSerialNumber(int minSerial, int maxSerial);
int getBeerSerialNumber(void* pBeer);
int refillItemBySerial(Inventory* pInventory);
void printRefillDetails(void* item, int itemsAdded, int elementSize, int (*getSerialNumber)(void*));
void refillStock(void* item, int startAmount, int* itemsAdded);
//int refillStock(Inventory* pInventory);
int handleRefillInventory(Inventory* pInventory);
int getWhiskeySerialNumber(void* pWhiskey);
int getWineSerialNumber(void* pWine);
void freeInventory(Inventory* inventory);

