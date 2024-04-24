#pragma once

#include <stdio.h>



# define VIP_THRESH 1000

typedef enum {
    eNew, eRegular, eVip, eNomOfCustomerTypes
} eCustomerType;

static const char* CustomerTypeStr[eNomOfCustomerTypes]
= { "New", "Regular", "Vip" };


typedef struct
{
    char*                name;
    double               totalSpent;
    eCustomerType        type;

}Customer;

Customer* returnBlanckCustomer(Customer* pCustomer)  ;
int       initCustomerWithoutName(Customer* pCustomer);
int       printCustomer( const Customer* pCustomer);
int       isSameCustomerName(const Customer* pCustomer1,const Customer* pCustomer2);
void      freeCustomerVal(void* value);
void      freeCustomer(Customer* pCustomer);
int       getCustomerName(Customer* pCustomer);
char*     allocateRightLength(char** wordsArray, int count, int totalLength);
void      changeNameOneWord(char* name, const char* word);
void      changeName(char* name, int count, char** wordsArray);
int       compareCustomersByTotalSpent(const void* a, const void* b);
