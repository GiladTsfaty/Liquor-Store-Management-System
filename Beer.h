#pragma once

typedef enum {
    eThird, ePaint, eHalf, eNumOfBeerSizes
} eBeerSize;

static const char* BeerSizeStr[eNumOfBeerSizes]
= { "Third", "Paint", "Half" };

typedef struct
{
    char* brand;
    //    char itemSerial[5]; //BGOLD
    int amountAvailable;
    int price;
    int numOfSolds;
    eBeerSize bSize;

}Beer;

void initBeer(Beer* pBeer, Beer* beerArr, int beerCount);
int generateItemSerial(Beer* pBeer);
eBeerSize getBeerSize();
const char* GetBeerSizeStr(int type);
void printBeer(const Beer* pBeer);

