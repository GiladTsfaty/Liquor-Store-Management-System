#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Wine.h"
#include "GeneralFunctions.h"

void initWine(Wine* pWine, Wine* wineArr, int winesCount)
{
    char* tempBrand = getStrExactName("Enter the Wine brand:");
    pWine->brand = tempBrand;
    pWine->amountAvailable = 15;
    pWine->price = 35;
    pWine->itemSerial = 222;
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

//int generateItemSerial(Beer* pBeer)
//{
//
//    // Create a temporary character array to store the generated item serial
//    char tempSerial[5];
//
//    // Set the first character based on the struct type
//    tempSerial[0] = 'B';
//
//    // Copy the first three characters of the brand name in uppercase
//    for (int i = 0; i < 3 && pBeer->brand[i] != '\0'; i++)
//    {
//        tempSerial[i + 1] = toupper(pBeer->brand[i]);
//    }
//
//    // Add null terminator
//    tempSerial[4] = '\0';
//
//    // Copy the generated item serial to the Beer struct's itemSerial array
//    strncpy(pBeer->itemSerial, tempSerial, sizeof(pBeer->itemSerial));
//
//    return 1;
//}

void printWine(const Wine* pWine)
{
    printf("Wine: Brand: %s, Amount Available: %d, Price: %d, Number of Sold: %d, Wine Type: %s\n",
        pWine->brand, pWine->amountAvailable, pWine->price, pWine->numOfSolds, WineTypeStr[pWine->wType]);
}