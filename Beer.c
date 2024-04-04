#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Beer.h"
#include "GeneralFunctions.h"


void initBeer(Beer* pBeer, Beer* beerArr, int beersCount)
{
    char* tempBrand = getStrExactName("Enter the Beer brand:");
    pBeer->brand = tempBrand;
    pBeer->amountAvailable = 40;
    pBeer->price = 8;
    pBeer->numOfSolds = 0;
    pBeer->itemSerial = 111;
    pBeer->bSize = getBeerSize();
    printf("Beer Added\n");
}

eBeerSize getBeerSize()
{
    int option;
    printf("\n\n");
    do {
        printf("Please enter one of the following types\n");
        for (int i = 0; i < eNumOfBeerSizes; i++)
            printf("%d for %s\n", i, BeerSizeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNumOfBeerSizes);
    getchar();
    return (eBeerSize)option;
}

const char* GetBeerSizeStr(int type)
{
    if (type < 0 || type >= eNumOfBeerSizes)
        return NULL;
    return BeerSizeStr[type];
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

void printBeer(const Beer* pBeer)
{
    printf("Beer: Brand: %s, Item Serial: %d Amount Available: %d, Price: %d, Number of Sold: %d, Beer Size: %s\n",
        pBeer->brand, pBeer->itemSerial, pBeer->amountAvailable, pBeer->price, pBeer->numOfSolds, BeerSizeStr[pBeer->bSize]);
}


