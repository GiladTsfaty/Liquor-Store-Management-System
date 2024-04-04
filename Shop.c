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


    pShop->inventory = NULL;
    pShop->salesDepartment = NULL;

    pShop->netBudget = 3500;

}