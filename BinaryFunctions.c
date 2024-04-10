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
    int len = (int)strlen(pBeer->brand) + 1;
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
    int len = (int)strlen(pWhiskey->brand) + 1;
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
    int len =(int)strlen(pWine->brand) + 1;
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


int initInventoryFromBinaryFile(Inventory* pInventory, const char* filename)
{
    FILE* fp = fopen(filename, "rb");

    if (!fp)
    {
        printf("Failed to open file: %s\n", filename);
        return 0;  // Return 0 to indicate failure
    }
    //CHECK_PRINT_RETURN_0(fp, "Failed to open file: %s\n", filename);

    // Read beer array
    if (fread(&pInventory->beersCount, sizeof(int), 1, fp) != 1) 
    {
        CLOSE_FILE_RETURN_0(fp); // Return 0 to indicate failure
    }
    pInventory->beerArray = (Beer*)malloc(pInventory->beersCount * sizeof(Beer));
    if (!pInventory->beerArray)
    {
        CLOSE_FILE_RETURN_0(fp);  // Return 0 to indicate failure
    }
    if (!readBeerArrFromBFile(fp, pInventory->beerArray, pInventory->beersCount)) 
    {
        CLOSE_FILE_RETURN_0(fp);  // Return 0 to indicate failure
    }

    // Read whiskey array
    if (fread(&pInventory->whiskeysCount, sizeof(int), 1, fp) != 1)
    {
        CLOSE_FILE_RETURN_0(fp); // Return 0 to indicate failure
    }
    pInventory->whiskeyArray = (Whiskey*)malloc(pInventory->whiskeysCount * sizeof(Whiskey));
    if (!pInventory->whiskeyArray) 
    {
        CLOSE_FILE_RETURN_0(fp);  // Return 0 to indicate failure
    }
    if (!readWhiskeyArrFromBFile(fp, pInventory->whiskeyArray, pInventory->whiskeysCount))
    {
        CLOSE_FILE_RETURN_0(fp); // Return 0 to indicate failure
    }

    // Read wine array
    if (fread(&pInventory->winesCount, sizeof(int), 1, fp) != 1) 
    {
        CLOSE_FILE_RETURN_0(fp);  // Return 0 to indicate failure
    }
    pInventory->wineArray = (Wine*)malloc(pInventory->winesCount * sizeof(Wine));
    if (!pInventory->wineArray)
    {
        CLOSE_FILE_RETURN_0(fp);  // Return 0 to indicate failure
    }
    if (!readWineArrFromBFile(fp, pInventory->wineArray, pInventory->winesCount))
    {
        CLOSE_FILE_RETURN_0(fp);  // Return 0 to indicate failure
    }

   /* fclose(fp);
    return 1; */
    CLOSE_FILE_RETURN_1(fp);// Return 1 to indicate success
}




int writeCustomerListToBFile(const Sales* pSales, FILE* fileName)
{
    FILE* fp = fopen(fileName, "wb");
    /*if (!fp)
    {
        printf("Error opening file for writing customer list.\n");
        return 0;
    }*/
    CHECK_PRINT_RETURN_0(fp, "Error opening file for writing customer list.")

    int count = L_length(&pSales->customersList) - 1;
    if (!writeIntToFile(count, fp, "Error writing customer count"))
    {
        CLOSE_FILE_RETURN_0(fp);
    }

    NODE* pNode = pSales->customersList.head.next;
    while (pNode != NULL)
    {
        Customer* pCustomer = (Customer*)pNode->key;
        if (!writeStringToFile(pCustomer->name, fp, "Error writing customer name"))
        {
            CLOSE_FILE_RETURN_0(fp);
        }
        if (!writeDoubleToFile(pCustomer->totalSpent, fp, "Error writing customer total spent"))
        {
            CLOSE_FILE_RETURN_0(fp);
        }
        if (!writeIntToFile(pCustomer->type, fp, "Error writing customer type"))
        {
            CLOSE_FILE_RETURN_0(fp);
        }

        pNode = pNode->next;
    }

    /*fclose(fp);
    return 1;*/
    CLOSE_FILE_RETURN_1(fp);
}





int readCustomerListFromBFile(Sales* pSales, const FILE* fileName)
{
    FILE* fp = fopen(fileName, "rb");

   /* if (!fp)
    {
        printf("Error opening file for reading customer list.\n");
        return 0;
    }*/
    CHECK_PRINT_RETURN_0(fp, "Error opening file for reading customer list.");

    int count;
    if (!readIntFromFile(&count, fp, "Error reading customer count"))
    {
        CLOSE_FILE_RETURN_0(fp);
    }

    L_init(&pSales->customersList);

    for (int i = 0; i < count; i++)
    {
        Customer* pCustomer = (Customer*)malloc(sizeof(Customer));
        if (!pCustomer)
        {
            CLOSE_FILE_RETURN_0(fp);
        }

        pCustomer->name = readStringFromFile(fp, "Error reading customer name");
        if (!pCustomer->name)
        {
            free(pCustomer);
            CLOSE_FILE_RETURN_0(fp);
        }



        //double totalSpent;
        if (!readDoubleFromFile(&pCustomer->totalSpent, fp, "Error reading customer total spent"))
        {
            free(pCustomer->name);
            free(pCustomer);
            CLOSE_FILE_RETURN_0(fp);
        }
        //pCustomer->totalSpent = ;



        int type;
        if (!readIntFromFile(&type, fp, "Error reading customer type"))
        {
            free(pCustomer->name);
            free(pCustomer);
            CLOSE_FILE_RETURN_0(fp);
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

    /*fclose(fp);
    return 1;*/
    CLOSE_FILE_RETURN_1(fp);
}




//// reservation///



// Function to save a single reservation to a binary file
void saveReservationToBinaryFile(const Reservation* reservation, FILE* file)
{
    fwrite(&reservation->ReservationCode, sizeof(int), 1, file);

    int nameLength =(int) strlen(reservation->customer->name) + 1;
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
        if (!savePurchasedItemToCompressedFile(item, file))
        {
            printf("Error saving purchased item to file\n");
            return;
        }
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
        if (!loadPurchasedItemFromCompressedFile(item, file))
        {
            printf("Error loading purchased item from file\n");
            freeReservationPtr(reservation);
            return NULL;
        }
        L_insert(&reservation->purchasedItems, item);
    }

    return reservation;


}








// Function to load reservations from a binary file
int loadReservationsArrayFromBinaryFile(Sales* pSales, const char* filename)
{
    FILE* fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }
   // CHECK_PRINT_RETURN_0(fp, "Failed to open file: %s", filename);

    // Read the number of reservations
    int count;
    fread(&count, sizeof(int), 1, fp);

    // Allocate memory for the reservation array
    pSales->reservationArray = (Reservation**)malloc(count * sizeof(Reservation*));
    if (pSales->reservationArray == NULL)
    {
        printf("Memory allocation failed for reservation array.\n");
        CLOSE_FILE_RETURN_0(fp)
    }

    // Read each reservation from the file
    for (int i = 0; i < count; i++)
    {
        Reservation* reservation = loadReservationFromBinaryFile(pSales, fp);
        if (reservation == NULL)
        {
            CLOSE_FILE_RETURN_0(fp)
        }
        pSales->reservationArray[i] = reservation;
    }

    pSales->reservationCount = count;
    /*fclose(fp);
    return 1;*/
    CLOSE_FILE_RETURN_1(fp);
}




// Function to save reservations to a binary file
int saveReservationsArrayToBinaryFile(const Sales* pSales, const char* filename)
{
    FILE* fp = fopen(filename, "wb");
    if (fp == NULL)
    {
        printf("Failed to open file: %s\n", filename);
        return 0;
    }
    //CHECK_PRINT_RETURN_0(fp, "Failed to open file: %s", filename);
    // Write the number of reservations
    fwrite(&pSales->reservationCount, sizeof(int), 1, fp);

    // Write each reservation to the file
    for (int i = 0; i < pSales->reservationCount; i++)
    {
        Reservation* reservation = pSales->reservationArray[i];
        saveReservationToBinaryFile(reservation, fp);
    }

   /* fclose(fp);
    return 1;*/
    CLOSE_FILE_RETURN_1(fp);
}




int	 writeStringToCompressFile(const char* str, FILE* fp, const char* msg)
{

    if (!writeCharsToFile(str, (int)strlen(str), fp, msg))
        return 0;


    return 1;
}





///from 1-4
int savePurchasedItemToCompressedFile(const PurchasedItem* pItem, FILE* fp)
{
    BYTE compressedData[5];

    // Compress serial number (0-999)
    compressedData[0] = (pItem->serial >> 2) & 0xFF;
    compressedData[1] = (pItem->serial & 0x3) << 6;

    // Compress amount (0-10)
    compressedData[1] |= (pItem->amount << 2);

    // Compress cost integer part (0-10000)
    compressedData[1] |= (pItem->costInt >> 8) & 0x3;
    compressedData[2] = pItem->costInt & 0xFF;

    // Compress cost decimal part (0-99)
    compressedData[3] = pItem->costDec;

    // Write compressed data to file
    if (fwrite(compressedData, sizeof(BYTE), 4, fp) != 4)
        return 0;

    return 1;
}


int loadPurchasedItemFromCompressedFile(PurchasedItem* pItem, FILE* fp)
{
    BYTE compressedData[5];

    // Read compressed data from file
    if (fread(compressedData, sizeof(BYTE), 4, fp) != 4)
        return 0;

    // Decompress serial number
    pItem->serial = (compressedData[0] << 2) | (compressedData[1] >> 6);

    // Decompress amount
    pItem->amount = (compressedData[1] >> 2) & 0xF;

    // Decompress cost integer part
    pItem->costInt = ((compressedData[1] & 0x3) << 8) | compressedData[2];

    // Decompress cost decimal part
    pItem->costDec = compressedData[3];

    return 1;
}



///////!!!compress-explantion!!!///// we need to make sure the "parts" of PurchasedItem stay in range 
/*  the PurchasedItem struct will be compressed using bitwise operations 
when saving to a file and decompressed when loading from a file. 
The compression scheme used here packs
the serial number (0-999), amount (0-10),
cost integer part (0-10000), and cost decimal part (0-99) 
into 4 bytes.   */