#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>
//
//#include "GeneralFunctions.h"
//#include "Shop.h"
//#include "Inventory.h"
//#include "Beer.h"
//#include "Wine.h"
//#include "Sales.h"
#include "Customer.h"
#include "list.h"
#include "Reservation.h"
#include "Date.h"




//typedef enum
//{
//    eLoadFromTextFile, eLoadFromBinaryFile, ePrintInventory, ePrintReservations,
//    eAddBeveragesToInventory, eAddClient, eMakeReservation, eFindReservationByResCode, eFindClientByName,
//    eOrderClientList, ecreativeFunc1, ecreativeFunc2,
//    eNofOptions
//} eMenuOptions;    //OrderClientList(name\status\resCode)
//


int main() {

   /* Inventory inventory;
    initInventory(&inventory);
    

    addBeer(&inventory);
    printBeer(&inventory.beerArray[0]);
    addWine(&inventory);
    printWine(&inventory.wineArray[0]);*/





    //Sales sales;
    //initSales(&sales);

    Customer client;
    initCustomerWithoutName(&client);
    getCustomerName(&client);
    printCustomer(&client);





    _CrtDumpMemoryLeaks();

    return 1;

}
