#include "Reservation.h"
#include "Customer.h"
#include "list.h"
#include "Date.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


//
//void initReservation(Reservation* pRes, Customer* pCus, Sales* pSales)
//{
//	getCorrectDate(&pRes->date);//date
//
//	pRes->totalAmount = 0;//amount
//
//	findCustomerByName( pSales ,&pRes->customer->name);//client
//
//
//
//
//
//
//
//}






void printReservatoin(const Reservation* pRes)
{

	printf("On the ");
	printDate(&pRes->date);
	printf(", %s made a Reservation,  REScode: %d, , in the amount of %d$. \n", pRes->customer->name,
		pRes->ReservationCode,pRes->totalAmount);

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
