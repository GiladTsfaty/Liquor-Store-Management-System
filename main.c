#define _CRTDBG_MAP_ALLOC

#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>

#include "GeneralFunctions.h"
#include "Filefunctions.h"
#include "BinaryFunctions.h"
#include "Shop.h"
#include "Inventory.h"
#include "Beer.h"
#include "Wine.h"
#include "Sales.h"
#include "Customer.h"
#include "list.h"
#include "Reservation.h"
#include "Date.h"

///inventory files ///
#define INVENTORY_FILE_NAME "Inventory.txt"
#define INVENTORY_BINARY_FILE_NAME "Inventory.bin"


///customer files ///
#define CUSTOMER_LIST_TEXT_FILE_LOAD_NAME "customer_list.txt"
#define CUSTOMER_LIST_TEXT_FILE_SAVE_NAME "customer_list_saveTo.txt"

#define CUSTOMER_LIST_BINARY_FILE_LOAD_NAME "BinaryCustomer.bin"
#define CUSTOMER_LIST_BINARY_FILE_SAVE_NAME "BinaryCustomerSaveTo.bin"

///reservations files ///
#define RESERVATIONS_ARR_TEXT_FILE_LOAD_NAME "reservation_arr.txt"
#define RESERVATIONS_ARR_TEXT_FILE_SAVE_NAME "reservation_arr_saveTo.txt"

#define RESERVATIONS_ARR_BINARY_FILE_LOAD_NAME "BinaryReservation.bin"
#define RESERVATIONS_ARR_BINARY_FILE_SAVE_NAME "BinaryReservationSaveTo.bin"


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
   Sales sales;
   initSales(&sales, &inventory);
   Customer cus ;
   returnBlanckCustomer(&cus);
   insertNewCustomerToList(&sales, &cus);

   initInventoryFromFile(&inventory, INVENTORY_FILE_NAME);
   //printInventory(&inventory);

   /*initCustomerWithoutName(&cus);
   getCustomerName(&cus);*/

   /*printReservationsArr(sales.reservationArray, sales.reservationCount);
   addNewReservationToArray2(&sales, &inventory, &cus);
   addNewReservationToArray2(&sales, &inventory, &cus);
   printReservationsArr(sales.reservationArray, sales.reservationCount);
   printCustomer(&cus); 

   saveReservationsArrayToTextFile(&sales, RESERVATIONS_ARR_TEXT_FILE_LOAD_NAME);*/

   loadReservationsArrayFromTextFile(&sales, RESERVATIONS_ARR_TEXT_FILE_LOAD_NAME);
   printReservationsArr(sales.reservationArray, sales.reservationCount);
   addNewReservationToArray2(&sales, &inventory, &cus);
   printReservationsArr(sales.reservationArray, sales.reservationCount);
   saveReservationsArrayToTextFile(&sales,RESERVATIONS_ARR_TEXT_FILE_SAVE_NAME);
      

   ////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

   //initInventoryFromFile(&inventory, INVENTORY_FILE_NAME);
   //printInventory(&inventory);

   ////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//     initInventory(&inventory);

//     saveInventoryToBinaryFile(&inventory, INVENTORY_BINARY_FILE_NAME);
//     initInventoryFromBinaryFile(&inventory, INVENTORY_BINARY_FILE_NAME);
//     addWine(&inventory);
//     addBeer(&inventory);
//     addWhiskey(&inventory);

   // printInventory(&inventory);



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
//    shop.salesDepartment = &sales;
//    Customer customer1;
//    initCustomerWithoutName(&customer1);

//
//
//
//    initCustomerWithoutName(&customer1);
//    getCustomerName(&customer1);
//    L_insertByNameOrder(sales.customersList, &customer1);
//    addNewReservationToArray(&sales,&customer1,items1,price1);
//    printReservationsArr(sales.reservationArray,sales.reservationCount);
//
//
//    initCustomerWithoutName(&customer2);
//    getCustomerName(&customer2);
//    addNewReservationToArray(&sales, &customer1, items2, price2);
//    addNewReservationToArray2(&sales, &inventory, &customer1);
//    printReservationsArr(sales.reservationArray, sales.reservationCount);
//    printCustomer(&customer1); /// sim lev -> ha amount sel res hitvasef ezal customer
//    printBeer(&inventory.beerArray[0]); // the amount ba res has substract from Inventory
//
//    freeReservationsArr(sales.reservationArray, sales.reservationCount);




   ///cusromer file check///

   //readCustomerListFromBFile(&sales, CUSTOMER_LIST_BINARY_FILE_LOAD_NAME );
   //printAllCustomers(&sales);
   //addNewCustomer(&sales);
   //printAllCustomers(&sales);
   //writeCustomerListToBFile(&sales,CUSTOMER_LIST_BINARY_FILE_SAVE_NAME);


   /*readCustomerListFromBFile(&sales, CUSTOMER_LIST_BINARY_FILE_SAVE_NAME);
   printAllCustomers(&sales);*/


   /*addNewCustomer(&sales);
   printAllCustomers(&sales);
   //initCustomerListFromTextFile(&sales, CUSTOMER_LIST_TEXT_FILE_LOAD_NAME);
   writeCustomerListToBFile(&sales, CUSTOMER_LIST_BINARY_FILE_SAVE_NAME);*/
   // saveCustomerListToTextFile(&sales,CUSTOMER_LIST_TEXT_FILE_SAVE_NAME);






  










    // The winter is coming. Buy Whiskey


    _CrtDumpMemoryLeaks();//dont delete put in comment


    return 1;

}
