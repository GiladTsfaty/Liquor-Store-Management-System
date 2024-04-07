#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Inventory.h"
#include "Customer.h"
#include "Date.h"
#include "Shop.h"




void initShop(Shop* pShop)
{
    printf("---------Init Shop-----------\n");

    pShop->inventory = NULL;
    pShop->salesDepartment = NULL;

    pShop->netBudget = 3500;

}

void freeShop(Shop* pShop)
{

    freeSales(pShop->salesDepartment);
    freeInventory(pShop->inventory);

}
