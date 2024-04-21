#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Beer.h"
#include "GeneralFunctions.h"
#include "Inventory.h"


void initBeer(Beer* pBeer, Beer* beerArr, int beersCount)
{
    char* tempBrand = getStrExactName("Enter the Beer brand:");
    pBeer->brand = tempBrand;
    pBeer->itemSerial = getUniqueSerialNumber(beerArr, beersCount, 100, 199, sizeof(Beer), getBeerSerialNumber);
    pBeer->amountAvailable = START_NUM_UNITS_OF_BEER;
    pBeer->price = getIntPositive("Enter the price:");
    pBeer->numOfSolds = 0;
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


void printBeer(const Beer* pBeer)
{
    printf("Beer: Brand: %s, Item Serial: %d Amount Available: %d, Price: %d, Number of Sold: %d, Beer Size: \n",
        pBeer->brand, pBeer->itemSerial, pBeer->amountAvailable, pBeer->price, pBeer->numOfSolds
        //, BeerSizeStr[pBeer->bSize]
    );
}


