#include "Reservation.h"
#include "Customer.h"
#include "list.h"
#include "Date.h"
#include "Sales.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



void initPurchasedItem(PurchasedItem* pItems)
{
	pItems->amount = 0;
	pItems->cost = 0;
	pItems->serial = 0;

}

void initReservation(Reservation* pRes, Customer* pCus) {
	
	pRes->ReservationCode = -1;

	// Copy customer information
	pRes->customer = pCus;

	// Initialize the date
	getCorrectDate(&(pRes->date));

	// Initialize the price of the order
	pRes->priceOfOrder = 0;

	// Initialize the list of purchased items
	initPurchasedItem(&pRes->purchasedItems) ;//& i add 
}



void printPurchasedItem(const void* pItemVoid)//NODE
{
    // Cast from void* to the appropriate type
    const PurchasedItem* pItem = (const PurchasedItem*)pItemVoid;

    // Print the details of the PurchasedItem
    printf("Item Serial: %d, Amount: %d, Cost: $%.2f\n",
           pItem->serial, pItem->amount, pItem->cost);
}


void printReservation(const Reservation* pRes)
{
	
	
	printf("\n\nOn the ");
	printDate(&pRes->date);
	printf(", %s made a Reservation,  REScode: %d, , in the amount of %.2f$. \n", pRes->customer->name,
		pRes->ReservationCode,pRes->priceOfOrder);
    printf("The Items are:\n");
    L_print((LIST*)&pRes->purchasedItems, (void(*)(const void*))printPurchasedItem);
	
}

void printReservationPtr(void* pResPtr)
{
	const Reservation* temp = *(Reservation**)pResPtr;
	printReservation(temp);

}

void freeReservationPtr(void* pResPtr)
{
	 Reservation* temp = *(Reservation**)pResPtr;
	 free(temp);
}










int compareReseravationByReservatinCode(const void* rese1, const void* rese2)//first in order -1
{
	const Reservation* pReservation1 = *(const Reservation**)rese1;
	const Reservation* pReservation2 = *(const Reservation**)rese2;

	if (pReservation1->ReservationCode < pReservation2->ReservationCode) {
		return -1;
	}
	else if (pReservation1->ReservationCode > pReservation2->ReservationCode) {
		return 1;
	}
	else 
		return 0;
}



int compareReseravationByCustomerName(const void* rese1, const void* rese2)
{
	const Reservation* pReservation1 = *(const Reservation**)rese1;
	const Reservation* pReservation2 = *(const Reservation**)rese2;

	return strcmp(pReservation1->customer->name, pReservation2->customer->name);

	return 0;
}

int compareReseravationByDate(const void* rese1, const void* rese2)
{
	const Reservation* pReservation1 = *(const Reservation**)rese1;
	const Reservation* pReservation2 = *(const Reservation**)rese2;


	return compareDate(&pReservation1->date, &pReservation2->date);
	return 0;
}
