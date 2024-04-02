#include <stdio.h>
#include "Shop.h"
#include "Inventory.h"
#include "Beer.h"
#include "Wine.h"
#include "Sales.h"



typedef enum
{
    eLoadFromTextFile, eLoadFromBinaryFile, ePrintInventory, ePrintReservations,
    eAddBeveragesToInventory, eAddClient, eMakeReservation, eFindReservationByResCode, eFindClientByName,
    eOrderClientList, ecreativeFunc1, ecreativeFunc2,
    eNofOptions
} eMenuOptions;    //OrderClientList(name\status\resCode)



int main() {

    Inventory inventory;
    initInventory(&inventory);


    addBeer(&inventory);
    printBeer(&inventory.beerArray[0]);
    addWine(&inventory);
    //printWine(&inventory.wineArray[0]);

    Sales sales;
    initSales(&sales, &inventory);


    return 1;
}
