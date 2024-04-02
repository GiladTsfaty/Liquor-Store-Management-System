#pragma once


#include "Inventory.h"
#include "Customer.h"
#include "Date.h"
#include "List.h"
#include "Sales.h"




#define MAX_RES_CODE_NUM 1000

typedef struct
{
    int         ReservationCode;
    Customer*   customer;
    LIST        purchasedItems;
    int         totalAmount;
    Date        date;

}Reservation;


//void initReservation(Reservation* pRes,Customer* pCus, Sales* pSales);


int makeReservation();

void printReservation(const Reservation* pRes);



int compareReseravationByReservatinCode(const void* rese1, const void* rese2);
int compareReseravationByCustomerName(const void* rese1, const void* rese2);
int compareReseravationByDate(const void* rese1, const void* rese2);