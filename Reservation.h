#pragma once


#include "Inventory.h"
#include "Customer.h"
#include "Date.h"
#include "list.h"
#include "Sales.h"




//#define MAX_RES_CODE_NUM 1000
typedef struct
{
    int serial;    // Serial number of the drink
    int amount;         // Amount purchased
    double cost;        // Cost of the purchased item
} PurchasedItem;


typedef struct
{
    int           ReservationCode;// will be the same as location in array 0 1 2 3....
    Customer*     customer;
    Date          date;

    double        priceOfOrder;
    LIST          purchasedItems;  //LIST*

}Reservation;

void initPurchasedItem(PurchasedItem* pItems);

void initReservation(Reservation* pRes,Customer* pCus);



void printReservation(const Reservation* pRes);
void printReservationPtr(void* pResPtr );

void freeReservationPtr(void* pResPtr);






int compareReseravationByReservatinCode(const void* rese1, const void* rese2);
int compareReseravationByCustomerName(const void* rese1, const void* rese2);
int compareReseravationByDate(const void* rese1, const void* rese2);