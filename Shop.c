#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Inventory.h"
#include "Customer.h"
#include "Date.h"
#include "Shop.h"
#include "BinaryFunctions.h"
#include "Filefunctions.h"




void initShop(Shop *pShop, Inventory *pInventory, Sales *pSales, int initialBudget)
{
    printf("---------Init Shop-----------\n");

    pShop->inventory = pInventory;
    pShop->salesDepartment = pSales;
    pShop->netBudget = initialBudget;
}

void initSystemFromFiles(Shop* pShop, Sales* pSales, Inventory* pInventory)
{
    int choice;
    printf("Select the file format to load from:\n");
    printf("1. Text files\n");
    printf("2. Binary files\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            // Load from text files
            if (!initCustomerListFromTextFile(pSales, "customer_list.txt"))
            {
                printf("Failed to load customers from text file.\n");
                return;
            }
            if (!initInventoryFromTextFile(pInventory, "Inventory.txt"))
            {
                printf("Failed to load inventory from text file.\n");
                return;
            }
            if (!loadReservationsArrayFromTextFile(pSales, "reservation_arr.txt"))
            {
                printf("Failed to load reservations from text file.\n");
                return;
            }
            printf("System loaded successfully from text files.\n");
            break;
        case 2:
            // Load from binary files
            if (!readCustomerListFromBFile(pSales, "BinaryCustomer.bin"))
            {
                printf("Failed to load customers from binary file.\n");
                return;
            }
            if (!initInventoryFromBinaryFile(pInventory, "Inventory.bin"))
            {
                printf("Failed to load inventory from binary file.\n");
                return;
            }
            if (!loadReservationsArrayFromBinaryFile(pSales, "BinaryReservation.bin"))
            {
                printf("Failed to load reservations from binary file.\n");
                return;
            }
            printf("System loaded successfully from binary files.\n");
            break;
        default:
            printf("Invalid choice. System not loaded.\n");
            break;
    }

    // Initialize the shop with the loaded inventory and sales
    initShop(pShop, pInventory, pSales, 0);
}

void freeShop(Shop* pShop)
{

    freeSales(pShop->salesDepartment);
    freeInventory(pShop->inventory);

}
