#pragma once



typedef enum {
    eRed, eWhite, eRose, eSparkling, eDessert, eFortified, eNumOfWineTypes
} eWineType;

static const char* WineTypeStr[eNumOfWineTypes]
= { "Red", "White","Rose", "Sparkling", "Dessert", "Fortified"};

typedef struct
{
    char*   brand;
    int     itemSerial; 
    int     amountAvailable;
    int     price;
    int     numOfSolds;
    eWineType wType;

}Wine;

void        initWine(Wine* pWine, Wine* wineArr, int wineCount);
eWineType   getWineType();
const char* GetWineTypeStr(int type);
void        printWine(const Wine* pWine);
