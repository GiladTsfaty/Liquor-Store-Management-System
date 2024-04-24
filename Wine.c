#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Wine.h"
#include "Inventory.h"
#include "GeneralFunctions.h"

void initWine(Wine* pWine, Wine* wineArr, int winesCount)
{
    char* tempBrand = getStrExactName("Enter the Wine brand:");
    pWine->brand = tempBrand;
    pWine->itemSerial = getUniqueSerialNumber(wineArr, winesCount,WINE_SERIAL_LOW, WINE_SERIAL_HIGH, sizeof(Wine), getWineSerialNumber);
    pWine->amountAvailable = START_NUM_UNITS_OF_WINE;
    pWine->price = getIntPositive("Enter the price:");
    pWine->numOfSolds = 0;
    pWine->wType = getWineType();
    printf("Wine Added\n");
}

eWineType getWineType()
{
    int option;
    printf("\n\n");
    do {
        printf("Please enter one of the following types\n");
        for (int i = 0; i < eNumOfWineTypes; i++)
            printf("%d for %s\n", i, WineTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNumOfWineTypes);
    getchar();
    return (eWineType)option;
}

const char* GetWineTypeStr(int type)
{
    if (type < 0 || type >= eNumOfWineTypes)
        return NULL;
    return WineTypeStr[type];
}


void printWine(const Wine* pWine)
{
    printf("Wine: Brand: %s, Amount Available: %d, Price: %d, Number of Sold: %d, Wine Type: %s\n",
        pWine->brand, pWine->amountAvailable, pWine->price, pWine->numOfSolds, WineTypeStr[pWine->wType]);
}