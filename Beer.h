#pragma once

typedef enum {
    eThirdLiter, ePaint, eImperialPaint, eJug, eNumOfBeerSizes
} eBeerSize;

static const char* BeerSizeStr[eNumOfBeerSizes]
= { "ThirdLiter", "Paint", "ImperialPaint", "Jug" };

typedef struct
{
    char* brand;
    int itemSerial;
    int amountAvailable;
    int price;
    int numOfSolds;
    eBeerSize bSize;

}Beer;

void        initBeer(Beer* pBeer, Beer* beerArr, int beerCount);
eBeerSize   getBeerSize();
const char* GetBeerSizeStr(int type);
void        printBeer(const Beer* pBeer);

