#pragma once

#include "Inventory.h"
#include "Sales.h"

typedef struct
{
    Inventory* inventory;
    Sales* salesDepartment;
    int netBudget;

}Shop;

void initShop(Shop* pShop);


