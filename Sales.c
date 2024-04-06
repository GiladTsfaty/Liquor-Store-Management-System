#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Sales.h"
#include "list.h"
#include "Reservation.h"
#include "GeneralFunctions.h"
#include "Customer.h"



void initSales(Sales* pSales, Inventory* pInventory)
{
    printf("---------Init Sales----------\n");

   // pSales->customersList = (LIST*)malloc(sizeof(LIST));
    /*if (pSales->customersList == NULL)
    {
        printf("Memory allocation failed for customersList.\n");
        return;
    }*/
    if (L_init(&pSales->customersList) == False)
    {
        printf("Memory allocation failed for customersList.\n");
        return;
    }
    //L_init(&pSales->customersList);//&
    pSales->inventory = pInventory;
    pSales->ReservationSortOpt = eNew;
    pSales->reservationCount = 0;
    pSales->reservationArray = NULL;
}



//
//void initSalesFromFile(Sales* pSales, const char* fileName)
//{
//   
//
//    if (loadSalesFromFile(pSales, fileName))
//        return FROM_FILE;
//
//    printf("-----------  Init airport Manager ---- User\n");
//    if (!L_init(&pSales->customersList))
//        return ERROR;
//
//
//    return FROM_USER;
//
//
//}


int addNewCustomer(Sales* pSales)
{
	Customer* pCustomer = initCustomer(pSales);
	if (!pCustomer)
		return 0;
	L_insertByNameOrder((LIST*) &pSales->customersList, pCustomer);
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
    int lengeth = (L_length((LIST*)&(pSales->customersList)) - 1);

    if (lengeth == -1) 
    {
        printf("there are NO clients\n");
       
    }
    else
    {
        printf("there are %d clients\n", lengeth);

        L_print((LIST*)&(pSales->customersList), (void (*)(const void*)) printCustomer);

        printf("\n");

    }
	

}

int insertNewCustomerToList(LIST* pList, Customer* pCustomer)
{

    NODE* pN = pList->head.next; //first Node
    NODE* pPrevNode = &pList->head;
    Customer* pTemp;
    int compRes;
    while (pN != NULL)
    {
        pTemp = (Customer*)pN->key;
        compRes = strcmp(pTemp->name, pCustomer->name);
        if (compRes == 0) //found a product with this name is cart
        {
            printf("Not new client - error!!!\n");
            return 0;
        }

        if (compRes > 0) {//found a place for new item, the next one bigger	
            if (!L_insert(pPrevNode, pCustomer))
                return 0;
            return 1;
        }
        pPrevNode = pN;
        pN = pN->next;
    }
    //insert at end
    if (!L_insert(pPrevNode, pCustomer))
        return 0;
    return 1;



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





//int makeNewReservationForCustomer(Sales* pSales, Customer* pCustomer)
//{
//	Date d;
//
//	// Create a new Reservation object
//	Reservation* pNewReservation = (Reservation*)malloc(sizeof(Reservation));
//	if (!pNewReservation) {
//		printf("Memory allocation failed for Reservation.\n");
//		return 0;
//	}
//
//	 pNewReservation->customer = pCustomer;
//	 getCorrectDate(&pNewReservation->date);
//	 pNewReservation->ReservationCode = 
//
//
//	return 0;
//}





//int addNewReservationToArray(Sales* pSales, Customer* pCustomer, char* itemsList, int itemsPrice)
//{
//    // Allocate memory for a new Reservation object
//    Reservation* pNewReservation = (Reservation*)calloc(1, sizeof(Reservation));
//    if (!pNewReservation)
//        return 0;
//
//    // Resize the reservationArray to accommodate the new reservation
//    Reservation** tempArray;
//    if (pSales->reservationArray == NULL)
//    {
//        // If reservationArray is NULL, allocate memory for the first reservation
//        tempArray = (Reservation**)malloc(sizeof(Reservation*));
//    }
//    else
//    {
//        // If reservationArray is not NULL, reallocate memory to accommodate the new reservation
//        tempArray = (Reservation**)realloc(pSales->reservationArray, (pSales->reservationCount + 1) * sizeof(Reservation*));
//    }
//
//    if (!tempArray)
//    {
//        // Memory allocation failed, free the previously allocated Reservation object
//        free(pNewReservation);
//        return 0;
//    }
//
//    pNewReservation->customer = pCustomer;
//    getCorrectDate(&pNewReservation->date);
//    pNewReservation->ReservationCode = pSales->reservationCount;
//    pNewReservation->purchasedItems = itemsList;
//    pNewReservation->priceOfOrder = itemsPrice;
//    pCustomer->totalSpent += itemsPrice;
//
//    if (pCustomer->totalSpent >= VIP_THRESH)
//        pCustomer->type = eVip;
//    else
//        pCustomer->type = eRegular;
//
//    // Assign the resized array to the reservationArray
//    pSales->reservationArray = tempArray;
//
//    // Add the new reservation to the end of the array
//    pSales->reservationArray[pSales->reservationCount] = pNewReservation;
//
//    // Increment the reservation count
//    pSales->reservationCount++;
//
//    // Reset the reservation sorting option (if needed)
//    pSales->ReservationSortOpt = eNone;
//
//    return 1; // Reservation added successfully
//}

// Function to print the list of beers
void printBeerList(Inventory* pInventory)
{
    printf("Beer List:\n");
    for (int i = 0; i < pInventory->beersCount; i++)
    {
        printf("%d. %s\n", pInventory->beerArray[i].itemSerial, pInventory->beerArray[i].brand);
    }
}

// Function to print the list of wines
void printWineList(Inventory* pInventory)
{
    printf("Wine List:\n");
    for (int i = 0; i < pInventory->winesCount; i++)
    {
        printf("%d. %s\n", pInventory->wineArray[i].itemSerial, pInventory->wineArray[i].brand);
    }
}

// Function to print the list of whiskeys
void printWhiskeyList(Inventory* pInventory)
{
    printf("Whiskey List:\n");
    for (int i = 0; i < pInventory->whiskeysCount; i++)
    {
        printf("%d. %s\n", pInventory->whiskeyArray[i].itemSerial, pInventory->whiskeyArray[i].brand);
    }
}

// Function to find a beer by serial number and update the inventory
double findBeerBySerialAndUpdate(Inventory* pInventory, int serialNumber, int numBottles)
{
    for (int i = 0; i < pInventory->beersCount; i++)
    {
        if (pInventory->beerArray[i].itemSerial == serialNumber)
        {
            if (pInventory->beerArray[i].amountAvailable >= numBottles)
            {
                double cost = pInventory->beerArray[i].price * numBottles;
                pInventory->beerArray[i].amountAvailable -= numBottles;
                return cost;
            }
            break;
        }
    }
    return 0.0;
}

// Function to find a wine by serial number and update the inventory
double findWineBySerialAndUpdate(Inventory* pInventory, int serialNumber, int numBottles)
{
    for (int i = 0; i < pInventory->winesCount; i++)
    {
        if (pInventory->wineArray[i].itemSerial == serialNumber)
        {
            if (pInventory->wineArray[i].amountAvailable >= numBottles)
            {
                double cost = pInventory->wineArray[i].price * numBottles;
                pInventory->wineArray[i].amountAvailable -= numBottles;
                return cost;
            }
            break;
        }
    }
    return 0.0;
}

// Function to find a whiskey by serial number and update the inventory
double findWhiskeyBySerialAndUpdate(Inventory* pInventory, int serialNumber, int numBottles)
{
    for (int i = 0; i < pInventory->whiskeysCount; i++)
    {
        if (pInventory->whiskeyArray[i].itemSerial == serialNumber)
        {
            if (pInventory->whiskeyArray[i].amountAvailable >= numBottles)
            {
                double cost = pInventory->whiskeyArray[i].price * numBottles;
                pInventory->whiskeyArray[i].amountAvailable -= numBottles;
                return cost;
            }
            break;
        }
    }
    return 0.0;
}

//Customer* getCustomerForReservation(Sales* pSales)
//{
//    Customer* pCustomer = NULL;
//    char choice;
//    int validChoice = 0;
//
//    while (!validChoice) {
//        //char name[MAX_NAME_LENGTH];
//
//        printf("New or existing customer? (n/e): ");
//        scanf(" %c", &choice);
//
//        if (choice == 'n' || choice == 'N')
//        {
//            if (!addNewCustomer(pCustomer))
//            {
//                return NULL;
//            }
//
//            return pCustomer;
//            validChoice = 1;
//        }
//        else if (choice == 'e' || choice == 'E') {
//            // Existing customer
//            printAllCustomers(pSales);
//            //printf("Enter customer name:\n");
//            getCustomerName(pCustomer);
//
//            Customer*   pTempCustomer = findCustomerByName(pSales, pCustomer->name);
//            if (pTempCustomer != NULL)
//            {
//                return pTempCustomer;
//            }
//            return NULL;
//            validChoice = 1;
//        }
//    }
//}

Customer* getCustomerForReservation(Sales* pSales)
{
    Customer* pCustomer = NULL;
    char choice;
    int validChoice = 0;
    char name[MAX_STR_LEN];

    while (!validChoice) {
        printf("New or existing customer? (n/e): ");
        scanf(" %c", &choice);

        // Convert input to lowercase for easier comparison
        choice = tolower(choice);

        // Check if the input is valid
        if (choice == 'n' || choice == 'e') {
            validChoice = 1;
        }
        else {
            printf("Invalid choice. Please enter 'n' for new customer or 'e' for existing customer.\n");
            // Consume any remaining characters in input buffer to prevent infinite loop
            while (getchar() != '\n');
        }
    }

    if (choice == 'n') {
        // New customer
        pCustomer = initCustomer(pSales);
        return pCustomer;
    }
    else {
        // Existing customer
        printAllCustomers(pSales);

        while (1) {
            printf("Enter a client name from the list: ");
            scanf("%s", name); // Remove the '&' before name

            pCustomer = findCustomerByName(pSales, name);
            if (pCustomer != NULL) {
                return pCustomer;
            }
            else {
                printf("Customer not found. Please enter a valid name.\n");
            }
        }
    }
}




// Function to add a new reservation to the array
int addNewReservationToArray2(Sales* pSales, Inventory* pInventory, Customer* pCustomer)
{
    // Allocate memory for a new Reservation object
    Reservation* pNewReservation = (Reservation*)calloc(1, sizeof(Reservation));
    if (!pNewReservation)
        return 0;

    // Initialize the list of purchased items
    L_init((LIST*)&pNewReservation->purchasedItems);
    double totalCost = 0.0;

    int addMoreItems = 1;
    while (addMoreItems)
    {
        // Ask the user to choose between beer, wine, or whiskey
        int choice;
        printf("\nEnter 0 for beer, 1 for wine, or 2 for whiskey: ");
        scanf("%d", &choice);

        // Print the list of drinks based on the user's choice
        if (choice == 0)
            printBeerList(pInventory);
        else if (choice == 1)
            printWineList(pInventory);
        else if (choice == 2)
            printWhiskeyList(pInventory);
        else
        {
            printf("Invalid choice.\n");
            continue;
        }

        // Ask the user to enter the serial number of the drink
        int serialNumber;
        printf("Enter the serial number of the drink: ");
        scanf("%d", &serialNumber);

        // Ask the user for the number of bottles
        int numBottles;
        printf("Enter the number of bottles: ");
        scanf("%d", &numBottles);

        // Find the drink in the inventory and update the cost
        double cost = 0.0;
        if (choice == 0)
            cost = findBeerBySerialAndUpdate(pInventory, serialNumber, numBottles);
        else if (choice == 1)
            cost = findWineBySerialAndUpdate(pInventory, serialNumber, numBottles);
        else if (choice == 2)
            cost = findWhiskeyBySerialAndUpdate(pInventory, serialNumber, numBottles);

        if (cost == 0.0)
        {
            printf("Invalid selection or insufficient bottles.\n");
            continue;
        }

        PurchasedItem* newItem = (PurchasedItem*)malloc(sizeof(PurchasedItem));
        if (newItem != NULL)
        {
            newItem->serial = serialNumber;
            newItem->amount = numBottles;
            newItem->cost = cost;
            L_insert(&pNewReservation->purchasedItems, newItem);//add .head.key//L_insert_rese 
        }
        else
        {
            printf("Memory allocation failed for newItem.\n");
            free(newItem);
        }
        totalCost += cost;

        // Ask the user if they want to add more items
        printf("Do you want to add another item? (1 for yes, 0 for no): ");
        scanf("%d", &addMoreItems);
    }

    // Resize the reservationArray to accommodate the new reservation
    Reservation** tempArray;
    if (pSales->reservationArray == NULL)
    {
        // If reservationArray is NULL, allocate memory for the first reservation
        tempArray = (Reservation**)malloc(sizeof(Reservation*));
    }
    else
    {
        // If reservationArray is not NULL, reallocate memory to accommodate the new reservation
        tempArray = (Reservation**)realloc(pSales->reservationArray, (pSales->reservationCount + 1) * sizeof(Reservation*));
    }

    if (!tempArray)
    {
        // Memory allocation failed, free the previously allocated Reservation object
        free(pNewReservation);
        return 0;
    }

    pNewReservation->customer = pCustomer;
    getCorrectDate(&pNewReservation->date);
    pNewReservation->ReservationCode = pSales->reservationCount;
    pNewReservation->priceOfOrder = totalCost;
    pCustomer->totalSpent += totalCost;

    if (pCustomer->totalSpent >= VIP_THRESH)
        pCustomer->type = eVip;
    else
        pCustomer->type = eRegular;

    // Assign the resized array to the reservationArray
    pSales->reservationArray = tempArray;

    // Add the new reservation to the end of the array
    pSales->reservationArray[pSales->reservationCount] = pNewReservation;

    // Increment the reservation count
    pSales->reservationCount++;

    // Reset the reservation sorting option (if needed)
    pSales->ReservationSortOpt = eNone;

    return 1; // Reservation added successfully
}

void printReservationsArr(struct Reservation** array, int size)
{
    if (!size)
    {
        printf("\nThere are no reservations.\n");
    }
    else
	    generalArrayFunction(array, size, sizeof(Reservation*), printReservationPtr);

}

void freeReservationsArr(struct Reservation** array, int size)
{
	generalArrayFunction(array, size, sizeof(Reservation*), freeReservationPtr);
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
	L_free((LIST*) & pSales->customersList, (void (*)(void*)) freeCustomer);//free clients

	//L_free(&(pSales->reservationList, freereservation);// free reservations 

}
