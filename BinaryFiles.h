#pragma once

#include <stdio.h>
#include "Inventory.h"

int saveInventoryToBinaryFile(const Inventory* pInventory, const char* filename);
int writeBeerArrToBFile(FILE* pFile, const Beer* pBeerArr, const int count);
int writeBeerToBFile(FILE* pFile, const Beer* pBeer);
int writeWhiskeyToBFile(FILE* pFile, const Whiskey* pWhiskey);
int writeWhiskeyArrToBFile(FILE* pFile, const Whiskey* pWhiskeyArr, const int count);
int writeWineToBFile(FILE* pFile, const Wine* pWine);
int writeWineArrToBFile(FILE* pFile, const Wine* pWineArr, const int count);
void initInventoryFromBinaryFile(Inventory* pInventory, const char* filename);
int readBeerFromBFile(FILE* pFile, Beer* pBeer);
int readBeerArrFromBFile(FILE* pFile, Beer* pBeerArr, const int count);
int readWhiskeyFromBFile(FILE* pFile, Whiskey* pWhiskey);
int readWhiskeyArrFromBFile(FILE* pFile, Whiskey* pWhiskeyArr, const int count);
int readWineFromBFile(FILE* pFile, Wine* pWine);
int readWineArrFromBFile(FILE* pFile, Wine* pWineArr, int count);



