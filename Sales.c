#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Sales.h"
#include "list.h"
#include "Reservation.h"
#include "GeneralFunctions.h"
#include "Customer.h"
#include "Filefunctions.h"

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

int saveSalesToTextFile(Sales* pSales, FILE* customerFileName, FILE* reservationFileName)
{
     saveCustomerListToTextFile(pSales, (char*)customerFileName);
     saveReservationsArrayToTextFile(pSales, (char*)reservationFileName);
            
   
    return 1;
}

int saveSalesToBinaryFile(Sales* pSales, FILE* customerFileName, FILE* reservationFileName)
{
    writeCustomerListToBFile(pSales, (char*)customerFileName);
    saveReservationsArrayToBinaryFile(pSales, (char*)reservationFileName);
    return 1;
}


int addNewCustomer(Sales* pSales)
{
	Customer* pCustomer = initCustomer(pSales);
	if (!pCustomer)
		return 0;
	//L_insertByNameOrder((LIST*) &pSales->customersList, pCustomer);////!!!
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
    insertNewCustomerToList(&pSales->customersList,pCustomer);
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
//creative2
void findTopCustomers(const Sales* pSales, int topN)
{
    if (topN <= 0 || topN > L_length(&pSales->customersList))
    {
        printf("Invalid number of top customers.\n");
        return;
    }

    // Create an array of Customer pointers
    Customer** customers = (Customer**)malloc(sizeof(Customer*) * (size_t)(L_length(&pSales->customersList)-1));//-1//size_t
    if (customers == NULL)
    {
        printf("Memory allocation failed for customers array.\n");
        return;
    }

    // Copy Customer pointers from the linked list to the array
    NODE* current = pSales->customersList.head.next;
    int index = 0;
    while (current != NULL)
    {
        customers[index++] = (Customer*)current->key;
        current = current->next;
    }

    // Sort the customers array based on total spent amount in descending order
    qsort(customers, (size_t)L_length(&pSales->customersList)-1, sizeof(Customer*), compareCustomersByTotalSpent);//(size_t)

    // Print the top N customers
    printf("Top %d customers by total spent amount:\n", topN);
    for (int i = 0; i < topN && i < L_length(&pSales->customersList)-1; i++)
    {
        printf("%d. %s - Total Spent: $%.2f\n", i + 1, customers[i]->name, customers[i]->totalSpent);
    }

    free(customers);
}


////RESERVATIONS////



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
                pInventory->beerArray[i].numOfSolds += numBottles;
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
                pInventory->wineArray[i].numOfSolds += numBottles;
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
                pInventory->whiskeyArray[i].numOfSolds += numBottles;
                return cost;
            }
            break;
        }
    }
    return 0.0;
}




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
        pCustomer =  initCustomer(pSales);//addNewCustomer(pSales);//need to return
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
void printDrinkList(Inventory* pInventory, int choice)
{
    if (choice == 0)
        printBeerList(pInventory);
    else if (choice == 1)
        printWineList(pInventory);
    else if (choice == 2)
        printWhiskeyList(pInventory);
}

int getDrinkSerialNumber()
{
    int serialNumber;
    printf("Enter the serial number of the drink: ");
    scanf("%d", &serialNumber);
    return serialNumber;
}

int getNumBottles()
{
    int numBottles;
    printf("Enter the number of bottles: ");
    scanf("%d", &numBottles);
    return numBottles;
}

double updateInventoryAndGetCost(Inventory* pInventory, int choice, int serialNumber, int numBottles)
{
    double cost = 0.0;
    if (choice == 0)
        cost = findBeerBySerialAndUpdate(pInventory, serialNumber, numBottles);
    else if (choice == 1)
        cost = findWineBySerialAndUpdate(pInventory, serialNumber, numBottles);
    else if (choice == 2)
        cost = findWhiskeyBySerialAndUpdate(pInventory, serialNumber, numBottles);
    return cost;
}


void addPurchasedItemToReservation(Reservation* pNewReservation, int serialNumber, int numBottles, double cost)
{
    // Reallocate memory for the array of purchased items
    PurchasedItem* newItems = (PurchasedItem*)realloc(pNewReservation->purchasedItems, sizeof(PurchasedItem) * ((size_t)pNewReservation->numPurchasedItems + 1));//(size_t)
    if (newItems == NULL) {
        printf("Memory allocation failed for new item.\n");
        return;
    }

    pNewReservation->purchasedItems = newItems;

    // Add the new item to the array
    pNewReservation->purchasedItems[pNewReservation->numPurchasedItems].serial = serialNumber;
    pNewReservation->purchasedItems[pNewReservation->numPurchasedItems].amount = numBottles;
    pNewReservation->purchasedItems[pNewReservation->numPurchasedItems].costInt = (int)cost;
    pNewReservation->purchasedItems[pNewReservation->numPurchasedItems].costDec = (int)((cost - pNewReservation->purchasedItems[pNewReservation->numPurchasedItems].costInt) * 100);

    pNewReservation->numPurchasedItems++;
}

//int addNewReservationToArray2(Sales* pSales, Inventory* pInventory, Customer* pCustomer)
//{
//    // Allocate memory for a new Reservation object
//    Reservation* pNewReservation = (Reservation*)calloc(1, sizeof(Reservation));
//    if (!pNewReservation)
//        return 0;
//
//    double totalCost = 0.0;
//
//    int addMoreItems = 1;
//    while (addMoreItems)
//    {
//        // Ask the user to choose between beer, wine, or whiskey
//        int choice;
//        printf("\nEnter 0 for beer, 1 for wine, or 2 for whiskey: ");
//        scanf("%d", &choice);
//
//        // Print the list of drinks based on the user's choice
//        printDrinkList(pInventory, choice);
//
//        // Ask the user to enter the serial number of the drink
//        int serialNumber = getDrinkSerialNumber();
//
//        // Ask the user for the number of bottles
//        int numBottles = getNumBottles();
//
//        // Find the drink in the inventory and update the cost
//        double cost = updateInventoryAndGetCost(pInventory, choice, serialNumber, numBottles);
//
//        if (cost == 0.0)
//        {
//            printf("Invalid selection or insufficient bottles.\n");
//            continue;
//        }
//
//        // Add the purchased item to the reservation
//        PurchasedItem* newItem = (PurchasedItem*)realloc(pNewReservation->purchasedItems, ((size_t)pNewReservation->numPurchasedItems + 1) * sizeof(PurchasedItem));//(size_t)
//        if (newItem == NULL)
//        {
//            printf("Memory allocation failed for new item.\n");
//            free(pNewReservation->purchasedItems);
//            free(pNewReservation);
//            return 0;
//        }
//        pNewReservation->purchasedItems = newItem;
//
//        PurchasedItem* item = &(pNewReservation->purchasedItems[pNewReservation->numPurchasedItems]);
//        item->serial = serialNumber;
//        item->amount = numBottles;
//        item->costInt = (int)cost;
//        item->costDec = (int)((cost - item->costInt) * 100);
//
//        pNewReservation->numPurchasedItems++;
//        totalCost += cost;
//
//        // Ask the user if they want to add more items
//        printf("Do you want to add another item? (1 for yes, 0 for no): ");
//        scanf("%d", &addMoreItems);
//    }
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
//        tempArray = (Reservation**)realloc(pSales->reservationArray, ((size_t)pSales->reservationCount + 1) * sizeof(Reservation*));//(size_t)
//    }
//
//    if (!tempArray)
//    {
//        // Memory allocation failed, free the previously allocated Reservation object
//        free(pNewReservation->purchasedItems);
//        free(pNewReservation);
//        return 0;
//    }
//
//    pNewReservation->customer = pCustomer;
//    getCorrectDate(&pNewReservation->date);
//    pNewReservation->ReservationCode = pSales->reservationCount;
//    pNewReservation->priceOfOrder = totalCost;
//    pCustomer->totalSpent += totalCost;
//
//    if (pCustomer->totalSpent >= VIP_THRESH)
//        pCustomer->type = eVip;
//    else
//        pCustomer->type = eRegular;
//
//    // Assign the resized array to the reservationArray
//    pSales->reservationArray = (struct Reservation**)tempArray;
//
//    // Add the new reservation to the end of the array
//    pSales->reservationArray[pSales->reservationCount] = (struct Reservation*)pNewReservation;
//
//    // Increment the reservation count
//    pSales->reservationCount++;
//
//    // Reset the reservation sorting option (if needed)
//    pSales->ReservationSortOpt = eNone;
//
//    return 1; // Reservation added successfully
//}
int addNewReservationToArray2(Sales* pSales, Inventory* pInventory, Customer* pCustomer)
{
    // Allocate memory for a new Reservation object
    Reservation* pNewReservation = (Reservation*)calloc(1, sizeof(Reservation));
    if (!pNewReservation)
        return 0;

    double totalCost = 0.0;

    int addMoreItems = 1;
    int itemCount = 0;
    while (addMoreItems && itemCount < 9)
    {
        // Ask the user to choose between beer, wine, or whiskey
        int choice;
        printf("\nEnter 0 for beer, 1 for wine, or 2 for whiskey: ");
        scanf("%d", &choice);

        // Print the list of drinks based on the user's choice
        printDrinkList(pInventory, choice);

        // Ask the user to enter the serial number of the drink
        int serialNumber = getDrinkSerialNumber();

        // Ask the user for the number of bottles
        int numBottles = getNumBottles();

        // Find the drink in the inventory and update the cost
        double cost = updateInventoryAndGetCost(pInventory, choice, serialNumber, numBottles);

        if (cost == 0.0)
        {
            printf("Invalid selection or insufficient bottles.\n");
            continue;
        }

        // Check if adding the item would exceed the total amount limit of $10,000
        if (totalCost + cost > 10000)
        {
            printf("Adding this item would exceed the total amount limit of $10,000. Item not added.\n");
            continue;
        }

        // Add the purchased item to the reservation
        PurchasedItem* newItem = (PurchasedItem*)realloc(pNewReservation->purchasedItems, ((size_t)pNewReservation->numPurchasedItems + 1) * sizeof(PurchasedItem));//(size_t)
        if (newItem == NULL)
        {
            printf("Memory allocation failed for new item.\n");
            free(pNewReservation->purchasedItems);
            free(pNewReservation);
            return 0;
        }
        pNewReservation->purchasedItems = newItem;

        PurchasedItem* item = &(pNewReservation->purchasedItems[pNewReservation->numPurchasedItems]);
        item->serial = serialNumber;
        item->amount = numBottles;
        item->costInt = (int)cost;
        item->costDec = (int)((cost - item->costInt) * 100);

        pNewReservation->numPurchasedItems++;
        totalCost += cost;
        itemCount++;

        // Ask the user if they want to add more items
        if (itemCount < 9)
        {
            printf("Do you want to add another item? (1 for yes, 0 for no): ");
            scanf("%d", &addMoreItems);
        }
        else
        {
            printf("Maximum number of items (9) reached. Cannot add more items.\n");
            addMoreItems = 0;
        }
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
        tempArray = (Reservation**)realloc(pSales->reservationArray, ((size_t)pSales->reservationCount + 1) * sizeof(Reservation*));//(size_t)
    }

    if (!tempArray)
    {
        // Memory allocation failed, free the previously allocated Reservation object
        free(pNewReservation->purchasedItems);
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
    pSales->reservationArray = (struct Reservation**)tempArray;

    // Add the new reservation to the end of the array
    pSales->reservationArray[pSales->reservationCount] = (struct Reservation*)pNewReservation;

    // Increment the reservation count
    pSales->reservationCount++;

    // Reset the reservation sorting option (if needed)
    pSales->ReservationSortOpt = eNone;

    return 1; // Reservation added successfully
}

void printReservationsArr(struct Reservation** array, int size)//struct
{
    if (!size)
    {
        printf("\nThere are no reservations.\n");
    }
    else
	    generalArrayFunction(array, size, sizeof(Reservation*), printReservationPtr);

}

void freeReservationsArr(struct Reservation** array, int size)//struct
{
	generalArrayFunction(array, size, sizeof(Reservation*), freeReservationPtr);
}










//
//
//void findReservation(const Sales* pSales) {
//    if (pSales->reservationCount == 0) {
//        printf("There are no reservations.\n");
//        return;
//    }
//
//    int(*compare)(const void* rese1, const void* rese2) = NULL;
//
//    switch (pSales->ReservationSortOpt) {
//    case eResCode:
//        printf("Enter the Reservation Code: ");
//        compare = compareReseravationByReservatinCode;
//        break;
//
//    case eCustomerName:
//        printf("Enter the Customer Name: ");
//        compare = compareReseravationByCustomerName;
//        break;
//
//    case eDate:
//        printf("Enter the Date (DD/MM/YYYY): ");
//        compare = compareReseravationByDate;
//        break;
//
//    default:
//        printf("Invalid - Reservations Are Not Sorted\n");
//        return;
//    }
//
//    Reservation tempReservation = { 0 };//= {0}
//    Reservation* pTempReservation = &tempReservation;
//
//    // Allocate memory for the customer field
//    pTempReservation->customer = (Customer*)malloc(sizeof(Customer));
//    if (pTempReservation->customer == NULL) {
//        printf("Memory allocation failed for customer.\n");
//        return;
//    }
//
//    switch (pSales->ReservationSortOpt) {
//    case eResCode:
//        scanf("%d", &pTempReservation->ReservationCode);
//        break;
//
//    case eCustomerName:
//        // Allocate memory for the customer name
//        pTempReservation->customer->name = (char*)malloc(sizeof(char) * MAX_STR_LEN);
//        if (pTempReservation->customer->name == NULL) {
//            printf("Memory allocation failed for customer name.\n");
//            free(pTempReservation->customer);
//            return;
//        }
//        scanf("%s", pTempReservation->customer->name);
//        break;
//
//    case eDate:
//        scanf("%d/%d/%d", &pTempReservation->date.day, &pTempReservation->date.month, &pTempReservation->date.year);
//        break;
//    }
//
//    Reservation** pFoundReservation = bsearch(&pTempReservation, pSales->reservationArray, pSales->reservationCount, sizeof(Reservation*), compare);
//
//    // Free the allocated memory for the customer field and name
//    free(pTempReservation->customer->name);
//    free(pTempReservation->customer);//exp
//
//    if (pFoundReservation == NULL)
//        printf("Reservation was not found\n");
//    else {
//        printf("Reservation found:\n");
//        printReservation(*pFoundReservation);
//    }
//}


void findReservation(const Sales* pSales) {
    if (pSales->reservationCount == 0) {
        printf("There are no reservations.\n");
        return;
    }

    int(*compare)(const void* rese1, const void* rese2) = NULL;

    switch (pSales->ReservationSortOpt) {
    case eResCode:
        printf("Enter the Reservation Code: ");
        compare = compareReseravationByReservatinCode;
        break;

    case eCustomerName:
        printf("Enter the Customer Name: ");
        compare = compareReseravationByCustomerName;
        break;

    case eDate:
        printf("Enter the Date (DD/MM/YYYY): ");
        compare = compareReseravationByDate;
        break;

    default:
        printf("Invalid - Reservations Are Not Sorted\n");
        return;
    }

    Reservation tempReservation = { 0 };
    Reservation* pTempReservation = &tempReservation;

    // Allocate memory for the customer field
    pTempReservation->customer = (Customer*)malloc(sizeof(Customer));
    if (pTempReservation->customer == NULL) {
        printf("Memory allocation failed for customer.\n");
        return;
    }

    switch (pSales->ReservationSortOpt) {
    case eResCode:
        scanf("%d", &pTempReservation->ReservationCode);
        break;

    case eCustomerName:
        // Allocate memory for the customer name
        pTempReservation->customer->name = (char*)malloc(sizeof(char) * MAX_STR_LEN);
        if (pTempReservation->customer->name == NULL) {
            printf("Memory allocation failed for customer name.\n");
            free(pTempReservation->customer);
            return;
        }
        scanf("%s", pTempReservation->customer->name);
        break;

    case eDate:
        scanf("%d/%d/%d", &pTempReservation->date.day, &pTempReservation->date.month, &pTempReservation->date.year);
        break;
    }

    Reservation** pFoundReservation = bsearch(&pTempReservation, pSales->reservationArray, pSales->reservationCount, sizeof(Reservation*), compare);

    // Free the allocated memory for the customer field and name
    if (pSales->ReservationSortOpt == eCustomerName && pTempReservation->customer->name != NULL) {
        free(pTempReservation->customer->name);
    }
    free(pTempReservation->customer);

    if (pFoundReservation == NULL)
        printf("Reservation was not found\n");
    else {
        printf("Reservation found:\n");
        printReservation(*pFoundReservation);
    }
}



void sortReservations(Sales* pSales)
{
    int(*compare)(const void* rese1, const void* rese2) = NULL;

    eSortOption sortOption = showSortMenu();
    pSales->ReservationSortOpt = sortOption;

    switch (sortOption)
    {
    case eResCode:
        compare = compareReseravationByReservatinCode;
        break;

    case eCustomerName:
        compare = compareReseravationByCustomerName;
        break;

    case eDate:
        compare = compareReseravationByDate;
        break;

    default:
        printf("Invalid sort option\n");
        return;
    }

    qsort(pSales->reservationArray, pSales->reservationCount, sizeof(Reservation*), compare);
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



//i want to fix the sortReservations and findReservation functions.
//
//the sortReservations  meant to show  showSortMenu and based on the pick sort the reservation array by order of pick.
//
//
//
//findReservation meant to find and reservation





void freeSales(Sales* pSales)
{
	L_free((LIST*) & pSales->customersList, (void (*)(void*)) freeCustomer);//free clients
    freeReservationsArr(pSales->reservationArray,pSales->reservationCount);//free reservations 
    free(pSales->reservationArray);
}
