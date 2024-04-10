#define _CRTDBG_MAP_ALLOC

//#include <crtdbg.h>
#include <stdlib.h>
#include <stdio.h>


#include "main.h"
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
#include "BinaryFunctions.h"

/////inventory files ///
//#define INVENTORY_FILE_NAME "Inventory.txt"
//#define INVENTORY_BINARY_FILE_NAME "Inventory.bin"
//
//
/////customer files ///
//#define CUSTOMER_LIST_TEXT_FILE_LOAD_NAME "customer_list.txt"
//#define CUSTOMER_LIST_TEXT_FILE_SAVE_NAME "customer_list_saveTo.txt"
//
//#define CUSTOMER_LIST_BINARY_FILE_LOAD_NAME "BinaryCustomer.bin"
//#define CUSTOMER_LIST_BINARY_FILE_SAVE_NAME "BinaryCustomerSaveTo.bin"
//
/////reservations files ///
//#define RESERVATIONS_ARR_TEXT_FILE_LOAD_NAME "reservation_arr.txt"
//#define RESERVATIONS_ARR_TEXT_FILE_SAVE_NAME "reservation_arr_saveTo.txt"
//
//#define RESERVATIONS_ARR_BINARY_FILE_LOAD_NAME "BinaryReservation.bin"
//#define RESERVATIONS_ARR_BINARY_FILE_SAVE_NAME "BinaryReservationSaveTo.bin"
//int main() {
//
//   Shop shop;
//   initShop(&shop);
//   Inventory inventory;
//   Sales sales;
//   initSales(&sales, &inventory);
//
//   Customer cus ;
//   returnBlanckCustomer(&cus);
//   insertNewCustomerToList(&sales, &cus);
//
//
//
//
//  /* initInventoryFromFile(&inventory, INVENTORY_FILE_NAME);
//   printInventory(&inventory);
//
//   printReservationsArr(sales.reservationArray, sales.reservationCount);
//
//   addNewReservationToArray2(&sales, &inventory, &cus);
//   addNewReservationToArray2(&sales, &inventory, &cus);
//
//   printReservationsArr(sales.reservationArray, sales.reservationCount);
//   printCustomer(&cus);
//
//   saveReservationsArrayToTextFile(&sales, RESERVATIONS_ARR_TEXT_FILE_LOAD_NAME);
//   saveReservationsArrayToBinaryFile(&sales, RESERVATIONS_ARR_BINARY_FILE_LOAD_NAME);
//
//   loadReservationsArrayFromTextFile(&sales, RESERVATIONS_ARR_TEXT_FILE_LOAD_NAME);
//   loadReservationsArrayFromBinaryFile(&sales, RESERVATIONS_ARR_BINARY_FILE_LOAD_NAME);
//   printReservationsArr(sales.reservationArray, sales.reservationCount);
//   saveReservationsArrayToTextFile(&sales, RESERVATIONS_ARR_TEXT_FILE_SAVE_NAME);
//   saveReservationsArrayToBinaryFile(&sales, RESERVATIONS_ARR_BINARY_FILE_SAVE_NAME);*/
////
////   /*initCustomerWithoutName(&cus);
////   getCustomerName(&cus);*/
////
////  /* printReservationsArr(sales.reservationArray, sales.reservationCount);
////   addNewReservationToArray2(&sales, &inventory, &cus);
////   addNewReservationToArray2(&sales, &inventory, &cus);
////   printReservationsArr(sales.reservationArray, sales.reservationCount);
////   printCustomer(&cus); 
////
////   saveReservationsArrayToTextFile(&sales, RESERVATIONS_ARR_TEXT_FILE_LOAD_NAME);*/
////
////   /*loadReservationsArrayFromTextFile(&sales, RESERVATIONS_ARR_TEXT_FILE_LOAD_NAME);
////   printReservationsArr(sales.reservationArray, sales.reservationCount);*/
////
////  /* addNewReservationToArray2(&sales, &inventory, &cus);
////   printReservationsArr(sales.reservationArray, sales.reservationCount);
////   saveReservationsArrayToTextFile(&sales,RESERVATIONS_ARR_TEXT_FILE_SAVE_NAME);
////  */
////   ///TESTING  
////  //loadReservationsArrayFromTextFile(&sales, RESERVATIONS_ARR_TEXT_FILE_LOAD_NAME); 
////
////   /*loadReservationsArrayFromBinaryFile(&sales, RESERVATIONS_ARR_BINARY_FILE_LOAD_NAME);
////   printReservationsArr(sales.reservationArray, sales.reservationCount);
////   addNewReservationToArray2(&sales, &inventory, &cus);
////   printReservationsArr(sales.reservationArray, sales.reservationCount);
////   saveReservationsArrayToBinaryFile(&sales, RESERVATIONS_ARR_BINARY_FILE_SAVE_NAME);*/
////
////
////
////   ////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
////
////   //initInventoryFromFile(&inventory, INVENTORY_FILE_NAME);
////   //printInventory(&inventory);
////
////   ////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//////     initInventory(&inventory);
////
//////     saveInventoryToBinaryFile(&inventory, INVENTORY_BINARY_FILE_NAME);
//////     initInventoryFromBinaryFile(&inventory, INVENTORY_BINARY_FILE_NAME);
//////     addWine(&inventory);
//////     addBeer(&inventory);
//////     addWhiskey(&inventory);
////
////   // printInventory(&inventory);
////
////
////
//////    
//////    Sales sales;
//////    initSales(&sales, &inventory);
////////    shop.salesDepartment = &sales;
//////    Customer customer1;
//////    initCustomerWithoutName(&customer1);
//////
//////
//////
////////    initCustomerWithoutName(&customer1);
//////    getCustomerName(&customer1);
//////    L_insertByNameOrder(sales.customersList, &customer1);
//////  //  addNewReservationToArray(&sales,&customer1,items1,price1);
//////    //printReservationsArr(sales.reservationArray,sales.reservationCount);
//////
//////
////////    initCustomerWithoutName(&customer2);
////////    getCustomerName(&customer2);
////////    addNewReservationToArray(&sales, &customer1, items2, price2);
//////    addNewReservationToArray2(&sales, &inventory, &customer1);
//////    printReservationsArr(sales.reservationArray, sales.reservationCount);
//////    printCustomer(&customer1); /// sim lev -> ha amount sel res hitvasef ezal customer
//////    printBeer(&inventory.beerArray[0]); // the amount ba res has substract from Inventory
//////
//////   // freeReservationsArr(sales.reservationArray, sales.reservationCount);// fix free
////
//// //   addBeer(&inventory);
//////    inventory.beerArray[0].itemSerial = 111;
//////    printBeer(&inventory.beerArray[0]);
//////    addWine(&inventory);
//////    printWine(&inventory.wineArray[0]);
////
////
////
////
////
////
////    
//////    Sales sales;
//////    initSales(&sales, &inventory);
//////    shop.salesDepartment = &sales;
//////    Customer customer1;
//////    initCustomerWithoutName(&customer1);
////
//////
//////
//////
//////    initCustomerWithoutName(&customer1);
//////    getCustomerName(&customer1);
//////    L_insertByNameOrder(sales.customersList, &customer1);
//////    addNewReservationToArray(&sales,&customer1,items1,price1);
//////    printReservationsArr(sales.reservationArray,sales.reservationCount);
//////
//////
//////    initCustomerWithoutName(&customer2);
//////    getCustomerName(&customer2);
//////    addNewReservationToArray(&sales, &customer1, items2, price2);
//////    addNewReservationToArray2(&sales, &inventory, &customer1);
//////    printReservationsArr(sales.reservationArray, sales.reservationCount);
//////    printCustomer(&customer1); /// sim lev -> ha amount sel res hitvasef ezal customer
//////    printBeer(&inventory.beerArray[0]); // the amount ba res has substract from Inventory
//////
//////    freeReservationsArr(sales.reservationArray, sales.reservationCount);
////
////
////
////
////   ///cusromer file check///
////
////   //readCustomerListFromBFile(&sales, CUSTOMER_LIST_BINARY_FILE_LOAD_NAME );
////   //printAllCustomers(&sales);
////   //addNewCustomer(&sales);
////   //printAllCustomers(&sales);
////   //writeCustomerListToBFile(&sales,CUSTOMER_LIST_BINARY_FILE_SAVE_NAME);
////
////
////   /*readCustomerListFromBFile(&sales, CUSTOMER_LIST_BINARY_FILE_SAVE_NAME);
////   printAllCustomers(&sales);*/
////
////
////   /*addNewCustomer(&sales);
////   printAllCustomers(&sales);
////   //initCustomerListFromTextFile(&sales, CUSTOMER_LIST_TEXT_FILE_LOAD_NAME);
////   writeCustomerListToBFile(&sales, CUSTOMER_LIST_BINARY_FILE_SAVE_NAME);*/
////   // saveCustomerListToTextFile(&sales,CUSTOMER_LIST_TEXT_FILE_SAVE_NAME);
////
////
////
////
//
//
//    // Winter Is Coming. Buy Whiskey
//
//
//    _CrtDumpMemoryLeaks();//dont delete put in comment
//
//
//    return 1;
//
//}

//
//i want to change the customer name
//modify the functions so that
//
//if one word - capitalize the first letter all other letters lower case, like - Jhon
//
//if 2 or more words - capitalize the first letter of every word 
//,all other letters lower case and put an "_" insted of eny blank space ,
//like - Jhon_Doe



int main() {
    Shop shop;
    Inventory inventory;
    Sales sales;
    int initialBudget = 3500;


    initShop(&shop, &inventory, &sales, initialBudget);//why init twice?

    //initSystemFromFiles(&shop, &sales, &inventory);


    //printInventory(&inventory);
    //printAllCustomers(&sales);
    //printReservation(sales.reservationArray[0]);
    //printReservationsArr(sales.reservationArray,sales.reservationCount);
    //addNewReservationToArray2(&sales,&inventory,);
    //saveReservationsArrayToBinaryFile(shop.salesDepartment, RESERVATIONS_ARR_BINARY_FILE_SAVE_NAME);


    Customer c;
    initSales(shop.salesDepartment, shop.inventory);
    addNewCustomer(shop.salesDepartment);
    printCustomer(shop.salesDepartment->customersList.head.next->key);


//    int loadOption;
//    int isSystemLoaded = 0;
//
//    while (!isSystemLoaded)
//    {
//        printf("HELLO AND WELLCOME TO THE LIQUOR STORE:\n");
//        printf("Choose how to load the system:\n");
//        printf("1 - Load from text files\n");
//        printf("2 - Load from binary files\n");
//        scanf("%d", &loadOption);
//
//        switch (loadOption)
//        {
//        case 1:
//            if (initSystemFromTextFiles(&sales, &inventory))
//            {
//                printf("System loaded successfully from text files.\n");
//                isSystemLoaded = 1;
//            }
//            else
//            {
//                printf("Error loading system from text files.\n");
//            }
//            break;
//        case 2:
//            if (initSystemFromBinaryFiles(&sales, &inventory))
//            {
//                printf("System loaded successfully from binary files.\n");
//                isSystemLoaded = 1;
//            }
//            else
//            {
//                printf("Error loading system from binary files.\n");
//            }
//            break;
//        default:
//            printf("Invalid option. Please try again.\n");
//            break;
//        }
//    }
//
//
//
//
//    int option;
//    int stop = 0;
//
//    do
//    {
//        option = menu();
//        switch (option)
//        {
//        case ePrintInventory:
//            printInventory(&inventory);
//            break;
//        case ePrintReservations:
//            printReservationsArr(&theShop.salesDepartment->reservationArray, theShop.salesDepartment->reservationCount);
//            break;
//        case ePrintCustomers:
//            printAllCustomers(&theShop.salesDepartment);
//            break;
//        case eAddBeveragesToInventory:
//            if (!addBeveragesToInventory(&inventory))
//                printf("Error adding beverages to inventory\n");
//            break;
//        case eAddClient:
//            if (!addNewCustomer(&theShop.salesDepartment))
//                printf("Error adding client\n");
//            break;
//        case eMakeReservation:
//            if (!addNewReservationToArray2(&theShop.salesDepartment, &theShop.inventory,getCustomerForReservation(&theShop.salesDepartment)));//not good template
//                printf("Error making reservation\n");
//            break;
//        case eSortReservationArray:
//            sortReservations(&sales);
//            break;
//        case eFindReservation:
//            findReservation(&sales);
//            break;
//        case ecreativeFunc1:
//            // Call creative function 1
//            break;
//        case ecreativeFunc2:
//            // Call creative function 2
//            break;
//        case EXIT:
//            printf("Bye bye\n");
//            stop = 1;
//            break;
//        default:
//            printf("Wrong option\n");
//            break;
//        }
//    } while (!stop);
//
//    saveShopToTextFile(&theShop);
//    saveShopToBianryFile(&theShop);
//
//<<<<<<< HEAD
//    freeShop(&theShop);
//=======
////    _CrtDumpMemoryLeaks();//dont delete put in comment
//
//>>>>>>> fd534e4 (justForSAFE)
//
//    printf("before dump\n");
//    _CrtDumpMemoryLeaks();
//    return 1;
//}
}

//int menu()
//{
//	int option;
//	printf("\n\n");
//	printf("Please choose one of the following options\n");
//	for (int i = 0; i < eNofOptions; i++)
//		printf("%d - %s\n", i, str[i]);
//	printf("%d - Quit\n", EXIT);
//	scanf("%d", &option);
//	//clean buffer
//	char tav;
//	scanf("%c", &tav);
//	return option;
//}