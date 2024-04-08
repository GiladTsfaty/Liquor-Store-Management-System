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
void freeShop(Shop* pShop);

//saveShopToTextFile(Shop* pShop);
//saveShopToBianryFile(Shop* pShop);

