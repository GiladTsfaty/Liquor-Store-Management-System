#pragma once

#include "Shop.h"
#include "Sales.h"
#include "BringThemHomeNow.h"



typedef enum
{
    ePrintInventory, ePrintReservations, ePrintCustomers,
    eAddBeveragesToInventory, eRefillInventory, eAddClient, eMakeReservation,
	eSortReservationArray, eFindReservation,
    ecalculateTotalRevenue, eTopNCustomers, eBringThemHome,
    eNofOptions
} eMenuOptions;




const char* str[eNofOptions] = {
    "Print inventory", "Print reservations", "Print all clients",
    "Add beverages to inventory", "Refill Inventory", "Add client", "Make reservation",
    "Sort reservation array", "Find reservation",
    "Show the shops profit", "Show the top clients", "Bring Them Home"
};


#define EXIT		      -1
#define FIND_TOP_N_CLIENTS 1
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



void initSystemFromFiles(Shop* pShop, Sales* pSales, Inventory* pInventory);
int menu();


