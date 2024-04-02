#pragma once


#include "Beer.h"
#include "Wine.h"
#include "Whiskey.h"



typedef struct
{
    Beer* beerArray;
    int beersCount;
    //Whiskey* whiskeyArray;
  //  Wine* wineArray;
    int winesCount;

}Inventory;

void initInventory(Inventory* pInventory);
void setInventoryDefaults(Inventory* pInventory);
int addBeer(Inventory* pInventory);
int addWine(Inventory* pInventory);

