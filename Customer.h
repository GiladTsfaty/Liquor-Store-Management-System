#pragma once

#include <stdio.h>



# define VIP_THRESH 1000
# define MAX_STR_LEN 255
#define SEP_CHAR '_'

typedef enum {
    eNew, eRegular, eVip, eNomOfCustomerTypes
} eCustomerType;

static const char* CustomerTypeStr[eNomOfCustomerTypes]
= { "New", "Regular", "Vip" };


typedef struct
{
   // char                  id; //like IATA   
    char*                name;
    double               totalSpent;
    eCustomerType        type;

}Customer;

Customer* returnBlanckCustomer(Customer* pCustomer)  ;

int  initCustomerWithoutName(Customer* pCustomer);
int  printCustomer( const Customer* pCustomer);
int  isSameCustomerName(const Customer* pCustomer1,const Customer* pCustomer2);
void freeCustomer(Customer* pCustomer);

int   getCustomerName(Customer* pCustomer);
char* allocateRightLength(char** wordsArray, int count, int totalLength);
void  changeNameOneWord(char* name, const char* word);
void  changeName(char* name, int count, char** wordsArray);

