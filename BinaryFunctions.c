#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Inventory.h"
#include "BinaryFunctions.h"
#include "Filefunctions.h"

///B inventory files ///

int saveInventoryToBinaryFile(const Inventory* pInventory, const char* filename)
{
    FILE* pFile = fopen(filename, "wb");
    if (!pFile) return 0;

    // Write beer array
    if (fwrite(&pInventory->beersCount, sizeof(int), 1, pFile) != 1) return 0;
    if (!writeBeerArrToBFile(pFile, pInventory->beerArray, pInventory->beersCount)) return 0;

    // Write whiskey array
    if (fwrite(&pInventory->whiskeysCount, sizeof(int), 1, pFile) != 1) return 0;
    if (!writeWhiskeyArrToBFile(pFile, pInventory->whiskeyArray, pInventory->whiskeysCount)) return 0;

    // Write wine array
    if (fwrite(&pInventory->winesCount, sizeof(int), 1, pFile) != 1) return 0;
    if (!writeWineArrToBFile(pFile, pInventory->wineArray, pInventory->winesCount)) return 0;

    fclose(pFile);
    return 1;
}



int writeBeerToBFile(FILE* pFile, const Beer* pBeer)
{
    int len = strlen(pBeer->brand) + 1;
    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pBeer->brand, sizeof(char), len, pFile) != len) return 0;
    if (fwrite(&pBeer->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pBeer->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pBeer->price, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pBeer->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pBeer->bSize, sizeof(eBeerSize), 1, pFile) != 1) return 0;
    return 1;
}

int writeBeerArrToBFile(FILE* pFile, const Beer* pBeerArr, const int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!writeBeerToBFile(pFile, &pBeerArr[i])) return 0;
    }
    return 1;
}



int writeWhiskeyToBFile(FILE* pFile, const Whiskey* pWhiskey)
{
    int len = strlen(pWhiskey->brand) + 1;
    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pWhiskey->brand, sizeof(char), len, pFile) != len) return 0;
    if (fwrite(&pWhiskey->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pWhiskey->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pWhiskey->price, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pWhiskey->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pWhiskey->whiskeyType, sizeof(eWhiskeyType), 1, pFile) != 1) return 0;
    return 1;
}

int writeWhiskeyArrToBFile(FILE* pFile, const Whiskey* pWhiskeyArr, const int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!writeWhiskeyToBFile(pFile, &pWhiskeyArr[i])) return 0;
    }
    return 1;
}




int writeWineToBFile(FILE* pFile, const Wine* pWine)
{
    int len = strlen(pWine->brand) + 1;
    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pWine->brand, sizeof(char), len, pFile) != len) return 0;
    if (fwrite(&pWine->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pWine->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pWine->price, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pWine->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pWine->wType, sizeof(eWineType), 1, pFile) != 1) return 0;
    return 1;
}

int writeWineArrToBFile(FILE* pFile, const Wine* pWineArr, const int count) {
    for (int i = 0; i < count; i++) {
        if (!writeWineToBFile(pFile, &pWineArr[i])) return 0;
    }
    return 1;
}



void initInventoryFromBinaryFile(Inventory* pInventory, const char* filename)
{
    FILE* pFile = fopen(filename, "rb");
    if (!pFile) return;

    // Read beer array
    if (fread(&pInventory->beersCount, sizeof(int), 1, pFile) != 1) return;
    pInventory->beerArray = (Beer*)malloc(pInventory->beersCount * sizeof(Beer));
    if (!pInventory->beerArray) return;
    if (!readBeerArrFromBFile(pFile, pInventory->beerArray, pInventory->beersCount)) return;

    // Read whiskey array
    if (fread(&pInventory->whiskeysCount, sizeof(int), 1, pFile) != 1) return;
    pInventory->whiskeyArray = (Whiskey*)malloc(pInventory->whiskeysCount * sizeof(Whiskey));
    if (!pInventory->whiskeyArray) return;
    if (!readWhiskeyArrFromBFile(pFile, pInventory->whiskeyArray, pInventory->whiskeysCount)) return;

    // Read wine array
    if (fread(&pInventory->winesCount, sizeof(int), 1, pFile) != 1) return;
    pInventory->wineArray = (Wine*)malloc(pInventory->winesCount * sizeof(Wine));
    if (!pInventory->wineArray) return;
    if (!readWineArrFromBFile(pFile, pInventory->wineArray, pInventory->winesCount)) return;

    fclose(pFile);
}



int readBeerFromBFile(FILE* pFile, Beer* pBeer)
{
    int len;
    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    pBeer->brand = (char*)malloc(len * sizeof(char));
    if (!pBeer->brand) return 0;
    if (fread(pBeer->brand, sizeof(char), len, pFile) != len) return 0;
    if (fread(&pBeer->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pBeer->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pBeer->price, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pBeer->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pBeer->bSize, sizeof(eBeerSize), 1, pFile) != 1) return 0;
    return 1;
}

int readBeerArrFromBFile(FILE* pFile, Beer* pBeerArr, const int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!readBeerFromBFile(pFile, &pBeerArr[i])) return 0;
    }
    return 1;
}



int readWhiskeyFromBFile(FILE* pFile, Whiskey* pWhiskey)
{
    int len;
    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    pWhiskey->brand = (char*)malloc(len * sizeof(char));
    if (!pWhiskey->brand) return 0;
    if (fread(pWhiskey->brand, sizeof(char), len, pFile) != len) return 0;
    if (fread(&pWhiskey->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pWhiskey->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pWhiskey->price, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pWhiskey->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pWhiskey->whiskeyType, sizeof(eWhiskeyType), 1, pFile) != 1) return 0;
    return 1;
}

int readWhiskeyArrFromBFile(FILE* pFile, Whiskey* pWhiskeyArr, const int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!readWhiskeyFromBFile(pFile, &pWhiskeyArr[i])) return 0;
    }
    return 1;
}



int readWineFromBFile(FILE* pFile, Wine* pWine)
{
    int len;
    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    pWine->brand = (char*)malloc(len * sizeof(char));
    if (!pWine->brand) return 0;
    if (fread(pWine->brand, sizeof(char), len, pFile) != len) return 0;
    if (fread(&pWine->itemSerial, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pWine->amountAvailable, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pWine->price, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pWine->numOfSolds, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pWine->wType, sizeof(eWineType), 1, pFile) != 1) return 0;
    return 1;
}

int readWineArrFromBFile(FILE* pFile, Wine* pWineArr, const int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!readWineFromBFile(pFile, &pWineArr[i])) return 0;
    }
    return 1;
}





///B inventory files ///







int writeCustomerListToBFile(const Sales* pSales, FILE* fileName)
{
    FILE* pFile = fopen(fileName, "wb");
    if (!pFile)
    {
        printf("Error opening file for writing customer list.\n");
        return 0;
    }

    int count = L_length(&pSales->customersList) - 1;
    if (!writeIntToFile(count, pFile, "Error writing customer count"))
    {
        fclose(pFile);
        return 0;
    }

    NODE* pNode = pSales->customersList.head.next;
    while (pNode != NULL)
    {
        Customer* pCustomer = (Customer*)pNode->key;
        if (!writeStringToFile(pCustomer->name, pFile, "Error writing customer name"))
        {
            fclose(pFile);
            return 0;
        }
        if (!writeDoubleToFile(pCustomer->totalSpent, pFile, "Error writing customer total spent"))
        {
            fclose(pFile);
            return 0;
        }
        if (!writeIntToFile(pCustomer->type, pFile, "Error writing customer type"))
        {
            fclose(pFile);
            return 0;
        }

        pNode = pNode->next;
    }

    fclose(pFile);
    return 1;
}





int readCustomerListFromBFile(Sales* pSales, const FILE* fileName)
{
    FILE* pFile = fopen(fileName, "rb");
    if (!pFile)
    {
        printf("Error opening file for reading customer list.\n");
        return 0;
    }

    int count;
    if (!readIntFromFile(&count, pFile, "Error reading customer count"))
    {
        fclose(pFile);
        return 0;
    }

    L_init(&pSales->customersList);

    for (int i = 0; i < count; i++)
    {
        Customer* pCustomer = (Customer*)malloc(sizeof(Customer));
        if (!pCustomer)
        {
            fclose(pFile);
            return 0;
        }

        pCustomer->name = readStringFromFile(pFile, "Error reading customer name");
        if (!pCustomer->name)
        {
            free(pCustomer);
            fclose(pFile);
            return 0;
        }



        //double totalSpent;
        if (!readDoubleFromFile(&pCustomer->totalSpent, pFile, "Error reading customer total spent"))
        {
            free(pCustomer->name);
            free(pCustomer);
            fclose(pFile);
            return 0;
        }
        //pCustomer->totalSpent = ;



        int type;
        if (!readIntFromFile(&type, pFile, "Error reading customer type"))
        {
            free(pCustomer->name);
            free(pCustomer);
            fclose(pFile);
            return 0;
        }
        pCustomer->type = (eCustomerType)type;

        NODE* pNode = pSales->customersList.head.next;
        if (pNode == NULL)
        {
            L_insert(&pSales->customersList.head, pCustomer);
        }
        else
        {
            while (pNode->next != NULL)
            {
                pNode = pNode->next;
            }
            L_insert(pNode, pCustomer);
        }
    }

    fclose(pFile);
    return 1;
}




//// reservation///

//// Function to load reservations from a binary file
//int loadReservationsFromBinaryFile(Sales* pSales, const char* filename)
//{
//    FILE* file = fopen(filename, "rb");
//    if (file == NULL)
//    {
//        printf("Failed to open file: %s\n", filename);
//        return 0;
//    }
//
//    // Read the number of reservations
//    int count;
//    fread(&count, sizeof(int), 1, file);
//
//    // Allocate memory for the reservation array
//    pSales->reservationArray = (Reservation**)malloc(count * sizeof(Reservation*));
//    if (pSales->reservationArray == NULL)
//    {
//        printf("Memory allocation failed for reservation array.\n");
//        fclose(file);
//        return 0;
//    }
//
//    // Read each reservation from the file
//    for (int i = 0; i < count; i++)
//    {
//        Reservation* reservation = (Reservation*)malloc(sizeof(Reservation));
//        if (reservation == NULL)
//        {
//            printf("Memory allocation failed for reservation.\n");
//            fclose(file);
//            return 0;
//        }
//
//        // Read reservation data from the file
//        fread(reservation, sizeof(Reservation), 1, file);
//        // Read other reservation fields as needed
//
//        pSales->reservationArray[i] = reservation;
//    }
//
//    pSales->reservationCount = count;
//    fclose(file);
//    return 1;
//}
//
//// Function to save reservations to a binary file
//int saveReservationsToBinaryFile(const Sales* pSales, const char* filename)
//{
//    FILE* file = fopen(filename, "wb");
//    if (file == NULL)
//    {
//        printf("Failed to open file: %s\n", filename);
//        return 0;
//    }
//
//    // Write the number of reservations
//    fwrite(&pSales->reservationCount, sizeof(int), 1, file);
//
//    // Write each reservation to the file
//    for (int i = 0; i < pSales->reservationCount; i++)
//    {
//        Reservation* reservation = pSales->reservationArray[i];
//        fwrite(reservation, sizeof(Reservation), 1, file);
//        // Write other reservation fields as needed
//    }
//
//    fclose(file);
//    return 1;
//}



// Function to save a single reservation to a binary file
void saveReservationToBinaryFile(const Reservation* reservation, FILE* file)
{
    fwrite(&reservation->ReservationCode, sizeof(int), 1, file);

    int nameLength = strlen(reservation->customer->name) + 1;
    fwrite(&nameLength, sizeof(int), 1, file);
    fwrite(reservation->customer->name, sizeof(char), nameLength, file);

    fwrite(&reservation->customer->type, sizeof(eCustomerType), 1, file);
    fwrite(&reservation->date, sizeof(Date), 1, file);
    fwrite(&reservation->priceOfOrder, sizeof(double), 1, file);

    // Save purchased items
    int itemCount = L_length(&reservation->purchasedItems)-1;//-1
    fwrite(&itemCount, sizeof(int), 1, file);
    NODE* pNode = reservation->purchasedItems.head.next;
    while (pNode != NULL)
    {
        PurchasedItem* item = (PurchasedItem*)pNode->key;
        fwrite(item, sizeof(PurchasedItem), 1, file);
        pNode = pNode->next;
    }
}

// Function to load a single reservation from a binary file
Reservation* loadReservationFromBinaryFile(Sales* pSales, FILE* file)
{
    Reservation* reservation = (Reservation*)malloc(sizeof(Reservation));
    if (reservation == NULL)
    {
        printf("Memory allocation failed for reservation.\n");
        return NULL;
    }

    // Read reservation data from the file
    fread(&reservation->ReservationCode, sizeof(int), 1, file);

    // Read customer name
    int nameLength;
    fread(&nameLength, sizeof(int), 1, file);
    char* customerName = (char*)malloc(nameLength * sizeof(char));
    fread(customerName, sizeof(char), nameLength, file);
    reservation->customer = findCustomerByName(pSales, customerName);
    free(customerName);

    // Read customer type
    fread(&reservation->customer->type, sizeof(eCustomerType), 1, file);

    // Read date
    fread(&reservation->date, sizeof(Date), 1, file);

    fread(&reservation->priceOfOrder, sizeof(double), 1, file);

    // Read purchased items
    int itemCount;
    fread(&itemCount, sizeof(int), 1, file);
    L_init(&reservation->purchasedItems);
    for (int j = 0; j < itemCount; j++)
    {
        PurchasedItem* item = (PurchasedItem*)malloc(sizeof(PurchasedItem));
        fread(item, sizeof(PurchasedItem), 1, file);
        L_insert(&reservation->purchasedItems, item);
    }

    return reservation;
}

//// Function to load a single reservation from a binary file
//Reservation* loadReservationFromBinaryFile(Sales* pSales, FILE* file)
//{
//    Reservation* reservation = (Reservation*)malloc(sizeof(Reservation));
//    if (reservation == NULL)
//    {
//        printf("Memory allocation failed for reservation.\n");
//        return NULL;
//    }
//
//    // Read reservation data from the file
//    fread(&reservation->ReservationCode, sizeof(int), 1, file);
//
//    // Read customer name
//    int nameLength;
//    fread(&nameLength, sizeof(int), 1, file);
//    char* customerName = (char*)malloc(nameLength * sizeof(char));
//    if (customerName == NULL)
//    {
//        printf("Memory allocation failed for customer name.\n");
//        free(reservation);
//        return NULL;
//    }
//    fread(customerName, sizeof(char), nameLength, file);
//
//    // Find the customer by name
//    reservation->customer = findCustomerByName(pSales, customerName);
//    if (reservation->customer == NULL)
//    {
//        printf("Customer not found: %s\n", customerName);
//        free(customerName);
//        free(reservation);
//        return NULL;
//    }
//    free(customerName);
//
//    // Read customer type
//    fread(&reservation->customer->type, sizeof(eCustomerType), 1, file);
//
//    // Read date
//    fread(&reservation->date, sizeof(Date), 1, file);
//
//    fread(&reservation->priceOfOrder, sizeof(double), 1, file);
//
//    // Read purchased items
//    int itemCount;
//    fread(&itemCount, sizeof(int), 1, file);
//    L_init(&reservation->purchasedItems);
//    for (int j = 0; j < itemCount; j++)
//    {
//        PurchasedItem* item = (PurchasedItem*)malloc(sizeof(PurchasedItem));
//        if (item == NULL)
//        {
//            printf("Memory allocation failed for purchased item.\n");
//            freeReservationPtr(reservation);
//            return NULL;
//        }
//        fread(item, sizeof(PurchasedItem), 1, file);
//        L_insert(&reservation->purchasedItems, item);
//    }
//
//    return reservation;
//}



// Function to load reservations from a binary file
int loadReservationsArrayFromBinaryFile(Sales* pSales, const char* filename)
{
    FILE* file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }

    // Read the number of reservations
    int count;
    fread(&count, sizeof(int), 1, file);

    // Allocate memory for the reservation array
    pSales->reservationArray = (Reservation**)malloc(count * sizeof(Reservation*));
    if (pSales->reservationArray == NULL)
    {
        printf("Memory allocation failed for reservation array.\n");
        fclose(file);
        return 0;
    }

    // Read each reservation from the file
    for (int i = 0; i < count; i++)
    {
        Reservation* reservation = loadReservationFromBinaryFile(pSales, file);
        if (reservation == NULL)
        {
            fclose(file);
            return 0;
        }
        pSales->reservationArray[i] = reservation;
    }

    pSales->reservationCount = count;
    fclose(file);
    return 1;
}

// Function to save reservations to a binary file
int saveReservationsArrayToBinaryFile(const Sales* pSales, const char* filename)
{
    FILE* file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }

    // Write the number of reservations
    fwrite(&pSales->reservationCount, sizeof(int), 1, file);

    // Write each reservation to the file
    for (int i = 0; i < pSales->reservationCount; i++)
    {
        Reservation* reservation = pSales->reservationArray[i];
        saveReservationToBinaryFile(reservation, file);
    }

    fclose(file);
    return 1;
}




int	 writeStringToComprassFile(const char* str, FILE* fp, const char* msg)
{

    if (!writeCharsToFile(str, strlen(str), fp, msg))
        return 0;


    return 1;
}