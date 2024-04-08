//#include <stdlib.h>
//#include <string.h>
//#include <stdio.h>
//
//#include "Inventory.h"
//#include "BinaryFiles.h"
//
//int saveInventoryToBinaryFile(const Inventory* pInventory, const char* filename)
//{
//    FILE* pFile = fopen(filename, "wb");
//    if (!pFile) return 0;
//
//    // Write beer array
//    if (fwrite(&pInventory->beersCount, sizeof(int), 1, pFile) != 1) return 0;
//    if (!writeBeerArrToBFile(pFile, pInventory->beerArray, pInventory->beersCount)) return 0;
//
//    // Write whiskey array
//    if (fwrite(&pInventory->whiskeysCount, sizeof(int), 1, pFile) != 1) return 0;
//    if (!writeWhiskeyArrToBFile(pFile, pInventory->whiskeyArray, pInventory->whiskeysCount)) return 0;
//
//    // Write wine array
//    if (fwrite(&pInventory->winesCount, sizeof(int), 1, pFile) != 1) return 0;
//    if (!writeWineArrToBFile(pFile, pInventory->wineArray, pInventory->winesCount)) return 0;
//
//    fclose(pFile);
//    return 1;
//}
//
//
//
//int writeBeerToBFile(FILE* pFile, const Beer* pBeer)
//{
//    int len = strlen(pBeer->brand) + 1;
//    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(pBeer->brand, sizeof(char), len, pFile) != len) return 0;
//    if (fwrite(&pBeer->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pBeer->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pBeer->price, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pBeer->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pBeer->bSize, sizeof(eBeerSize), 1, pFile) != 1) return 0;
//    return 1;
//}
//
//int writeBeerArrToBFile(FILE* pFile, const Beer* pBeerArr, const int count)
//{
//    for (int i = 0; i < count; i++)
//    {
//        if (!writeBeerToBFile(pFile, &pBeerArr[i])) return 0;
//    }
//    return 1;
//}
//
//
//
//int writeWhiskeyToBFile(FILE* pFile, const Whiskey* pWhiskey)
//{
//    int len = strlen(pWhiskey->brand) + 1;
//    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(pWhiskey->brand, sizeof(char), len, pFile) != len) return 0;
//    if (fwrite(&pWhiskey->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pWhiskey->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pWhiskey->price, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pWhiskey->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pWhiskey->whiskeyType, sizeof(eWhiskeyType), 1, pFile) != 1) return 0;
//    return 1;
//}
//
//int writeWhiskeyArrToBFile(FILE* pFile, const Whiskey* pWhiskeyArr, const int count)
//{
//    for (int i = 0; i < count; i++)
//    {
//        if (!writeWhiskeyToBFile(pFile, &pWhiskeyArr[i])) return 0;
//    }
//    return 1;
//}
//
//
//
//
//int writeWineToBFile(FILE* pFile, const Wine* pWine)
//{
//    int len = strlen(pWine->brand) + 1;
//    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(pWine->brand, sizeof(char), len, pFile) != len) return 0;
//    if (fwrite(&pWine->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pWine->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pWine->price, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pWine->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pWine->wType, sizeof(eWineType), 1, pFile) != 1) return 0;
//    return 1;
//}
//
//int writeWineArrToBFile(FILE* pFile, const Wine* pWineArr, const int count) {
//    for (int i = 0; i < count; i++) {
//        if (!writeWineToBFile(pFile, &pWineArr[i])) return 0;
//    }
//    return 1;
//}
//
//
//
//void initInventoryFromBinaryFile(Inventory* pInventory, const char* filename)
//{
//    FILE* pFile = fopen(filename, "rb");
//    if (!pFile) return;
//
//    // Read beer array
//    if (fread(&pInventory->beersCount, sizeof(int), 1, pFile) != 1) return;
//    pInventory->beerArray = (Beer*)malloc(pInventory->beersCount * sizeof(Beer));
//    if (!pInventory->beerArray) return;
//    if (!readBeerArrFromBFile(pFile, pInventory->beerArray, pInventory->beersCount)) return;
//
//    // Read whiskey array
//    if (fread(&pInventory->whiskeysCount, sizeof(int), 1, pFile) != 1) return;
//    pInventory->whiskeyArray = (Whiskey*)malloc(pInventory->whiskeysCount * sizeof(Whiskey));
//    if (!pInventory->whiskeyArray) return;
//    if (!readWhiskeyArrFromBFile(pFile, pInventory->whiskeyArray, pInventory->whiskeysCount)) return;
//
//    // Read wine array
//    if (fread(&pInventory->winesCount, sizeof(int), 1, pFile) != 1) return;
//    pInventory->wineArray = (Wine*)malloc(pInventory->winesCount * sizeof(Wine));
//    if (!pInventory->wineArray) return;
//    if (!readWineArrFromBFile(pFile, pInventory->wineArray, pInventory->winesCount)) return;
//
//    fclose(pFile);
//}
//
//
//
//int readBeerFromBFile(FILE* pFile, Beer* pBeer)
//{
//    int len;
//    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
//    pBeer->brand = (char*)malloc(len * sizeof(char));
//    if (!pBeer->brand) return 0;
//    if (fread(pBeer->brand, sizeof(char), len, pFile) != len) return 0;
//    if (fread(&pBeer->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pBeer->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pBeer->price, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pBeer->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pBeer->bSize, sizeof(eBeerSize), 1, pFile) != 1) return 0;
//    return 1;
//}
//
//int readBeerArrFromBFile(FILE* pFile, Beer* pBeerArr, const int count)
//{
//    for (int i = 0; i < count; i++)
//    {
//        if (!readBeerFromBFile(pFile, &pBeerArr[i])) return 0;
//    }
//    return 1;
//}
//
//
//
//int readWhiskeyFromBFile(FILE* pFile, Whiskey* pWhiskey)
//{
//    int len;
//    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
//    pWhiskey->brand = (char*)malloc(len * sizeof(char));
//    if (!pWhiskey->brand) return 0;
//    if (fread(pWhiskey->brand, sizeof(char), len, pFile) != len) return 0;
//    if (fread(&pWhiskey->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pWhiskey->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pWhiskey->price, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pWhiskey->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pWhiskey->whiskeyType, sizeof(eWhiskeyType), 1, pFile) != 1) return 0;
//    return 1;
//}
//
//int readWhiskeyArrFromBFile(FILE* pFile, Whiskey* pWhiskeyArr, const int count)
//{
//    for (int i = 0; i < count; i++)
//    {
//        if (!readWhiskeyFromBFile(pFile, &pWhiskeyArr[i])) return 0;
//    }
//    return 1;
//}
//
//
//
//int readWineFromBFile(FILE* pFile, Wine* pWine)
//{
//    int len;
//    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
//    pWine->brand = (char*)malloc(len * sizeof(char));
//    if (!pWine->brand) return 0;
//    if (fread(pWine->brand, sizeof(char), len, pFile) != len) return 0;
//    if (fread(&pWine->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pWine->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pWine->price, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pWine->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pWine->wType, sizeof(eWineType), 1, pFile) != 1) return 0;
//    return 1;
//}
//
//int readWineArrFromBFile(FILE* pFile, Wine* pWineArr, const int count)
//{
//    for (int i = 0; i < count; i++)
//    {
//        if (!readWineFromBFile(pFile, &pWineArr[i])) return 0;
//    }
//    return 1;
//}
