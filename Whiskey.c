#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Whiskey.h"
#include "Inventory.h"
#include "GeneralFunctions.h"

void initWhiskey(Whiskey* pWhiskey, Whiskey* whiskeyArr, int whiskeysCount)
{
    char* tempBrand = getStrExactName("Enter the Whiskey brand:");
    pWhiskey->brand = tempBrand;
    pWhiskey->itemSerial = getUniqueSerialNumber(whiskeyArr, whiskeysCount, 200, 299, sizeof(Whiskey), getWhiskeySerialNumber);
    pWhiskey->amountAvailable = START_NUM_UNITS_OF_WHISKEY;
    pWhiskey->price = getIntPositive("Enter the price:");
    pWhiskey->numOfSolds = 0;
    pWhiskey->whiskeyType = getWhiskeyType();
    printf("Whiskey Added\n");
}

eWhiskeyType getWhiskeyType()
{
    int option;
    printf("\n\n");
    do {
        printf("Please enter one of the following types\n");
        for (int i = 0; i < eNumOfWhiskeyTypes; i++)
            printf("%d for %s\n", i, WhiskeyTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNumOfWhiskeyTypes);
    getchar();
    return (eWhiskeyType)option;
}

const char* GetWhiskeyTypeStr(int type)
{
    if (type < 0 || type >= eNumOfWhiskeyTypes)
        return NULL;
    return WhiskeyTypeStr[type];
}