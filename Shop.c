#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Shop.h"



void initShop(Shop *pShop, Inventory *pInventory, Sales *pSales, int initialBudget)
////needs to call init salse/inventory/reservations functions
{
    printf("---------Init Shop-----------\n");

    pShop->inventory = pInventory;
    pShop->salesDepartment = pSales;
    pShop->netBudget = initialBudget;
}

int saveShopToTextFile(Shop* pShop, FILE* inventoryFileName, FILE* customerFileName, FILE* reservationFileName)
{
    saveSalesToTextFile(pShop->salesDepartment,customerFileName,reservationFileName);
    saveInventoryToTextFile(pShop->inventory, (char*)inventoryFileName);

    return 1;
}

int saveShopToBianryFile(Shop* pShop, FILE* inventoryFileName, FILE* customerFileName, FILE* reservationFileName)
{
    saveSalesToBinaryFile(pShop->salesDepartment, customerFileName, reservationFileName);
    saveInventoryToBinaryFile(pShop->inventory, (char*)inventoryFileName);

    return 1;
}




double calculateReservationRevenue(const Sales* pSales)
{
    double totalRevenue = 0.0;
    for (int i = 0; i < pSales->reservationCount; i++)
    {
        totalRevenue +=((Reservation*)pSales->reservationArray[i])->priceOfOrder;
    }
    return totalRevenue;
}

void printTotalRevenue(const Shop* pShop, int initialBudget)
{
    double reservationRevenue = calculateReservationRevenue(pShop->salesDepartment);
    double totalRevenue = reservationRevenue + initialBudget;
    printf("Total Revenue: $%.2f\n", totalRevenue);
}







void freeShop(Shop* pShop)
{

    freeSales(pShop->salesDepartment);
    freeInventory(pShop->inventory);

}
