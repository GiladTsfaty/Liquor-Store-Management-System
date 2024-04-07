#pragma once

#include "Shop.h"
#include "Sales.h"



typedef enum
{
    ePrintInventory, ePrintReservations, ePrintCustomers,
    eAddBeveragesToInventory, eAddClient, eMakeReservation,
	eSortReservationArray, eFindReservation,
    ecreativeFunc1, ecreativeFunc2,
    eNofOptions
} eMenuOptions;

// eLoadFromTextFile, eLoadFromBinaryFile,
// eOrderClientList, 
// 
//   "Load from text file", "Load from binary file",



const char* str[eNofOptions] = {
    "Print inventory", "Print reservations", "Print customers",
    "Add beverages to inventory", "Add client", "Make reservation",
    "Sort reservation array", "Find reservation",
    "Creative function 1", "Creative function 2"
};


#define EXIT			-1
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




int menu();


