#pragma once


#include "Inventory.h"

# define VIP_THRESH 1000
# define MAX_STR_LEN 255
#define SEP_CHAR '_'

typedef enum {
    eVip, eRegular, eNew, eNomOfCustomerTypes
} eCustomerType;

static const char* CustomerTypeStr[eNomOfCustomerTypes]
= { "Regular", "Vip", "New" };

typedef struct
{
    char* name;
   // int serialNum;
   // int numOfReservations;
   double totalSpent;
    eCustomerType type;

}Customer;

Customer* returnBlanckCustomer(Customer* pCustomer)  ;

int  initCustomerWithoutName(Customer* pCustomer);
int  printCustomer( const Customer* pCustomer);
int  getCustomerName( Customer* pCustomer);
int  isSameCustomerName(const Customer* pCustomer1,const Customer* pCustomer2);
void freeCustomer(Customer* pCustomer);

