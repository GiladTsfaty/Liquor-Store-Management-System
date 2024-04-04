#pragma once



typedef enum {
    eScotch, eIrish, eBourbon, eTennessee, eBlended, eJapanese,  eNumOfWhiskeyTypes
} eWhiskeyType;

static const char* WhiskeyTypeStr[eNumOfWhiskeyTypes]
        = { "Scotch", "Irish", "Bourbon", "Tennessee", "Blended", "Japanese" };

typedef struct
{
    char* brand;
    int itemSerial; // 222
    int amountAvailable;
    int price;
    int numOfSolds;
    eWhiskeyType whiskeyType;

}Whiskey;

void initWhiskey(Whiskey* pWhiskey, Whiskey* whiskeyArr, int whiskeyCount);
eWhiskeyType getWhiskeyType();
const char* GetWhiskeyTypeStr(int type);
void printWhiskey(const Whiskey* pWhiskey);