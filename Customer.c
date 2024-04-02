
#include "Customer.h"
#include "list.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>



int initCustomerWithoutName(Customer* pCustomer)
{

	/*if (!getCustomerName(pCustomer))
		return 0;*/
   
	pCustomer->type = eNew;
	pCustomer->totalSpent = 0;

	return 1;
}

int printCustomer(const Customer* pCustomer)
{
	printf("Customer - %s is a %s client and has spent a total of %d$. \n",pCustomer->name, pCustomer->type, pCustomer->totalSpent);

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






char* allocateRightLength(char** wordsArray, int count, int totalLength) {
    if (count == 1)
        totalLength += (int)strlen(wordsArray[0]);
    else {
        if (count % 2 == 0)
            totalLength += (count - 1) * 2 + 1;
        else
            totalLength += count;
    }

    char* name = (char*)calloc(totalLength, sizeof(char));
    if (!name) {
        for (int i = 0; i < count; i++)
            free(wordsArray[i]);
        free(wordsArray);
        return NULL;
    }

    return name;
}

void changeNameOneWord(char* name, const char* word) {
    int len = (int)strlen(word);
    int index = 0;
    for (int i = 0; i < len - 1; i++) {
        name[index++] = toupper(word[i]);
        name[index++] = SEP_CHAR;
    }

    name[index] = toupper(word[len - 1]);
}

void changeName(char* name, int count, char** wordsArray) {
    for (int i = 0; i < count; i++) {
        wordsArray[i][0] = toupper(wordsArray[i][0]);
        strcat(name, wordsArray[i]);
        if (i != count - 1) { //not last
            strcat(name, " ");
            if (count % 2 == 0)
                strcat(name, " ");
        }
    }
}

int getCustomerName(Customer* pCustomer) {
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






//
//
//int getCustomerName(Customer* pCustomer) {
//    char input[MAX_STR_LEN];
//    printf("Please enter your name (e.g., john doe): ");
//    fgets(input, sizeof(input), stdin);
//    // Remove newline character at the end if present
//    input[strcspn(input, "\n")] = '\0';
//
//    // Allocate memory for the formatted name
//    char* formattedName = (char*)calloc(strlen(input), sizeof(char));
//    if (!formattedName)
//    {
//        printf("Memory allocation failed.\n");
//        free(formattedName);
//        return 0;
//    }
//
//    // Convert to CamelCase
//    strcpy(formattedName, input);
//    convertToCamelCase(formattedName);
//    // Replace spaces with underscore
//    replaceSpacesWithUnderscore(formattedName);
//
//    pCustomer->name = formattedName;
//    return 1;
//}
//
//
//
//void convertToCamelCase(char* str) {
//    int i;
//    // Capitalize the first letter of each word
//    for (i = 0; str[i] != '\0'; i++) {
//        // If it's the first character or the previous character is a space
//        if (i == 0 || str[i - 1] == ' ') {
//            str[i] = toupper(str[i]);
//        }
//        else {
//            str[i] = tolower(str[i]);
//        }
//    }
//}
//
//void replaceSpacesWithUnderscore(char* str) {
//    int i;
//    // Replace spaces with underscore
//    for (i = 0; str[i] != '\0'; i++) {
//        if (str[i] == ' ') {
//            str[i] = '_';
//        }
//    }
//}

