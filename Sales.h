#pragma once



#include "Customer.h"
//#include "Reservation.h"
#include "Inventory.h"
#include "list.h"


typedef enum { eNone, eResCode, eCustomerName, eDate, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt];



typedef struct
{
    LIST*                   customersList;
    struct Reservation**    reservationArray;
    int                     reservationCount;
    eSortOption	            ReservationSortOpt;
    Inventory*              inventory;
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
//int         pickCustomerFromList(const Sales* pSales);//print all clients 

void        printAllCustomers(const Sales* pSales);

int		insertNewAirportToList(LIST* pList, Customer* pCustomer);


int   initCustomerListFromTextFile(Sales* pSales, const char* fileName);
int   saveCustomerListToTextFile(Sales* pSales, const char* fileName);


/// <summary>
/// /Res funcs
 
//void         initReservationArray();

Customer*   getCustomerForReservation(Sales* pSales);


//int         addNewReservationToArray(Sales* pSales, Customer* pCustomer, char* itemsList, int itemsPrice);
int         addNewReservationToArray2(Sales* pSales, Inventory* pInventory,Customer* pCustomer);

void        printReservationsArr(struct Reservation** array ,int size);

void        freeReservationsArr(struct Reservation** array, int size);



eSortOption showSortMenu();
void        findReservation(const Sales* pSales); //bsearch- 1)ResCode  2)clientName   3)date?
void        sortReservations(Sales* pSales);
