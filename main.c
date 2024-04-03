#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>

#include "GeneralFunctions.h"
#include "Shop.h"
#include "Inventory.h"
#include "Beer.h"
#include "Wine.h"
#include "Sales.h"
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
    //addNewCustomer(&sales);
    //printAllCustomers(&sales);
    //addNewCustomer(&sales);
    //printAllCustomers(&sales);


   /* Customer client;
    initCustomerWithoutName(&client);
    getCustomerName(&client);
    printCustomer(&client);
    freeCustomer(&client);*/

    
    Sales sales;
    Customer customer1;
    int price1 = 500 ;
    char* items1 = "3-beers, 2-wines, 1-whisky";

    Customer customer2;
    int price2 = 1200;
    char* items2 = "5-beers, 5-wines, 5-whisky";

    initCustomerWithoutName(&customer1);
    getCustomerName(&customer1);
    addNewReservationToArray(&sales,&customer1,items1,price1);
    printReservationsArr(sales.reservationArray,sales.reservationCount);


    initCustomerWithoutName(&customer2);
    getCustomerName(&customer2);
    addNewReservationToArray(&sales, &customer1, items2, price2);
    printReservationsArr(sales.reservationArray, sales.reservationCount);

    freeReservationsArr(sales.reservationArray, sales.reservationCount);


    _CrtDumpMemoryLeaks();

    return 1;

}
