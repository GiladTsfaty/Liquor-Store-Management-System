#pragma once

#include <stdio.h>
#include "Inventory.h"
#include "Filefunctions.h"
#include "Sales.h"

typedef unsigned char BYTE;



///B inventory files ///
int writeBeerArrToBFile(FILE* pFile, const Beer* pBeerArr, const int count);
int writeBeerToBFile(FILE* pFile, const Beer* pBeer);
int writeWhiskeyToBFile(FILE* pFile, const Whiskey* pWhiskey);
int writeWhiskeyArrToBFile(FILE* pFile, const Whiskey* pWhiskeyArr, const int count);
int writeWineToBFile(FILE* pFile, const Wine* pWine);
int writeWineArrToBFile(FILE* pFile, const Wine* pWineArr, const int count);
//void initInventoryFromBinaryFile(Inventory* pInventory, const char* filename);
int readBeerFromBFile(FILE* pFile, Beer* pBeer);
int readBeerArrFromBFile(FILE* pFile, Beer* pBeerArr, const int count);
int readWhiskeyFromBFile(FILE* pFile, Whiskey* pWhiskey);
int readWhiskeyArrFromBFile(FILE* pFile, Whiskey* pWhiskeyArr, const int count);
int readWineFromBFile(FILE* pFile, Wine* pWine);
int readWineArrFromBFile(FILE* pFile, Wine* pWineArr, int count);





int initInventoryFromBinaryFile(Inventory* pInventory, const char* filename);
int saveInventoryToBinaryFile(const Inventory* pInventory, const char* filename);


///B customer files ///



int writeCustomerListToBFile(const Sales* pSales, const char* fileName);
int readCustomerListFromBFile(Sales* pSales, const char* fileName);



// Functions for loading and saving reservations to/from binary files
 
//int loadReservationsFromBinaryFile(Sales* pSales, const char* filename);
//int saveReservationsToBinaryFile(const Sales* pSales, const char* filename);



void			saveReservationToBinaryFile(const Reservation* reservation, FILE* file);
Reservation*	loadReservationFromBinaryFile(Sales* pSales, FILE* file);

int				loadReservationsArrayFromBinaryFile(Sales* pSales, const char* filename);// change to FILE*
int				saveReservationsArrayToBinaryFile(const Sales* pSales, const char* filename);

/// Compress///

int	 writeStringToCompressFile(const char* str, FILE* fp, const char* msg);

int savePurchasedItemToCompressedFile(const PurchasedItem* pItem, FILE* fp);
int loadPurchasedItemFromCompressedFile(PurchasedItem* pItem, FILE* fp);


