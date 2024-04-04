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
#include "BinaryFiles.h"

#define INVENTORY_FILE_NAME "Inventory.txt"

#define CUSTOMER_LIST_TEXT_FILE_NAME "customer_list.txt"

#define INVENTORY_BINARY_FILE_NAME "Inventory.bin"



//typedef enum
//{
//    eLoadFromTextFile, eLoadFromBinaryFile, ePrintInventory, ePrintReservations,
//    eAddBeveragesToInventory, eAddClient, eMakeReservation, eFindReservationByResCode, eFindClientByName,
//    eOrderClientList, ecreativeFunc1, ecreativeFunc2,
//    eNofOptions
//} eMenuOptions;    //OrderClientList(name\status\resCode)
//


int main() {

   Shop shop;
   initShop(&shop);
   Inventory inventory;
   ////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

//   initInventoryFromFile(&inventory, INVENTORY_FILE_NAME);
//   printInventory(&inventory);

   ////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//   initInventory(&inventory);

//    saveInventoryToBinaryFile(&inventory, INVENTORY_BINARY_FILE_NAME);
//     initInventoryFromBinaryFile(&inventory, INVENTORY_BINARY_FILE_NAME);
//    addWine(&inventory);
//    addBeer(&inventory);
//    addWhiskey(&inventory);

//     printInventory(&inventory);



//    
//    Sales sales;
//    initSales(&sales, &inventory);
////    shop.salesDepartment = &sales;
//    Customer customer1;
//    initCustomerWithoutName(&customer1);
//
//
//
////    initCustomerWithoutName(&customer1);
//    getCustomerName(&customer1);
//    L_insertByNameOrder(sales.customersList, &customer1);
//  //  addNewReservationToArray(&sales,&customer1,items1,price1);
//    //printReservationsArr(sales.reservationArray,sales.reservationCount);
//
//
////    initCustomerWithoutName(&customer2);
////    getCustomerName(&customer2);
////    addNewReservationToArray(&sales, &customer1, items2, price2);
//    addNewReservationToArray2(&sales, &inventory, &customer1);
//    printReservationsArr(sales.reservationArray, sales.reservationCount);
//    printCustomer(&customer1); /// sim lev -> ha amount sel res hitvasef ezal customer
//    printBeer(&inventory.beerArray[0]); // the amount ba res has substract from Inventory
//
//   // freeReservationsArr(sales.reservationArray, sales.reservationCount);// fix free

 //   addBeer(&inventory);
//    inventory.beerArray[0].itemSerial = 111;
//    printBeer(&inventory.beerArray[0]);
//    addWine(&inventory);
//    printWine(&inventory.wineArray[0]);






    
//    Sales sales;
//    initSales(&sales, &inventory);
////    shop.salesDepartment = &sales;
//    Customer customer1;
//    initCustomerWithoutName(&customer1);

//
//
//
////    initCustomerWithoutName(&customer1);
//    getCustomerName(&customer1);
//    L_insertByNameOrder(sales.customersList, &customer1);
//  //  addNewReservationToArray(&sales,&customer1,items1,price1);
//    //printReservationsArr(sales.reservationArray,sales.reservationCount);
//
//
////    initCustomerWithoutName(&customer2);
////    getCustomerName(&customer2);
////    addNewReservationToArray(&sales, &customer1, items2, price2);
//    addNewReservationToArray2(&sales, &inventory, &customer1);
//    printReservationsArr(sales.reservationArray, sales.reservationCount);
//    printCustomer(&customer1); /// sim lev -> ha amount sel res hitvasef ezal customer
//    printBeer(&inventory.beerArray[0]); // the amount ba res has substract from Inventory
//
//    freeReservationsArr(sales.reservationArray, sales.reservationCount);





   Sales sales;
   initSales(&sales, &inventory);
   initCustomerListFromTextFile(&sales, CUSTOMER_LIST_TEXT_FILE_NAME);
   printAllCustomers(&sales);



    // The winter is coming. Buy Whiskey


    _CrtDumpMemoryLeaks();//dont delete put in comment


    return 1;

}
