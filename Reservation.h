#pragma once


#include "Inventory.h"
#include "Customer.h"
#include "Date.h"
#include "list.h"
#include "Sales.h"



typedef struct
{
    unsigned int serial;    // Serial number of the drink (0-999)
    unsigned int amount;    // Amount purchased (0-10)
    unsigned int costInt;   // Integer part of the cost (0-10000)
    unsigned int costDec;   // Decimal part of the cost (0-99)
} PurchasedItem;



typedef struct
{
    int           ReservationCode;
    Customer*     customer;
    Date          date;
    double        priceOfOrder;
    PurchasedItem* purchasedItems;
    int           numPurchasedItems;


}Reservation;



void initPurchasedItem(PurchasedItem* pItems);
void printPurchasedItem(const void* pItemVoid);
void initReservation(Reservation* pRes,Customer* pCus);
void printReservation(const Reservation* pRes);
void printReservationPtr(void* pResPtr );
void freeReservationPtr(void* pResPtr);
int compareReseravationByReservatinCode(const void* rese1, const void* rese2);
int compareReseravationByCustomerName(const void* rese1, const void* rese2);
int compareReseravationByDate(const void* rese1, const void* rese2);