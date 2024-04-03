#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Sales.h"
#include "list.h"
#include "Reservation.h"



void initSales(Sales* pSales)
{
	printf("-----------  Init Sales ----------\n");

	L_init(&pSales->customersList);

	pSales->reservationCount = 0;
	pSales->reservationArray = NULL;

}



//void initSales(Sales* pSales, Inventory* pInventory)
//{
//    pSales->inventory = pInventory;
//    L_init(pSales->customersList);
//    pSales->customerCount = 0;
//    pSales->reservationArray = NULL;
//    pSales->reservationCount = 0;
//}

int addNewCustomer(Sales* pSales)
{
	Customer* pCustomer = initCustomer(pSales);
	if (!pCustomer)
		return 0;
	L_insertByNameOrder(&pSales->customersList, pCustomer);
	return 1;
}



Customer* initCustomer(Sales* pSales)
{
	Customer* pCustomer = (Customer*)calloc(1, sizeof(Customer));
	if (!pCustomer)
		return NULL;

	while (1)
	{
		getCustomerName(pCustomer);
		if (uniqeNameCheck(pCustomer->name, pSales))
			break;

		printf("This client name is already in use - please change name \n");
	}

	initCustomerWithoutName(pCustomer);
	return pCustomer;
}




int uniqeNameCheck(const char* name, const Sales* pSales)
{
	Customer* customer = findCustomerByName(pSales, name);

	if (customer != NULL)
		return 0;

	return 1;
}




Customer* findCustomerByName(const Sales* pSales, const char* name)
{
	NODE* pN = pSales->customersList.head.next; //first Node
	if (!pN)
		return NULL;

	Customer* pTemp;
	int compRes;
	while (pN != NULL)
	{
		pTemp = (Customer*)pN->key;
		compRes = strcmp(pTemp->name, name);
		if (compRes == 0)
			return pTemp;
		if (compRes > 1) //not found
			return NULL;
		pN = pN->next;
	}

	return NULL;
}






int customerCompare(const void* data1, const void* data2) //if code is uniqe return 0 
{
	const Customer* pCustomer1 = (const  Customer*)data1;
	const Customer* pCustomer2 = (const  Customer*)data2;

	if (!strcmp(pCustomer1->name, pCustomer2->name))
		return 1;
	return 0;
}




void printAllCustomers(const Sales* pSales)
{

	printf("there are %d clients\n", L_length(&(pSales->customersList)) - 1);

	L_print(&(pSales->customersList), printCustomer);

	printf("\n");


}



////RESERVATIONS////







//int addNewReservation(Sales* pSales)
//{
//
//	Reservation* pRes = (Reservation*)calloc(1, sizeof(Reservation));
//	if(!pRes)
//		return 0;
//
//
//	pSales->reservationArray = (Reservation**)realloc(pSales->reservationArray, (pSales->reservationCount + 1) * sizeof(Reservation*));//arr++
//	if (!pSales->reservationArray)
//	{
//		free(pRes);
//		return 0;
//	}
//
//	pSales->reservationArray[pSales->reservationCount] = pRes;//added to end of arr 
//	pSales->reservationCount++; //arr
//	pSales->ReservationSortOpt = eNone;
//	
//	return 1;
//}





int addNewReservation(Sales* pSales) {
	// Allocate memory for a new Reservation object
	Reservation* pRes = (Reservation*)calloc(1, sizeof(Reservation));
	if (!pRes)
		return 0; // Memory allocation failed

	// Resize the reservationArray to accommodate the new reservation
	Reservation** tempArray = (Reservation**)realloc(pSales->reservationArray, (pSales->reservationCount + 1) * sizeof(Reservation*));
	if (!tempArray) {
		// Memory allocation failed, free the previously allocated Reservation object
		free(pRes);
		return 0;
	}

	// Assign the resized array to a temporary variable
	Reservation** resizedArray = (Reservation**)tempArray;

	// Add the new reservation to the end of the array
	resizedArray[pSales->reservationCount] = pRes;

	// Update pSales->reservationArray with the resized array(casting to the same type)
		pSales->reservationArray = (Reservation**)resizedArray;

	// Increment the reservation count
	pSales->reservationCount++;

	// Reset the reservation sorting option (if needed)
	pSales->ReservationSortOpt = eNone;

	return 1; // Reservation added successfully
}







void findReservation(const Sales* pSales) {
	int(*compare)(const void* rese1, const void* rese2) = NULL; // Initialize to NULL

	Reservation reservation = { 0 };
	Reservation* pCurrentReservation = &reservation;

	switch (pSales->ReservationSortOpt) {
	case eResCode:
		printf("%s\t", "Reservation Code:"); // Corrected printing statement
		compare = compareReseravationByReservatinCode;
		break;

	case eCustomerName:
		printf("%s\t", "Customer Name:"); // Corrected printing statement
		compare = compareReseravationByCustomerName; // Set the comparison function
		break;

	case eDate:
		printf("%s\t", "Date:");
		compare = compareReseravationByDate; // Set the comparison function
		break;

	default:
		printf("Invalid ReservationSortOpt\n");
		return; // Exit the function
	}

	if (compare != NULL) {
		// Assuming bsearch is used to search the reservation in the sorted array
		Reservation** pFoundReservation = bsearch(&pCurrentReservation, pSales->reservationArray, pSales->reservationCount, sizeof(Reservation*), compare);
		if (pFoundReservation == NULL)
			printf("Reservation was not found\n");
		else {
			printf("Reservation found: ");
			// Assuming printReservation is a function to print reservation details
			printReservation(*pFoundReservation);
		}
	}
	else {
		printf("The search cannot be performed, array not sorted\n");
	}
}



void sortReservations(Sales* pSales)
{
	int(*compare)(const void* rese1, const void* rese2) = NULL;
	Reservation r = { 0 };
	Reservation* pReservation = &r;

	switch (pSales->ReservationSortOpt)
	{
	case eResCode:
		printf("%s\t", "Reservation Code:"); // Corrected printing statement

		compare = compareReseravationByReservatinCode;
		break;

	case eCustomerName:
		printf("%s\t", "Customer Name:"); // Corrected printing statement
		compare = compareReseravationByCustomerName; // Set the comparison function
		break;
       

	case eDate:
		getCorrectDate(&r.date);
		compare = compareReseravationByDate;
		break;

	}

}


eSortOption showSortMenu()
{
	int opt;
	printf("Base on what field do you want to sort the reservations?\n");
	do {
		for (int i = 1; i < eNofSortOpt; i++)
			printf("Enter %d for %s\n", i, sortOptStr[i]);
		scanf("%d", &opt);
	} while (opt < 0 || opt >= eNofSortOpt);

	return (eSortOption)opt;
}




void freeSales(Sales* pSales)
{
	L_free(&pSales->customersList, freeCustomer);//free clients

	//L_free(&(pSales->reservationList, freereservation);// free reservations 

}
