
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "Filefunctions.h"


void parseBeerSize(const char* sizeStr, eBeerSize* size)
{
    if (strcmp(sizeStr, "ThirdLiter") == 0)
        *size = eThirdLiter;
    else if (strcmp(sizeStr, "Paint") == 0)
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

int initInventoryFromTextFile(Inventory* pInventory, const char* filename)
{
    FILE* fp = fopen(filename, "r");
    if (!fp)
    {
        perror("Unable to open file");
        return 0;
    }

    char line[256];
    int itemCount;

    // Read Beers
    if (fscanf(fp, "%d\n", &itemCount) != 1)
    {
        CLOSE_FILE_RETURN_0(fp);
    }
    pInventory->beerArray = (Beer*)malloc(itemCount * sizeof(Beer));
    if (pInventory->beerArray == NULL) {
        printf("Memory allocation failed for beer array.\n");
        CLOSE_FILE_RETURN_0(fp);
    }
    pInventory->beersCount = itemCount;
    for (int i = 0; i < itemCount; ++i) {
        char tempBrand[256];
        readLine(fp, tempBrand, sizeof(tempBrand));
        pInventory->beerArray[i].brand = (char*)malloc((strlen(tempBrand) + 1) * sizeof(char));
        if (pInventory->beerArray[i].brand != NULL) {
            strcpy(pInventory->beerArray[i].brand, tempBrand);
        }

        if (fscanf(fp, "%d\n%d\n%d\n%d\n",
            &pInventory->beerArray[i].itemSerial,
            &pInventory->beerArray[i].amountAvailable,
            &pInventory->beerArray[i].price,
            &pInventory->beerArray[i].numOfSolds) != 4) {
            CLOSE_FILE_RETURN_0(fp);
        }

        readLine(fp, line, sizeof(line));
        parseBeerSize(line, &pInventory->beerArray[i].bSize);
    }

    // Read Whiskeys
    if (fscanf(fp, "%d\n", &itemCount) != 1) {
        CLOSE_FILE_RETURN_0(fp);
    }
    pInventory->whiskeyArray = (Whiskey*)malloc(itemCount * sizeof(Whiskey));
    if (pInventory->whiskeyArray == NULL) {
        printf("Memory allocation failed for whiskey array.\n");
        CLOSE_FILE_RETURN_0(fp);
    }
    pInventory->whiskeysCount = itemCount;
    for (int i = 0; i < itemCount; ++i) {
        char tempBrand[256];
        readLine(fp, tempBrand, sizeof(tempBrand));
        pInventory->whiskeyArray[i].brand = (char*)malloc((strlen(tempBrand) + 1) * sizeof(char));
        if (pInventory->whiskeyArray[i].brand != NULL) {
            strcpy(pInventory->whiskeyArray[i].brand, tempBrand);
        }

        if (fscanf(fp, "%d\n%d\n%d\n%d\n",
            &pInventory->whiskeyArray[i].itemSerial,
            &pInventory->whiskeyArray[i].amountAvailable,
            &pInventory->whiskeyArray[i].price,
            &pInventory->whiskeyArray[i].numOfSolds) != 4) {
            CLOSE_FILE_RETURN_0(fp);
        }

        readLine(fp, line, sizeof(line));
        parseWhiskeyType(line, &pInventory->whiskeyArray[i].whiskeyType);
    }

    // Read Wines
    if (fscanf(fp, "%d\n", &itemCount) != 1)
    {
        CLOSE_FILE_RETURN_0(fp);
    }
    pInventory->wineArray = (Wine*)malloc(itemCount * sizeof(Wine));
    if (pInventory->wineArray == NULL) {
        printf("Memory allocation failed for wine array.\n");
        CLOSE_FILE_RETURN_0(fp);
    }
    pInventory->winesCount = itemCount;
    for (int i = 0; i < itemCount; ++i) {
        char tempBrand[256];
        readLine(fp, tempBrand, sizeof(tempBrand));
        pInventory->wineArray[i].brand = (char*)malloc((strlen(tempBrand) + 1) * sizeof(char));
        if (pInventory->wineArray[i].brand != NULL) {
            strcpy(pInventory->wineArray[i].brand, tempBrand);
        }

        if (fscanf(fp, "%d\n%d\n%d\n%d\n",
            &pInventory->wineArray[i].itemSerial,
            &pInventory->wineArray[i].amountAvailable,
            &pInventory->wineArray[i].price,
            &pInventory->wineArray[i].numOfSolds) != 4) {
            CLOSE_FILE_RETURN_0(fp);
        }

        readLine(fp, line, sizeof(line));
        parseWineType(line, &pInventory->wineArray[i].wType);
    }

    CLOSE_FILE_RETURN_1(fp);
}

int saveInventoryToTextFile(const Inventory* pInventory, char* filename)
{
    FILE* fp = fopen(filename, "w");
   
    CHECK_PRINT_RETURN_0(fp, "Failed to open file");

    // Write Beers
    fprintf(fp, "%d\n", pInventory->beersCount);
    for (int i = 0; i < pInventory->beersCount; i++) {
        const Beer* pBeer = &pInventory->beerArray[i];
        fprintf(fp, "%s\n", pBeer->brand);
        fprintf(fp, "%d\n%d\n%d\n%d\n", pBeer->itemSerial, pBeer->amountAvailable, pBeer->price, pBeer->numOfSolds);
        fprintf(fp, "%s\n", BeerSizeStr[pBeer->bSize]);//!!
    }

    // Write Whiskeys
    fprintf(fp, "%d\n", pInventory->whiskeysCount);
    for (int i = 0; i < pInventory->whiskeysCount; i++) {
        const Whiskey* pWhiskey = &pInventory->whiskeyArray[i];
        fprintf(fp, "%s\n", pWhiskey->brand);
        fprintf(fp, "%d\n%d\n%d\n%d\n", pWhiskey->itemSerial, pWhiskey->amountAvailable, pWhiskey->price, pWhiskey->numOfSolds);
        fprintf(fp, "%s\n", WhiskeyTypeStr[pWhiskey->whiskeyType]);
    }

    // Write Wines
    fprintf(fp, "%d\n", pInventory->winesCount);
    for (int i = 0; i < pInventory->winesCount; i++) {
        const Wine* pWine = &pInventory->wineArray[i];
        fprintf(fp, "%s\n", pWine->brand);
        fprintf(fp, "%d\n%d\n%d\n%d\n", pWine->itemSerial, pWine->amountAvailable, pWine->price, pWine->numOfSolds);
        fprintf(fp, "%s\n", WineTypeStr[pWine->wType]);
    }

   
    CLOSE_FILE_RETURN_1(fp);
}

void readInventoryFromFile(Inventory* pInventory, const char* filename) //MAX_STR_LEN
{
    FILE* fp = fopen(filename, "r");
    if (!fp)
    {
        perror("Unable to open file");
        return;
    }

    char line[MAX_STR_LEN];
    int itemCount;

    // Read Beers
    fscanf(fp, "%d\n", &itemCount); // Read the count of beer items
    pInventory->beerArray = (Beer*)malloc(itemCount * sizeof(Beer));
    if (pInventory->beerArray == NULL) {
        printf("Memory allocation failed for beer array.\n");
        fclose(fp);
        return;
    }
    pInventory->beersCount = itemCount;
    for (int i = 0; i < itemCount; ++i) {
        char tempBrand[MAX_STR_LEN];
        readLine(fp, tempBrand, sizeof(tempBrand));
        pInventory->beerArray[i].brand = (char*)malloc((strlen(tempBrand) + 1) * sizeof(char));
        if (pInventory->beerArray[i].brand != NULL) {
            strcpy(pInventory->beerArray[i].brand, tempBrand);
        }

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
    if (pInventory->whiskeyArray == NULL) {
        printf("Memory allocation failed for whiskey array.\n");
        fclose(fp);
        return;
    }
    pInventory->whiskeysCount = itemCount;
    for (int i = 0; i < itemCount; ++i) {
        char tempBrand[MAX_STR_LEN];
        readLine(fp, tempBrand, sizeof(tempBrand));
        pInventory->whiskeyArray[i].brand = (char*)malloc((strlen(tempBrand) + 1) * sizeof(char));
        if (pInventory->whiskeyArray[i].brand != NULL) {
            strcpy(pInventory->whiskeyArray[i].brand, tempBrand);
        }

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
    if (pInventory->wineArray == NULL) {
        printf("Memory allocation failed for wine array.\n");
        fclose(fp);
        return;
    }
    pInventory->winesCount = itemCount;
    for (int i = 0; i < itemCount; ++i) {
        char tempBrand[MAX_STR_LEN];
        readLine(fp, tempBrand, sizeof(tempBrand));
        pInventory->wineArray[i].brand = (char*)malloc((strlen(tempBrand) + 1) * sizeof(char));
        if (pInventory->wineArray[i].brand != NULL) {
            strcpy(pInventory->wineArray[i].brand, tempBrand);
        }

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
        CLOSE_FILE_RETURN_0(fp);
    }
    return 1;
}

int loadCustomerFromTextFile(Customer* pCustomer, FILE* fp)
{
    char temp[MAX_STR_LEN];

    if (!pCustomer)
        return 0;

    // Read customer name
    if (myGetsFile(temp, MAX_STR_LEN, fp) == NULL)
        return 0;
    pCustomer->name = getDynStr(temp);
    if (pCustomer->name == NULL)
        return 0;

    // Read total spent
    if (myGetsFile(temp, MAX_STR_LEN, fp) == NULL)
        return 0;
    pCustomer->totalSpent = atof(temp);

    // Read customer type
    if (myGetsFile(temp, MAX_STR_LEN, fp) == NULL)
        return 0;

    // Convert the string to enum value
    pCustomer->type = eNomOfCustomerTypes; // Set a default value
    for (int i = 0; i < eNomOfCustomerTypes; i++)
    {
        if (strcmp(temp, CustomerTypeStr[i]) == 0)
        {
            pCustomer->type = (eCustomerType)i;
            break;
        }
    }


    return 1;
}

int saveCustomerToFile(Customer* pCustomer, FILE* fp)
{

    if (!pCustomer)
        return 0;

    fprintf(fp, "%s\n", pCustomer->name);
    fprintf(fp, "%.2f\n", pCustomer->totalSpent);
    fprintf(fp, "%s\n", CustomerTypeStr[pCustomer->type]);
    return 1;
}

int initCustomerListFromTextFile(Sales* pSales, const char* fileName)
{
    FILE* fp;
    fp = fopen(fileName, "r");
   
    CHECK_PRINT_RETURN_0(fp,"Error opening customer list file");

    L_init(&pSales->customersList);

    int count;
    fscanf(fp, "%d", &count);
    // Clean the buffer
    fgetc(fp);

    Customer* pCustomer;


    for (int i = 0; i < count; i++)
    {
        pCustomer = (Customer*)calloc(1, sizeof(Customer));
        if (!pCustomer)
            break;

        if (!loadCustomerFromTextFile(pCustomer, fp))
        {
            printf("Error loading customer from file\n");
            CLOSE_FILE_RETURN_0(fp);
        }

        insertNewCustomerToList(&pSales->customersList, pCustomer);

    }

   
    CLOSE_FILE_RETURN_1(fp);
}

int saveCustomerListToTextFile(const Sales* pSales,  char* fileName)
{


    FILE* fp;

    fp = fopen(fileName, "w"); //open to write 
    
    CHECK_PRINT_RETURN_0(fp, "cant open file to write in ");


    fprintf(fp, "%d\n", L_length(&(pSales->customersList)) - 1);// first line num of clients/length of list

    NODE* pNode = (pSales->customersList.head.next); //first member of list 
    while (pNode) {
        if (!saveCustomerToFile(pNode->key, fp))
        {
            printf("cant write customer to file\n");
            CLOSE_FILE_RETURN_0(fp);
        }
        pNode = pNode->next;


    }
   
    CLOSE_FILE_RETURN_1(fp);//success


}


///resevation///
void saveReservationToFile(const Reservation* reservation, FILE* file)
{
    fprintf(file, "%d\n", reservation->ReservationCode);
    fprintf(file, "%s\n", reservation->customer->name);
    fprintf(file, "%s\n", CustomerTypeStr[reservation->customer->type]);
    fprintf(file, "%d %d %d\n", reservation->date.day, reservation->date.month, reservation->date.year);
    fprintf(file, "%.2f\n", reservation->priceOfOrder);

    // Save purchased items
    fprintf(file, "%d\n", reservation->numPurchasedItems);
    for (int i = 0; i < reservation->numPurchasedItems; i++) {
        PurchasedItem* item = &(reservation->purchasedItems[i]);
        fprintf(file, "%d %d %d %d\n", item->serial, item->amount, item->costInt, item->costDec);
    }
}

Reservation* loadReservationFromFile(Sales* pSales, FILE* file)
{
    Reservation* reservation = (Reservation*)malloc(sizeof(Reservation));
    if (reservation == NULL)
    {
        printf("Memory allocation failed for reservation.\n");
        return NULL;
    }

    // Read reservation data from the file
    fscanf(file, "%d\n", &reservation->ReservationCode);

    // Read customer name
    char customerName[MAX_STR_LEN];
    fgets(customerName, MAX_STR_LEN, file);
    customerName[strcspn(customerName, "\n")] = '\0'; // Remove trailing newline character
    reservation->customer = findCustomerByName(pSales, customerName);

    if (reservation->customer == NULL) {
        printf("Customer not found: %s\n", customerName);
        free(reservation);
        return NULL;
    }

    // Read customer type
    char customerType[20];
    fgets(customerType, 20, file);
    customerType[strcspn(customerType, "\n")] = '\0'; // Remove trailing newline character
    for (int i = 0; i < eNomOfCustomerTypes; i++) {
        if (strcmp(customerType, CustomerTypeStr[i]) == 0) {
            reservation->customer->type = (eCustomerType)i;
            break;
        }
    }

    // Read date
    fscanf(file, "%d %d %d\n", &reservation->date.day, &reservation->date.month, &reservation->date.year);

    fscanf(file, "%lf\n", &reservation->priceOfOrder);

    // Read purchased items
    fscanf(file, "%d\n", &reservation->numPurchasedItems);
    reservation->purchasedItems = (PurchasedItem*)malloc(reservation->numPurchasedItems * sizeof(PurchasedItem));
    if (reservation->purchasedItems == NULL) {
        printf("Memory allocation failed for purchased items.\n");
        free(reservation);
        return NULL;
    }

    for (int j = 0; j < reservation->numPurchasedItems; j++)
    {
        PurchasedItem* item = &(reservation->purchasedItems[j]);
        fscanf(file, "%d %d %d %d\n", &item->serial, &item->amount, &item->costInt, &item->costDec);
    }

    return reservation;
}

int loadReservationsArrayFromTextFile(Sales* pSales, const char* filename)
{
    FILE* fp = fopen(filename, "r");
    
    CHECK_PRINT_RETURN_0(fp, "Failed to open file");

    // Read the number of reservations
    int count;
    fscanf(fp, "%d\n", &count);

    pSales->reservationArray = (struct Reservation **) (Reservation **) malloc(count * sizeof(Reservation *));
    if (pSales->reservationArray == NULL) 
    {
        printf("Memory allocation failed for reservation array.\n");
        CLOSE_FILE_RETURN_0(fp);
    }

// Read each reservation from the file
    for (int i = 0; i < count; i++) {
        Reservation* reservation = loadReservationFromFile(pSales, fp);
        if (reservation == NULL)
        {
            CLOSE_FILE_RETURN_0(fp);
        }
        pSales->reservationArray[i] = (struct Reservation *) reservation;
    }

    pSales->reservationCount = count;
   
    CLOSE_FILE_RETURN_1(fp);
}

int saveReservationsArrayToTextFile(const Sales* pSales,  char* filename)
{
    FILE* fp = fopen(filename, "w");
   
    CHECK_PRINT_RETURN_0(fp, "Failed to open file");
    
    // Write the number of reservations
    fprintf(fp, "%d\n", pSales->reservationCount);

    // Write each reservation to the file
    for (int i = 0; i < pSales->reservationCount; i++)
    {
        struct Reservation* reservation = pSales->reservationArray[i];//(struct)
        saveReservationToFile((Reservation*)reservation, fp);//(Reservation*)
    }

   
    CLOSE_FILE_RETURN_1(fp);
}





