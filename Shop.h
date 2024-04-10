#pragma once

#include "Inventory.h"
#include "Sales.h"

typedef struct
{
    Inventory* inventory;
    Sales* salesDepartment;
    int netBudget;

}Shop;

void initSystemFromFiles(Shop* pShop, Sales* pSales, Inventory* pInventory);
void initShop(Shop *pShop, Inventory *pInventory, Sales *pSales, int initialBudget);

int saveShopToTextFile(Shop* pShop, FILE* inventoryFileName, FILE* customerFileName, FILE* reservationFileName);// change to FILE*
int saveShopToBianryFile(Shop* pShop, FILE* inventoryFileName, FILE* customerFileName, FILE* reservationFileName);

void freeShop(Shop* pShop);
