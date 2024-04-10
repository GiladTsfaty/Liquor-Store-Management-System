#pragma once


#include "Customer.h"
#include "Reservation.h"
#include "Inventory.h"
#include "list.h"




#define ERROR 0
#define FROM_FILE 1
#define FROM_USER 2


typedef enum { eNone, eResCode, eCustomerName, eDate, eNofSortOpt } eSortOption;
static const char* sortOptStr[eNofSortOpt];



typedef struct
{
    LIST                    customersList;//list*??
    struct Reservation**    reservationArray;
    int                     reservationCount;
    eSortOption	            ReservationSortOpt;
    Inventory*              inventory;
}Sales;


//void        initSalesFromFile(Sales* pSales, const char* fileName);

void        initSales(Sales* pSales, Inventory* pInventory);

int         saveSalesToTextFile(Sales* pSales, FILE* customerFileName, FILE* reservationFileName);// change to FILE*
int         saveSalesToBinaryFile(Sales* pSales, FILE* customerFileName, FILE* reservationFileName);

void        freeSales(Sales* pSales);




/// Client funcs
int         addNewCustomer(Sales* pSales);
Customer*   initCustomer(Sales* pSales);
Customer*   findCustomerByName(const Sales* pSales, const char* name);
int         uniqeNameCheck(const char* name, const Sales* pSales);
int         customerCompare(const void* data1, const void* data2);//name comperator
void        printAllCustomers(const Sales* pSales);
int		    insertNewCustomerToList(LIST* pList, Customer* pCustomer);

//int         pickCustomerFromList(const Sales* pSales);//print all clients 



///Res funcs
 
//void         initReservationArray();
Customer*   getCustomerForReservation(Sales* pSales);
//int         addNewReservationToArray(Sales* pSales, Customer* pCustomer, char* itemsList, int itemsPrice);
int         addNewReservationToArray2(Sales* pSales, Inventory* pInventory,Customer* pCustomer);
void        printReservationsArr(struct Reservation** array ,int size);
void        freeReservationsArr(struct Reservation** array, int size);



eSortOption showSortMenu();
void        findReservation(const Sales* pSales); //bsearch- 1)ResCode  2)clientName   3)date?
void        sortReservations(Sales* pSales);
