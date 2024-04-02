
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileFunctions.h"
#include "General.h"


int	 writeStringToFile(char* str, FILE* fp, const char* msg)
{
    int length = (int)strlen(str);
    length++;
    if (!writeIntToFile(length, fp, msg))
        return 0;

    if (!writeCharsToFile(str, length, fp, msg))
        return 0;


    return 1;
}

int	 writeCharsToFile(char* arr, int size, FILE* fp, const char* msg)
{
    if (fwrite(arr, sizeof(char), size, fp) != size)
    {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;

}

int	 writeIntToFile(int val, FILE* fp, const char* msg)
{
    if (fwrite(&val, sizeof(int), 1, fp) != 1)
    {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;
}

char* readStringFromFile(FILE* fp, const char* msg)
{
    char* str;
    int length;
    if (!readIntFromFile(&length, fp, msg))
        return NULL;
    str = (char*)malloc((length) * sizeof(char));
    if (!str)
    {
        puts(msg);
        fclose(fp);
        return NULL;
    }
    if (fread(str, sizeof(char), length, fp) != length)
    {
        puts(msg);
        fclose(fp);
        return NULL;
    }
    return str;

}

int	 readCharsFromFile(char* arr, int length, FILE* fp, const char* msg)
{
    if (fread(arr, sizeof(char), length, fp) != length)
    {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;
}

int	  readIntFromFile(int* pVal, FILE* fp, const char* msg)
{
    if (fread(pVal, sizeof(int), 1, fp) != 1)
    {
        puts(msg);
        fclose(fp);
        return 0;
    }
    return 1;

}

int writeAirlineToBFile(FILE* pFile, const Airline* pComp)
{
    int len = (int)strlen(pComp->name) + 1;
    if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pComp->name, sizeof(char), len, pFile) != len) return 0;
    if (fwrite(&pComp->planeCount, sizeof(int), 1, pFile) != 1) return 0;
    if (!writePlaneArrToBFile(pFile, pComp->planeArr, pComp->planeCount)) return 0;
    if (fwrite(&pComp->flightCount, sizeof(int), 1, pFile) != 1) return 0;
    if (!writeFlightArrToBFile(pFile, pComp->flightArr, pComp->flightCount)) return 0;
    return 1;
}

int writePlaneArrToBFile(FILE* pFile, const Plane* pPlaneArr, const int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!writePlaneToBFile(pFile, &pPlaneArr[i]))
        {
            fclose(pFile);
            return 0;
        }
    }
    return 1;
}

int writePlaneToBFile(FILE* pFile, const Plane* pPlane)
{
    if (fwrite(&pPlane->serialNum, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pPlane->type, sizeof(ePlaneType), 1, pFile) != 1) return 0;
    return 1;
}

int writeFlightArrToBFile(FILE* pFile, Flight** const flightArr, const int count)
{
    for (int i = 0; i < count; i++)
    {
        if (!writeFlightToBFile(pFile, flightArr[i]))
        {
            fclose(pFile);
            return 0;
        }
    }
    return 1;
}

int writeFlightToBFile(FILE* pFile, const Flight* pFlight)
{
    //int len = strlen(pFlight->sourceCode); // for both source and dest codes

    //if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pFlight->sourceCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;

    //if (fwrite(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(pFlight->destCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;

    if (fwrite(&pFlight->flightPlane.serialNum, sizeof(int), 1, pFile) != 1) return 0;
    if (fwrite(&pFlight->date, sizeof(Date), 1, pFile) != 1) return 0;
    return 1;
}



int readAirlineFromBFile(FILE* pFile, Airline* pComp, AirportManager* pManager)
{
    int len;

    if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    pComp->name = (char*)malloc(len * sizeof(char));
    if (!pComp->name) return 0;
    if (fread(pComp->name, sizeof(char), len, pFile) != len) return 0;

    if (fread(&pComp->planeCount, sizeof(int), 1, pFile) != 1) return 0;

    // Use a temporary pointer for realloc
    Plane* tempPlaneArr = (Plane*)realloc(pComp->planeArr, (pComp->planeCount) * sizeof(Plane));
    if (!tempPlaneArr) {
        free(pComp->name); // Free allocated memory in case of failure
        return 0;
    }
    pComp->planeArr = tempPlaneArr;

    readPlaneArrFromBFile(pFile, pComp->planeArr, pComp->planeCount);

    if (fread(&pComp->flightCount, sizeof(int), 1, pFile) != 1) return 0;

    // Use a temporary pointer for realloc
    Flight** tempFlightArr = (Flight**)realloc(pComp->flightArr, (pComp->flightCount) * sizeof(Flight*));
    if (!tempFlightArr) {
        free(pComp->name);
        free(pComp->planeArr); // Free allocated memory in case of failure
        return 0;
    }
    pComp->flightArr = tempFlightArr;

    readFlightArrFromBFile(pFile, pComp->flightArr, pComp->flightCount, pComp->planeArr, pComp->planeCount);

    return 1;
}


int readPlaneArrFromBFile(FILE* pFile, Plane* planeArr, const int planeCount)
{
    Plane* pPlane = NULL;
    for (int i = 0; i < planeCount; i++)
    {
        pPlane = (Plane*)calloc(1, sizeof(Plane));
        if (!pPlane) return 0;
        if (!readPlaneFromBFile(pFile, pPlane)) return 0;
        planeArr[i] = *pPlane;
    }
    return 1;
}

int readPlaneFromBFile(FILE* pFile, Plane* pPlane)
{
    if (fread(&pPlane->serialNum, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(&pPlane->type, sizeof(ePlaneType), 1, pFile) != 1) return 0;
    return 1;
}

int readFlightArrFromBFile(FILE* pFile, Flight** pFlightArr, const int flightCount, Plane* planeArr, const int planeCount)
{
    Flight* pFlight = NULL;
    for (int i = 0; i < flightCount; i++)
    {
        pFlight = (Flight*)calloc(1, sizeof(Flight));
        if (!pFlight) return 0;
        if (!readFlightFromBFile(pFile, pFlight, planeArr, planeCount)) return 0;
        pFlightArr[i] = pFlight;
    }
    return 1;
}

int readFlightFromBFile(FILE* pFile, Flight* pFlight, Plane* planeArr, const int planeCount)
{
    int len = 0, serialNumber;
    //if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(pFlight->sourceCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;
    pFlight->sourceCode[IATA_LENGTH] = '\0';

    //if (fread(&len, sizeof(int), 1, pFile) != 1) return 0;
    if (fread(pFlight->destCode, sizeof(char), IATA_LENGTH, pFile) != IATA_LENGTH) return 0;
    pFlight->destCode[IATA_LENGTH] = '\0';

    if (fread(&serialNumber, sizeof(int), 1, pFile) != 1) return 0;
    pFlight->flightPlane = *findPlaneBySN(planeArr, planeCount, serialNumber);

    if (fread(&pFlight->date, sizeof(Date), 1, pFile) != 1) return 0;

    return 1;
}