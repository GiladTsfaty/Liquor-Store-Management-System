#pragma once

#include "Customer.h"
#include "Reservation.h"
//#include "Inventory.h"



typedef enum { eNone, eResCode, eCustomerName, eDate, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt];



typedef struct
{
    LIST customersList;

    Reservation** reservationArray;
    int reservationCount;

    eSortOption	ReservationSortOpt;


    //LIST reservationList;

    //Inventory* inventory;
   
    //int customerCount;
  

}Sales;



void        initSales(Sales* pSales, Inventory* pInventory);
void        freeSales(Sales* pSales);


/// <summary>
/// Client funcs
int         addNewCustomer(Sales* pSales);
Customer*   initCustomer(Sales* pSales);
Customer*   findCustomerByName(const Sales* pSales, const char* name);
int         uniqeNameCheck(const char* name, const Sales* pSales);
int         customerCompare(const void* data1, const void* data2);//name comperator

void        printAllCustomers(const Sales* pSales);

/// <summary>
/// /Res funcs
 

eSortOption showSortMenu();  

int         addNewReservation(Sales* pSales);

void        findReservation(const Sales* pSales); //bsearch- 1)ResCode  2)clientName   3)date?
void        sortReservations(Sales* pSales);

void        printReservationsArr(const Sales* pSales);
