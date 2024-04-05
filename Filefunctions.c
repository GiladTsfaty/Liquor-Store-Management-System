
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Filefunctions.h"
#include "General.h"
#include "Wine.h"
#include "Inventory.h"
#include "Beer.h"
#include "Whiskey.h"

void parseBeerSize(const char* sizeStr, eBeerSize* size) {
    if (strcmp(sizeStr, "Paint") == 0)
        *size = ePaint;
    else if (strcmp(sizeStr, "ImperialPaint") == 0)
        *size = eImperialPaint;
    else if (strcmp(sizeStr, "Jug") == 0)
        *size = eJug;
}

void parseWhiskeyType(const char* typeStr, eWhiskeyType* type) {
    if (strcmp(typeStr, "Scotch") == 0)
        *type = eScotch;
    else if (strcmp(typeStr, "Irish") == 0)
        *type = eIrish;
    else if (strcmp(typeStr, "Bourbon") == 0)
        *type = eBourbon;
    else if (strcmp(typeStr, "Tennessee") == 0)
        *type = eTennessee;
    else if (strcmp(typeStr, "Blended") == 0)
        *type = eBlended;
    else if (strcmp(typeStr, "Japanese") == 0)
        *type = eJapanese;
}

void parseWineType(const char* typeStr, eWineType* type) {
    if (strcmp(typeStr, "Red") == 0)
        *type = eRed;
    else if (strcmp(typeStr, "White") == 0)
        *type = eWhite;
    else if (strcmp(typeStr, "Rose") == 0)
        *type = eRose;
    else if (strcmp(typeStr, "Sparkling") == 0)
        *type = eSparkling;
    else if (strcmp(typeStr, "Fortified") == 0)
        *type = eFortified;
}




void readLine(FILE* file, char* buffer, int bufferSize) {
    if (file == NULL || buffer == NULL || bufferSize <= 0) {
        // Invalid parameters, handle the error accordingly
        return;
    }

    if (fgets(buffer, bufferSize, file) != NULL) {
        buffer[strcspn(buffer, "\n")] = '\0'; // Remove newline character
    } else {
        // Error occurred while reading the line or reached end of file
        buffer[0] = '\0'; // Set the buffer to an empty string
    }
}


void readInventoryFromFile(Inventory* pInventory, const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        perror("Unable to open file");
        return;
    }

    char line[256];
    int itemCount;

    // Read Beers
    fscanf(fp, "%d\n", &itemCount); // Read the count of beer items
    pInventory->beerArray = (Beer*)malloc(itemCount * sizeof(Beer));
    pInventory->beersCount = itemCount;
    for (int i = 0; i < itemCount; ++i) {
        char tempBrand[256];
        readLine(fp, tempBrand, sizeof(tempBrand));
        pInventory->beerArray[i].brand = (char*)malloc((strlen(tempBrand) + 1) * sizeof(char));
        strcpy(pInventory->beerArray[i].brand, tempBrand);

        fscanf(fp, "%d\n%d\n%d\n%d\n",
               &pInventory->beerArray[i].itemSerial,
               &pInventory->beerArray[i].amountAvailable,
               &pInventory->beerArray[i].price,
               &pInventory->beerArray[i].numOfSolds);

        readLine(fp, line, sizeof(line)); // Read the beer size/type as string
        parseBeerSize(line, &pInventory->beerArray[i].bSize);
    }

    // Read Whiskeys
    fscanf(fp, "%d\n", &itemCount); // Read the count of whiskey items
    pInventory->whiskeyArray = (Whiskey*)malloc(itemCount * sizeof(Whiskey));
    pInventory->whiskeysCount = itemCount;
    for (int i = 0; i < itemCount; ++i) {
        char tempBrand[256];
        readLine(fp, tempBrand, sizeof(tempBrand));
        pInventory->whiskeyArray[i].brand = (char*)malloc((strlen(tempBrand) + 1) * sizeof(char));
        strcpy(pInventory->whiskeyArray[i].brand, tempBrand);

        fscanf(fp, "%d\n%d\n%d\n%d\n",
               &pInventory->whiskeyArray[i].itemSerial,
               &pInventory->whiskeyArray[i].amountAvailable,
               &pInventory->whiskeyArray[i].price,
               &pInventory->whiskeyArray[i].numOfSolds);

        readLine(fp, line, sizeof(line)); // Read the whiskey type as string
        parseWhiskeyType(line, &pInventory->whiskeyArray[i].whiskeyType);
    }

    // Read Wines
    fscanf(fp, "%d\n", &itemCount); // Read the count of wine items
    pInventory->wineArray = (Wine*)malloc(itemCount * sizeof(Wine));
    pInventory->winesCount = itemCount;
    for (int i = 0; i < itemCount; ++i) {
        char tempBrand[256];
        readLine(fp, tempBrand, sizeof(tempBrand));
        pInventory->wineArray[i].brand = (char*)malloc((strlen(tempBrand) + 1) * sizeof(char));
        strcpy(pInventory->wineArray[i].brand, tempBrand);

        fscanf(fp, "%d\n%d\n%d\n%d\n",
               &pInventory->wineArray[i].itemSerial,
               &pInventory->wineArray[i].amountAvailable,
               &pInventory->wineArray[i].price,
               &pInventory->wineArray[i].numOfSolds);

        readLine(fp, line, sizeof(line)); // Read the wine type as string
        parseWineType(line, &pInventory->wineArray[i].wType);
    }

    fclose(fp);
}


int	 writeStringToFile(char* str, FILE* fp, const char* msg)
{
    int length = (int)strlen(str);
    length++;
    if (!writeIntToFile(length, fp, msg))
        return 0;

    if (!writeCharsToFile(str, length, fp, msg))
        return 0;


    return 1;
}

int	 writeCharsToFile(char* arr, int size, FILE* fp, const char* msg)
{
    if (fwrite(arr, sizeof(char), size, fp) != size)
    {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;

}

int	 writeIntToFile(int val, FILE* fp, const char* msg)
{
    if (fwrite(&val, sizeof(int), 1, fp) != 1)
    {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;
}


int writeDoubleToFile(double val, FILE* fp, const char* msg)
{
    if (fwrite(&val, sizeof(double), 1, fp) != 1)
    {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;
}



char* readStringFromFile(FILE* fp, const char* msg)
{
    char* str;
    int length;
    if (!readIntFromFile(&length, fp, msg))
        return NULL;
    str = (char*)malloc((length) * sizeof(char));
    if (!str)
    {
        puts(msg);
        fclose(fp);
        return NULL;
    }
    if (fread(str, sizeof(char), length, fp) != length)
    {
        puts(msg);
        fclose(fp);
        return NULL;
    }
    return str;

}

int	 readCharsFromFile(char* arr, int length, FILE* fp, const char* msg)
{
    if (fread(arr, sizeof(char), length, fp) != length)
    {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;
}

int	  readIntFromFile(int* pVal, FILE* fp, const char* msg)
{
    if (fread(pVal, sizeof(int), 1, fp) != 1)
    {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;

}




int readDoubleFromFile(double* pVal, FILE* fp, const char* msg)
{
    if (fread(pVal, sizeof(double), 1, fp) != 1)
    {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;
}








int writeCustomerListToBFile(const Sales* pSales, FILE* fileName)
{
    FILE* pFile = fopen(fileName, "wb");
    if (!pFile)
    {
        printf("Error opening file for writing customer list.\n");
        return 0;
    }

    int count = L_length(&pSales->customersList)-1;
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








//int readCustomerListFromBFile(Sales* pSales, const FILE* fileName) 
//{
//
//    FILE* pFile = fopen(fileName, "rb");
//    if (!pFile)
//    {
//        printf("Error opening file for reading customer list.\n");
//        return 0;
//    }
//
//    int count;
//    if (!readIntFromFile(&count, pFile, "Error reading customer count"))
//    {
//        fclose(pFile);
//        return 0;
//    }
//
//    L_init(&pSales->customersList);
//
//    for (int i = 0; i < count; i++)
//    {
//        Customer* pCustomer = (Customer*)malloc(sizeof(Customer));
//        if (!pCustomer)
//        {
//            fclose(pFile);
//            return 0;
//        }
//
//        pCustomer->name = readStringFromFile(pFile, "Error reading customer name");
//        if (!pCustomer->name)
//        {
//            free(pCustomer);
//            fclose(pFile);
//            return 0;
//        }
//
//        if (fread(&pCustomer->totalSpent, sizeof(double), 1, pFile) != 1)
//        {
//            printf("Error reading customer total spent.\n");
//            free(pCustomer->name);
//            free(pCustomer);
//            fclose(pFile);
//            return 0;
//        }
//
//        int type;
//        if (!readIntFromFile(&type, pFile, "Error reading customer type"))
//        {
//            free(pCustomer->name);
//            free(pCustomer);
//            fclose(pFile);
//            return 0;
//        }
//        pCustomer->type = (eCustomerType)type;
//
//        NODE* pNode = pSales->customersList.head.next;
//        if (pNode == NULL)
//        {
//            L_insert(&pSales->customersList.head, pCustomer);
//        }
//        else
//        {
//            while (pNode->next != NULL)
//            {
//                pNode = pNode->next;
//            }
//            L_insert(pNode, pCustomer);
//        }
//    }
//
//    fclose(pFile);
//    return 1;
//
//
//
//}













//
//int writeAirlineToBFile(FILE* pFile, const Airline* pComp)
//{
//    int len = (int)strlen(pComp->name) + 1;
//    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(pComp->name, sizeof(char), len, pFile) != len) return 0;
//    if (fwrite(&pComp->planeCount, sizeof(int), 1, pFile) != 1) return 0;
//    if (!writePlaneArrToBFile(pFile, pComp->planeArr, pComp->planeCount)) return 0;
//    if (fwrite(&pComp->flightCount, sizeof(int), 1, pFile) != 1) return 0;
//    if (!writeFlightArrToBFile(pFile, pComp->flightArr, pComp->flightCount)) return 0;
//    return 1;
//}
//
//int writePlaneArrToBFile(FILE* pFile, const Plane* pPlaneArr, const int count)
//{
//    for (int i = 0; i < count; i++)
//    {
//        if (!writePlaneToBFile(pFile, &pPlaneArr[i]))
//        {
//            fclose(pFile);
//            return 0;
//        }
//    }
//    return 1;
//}
//
//int writePlaneToBFile(FILE* pFile, const Plane* pPlane)
//{
//    if (fwrite(&pPlane->serialNum, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pPlane->type, sizeof(ePlaneType), 1, pFile) != 1) return 0;
//    return 1;
//}
//
//int writeFlightArrToBFile(FILE* pFile, Flight** const flightArr, const int count)
//{
//    for (int i = 0; i < count; i++)
//    {
//        if (!writeFlightToBFile(pFile, flightArr[i]))
//        {
//            fclose(pFile);
//            return 0;
//        }
//    }
//    return 1;
//}
//
//int writeFlightToBFile(FILE* pFile, const Flight* pFlight)
//{
//    //int len = strlen(pFlight->sourceCode); // for both source and dest codes
//
//    //if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(pFlight->sourceCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;
//
//    //if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(pFlight->destCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;
//
//    if (fwrite(&pFlight->flightPlane.serialNum, sizeof(int), 1, pFile) != 1) return 0;
//    if (fwrite(&pFlight->date, sizeof(Date), 1, pFile) != 1) return 0;
//    return 1;
//}
//
//
//
//int readAirlineFromBFile(FILE* pFile, Airline* pComp, AirportManager* pManager)
//{
//    int len;
//
//    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
//    pComp->name = (char*)malloc(len * sizeof(char));
//    if (!pComp->name) return 0;
//    if (fread(pComp->name, sizeof(char), len, pFile) != len) return 0;
//
//    if (fread(&pComp->planeCount, sizeof(int), 1, pFile) != 1) return 0;
//
//    // Use a temporary pointer for realloc
//    Plane* tempPlaneArr = (Plane*)realloc(pComp->planeArr, (pComp->planeCount) * sizeof(Plane));
//    if (!tempPlaneArr) {
//        free(pComp->name); // Free allocated memory in case of failure
//        return 0;
//    }
//    pComp->planeArr = tempPlaneArr;
//
//    readPlaneArrFromBFile(pFile, pComp->planeArr, pComp->planeCount);
//
//    if (fread(&pComp->flightCount, sizeof(int), 1, pFile) != 1) return 0;
//
//    // Use a temporary pointer for realloc
//    Flight** tempFlightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount) * sizeof(Flight*));
//    if (!tempFlightArr) {
//        free(pComp->name);
//        free(pComp->planeArr); // Free allocated memory in case of failure
//        return 0;
//    }
//    pComp->flightArr = tempFlightArr;
//
//    readFlightArrFromBFile(pFile, pComp->flightArr, pComp->flightCount, pComp->planeArr, pComp->planeCount);
//
//    return 1;
//}
//
//
//int readPlaneArrFromBFile(FILE* pFile, Plane* planeArr, const int planeCount)
//{
//    Plane* pPlane = NULL;
//    for (int i = 0; i < planeCount; i++)
//    {
//        pPlane = (Plane*)calloc(1, sizeof(Plane));
//        if (!pPlane) return 0;
//        if (!readPlaneFromBFile(pFile, pPlane)) return 0;
//        planeArr[i] = *pPlane;
//    }
//    return 1;
//}
//
//int readPlaneFromBFile(FILE* pFile, Plane* pPlane)
//{
//    if (fread(&pPlane->serialNum, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(&pPlane->type, sizeof(ePlaneType), 1, pFile) != 1) return 0;
//    return 1;
//}
//
//int readFlightArrFromBFile(FILE* pFile, Flight** pFlightArr, const int flightCount, Plane* planeArr, const int planeCount)
//{
//    Flight* pFlight = NULL;
//    for (int i = 0; i < flightCount; i++)
//    {
//        pFlight = (Flight*)calloc(1, sizeof(Flight));
//        if (!pFlight) return 0;
//        if (!readFlightFromBFile(pFile, pFlight, planeArr, planeCount)) return 0;
//        pFlightArr[i] = pFlight;
//    }
//    return 1;
//}
//
//int readFlightFromBFile(FILE* pFile, Flight* pFlight, Plane* planeArr, const int planeCount)
//{
//    int len = 0, serialNumber;
//    //if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(pFlight->sourceCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;
//    pFlight->sourceCode[IATA_LENGTH] = '\0';
//
//    //if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
//    if (fread(pFlight->destCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;
//    pFlight->destCode[IATA_LENGTH] = '\0';
//
//    if (fread(&serialNumber, sizeof(int), 1, pFile) != 1) return 0;
//    pFlight->flightPlane = *findPlaneBySN(planeArr, planeCount, serialNumber);
//
//    if (fread(&pFlight->date, sizeof(Date), 1, pFile) != 1) return 0;
//
//    return 1;
//}