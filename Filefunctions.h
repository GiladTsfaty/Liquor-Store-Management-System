#pragma once


#include "Sales.h"
#include "Inventory.h"
#include "GeneralFunctions.h"
#include "BinaryFunctions.h"
#include "Wine.h"
#include "Beer.h"
#include "Whiskey.h"


int	 writeStringToFile(char* str, FILE* fp, const char* msg);
int	 writeCharsToFile(char* arr, int size, FILE* fp, const char* msg);
int	 writeIntToFile(int val, FILE* fp, const char* msg);
int  writeDoubleToFile(double val, FILE* fp, const char* msg);

char* readStringFromFile(FILE* fp, const char* msg);
int	  readCharsFromFile(char* arr, int size, FILE* fp, const char* msg);
int	  readIntFromFile(int* val, FILE* fp, const char* msg);
int   readDoubleFromFile(double* pVal, FILE* fp, const char* msg);


void parseBeerSize(const char* sizeStr, eBeerSize* size);
void parseWhiskeyType(const char* typeStr, eWhiskeyType* type);
void parseWineType(const char* typeStr, eWineType* type);
///inventory text files ///

void  readInventoryFromFile(Inventory* pInventory, const char* filename);//what is the diff
int   initInventoryFromTextFile(Inventory* pInventory, const char* filename);
int   saveInventoryToTextFile(const Inventory* pInventory,  char* filename);


///customer text files ///
int   loadCustomerFromTextFile(Customer* pCustomer, FILE* fp);
int   saveCustomerToFile(Customer* pCustomer, FILE* fp);


int   initCustomerListFromTextFile(Sales* pSales, const char* fileName);// change to FILE*
int   saveCustomerListToTextFile(const Sales* pSales,  char* fileName);




// Functions for loading and saving reservations to/from text files
Reservation*	loadReservationFromFile(Sales* pSales, FILE* file);
void			saveReservationToFile(const Reservation* reservation, FILE* file);


int				loadReservationsArrayFromTextFile(Sales* pSales, const char* filename);// change to FILE*
int				saveReservationsArrayToTextFile(const Sales* pSales,  char* filename);







//int loadReservationsFromTextFile(Sales* pSales, const char* filename);
//int saveReservationsToTextFile(const Sales* pSales, const char* filename);


//int writeAirlineToBFile(FILE* pFile, const Airline* pComp);
//int writePlaneArrToBFile(FILE* pFile, const Plane* pPlaneArr, const int count);
//int writePlaneToBFile(FILE* pFile, const Plane* pPlane);
//int writeFlightArrToBFile(FILE* pFile, Flight** const flightArr, const int count);
//int writeFlightToBFile(FILE* pFile, const Flight* pFlight);
//
//int readAirlineFromBFile(FILE* pFile, Airline* pComp, AirportManager* pManager);
//int readPlaneArrFromBFile(FILE* pFile, Plane* pPlaneArr, const int planeCount);
//int readPlaneFromBFile(FILE* pFile, Plane* pPlane);
//int readFlightArrFromBFile(FILE* pFile, Flight** pFlightArr, const int flightCount, Plane* pPlaneArr, const int planeCount);
//int readFlightFromBFile(FILE* pFile, Flight* pFlight, Plane* pPlaneArr, const int planeCount);
