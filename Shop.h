#pragma once

#include "Inventory.h"
#include "Sales.h"
#include "Customer.h"
#include "Reservation.h"
#include "Date.h"
#include "BinaryFunctions.h"
#include "Filefunctions.h"

typedef struct
{
    Inventory*   inventory;
    Sales*       salesDepartment;
    int          netBudget;
    double       profit;
}Shop;


void    initShop(Shop *pShop, Inventory *pInventory, Sales *pSales, int initialBudget);
int     saveShopToTextFile(Shop* pShop, FILE* inventoryFileName, FILE* customerFileName, FILE* reservationFileName);
int     saveShopToBianryFile(Shop* pShop, FILE* inventoryFileName, FILE* customerFileName, FILE* reservationFileName);
double  calculateReservationRevenue(const Sales* pSales);
void    printTotalRevenue(const Shop* pShop, int initialBudget);
void    freeShop(Shop* pShop);
