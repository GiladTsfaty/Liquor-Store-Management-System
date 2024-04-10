

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include "Customer.h"
#include "list.h"
#include "Inventory.h"
#include "GeneralFunctions.h"

Customer* returnBlanckCustomer(Customer* pCustomer)
{
    pCustomer->name = "Jhon_Doe";
    pCustomer->totalSpent = 0;
    pCustomer->type = eNew;

    return pCustomer;
}

int initCustomerWithoutName(Customer* pCustomer)
{

	/*if (!getCustomerName(pCustomer))
		return 0;*/
   
	pCustomer->type = eNew;
	pCustomer->totalSpent = 0;
    printf("Customer created\n");

	return 1;
}


int printCustomer(const Customer* pCustomer)
{
    printf("Customer - %s is a %s client and has spent a total of %.2f$.\n",
        pCustomer->name, CustomerTypeStr[pCustomer->type], pCustomer->totalSpent);

    return 1;
}




int isSameCustomerName(const Customer* pCustomer1, const Customer* pCustomer2)///returns 1 if name is the same 
{

	return strcmp(pCustomer1->name, pCustomer2->name) == 0;
}

void freeCustomer(Customer* pCustomer)
{
    free(pCustomer->name);
}










//
//char* allocateRightLength(char** wordsArray, int count, int totalLength) {
//    if (count == 1)
//        totalLength += (int)strlen(wordsArray[0]);
//    else {
//        if (count % 2 == 0)
//            totalLength += (count - 1) * 2 + 1;
//        else
//            totalLength += count;
//    }
//
//    char* name = (char*)calloc(totalLength, sizeof(char));
//    if (!name) {
//        for (int i = 0; i < count; i++)
//            free(wordsArray[i]);
//        free(wordsArray);
//        return NULL;
//    }
//
//    return name;
//}
//
//void changeNameOneWord(char* name, const char* word) {
//    int len = (int)strlen(word);
//    int index = 0;
//    for (int i = 0; i < len - 1; i++) {
//        name[index++] = toupper(word[i]);
//        name[index++] = SEP_CHAR;
//    }
//
//    name[index] = toupper(word[len - 1]);
//}
//
//void changeName(char* name, int count, char** wordsArray) {
//    for (int i = 0; i < count; i++) {
//        wordsArray[i][0] = toupper(wordsArray[i][0]);
//        strcat(name, wordsArray[i]);
//        if (i != count - 1) { //not last
//            strcat(name, " ");
//            if (count % 2 == 0)
//                strcat(name, " ");
//        }
//    }
//}
//
//int getCustomerName(Customer* pCustomer) {
//    char temp[MAX_STR_LEN];
//    char** wordsArray = NULL;
//    int totalLength = 0;
//    int count = 0;
//
//    while (count == 0) {
//        printf("Enter customer name\n");
//        myGets(temp, MAX_STR_LEN);
//        wordsArray = splitCharsToWords(temp, &count, &totalLength);
//    }
//
//    pCustomer->name = allocateRightLength(wordsArray, count, totalLength);
//    if (!pCustomer->name) {
//        printf("Memory allocation failed.\n");
//        for (int i = 0; i < count; i++)
//            free(wordsArray[i]);
//        free(wordsArray);
//        return 0;
//    }
//
//    if (count == 1)
//        changeNameOneWord(pCustomer->name, wordsArray[0]);
//    else
//        changeName(pCustomer->name, count, wordsArray);
//
//    // Clean temp data
//    for (int i = 0; i < count; i++)
//        free(wordsArray[i]);
//    free(wordsArray);
//    return 1;
//}




/// I changed the funcs to do - Jhon  , Jhon_Doe ///

int getCustomerName(Customer* pCustomer)
{
    char temp[MAX_STR_LEN];
    char** wordsArray = NULL;
    int totalLength = 0;
    int count = 0;

    while (count == 0) {
        printf("Enter customer name\n");
        myGets(temp, MAX_STR_LEN);
        wordsArray = splitCharsToWords(temp, &count, &totalLength);
    }

    pCustomer->name = allocateRightLength(wordsArray, count, totalLength);
    if (!pCustomer->name) {
        printf("Memory allocation failed.\n");
        for (int i = 0; i < count; i++)
            free(wordsArray[i]);
        free(wordsArray);
        return 0;
    }

    if (count == 1)
        changeNameOneWord(pCustomer->name, wordsArray[0]);
    else
        changeName(pCustomer->name, count, wordsArray);

    // Clean temp data
    for (int i = 0; i < count; i++)
        free(wordsArray[i]);
    free(wordsArray);
    return 1;
}

char* allocateRightLength(char** wordsArray, int count, int totalLength) 
{
    if (count == 1)
        totalLength += (int)strlen(wordsArray[0]);
    else {
        totalLength += (count - 1); // Add space for underscores
    }

    char* name = (char*)calloc(totalLength + 1, sizeof(char)); // +1 for null terminator
    if (!name) {
        for (int i = 0; i < count; i++)
            free(wordsArray[i]);
        free(wordsArray);
        return NULL;
    }

    return name;
}

//void changeNameOneWord(char* name, const char* word)
//{
//    int len = (int)strlen(word);
//    name[0] = toupper(word[0]);
//    for (int i = 1; i < len; i++) 
//    {
//        name[i] = tolower(word[i]);
//    }
//}
void changeNameOneWord(char* name, const char* word)
{
    int len = (int)strlen(word);

    name[0] = toupper(word[0]);

    for (int i = 1; i < len; i++)
    {
        name[i] = tolower(word[i]);
    }

    name[len] = '\0'; // Null-terminate the string
}

void changeName(char* name, int count, char** wordsArray) {
    for (int i = 0; i < count; i++) {
        wordsArray[i][0] = toupper(wordsArray[i][0]);
        for (int j = 1; j < strlen(wordsArray[i]); j++) {
            wordsArray[i][j] = tolower(wordsArray[i][j]);
        }
        strcat(name, wordsArray[i]);
        if (i != count - 1) { // Not the last word
            strcat(name, "_");
        }
    }
}