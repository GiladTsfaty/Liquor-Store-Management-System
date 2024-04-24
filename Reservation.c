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
	pItems->serial = 0;
	pItems->amount = 0;
	pItems->costInt = 0;
	pItems->costDec = 0;
}


void printPurchasedItem(const void* pItemVoid)
{
	const PurchasedItem* pItem = (const PurchasedItem*)pItemVoid;
	double cost = pItem->costInt + (double)pItem->costDec / 100.0;
	printf("Item Serial: %d, Amount: %d, Cost: $%.2f\n",
		pItem->serial, pItem->amount, cost);
}



void initReservation(Reservation* pRes, Customer* pCus) {
	pRes->ReservationCode = -1;
	pRes->customer = pCus;
	getCorrectDate(&(pRes->date));
	pRes->priceOfOrder = 0;
	pRes->purchasedItems = NULL;
	pRes->numPurchasedItems = 0;
}


void printReservation(const Reservation* pRes)
{
	printf("\n\nOn the ");
	printDate(&pRes->date);
	printf(", %s made a Reservation,  REScode: %d, , in the amount of %.2f$. \n", pRes->customer->name,
		pRes->ReservationCode, pRes->priceOfOrder);
	printf("The Items are:\n");

	for (int i = 0; i < pRes->numPurchasedItems; i++)
	{
		printPurchasedItem(&(pRes->purchasedItems[i]));
	}
}



void printReservationPtr(void* pResPtr)
{
	const Reservation* temp = *(Reservation**)pResPtr;
	printReservation(temp);

}



void freeReservationPtr(void* pResPtr)
{
	Reservation* temp = *(Reservation**)pResPtr;
	free(temp->purchasedItems); // Free the array of purchased items
	free(temp);
}


int compareReseravationByReservatinCode(const void* rese1, const void* rese2)
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
